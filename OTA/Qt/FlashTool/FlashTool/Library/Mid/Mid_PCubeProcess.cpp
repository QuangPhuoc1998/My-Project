#include "Mid_PCubeProcess.h"
#include "Mid_ReadFile.h"

Mid_PCubeProcess::Mid_PCubeProcess(QObject *parent) : QThread(parent)
{
    qDebug() << "PCube thread start!";
}

Mid_PCubeProcess::~Mid_PCubeProcess()
{
    qDebug() << "PCube thread stop!";
}

void Mid_PCubeProcess::_PCubeProcess()
{
    uint8_t ubCheckSum = 0;

    if(PCUBE_RECEIVE_DONE_FLAG == C_ON)
    {
        /*---*/
        ubCheckSum = Ex_CheckSum(g_aubRxRealData, g_ubRxRealLen-2);
        if(ubCheckSum == g_aubRxRealData[g_ubRxRealLen-2])
        {
            _PCubeProcessData();
            PCUBE_CHECKSUM_OK = C_ON;
            PCUBE_CHECKSUM_ERROR = C_OFF;;
        }
        else
        {
            PCUBE_CHECKSUM_OK = C_OFF;
            PCUBE_CHECKSUM_ERROR = C_ON;
        }
        /*---*/
        PCUBE_RECEIVE_DONE_FLAG = C_OFF;
    }
    else if(APP_PROGRAM_REQUEST == C_ON)
    {
        _PCubeProgramData();
    }
}

void Mid_PCubeProcess::_PCubeProcessData()
{
    uint8_t ubCMDID = g_aubRxRealData[PCUBE_CMD_INDEX];
    switch (ubCMDID)
    {
        case PCUBE_CMD_READ:
            _PCubeProcessRead();
            break;
        case PCUBE_CMD_READ_RESPONSE:
            _PCubeProcessReadResponse();
            break;
        case PCUBE_CMD_WRITE:
            _PCubeProcessWrite();
            break;
        case PCUBE_CMD_WRITE_RESPONSE:
            _PCubeProcessWriteResponse();
            break;
        default:
            break;
    }
}

void Mid_PCubeProcess::_PCubeProcessRead()
{

}

void Mid_PCubeProcess::_PCubeProcessReadResponse()
{

}

void Mid_PCubeProcess::_PCubeProcessWrite()
{

}

void Mid_PCubeProcess::_PCubeProcessWriteResponse()
{
    uint8_t temp = 0;
    for(int i = PCUBE_ATTR_START_INDEX ; i < (g_aubRxRealData[PCUBE_ATTR_LEN_INDEX] + 5) ; i += g_aubRxRealData[i+1] + 2)
    {
        temp = g_aubRxRealData[i];
        switch (temp)
        {
            case PCUBE_ATTR_ERASE:
                APP_PROGRAM_STEP1_ERASE_DONE = C_ON;
                APP_PROGRAM_STEP1_ERASE = C_OFF;
                emit qml_UpdateMonitor("=> Erase done");
                qDebug() << "Erase done";
                break;
            case PCUBE_ATTR_PROGRAM:
                if(g_aubRxRealData[i+2] == PCUBE_ACK)
                {
                    APP_PROGRAM_DONE = C_ON;
                }
                break;
            case PCUBE_ATTR_AP_RUN:
                emit qml_UpdateMonitor("=> Reset after 2s");
                SERIALPORT_CHECK_CONNECT = C_OFF;
                break;
            case PCUBE_ATTR_GOTO_BL:
                break;
            default:
                break;
        }
    }
}

void Mid_PCubeProcess::_PCubeProgramData()
{
    if(APP_PROGRAM_STEP1_ERASE == C_ON)
    {
        _PCubeEraseData();
    }
    else if(APP_PROGRAM_STEP1_ERASE_DONE == C_ON)
    {
        _PCubeFlashData();
    }
}

void Mid_PCubeProcess::_PCubeEraseData()
{
    if(APP_ERASE_FIRST_INIT == C_ON)
    {
        emit qml_UpdateMonitor("Erase start:");
        g_aubTxData[PCUBE_STX_INDEX] = PCUBE_STX_DATA;
        g_aubTxData[PCUBE_LEN_INDEX] = 9;
        g_aubTxData[PCUBE_CLU_INDEX] = 0x02;

        g_aubTxData[PCUBE_CMD_INDEX]        = PCUBE_CMD_WRITE;
        g_aubTxData[PCUBE_ATTR_LEN_INDEX]   = 4;
        g_aubTxData[PCUBE_ATTR_START_INDEX] = PCUBE_ATTR_ERASE;
        g_aubTxData[PCUBE_ATTR_START_INDEX+1] = 2;
        g_aubTxData[PCUBE_ATTR_START_INDEX+2] = 1;
        g_aubTxData[PCUBE_ATTR_START_INDEX+3] = _PCubeCalculateSector(Mid_ProcessFileCalcLen());

        g_aubTxData[PCUBE_ATTR_START_INDEX+4] = Ex_CheckSum(g_aubTxData, g_aubTxData[PCUBE_LEN_INDEX]);
        g_aubTxData[g_aubTxData[PCUBE_LEN_INDEX]+2-1] = PCUBE_ETX_DATA;

        g_ubTxRealLen = g_aubTxData[PCUBE_LEN_INDEX]+2;
        Ex_CopyArray(g_aubTxData, g_aubTxRealData, g_ubTxRealLen);

        emit _PCubeSendData();

        APP_ERASE_FIRST_INIT = C_OFF;
    }
    if(APP_PROGRAM_TIMEOUT_FLAG == C_ON)
    {
        emit qml_UpdateMonitor("=> Time out");
        APP_PROGRAM_STEP2_FLASH = C_OFF;
        APP_PROGRAM_REQUEST = C_OFF;
        APP_PROGRAM_FIRST_INIT = C_OFF;
        APP_ERASE_FIRST_INIT = C_OFF;
    }
}

void Mid_PCubeProcess::_PCubeFlashData()
{
    static uint8_t index = 0;
    static uint32_t bytes_remaining=0;
    static uint32_t t_len_of_file=0;
    static uint32_t bytes_so_far_sent = 0,len_to_read=0;
    static uint32_t base_mem_address = ADDRESS_SECTOR_1;
    static uint8_t probar = 0;

    if(APP_PROGRAM_FIRST_INIT == C_ON)
    {
        t_len_of_file = Mid_ProcessFileCalcLen();
        Mid_ProcessFileOpen();
        bytes_remaining = t_len_of_file - bytes_so_far_sent;
        probar = (t_len_of_file / 128) + 1;

        APP_PROGRAM_FIRST_INIT = C_OFF;
        emit qml_UpdateMonitor("Start flash");
    }


     if(APP_PROGRAM_TIMEOUT_FLAG == C_OFF && APP_PROGRAM_DONE == C_ON && bytes_remaining != 0)
     {
         if(bytes_remaining >= 128)
         {
             len_to_read = 128;
         }else
         {
             len_to_read = bytes_remaining;
         }

         /*--- Send data ---*/

         g_aubTxData[PCUBE_STX_INDEX] = PCUBE_STX_DATA;
         g_aubTxData[PCUBE_LEN_INDEX] = 12 + len_to_read;//
         g_aubTxData[PCUBE_CLU_INDEX] = 0x02;

         g_aubTxData[PCUBE_CMD_INDEX]        = PCUBE_CMD_WRITE;
         g_aubTxData[PCUBE_ATTR_LEN_INDEX]   = 6 + len_to_read; //
         g_aubTxData[PCUBE_ATTR_START_INDEX] = PCUBE_ATTR_PROGRAM;

         g_aubTxData[PCUBE_ATTR_START_INDEX+1] = len_to_read + 5;

         g_aubTxData[PCUBE_ATTR_START_INDEX+2] = Mid_ExWordtoByte(base_mem_address,1);
         g_aubTxData[PCUBE_ATTR_START_INDEX+3] = Mid_ExWordtoByte(base_mem_address,2);
         g_aubTxData[PCUBE_ATTR_START_INDEX+4] = Mid_ExWordtoByte(base_mem_address,3);
         g_aubTxData[PCUBE_ATTR_START_INDEX+5] = Mid_ExWordtoByte(base_mem_address,4);

         g_aubTxData[PCUBE_ATTR_START_INDEX+6] = len_to_read;

         Mid_ProcessFileRead(&g_aubTxData[PCUBE_ATTR_START_INDEX+7], len_to_read);

         g_aubTxData[g_aubTxData[PCUBE_LEN_INDEX]+2-2] = Ex_CheckSum(g_aubTxData, g_aubTxData[PCUBE_LEN_INDEX]);
         g_aubTxData[g_aubTxData[PCUBE_LEN_INDEX]+2-1] = PCUBE_ETX_DATA;

         g_ubTxRealLen = g_aubTxData[PCUBE_LEN_INDEX]+2;
         Ex_CopyArray(g_aubTxData, g_aubTxRealData, g_ubTxRealLen);

         emit _PCubeSendData();
         index++;
         if((index * 100 / probar) % 10 == 0)
         {
             emit qml_UpdateMonitor(QString::number(index * 100 / probar)+ "%");
         }

         /*---*/
         base_mem_address+=len_to_read;
         bytes_so_far_sent+=len_to_read;
         bytes_remaining = t_len_of_file - bytes_so_far_sent;

         APP_PROGRAM_DONE = C_OFF;
     }
     if(bytes_remaining == 0 && APP_PROGRAM_TIMEOUT_FLAG == C_OFF && APP_PROGRAM_DONE == C_ON)
     {
         emit qml_UpdateMonitor("=> Flash done");
         APP_PROGRAM_STEP2_FLASH = C_OFF;
         APP_PROGRAM_REQUEST = C_OFF;
         APP_PROGRAM_FIRST_INIT = C_OFF;
         Mid_ProcessFileClose();

         index = 0;
         bytes_remaining=0;
         t_len_of_file=0;
         bytes_so_far_sent = 0,len_to_read=0;
         base_mem_address = ADDRESS_SECTOR_1;
         probar = 0;
     }
     if(APP_PROGRAM_TIMEOUT_FLAG == C_ON)
     {
        emit qml_UpdateMonitor("=> Time out");
        APP_PROGRAM_STEP2_FLASH = C_OFF;
        APP_PROGRAM_REQUEST = C_OFF;
        APP_PROGRAM_FIRST_INIT = C_OFF;
        Mid_ProcessFileClose();

        index = 0;
        bytes_remaining=0;
        t_len_of_file=0;
        bytes_so_far_sent = 0,len_to_read=0;
        base_mem_address = ADDRESS_SECTOR_1;
        probar = 0;
     }
}

uint8_t Mid_PCubeProcess::_PCubeCalculateSector(uint32_t FileSize)
{
    uint8_t ubNumberOfSector = 0;
    if(FileSize < 32000)
    {
        ubNumberOfSector = 1;
    }
    else if(FileSize < 64000)
    {
        ubNumberOfSector = 2;
    }
    else if(FileSize < 96000)
    {
        ubNumberOfSector = 3;
    }
    else if(FileSize < 224000)
    {
        ubNumberOfSector = 4;
    }
    else if(FileSize < 480000)
    {
        ubNumberOfSector = 5;
    }
    else if(FileSize < 736000)
    {
        ubNumberOfSector = 6;
    }
    else if(FileSize < 992000)
    {
        ubNumberOfSector = 7;
    }
    else if(FileSize < 1248000)
    {
        ubNumberOfSector = 8;
    }
    else if(FileSize < 1504000)
    {
        ubNumberOfSector = 9;
    }
    else if(FileSize < 1760000)
    {
        ubNumberOfSector = 10;
    }
    else if(FileSize < 2016000)
    {
        ubNumberOfSector = 11;
    }
    return ubNumberOfSector;
}

void Mid_PCubeProcess::run()
{
    while (PCUBE_THREAD_FLAG_STOP)
    {
        _PCubeProcess();
    }
}

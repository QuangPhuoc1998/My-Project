#include "op_interruptmanager.h"
#include <QMutex>
#include "Library/Mid/Mid_PCubeProcess.h"
#include "Library/Mid/Mid_ReadFile.h"
#include <QFileDialog>

Op_InterruptManager::Op_InterruptManager(QObject *parent) : QObject(parent)
{
    SERIALPORT_IS_RUNNING = C_OFF;
    SERIALPROT_IS_SELECT  = C_OFF;

    PCUBE_THREAD_FLAG_STOP = C_ON;

    Mid_PCubeProcessThread = new Mid_PCubeProcess(this);

    connect(Mid_PCubeProcessThread,&Mid_PCubeProcess::_PCubeSendData,this,&Op_InterruptManager::ser_SendData);
    connect(Mid_PCubeProcessThread,&Mid_PCubeProcess::qml_UpdateMonitor,this,&Op_InterruptManager::qml_UpdateMonitor);

    Mid_PCubeProcessThread->start();

    timer10ms = new QTimer(this);
    timer50ms = new QTimer(this);
    timer100ms = new QTimer(this);
    timer1000ms = new QTimer(this);

    connect(timer10ms, &QTimer::timeout, this, &Op_InterruptManager::Timer10msEvent);
    connect(timer50ms, &QTimer::timeout, this, &Op_InterruptManager::Timer50msEvent);
    connect(timer100ms, &QTimer::timeout, this, &Op_InterruptManager::Timer100msEvent);
    connect(timer1000ms, &QTimer::timeout, this, &Op_InterruptManager::Timer1000msEvent);

    timer10ms->start(10);
    timer50ms->start(50);
    timer100ms->start(100);
    timer1000ms->start(1000);
}

Op_InterruptManager::~Op_InterruptManager()
{
    PCUBE_THREAD_FLAG_STOP = C_OFF;
    Mid_PCubeProcessThread->exit();
    timer10ms->stop();
    timer50ms->stop();
    timer100ms->stop();
    timer1000ms->stop();
}

void Op_InterruptManager::btn_ConnectOnClick()
{
    qDebug() << "Connect click";
    qml_UpdateMonitor("Connect " + ComPortName);
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        ser_DisconncetComPort();
    }
    else
    {
        ser_ConnectComPort();
    }
}

void Op_InterruptManager::btn_ServiceOnClick()
{
    qDebug() << "Service click";
}

void Op_InterruptManager::btn_RefeshOnClick()
{
    qDebug() << "Scan click";
    qml_UpdateMonitor("Scan COM");
    emit cb_ClearComPort();
    /*--- Update serial port ---*/
    foreach (const QSerialPortInfo &ThisPort, QSerialPortInfo::availablePorts())
    {
        emit cb_UpdateComPort(ThisPort.portName());
    }
}

void Op_InterruptManager::btn_OpenFileOnClick(QString FileName)
{
    if(FILE_IS_CHOOSE == C_OFF)
    {
        FILE_IS_CHOOSE = C_ON;
    }
    Mid_ProcessSetFile(FileName);
    qml_UpdateMonitor("=> " + FileName);
    qml_UpdateMonitor("=> Size: " + QString::number(Mid_ProcessFileCalcLen()) + " Byte");

    qDebug() << FileName;
    qDebug() << "=> Size: " << Mid_ProcessFileCalcLen();
}

void Op_InterruptManager::btn_FlashOnClick()
{
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        if(FILE_IS_CHOOSE == C_OFF)
        {
            qml_UpdateMonitor("Select file to flash");
        }
        else
        {
            APP_PROGRAM_REQUEST = C_ON;
            APP_PROGRAM_STEP1_ERASE = C_ON;
            APP_PROGRAM_STEP1_ERASE_DONE = C_OFF;
            APP_PROGRAM_STEP2_FLASH = C_ON;
            APP_PROGRAM_STEP2_FLASH_DONE = C_OFF;
            APP_PROGRAM_FIRST_INIT = C_ON;
            APP_ERASE_FIRST_INIT = C_ON;
            APP_PROGRAM_DONE = C_ON;
            APP_PROGRAM_TIMEOUT_FLAG = C_OFF;
        }
    }
    else
    {
        qDebug() << "Open comport first";
        qml_UpdateMonitor("Select COM first");
    }
}

void Op_InterruptManager::btn_EraseOnClick()
{

}

void Op_InterruptManager::btn_ResetOnClick()
{
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        qml_UpdateMonitor("Reset MCU");
        SERIALPORT_CHECK_CONNECT = C_ON;
        g_aubTxData[PCUBE_STX_INDEX] = PCUBE_STX_DATA;
        g_aubTxData[PCUBE_LEN_INDEX] = 8;
        g_aubTxData[PCUBE_CLU_INDEX] = 0x02;

        g_aubTxData[PCUBE_CMD_INDEX]        = PCUBE_CMD_WRITE;
        g_aubTxData[PCUBE_ATTR_LEN_INDEX]   = 3;
        g_aubTxData[PCUBE_ATTR_START_INDEX] = PCUBE_ATTR_AP_RUN;
        g_aubTxData[PCUBE_ATTR_START_INDEX+1] = 0;
        g_aubTxData[PCUBE_ATTR_START_INDEX+2] = 1;

        g_aubTxData[PCUBE_ATTR_START_INDEX+3] = Ex_CheckSum(g_aubTxData, g_aubTxData[PCUBE_LEN_INDEX]);
        g_aubTxData[g_aubTxData[PCUBE_LEN_INDEX]+2-1] = PCUBE_ETX_DATA;

        g_ubTxRealLen = g_aubTxData[PCUBE_LEN_INDEX]+2;
        Ex_CopyArray(g_aubTxData, g_aubTxRealData, g_ubTxRealLen);

        ser_SendData();
    }
    else
    {
        qDebug() << "Open comport first";
        qml_UpdateMonitor("Select COM first");
    }
}

void Op_InterruptManager::btn_CheckOnClick()
{

}

void Op_InterruptManager::ser_ConnectComPort()
{
    if(SERIALPROT_IS_SELECT != C_ON)
    {
        qDebug() << "Select comport";
        qml_UpdateMonitor("Select COM first");
    }
    else if(SERIALPORT_IS_RUNNING == C_OFF)
    {
        SerialPort = new QSerialPort();
        SerialPort->setPortName(ComPortName);
        SerialPort->setBaudRate(QSerialPort::Baud115200);
        SerialPort->setDataBits(QSerialPort::Data8);
        SerialPort->setParity(QSerialPort::NoParity);
        SerialPort->setStopBits(QSerialPort::OneStop);

        SerialPort->open((QIODevice::ReadWrite));

        connect(SerialPort,SIGNAL(readyRead()),this,SLOT(ser_DataReceive()));

        SERIALPORT_IS_RUNNING = C_ON;
        emit btn_UpdateBtnConnect("Disconnect");
    }
    else
    {
        qDebug() << "Comport already";
        qml_UpdateMonitor("COM already");
    }
}

void Op_InterruptManager::ser_DisconncetComPort()
{
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        SerialPort->close();
        SERIALPORT_IS_RUNNING = C_OFF;
        emit btn_UpdateBtnConnect("Connect");
    }
    else
    {
        qDebug() << "Comport not open";
        qml_UpdateMonitor("COM not open");
    }
}

void Op_InterruptManager::ser_SetComPort(QString PortName)
{
    SERIALPROT_IS_SELECT = C_ON;
    ComPortName = PortName;
    qDebug() << PortName;
}

void Op_InterruptManager::ser_SetBaudRate(QString BaudRateIndex)
{
    qDebug() << BaudRateIndex;
}

void Op_InterruptManager::ser_DataReceive()
{
    uint8_t ub_ETXIndex = 0;
    QByteArray data = SerialPort->readAll();

    for(uint8_t i = 0 ; i < data.length(); i++)
    {
        if(g_ubRxIndexCount < PCUBE_HEADER_COUNT)
        {
            g_aubRxData[g_ubRxIndexCount] = data[i];
            if(g_ubRxIndexCount == PCUBE_STX_INDEX)
            {
                if(g_aubRxData[g_ubRxIndexCount] != PCUBE_STX_DATA)
                {
                    g_ubRxIndexCount = 0;
                }
                else
                {
                    g_ubRxIndexCount++;
                }
            }
            else
            {
                g_ubRxIndexCount++;
            }
        }
        else if(g_ubRxIndexCount < (g_aubRxData[PCUBE_LEN_INDEX] + 2))
        {
            g_aubRxData[g_ubRxIndexCount] = data[i];
            ub_ETXIndex = g_aubRxData[PCUBE_LEN_INDEX] + 2 - 1;
            if(g_ubRxIndexCount == ub_ETXIndex)
            {
                if(g_aubRxData[g_ubRxIndexCount] == PCUBE_ETX_DATA)
                {
                    // pass
                    g_ubRxRealLen = g_ubRxIndexCount+1;
                    Ex_CopyArray(g_aubRxData, g_aubRxRealData, g_ubRxRealLen);

                    for(uint8_t i = 0 ; i < g_ubRxRealLen ; i++)
                    {
                        qDebug() << "Hex num: " <<Qt::hex << g_aubRxRealData[i];
                    }
                    PCUBE_RECEIVE_DONE_FLAG = C_ON;
                    //
                }
                g_ubRxIndexCount = 0;
            }
            else
            {
                g_ubRxIndexCount++;
            }
        }
        else
        {
            g_ubRxIndexCount = 0;
        }
    }
}

void Op_InterruptManager::Timer10msEvent()
{

}

void Op_InterruptManager::Timer50msEvent()
{

}

void Op_InterruptManager::Timer100msEvent()
{

}

void Op_InterruptManager::Timer1000msEvent()
{
    static uint8_t ubProgramWatchDogCnt = 0;
    static uint8_t ubConnectWatchDogCnt = 0;
    if(APP_PROGRAM_REQUEST == C_ON)
    {
        ubProgramWatchDogCnt++;
        if(ubProgramWatchDogCnt >= TIME_5S_BY_1S)
        {
            APP_PROGRAM_TIMEOUT_FLAG = C_ON;
        }
    }
    else
    {
        ubProgramWatchDogCnt = 0;
    }

    if(SERIALPORT_CHECK_CONNECT == C_ON)
    {
        ubConnectWatchDogCnt++;
        if(ubConnectWatchDogCnt >= TIME_5S_BY_1S)
        {
            qml_UpdateMonitor("=> Connect timeout");
            SERIALPORT_CHECK_CONNECT = C_OFF;
        }
    }
}

void Op_InterruptManager::ser_SendData()
{
    if(SERIALPORT_IS_RUNNING == C_ON)
    {
        SerialPort->write((char*)g_aubTxRealData, g_ubTxRealLen);
    }
    else
    {
        qDebug() << "Open comport first";
    }
}

void Op_InterruptManager::qml_UpdateMonitor(QString NewData)
{
    emit txt_UpdateMonitor(NewData);
}

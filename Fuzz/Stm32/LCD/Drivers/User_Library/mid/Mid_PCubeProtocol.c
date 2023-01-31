#include "Mid_PCubeProtocol.h"

void _PCubeProcessData(void);
void _PCubeProcessWrite(void);
void _PCubeProcessWriteResponse(void);
void _PCubeProcessRead(void);
void _PCubeProcessReadResponse(void);

void _PCubeConfigData(void);
uint8_t _PCubePickAttrID(void);
uint8_t _PCubeSetAttrData(uint8_t ubAttrNumber);

void Mid_PCubeProcess(void)
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
	else if(PCUBE_RESPONSE_START == C_ON)
	{
		_PCubeConfigData();
		PCUBE_RESPONSE_START = C_OFF;
	}
}

void _PCubeProcessData(void)
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
void _PCubeProcessWrite(void)
{
	uint8_t temp = 0;
	for(uint32_t i = PCUBE_ATTR_START_INDEX ; i < (g_aubRxRealData[PCUBE_ATTR_LEN_INDEX] + 5) ; i += g_aubRxRealData[i+1] + 2)
	{
		temp = g_aubRxRealData[i];
		switch (temp)
		{
			case PCUBE_ATTR_ERASE:
				sDataToErase.ubSectorNumber = g_aubRxRealData[i+2];
				sDataToErase.ubNumberOfSector = g_aubRxRealData[i+3];
			
				FLASH_ERASE_REQUEST = C_ON;
				FLASH_ERASE_SECTOR = C_ON;
				break;
			case PCUBE_ATTR_PROGRAM:
				sDataToWrite.uwMemAddress = *((uint32_t *) ( &g_aubRxRealData[i+2]));
				sDataToWrite.uwLen = g_aubRxRealData[i+6];
			  sDataToWrite.pData = &g_aubRxRealData[i+7];
			
			  FLASH_WRITE_REQUEST = C_ON;
				FLASH_WRITE_PROGRAM = C_ON;
				break;
			case PCUBE_ATTR_AP_RUN:
				OP_RESET_FLAG = C_ON;
				RESET_REQUEST = C_ON;
				PCUBE_RESPONSE_START = C_ON;
				g_ubResetCnt = TIME_2S_BY_1S;
				break;
			case PCUBE_ATTR_GOTO_BL:
				break;
			default:
				break;
		}
	}
}
void _PCubeProcessWriteResponse(void)
{
	
}
void _PCubeProcessRead(void)
{
	
}
void _PCubeProcessReadResponse(void)
{
	
}

void _PCubeConfigData(void)
{
	uint8_t ubAttributeNumber = 0;
	uint8_t ubAttributeLen = 0;
	
	ubAttributeNumber = _PCubePickAttrID();
	ubAttributeLen = _PCubeSetAttrData(ubAttributeNumber);
	
	g_aubTxData[PCUBE_STX_INDEX] = PCUBE_STX_DATA;
	g_aubTxData[PCUBE_LEN_INDEX] = (ubAttributeLen - PCUBE_ATTR_START_INDEX) + PCUBE_HEADER_LEN + PCUEB_ETX_LEN - 2;
	g_aubTxData[PCUBE_CLU_INDEX] = PCUBE_CLU_DEVICE;

	g_aubTxData[PCUBE_ATTR_LEN_INDEX] = ubAttributeLen-PCUBE_ATTR_START_INDEX;
	
	g_aubTxData[g_aubTxData[PCUBE_LEN_INDEX]+2-2] = Ex_CheckSum(g_aubTxData, g_aubTxData[PCUBE_LEN_INDEX]+2-2);
	g_aubTxData[g_aubTxData[PCUBE_LEN_INDEX]+2-1] = PCUBE_ETX_DATA;
	
	g_ubTxRealLen = g_aubTxData[PCUBE_LEN_INDEX]+2;
	Ex_CopyArray(g_aubTxData, g_aubTxRealData, g_ubTxRealLen);
	
	PCUBE_WRITE_START = C_ON;
}
uint8_t _PCubePickAttrID(void)
{
	uint8_t ubAttributeNumber = 0;
	if(FLASH_WRITE_REQUEST == C_ON)
	{
		g_aubAttrList[ubAttributeNumber++] = PCUBE_ATTR_PROGRAM;
		FLASH_WRITE_REQUEST = C_OFF;
	}
	if(FLASH_ERASE_REQUEST == C_ON)
	{
		g_aubAttrList[ubAttributeNumber++] = PCUBE_ATTR_ERASE;
		FLASH_ERASE_REQUEST = C_OFF;
	}
	if(RESET_REQUEST == C_ON)
	{
		g_aubAttrList[ubAttributeNumber++] = PCUBE_ATTR_AP_RUN;
		RESET_REQUEST = C_OFF;
	}
	return ubAttributeNumber;
}

uint8_t _PCubeSetAttrData(uint8_t ubAttrNumber)
{
	uint8_t ubAttrStart = PCUBE_ATTR_START_INDEX;
	uint8_t ubCMDID = g_aubRxRealData[PCUBE_CMD_INDEX];
	switch (ubCMDID)
	{
		case PCUBE_CMD_READ:
			g_aubTxData[PCUBE_CMD_INDEX] = PCUBE_CMD_READ_RESPONSE;
			for(uint8_t i = 0 ; i < ubAttrNumber;i++)
			{
				
			}
			break;
		case PCUBE_CMD_READ_RESPONSE:
			for(uint8_t i = 0 ; i < ubAttrNumber;i++)
			{
				
			}
			break;
		case PCUBE_CMD_WRITE:
			g_aubTxData[PCUBE_CMD_INDEX] = PCUBE_CMD_WRITE_RESPONSE;
			for(uint8_t i = 0 ; i < ubAttrNumber;i++)
			{
				if(g_aubAttrList[i] == PCUBE_ATTR_PROGRAM)
				{
					g_aubTxData[ubAttrStart++] = PCUBE_ATTR_PROGRAM;
					g_aubTxData[ubAttrStart++] = 1;
					g_aubTxData[ubAttrStart++] = PCUBE_ACK;
				}
				else if(g_aubAttrList[i] == PCUBE_ATTR_ERASE)
				{
					g_aubTxData[ubAttrStart++] = PCUBE_ATTR_ERASE;
					g_aubTxData[ubAttrStart++] = 1;
					g_aubTxData[ubAttrStart++] = PCUBE_ACK;
				}
				else if(g_aubAttrList[i] == PCUBE_ATTR_AP_RUN)
				{
					g_aubTxData[ubAttrStart++] = PCUBE_ATTR_AP_RUN;
					g_aubTxData[ubAttrStart++] = 1;
					g_aubTxData[ubAttrStart++] = PCUBE_ACK;
				}
			}
			break;
		case PCUBE_CMD_WRITE_RESPONSE:
			for(uint8_t i = 0 ; i < ubAttrNumber;i++)
			{
				
			}
			break;
		default:
			break;
	}
	return ubAttrStart;
}

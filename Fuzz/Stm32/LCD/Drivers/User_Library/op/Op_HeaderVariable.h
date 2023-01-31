#ifndef _OP_HEADER_VARIABLE_H_
#define _OP_HEADER_VARIABLE_H_

#include "main.h"
#include "Op_HeaderDefine.h"

#ifndef GLOBAL_DEFINE
#define HEADER_VARIABLE extern
#else
#define HEADER_VARIABLE
#endif

typedef struct
{
	uint8_t LayOutIndex;
	uint8_t Consent;
	uint8_t DotNavi;
	float ReverbTime;
	float ReverbWet;
	float ChorusOffset;
	float ChorusDepth;
	float DelayTime;
	uint8_t Operation;
} LCD_Handler_t;

/*--- Variable for PCube ---*/
HEADER_VARIABLE uint8_t g_ubRxDataBuffer;
HEADER_VARIABLE uint8_t g_aubRxData[MAX_DATA_LEN_UART];
HEADER_VARIABLE uint8_t g_aubRxRealData[MAX_DATA_LEN_UART];
HEADER_VARIABLE uint8_t g_aubTxData[MAX_DATA_LEN_UART];
HEADER_VARIABLE uint8_t g_aubTxRealData[MAX_DATA_LEN_UART];
HEADER_VARIABLE uint8_t g_aubAttrList[MAX_ATTR_LEN];
HEADER_VARIABLE uint8_t g_ubRxIndexCount; 
HEADER_VARIABLE uint8_t g_ubRxRealLen;
HEADER_VARIABLE uint8_t g_ubTxRealLen;
HEADER_VARIABLE uint8_t g_ubRxWatchDogCnt;
/*--- Variable for Flash ---*/
HEADER_VARIABLE FlashWriteControl_t sDataToWrite;
HEADER_VARIABLE FlashEraseControl_t sDataToErase;
/*--- Variable for Operation ---*/
HEADER_VARIABLE uint8_t g_ubResetCnt;
HEADER_VARIABLE uint8_t g_ubErrorType;
HEADER_VARIABLE uint8_t ubProgramWatchDogCnt;
/*--- Variable for SD card ---*/
HEADER_VARIABLE uint8_t * g_pubFileName[MAX_BIN_FILE];
HEADER_VARIABLE uint8_t g_ubNumberOfFiles;
HEADER_VARIABLE int8_t g_ubFileIndex;
/*--- Variable for LCD ---*/
HEADER_VARIABLE LCD_Handler_t g_tLcdStatus;
HEADER_VARIABLE LCD_Handler_t g_tLcdPreStatus;
/*--- Variable for bootloader ---*/
HEADER_VARIABLE uint8_t g_aubDataToWrite[128];
HEADER_VARIABLE uint8_t g_aubFileName[32];
/*--- Variable for Key ---*/
HEADER_VARIABLE uint8_t g_ubKeyOffCount;
HEADER_VARIABLE uint32_t g_ulKeyInValue;
HEADER_VARIABLE uint8_t g_ubKeyPositionValue;
HEADER_VARIABLE uint16_t g_uwKeyContinousCount;
HEADER_VARIABLE uint8_t g_ubUpDownMoveValue;
/*--- Variable for effect ---*/
HEADER_VARIABLE biquad * bq;
/*--- Variable for audio ---*/
HEADER_VARIABLE uint16_t g_uwSetFreLowPass;
HEADER_VARIABLE float g_uwSetGainLowPass;
HEADER_VARIABLE float g_uwSetQLowPass;
HEADER_VARIABLE FilterConfigType_t g_ubConfigFilter;
HEADER_VARIABLE float g_wlSetWet;
HEADER_VARIABLE float g_wlSetDelayTime;
HEADER_VARIABLE ReverbConfigType_t g_ubConfigReverb;
#endif // _OP_HEADER_VARIABLE_H_

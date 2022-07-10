#ifndef _OP_HEADER_VARIABLE_H_
#define _OP_HEADER_VARIABLE_H_

#include <iostream>
#include "Op_HeaderDefine.h"

#ifndef GLOBAL_DEFINE
#define HEAER_VARIABLE extern
#else
#define HEAER_VARIABLE
#endif

/*--- Variable for PCube ---*/
HEAER_VARIABLE uint8_t g_ubRxDataBuffer;
HEAER_VARIABLE uint8_t g_aubRxData[MAX_DATA_LEN_UART];
HEAER_VARIABLE uint8_t g_aubRxRealData[MAX_DATA_LEN_UART];
HEAER_VARIABLE uint8_t g_aubTxData[MAX_DATA_LEN_UART];
HEAER_VARIABLE uint8_t g_aubTxRealData[MAX_DATA_LEN_UART];
HEAER_VARIABLE uint8_t g_aubAttrList[MAX_ATTR_LEN];
HEAER_VARIABLE uint8_t g_ubRxIndexCount;
HEAER_VARIABLE uint8_t g_ubRxRealLen;
HEAER_VARIABLE uint8_t g_ubTxRealLen;
HEAER_VARIABLE uint8_t g_ubRxWatchDogCnt;
/*--- Variable for Flash ---*/
HEAER_VARIABLE FlashWriteControl_t sDataToWrite;
HEAER_VARIABLE FlashEraseControl_t sDataToErase;
/*--- Variable for Operation ---*/
HEAER_VARIABLE uint8_t g_ubResetCnt;
HEAER_VARIABLE uint8_t ubProgramWatchDogCnt;
#endif // _OP_HEADER_VARIABLE_H_

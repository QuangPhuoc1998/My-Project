#ifndef _OP_HEADER_FUNCTION_H_
#define _OP_HEADER_FUNCTION_H_

#include "main.h"

void Ex_CopyArray(uint8_t * pSource, uint8_t * pSink, uint32_t uwlen);
uint8_t Ex_CheckSum(uint8_t * pSource, uint8_t ublen);
uint8_t Mid_ExWordtoByte(uint32_t addr, uint8_t index);
uint8_t CalculateSector(uint32_t FileSize);
#endif // _OP_HEADER_FUNCTION_H_

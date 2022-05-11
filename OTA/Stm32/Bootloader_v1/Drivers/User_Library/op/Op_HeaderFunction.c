#include "Op_HeaderFunction.h"

void Ex_CopyArray(uint8_t * pSource, uint8_t * pSink, uint32_t uwlen)
{
	for(uint32_t i = 0 ; i < uwlen ; i++)
	{
		pSink[i] = pSource[i];
		pSource[i] = 0;
	}
}
uint8_t Ex_CheckSum(uint8_t * pSource, uint8_t ublen)
{
	uint8_t ubCheckSum = 0;
	for(uint8_t i = 0 ; i < ublen ; i++)
	{
		ubCheckSum ^= pSource[i];
	}
	return ubCheckSum;
}

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
uint8_t Mid_ExWordtoByte(uint32_t addr, uint8_t index)
{
      uint8_t value = (addr >> ( 8 * ( index -1)) & 0x000000FF );
      return value;
}
uint8_t CalculateSector(uint32_t FileSize)
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

#ifndef _OP_HEADER_DEFINE_H_
#define _OP_HEADER_DEFINE_H_

#include "main.h"

#define C_ON 	(1)
#define C_OFF (0)

#define MAX_DATA_LEN_UART 256
#define MAX_ATTR_LEN			16

#define TIME_10MS_BY_1MS  (10)
#define TIME_2S_BY_1S 		(2)

#define STM32F769_NUM_OF_SECTOR (8)

#define ERASE_FULL (0xFF)

typedef struct
{
	uint8_t * pData;
	uint32_t uwMemAddress;
	uint32_t uwLen;
} FlashWriteControl_t;

typedef struct
{
	uint8_t ubSectorNumber;
	uint8_t ubNumberOfSector;
} FlashEraseControl_t;
typedef enum
{
	NO_ERROR,
	INVALID_SECTOR
} ERROR_LIST;
#endif // _OP_HEADER_DEFINE_H_

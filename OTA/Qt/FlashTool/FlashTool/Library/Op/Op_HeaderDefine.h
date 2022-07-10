#ifndef _OP_HEADER_DEFINE_H_
#define _OP_HEADER_DEFINE_H_

#include <iostream>

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

#define PCUBE_ACK		(0x0F)
#define PCUBE_NACK  (0xF0)

#define PCUBE_HEADER_LEN (5)
#define PCUEB_ETX_LEN		 (2)

#define PCUBE_STX_DATA			(0xD0)
#define PCUBE_ETX_DATA			(0xE0)

#define PCUBE_STX_INDEX 		(0)
#define PCUBE_LEN_INDEX 		(1)
#define PCUBE_CLU_INDEX			(2)
#define PCUBE_CMD_INDEX			(3)
#define PCUBE_ATTR_LEN_INDEX				(4)
#define PCUBE_ATTR_START_INDEX			(5)

#define PCUBE_HEADER_COUNT  (2)

#define PCUBE_CMD_READ 						(0x01)
#define PCUBE_CMD_READ_RESPONSE 	(0x02)
#define PCUBE_CMD_WRITE 					(0x03)
#define PCUBE_CMD_WRITE_RESPONSE	(0x04)

#define PCUBE_ATTR_VERSION_CODE		(0X01)
#define PCUBE_ATTR_VERSION_BOOT		(0X02)
#define PCUBE_ATTR_STATUS					(0X03)
#define PCUBE_ATTR_READ_FLASH			(0X04)

#define PCUBE_ATTR_ERASE					(0X05)
#define PCUBE_ATTR_PROGRAM				(0X06)
#define PCUBE_ATTR_AP_RUN					(0X07)
#define PCUBE_ATTR_GOTO_BL				(0X08)

#define PCUBE_CLU_MOBILE					(0x01)
#define PCUBE_CLU_DESKTOP 				(0x02)
#define PCUBE_CLU_WIFI_DONGLE 		(0x03)
#define PCUBE_CLU_DEVICE 					(0x04)

#define TIME_20S_BY_1S (20)
#define TIME_5S_BY_1S (5)

#endif // _OP_HEADER_DEFINE_H_

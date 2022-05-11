#ifndef _MID_PCUBE_PROTOCOL_H_
#define _MID_PCUBE_PROTOCOL_H_

#include "main.h"
#include "Op_HeaderFlag.h"
#include "Op_HeaderVariable.h"
#include "Op_HeaderDefine.h"
#include "Op_HeaderFunction.h"

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

void Mid_PCubeProcess(void);
void Mid_PCubeTxConfig(void);
#endif

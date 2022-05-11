#ifndef _OP_HEADER_FLAG_H_
#define _OP_HEADER_FLAG_H_

#include "main.h"

#ifdef GLOBAL_DEFINE
#define HEADER_FLAG
#else
#define HEADER_FLAG extern
#endif

typedef struct
{
	uint8_t bit0 : 1;
	uint8_t bit1 : 1;
	uint8_t bit2 : 1;
	uint8_t bit3 : 1;
	uint8_t bit4 : 1;
	uint8_t bit5 : 1;
	uint8_t bit6 : 1;
	uint8_t bit7 : 1;
} BYTE_T;

typedef union
{
	uint8_t origin;
	BYTE_T member;
} BYTE_FIELD_T;
/*--- Flag for PCube ---*/
HEADER_FLAG BYTE_FIELD_T PcubeFlag1;
#define PCUBE_RECEIVE_DONE_FLAG PcubeFlag1.member.bit0
#define PCUBE_CHECKSUM_OK				PcubeFlag1.member.bit1
#define PCUBE_CHECKSUM_ERROR		PcubeFlag1.member.bit2
#define PCUBE_RESPONSE_START		PcubeFlag1.member.bit3
#define PCUBE_WRITE_START				PcubeFlag1.member.bit4
#define PCUBE_WRITE_DONE				PcubeFlag1.member.bit5
/*--- Flag for Flash ---*/
HEADER_FLAG BYTE_FIELD_T FlashFlag1;
#define FLASH_WRITE_REQUEST 	FlashFlag1.member.bit0
#define FLASH_READ_REQUEST		FlashFlag1.member.bit1
#define FLASH_ERASE_REQUEST 	FlashFlag1.member.bit2
#define FLASH_WRITE_DONE 		FlashFlag1.member.bit3
#define FLASH_READ_DONE 		FlashFlag1.member.bit4
#define FLASH_ERASE_DONE 		FlashFlag1.member.bit5
#define FLASH_WRITE_PROGRAM FlashFlag1.member.bit6
#define FLASH_ERASE_SECTOR 	FlashFlag1.member.bit7

HEADER_FLAG BYTE_FIELD_T FlashFlag2;
#define RESET_REQUEST 	FlashFlag2.member.bit1
/*--- Flag for operation ---*/
HEADER_FLAG BYTE_FIELD_T OperationFlag1;
#define OP_RESET_FLAG OperationFlag1.member.bit0
#endif // _OP_HEADER_FLAG_H_

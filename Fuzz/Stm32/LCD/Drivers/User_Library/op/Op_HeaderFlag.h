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
/*--- Flag for SD card ---*/
HEADER_FLAG BYTE_FIELD_T SDCardFlag1;
#define SD_CARD_INIT_SUCCESS_FLAG SDCardFlag1.member.bit0
/*--- Flag for LCD ---*/
HEADER_FLAG BYTE_FIELD_T LCDFlag1;
#define LCD_CHANGE_SCREEN_FLAG LCDFlag1.member.bit0
#define LCD_CONSENT_INIT_FLAG LCDFlag1.member.bit1
#define LCD_PROGRESS_INIT_FLAG LCDFlag1.member.bit2
#define LCD_PROGRESS_UPDATE_FLAG LCDFlag1.member.bit3
#define LCD_BACK_TO_LIST_FLAG LCDFlag1.member.bit3
#define LCD_50MS_CALL_FLAG		LCDFlag1.member.bit4
/*--- Flag for Bootloader ---*/
HEADER_FLAG BYTE_FIELD_T BootLoaderFlag1;
#define BOOTLOADER_START_FLAG 		BootLoaderFlag1.member.bit0
#define BOOTLOADER_STEP_ERASE 		BootLoaderFlag1.member.bit1
#define BOOTLOADER_STEP_ERASE_DONE 		BootLoaderFlag1.member.bit2
#define BOOTLOADER_ERASE_FIRST_INIT		BootLoaderFlag1.member.bit3
#define BOOTLOADER_STEP_FLASH					BootLoaderFlag1.member.bit4
#define BOOTLOADER_TIMEOUT_FLAG				BootLoaderFlag1.member.bit5
#define BOOTLOADER_FIRST_INIT					BootLoaderFlag1.member.bit6
#define BOOTLOADER_PROGRAM_DONE					BootLoaderFlag1.member.bit7

HEADER_FLAG BYTE_FIELD_T BootLoaderFlag2;
#define BOOTLOADER_STEP_FLASH_DONE 		BootLoaderFlag2.member.bit0
#define BOOTLOADER_FINISH_FLAG 		BootLoaderFlag2.member.bit1
#define BOOTLOADER_RUNNING_FLAG 		BootLoaderFlag2.member.bit2
/*--- Flag for Key ---*/
HEADER_FLAG BYTE_FIELD_T KeyFlag1;
#define KEY_1CLICK_FLAG						KeyFlag1.member.bit0
#define KEY_0_5SEC_CLICK_FLAG			KeyFlag1.member.bit1
#define KEY_1SEC_CLICK_FLAG			KeyFlag1.member.bit2
#define KEY_1_5SEC_CLICK_FLAG			KeyFlag1.member.bit3
#define KEY_2SEC_CLICK_FLAG			KeyFlag1.member.bit4
#define KEY_3SEC_CLICK_FLAG			KeyFlag1.member.bit5
#define KEY_5SEC_CLICK_FLAG			KeyFlag1.member.bit6
#define KEY_7SEC_CLICK_FLAG			KeyFlag1.member.bit7

HEADER_FLAG BYTE_FIELD_T KeyFlag2;
#define KEY_RELEASE_CLICK_FLAG						KeyFlag2.member.bit0
#define ERROR_KEYSHORT_FLAG								KeyFlag2.member.bit1

/*--- Flag for Display ---*/
HEADER_FLAG BYTE_FIELD_T DisplayFlag;
#define DISPLAY_FIRST_TIME_FLAG DisplayFlag.member.bit0
/*--- Flag for Audio ---*/
HEADER_FLAG BYTE_FIELD_T AudioFlag;
#define APPLY_CHORUS_FLAG AudioFlag.member.bit0
#define APPLY_REVERS_FLAG AudioFlag.member.bit1
#endif // _OP_HEADER_FLAG_H_

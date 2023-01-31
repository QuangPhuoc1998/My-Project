#ifndef _OP_HEADER_DEFINE_H_
#define _OP_HEADER_DEFINE_H_

#include "main.h"

#define sbi(str,bit) (str |= (1<<bit)) // set bit in register
#define cbi(str,bit) (str &= ~(1<<bit)) // clear bit in register
#define tbi(str,bit) (str ^= (1<<bit)) // toggle bit in register
/*--- Define for operation ---*/
#define C_ON 	(1)
#define C_OFF (0)
/*--- Define for UART ---*/
#define MAX_DATA_LEN_UART 256
#define MAX_ATTR_LEN			16
/*--- Define for timer counter ---*/
#define TIME_10MS_BY_1MS  (10)
#define TIME_5S_BY_1S			(5)
#define TIME_2S_BY_1S 		(2)

/*--- Define for Flash ---*/
#define STM32F769_NUM_OF_SECTOR (8)
#define ERASE_FULL (0xFF)
/*--- Define for SD Card ---*/
#define MAX_BIN_FILE (10)
/*--- Define for LCD ---*/
#define LCD_LAYOUT_REVERB		(1)
#define LCD_LAYOUT_CHORUS		(2)
#define LCD_LAYOUT_DELAY		(3)
#define LCD_LAYOUT_OVERDRIVE		(4)
#define LCD_LAYOUT_LOOP			(5)

#define CONSENT_YES (0)
#define CONSENT_NO (1)
/*--- Define for Error ---*/
#define ERROR_NOP								 (0)
#define ERROR_BOOTLOADER_TIMEOUT (1)
/*--- Define for Key ---*/
#define KEY_1CLICK_COUNT (3)
#define KEY_0_5SEC_COUNT (25)
#define KEY_1SEC_COUNT (50)
#define KEY_1_5SEC_COUNT (75)
#define KEY_2SEC_COUNT (100)
#define KEY_3SEC_COUNT (150)
#define KEY_5SEC_COUNT (250)
#define KEY_7SEC_COUNT (350)
#define KEY_SHORTERROR_COUNT (1500)

#define KEY_OFF_DEBOUCE (1)
#define KEY_ON_DEBOUNCE (2)
/*--- Define for my color ---*/
#define BACK_GROUND_COLOR ((uint32_t) 0xFF242424)
/*--- Define for Dotnavi ---*/
#define MAX_DOT_NAVI 		(5)
/*--- Define for setting ---*/
#define MODE_SETTING_ON_IN		(1)
#define REVERB_TIME_ON_IN			(2)
#define REVERB_WET_ON_IN			(3)
#define CHORUS_OFFSET_ON_IN		(4)
#define CHORUS_DEPTH_ON_IN		(5)
#define DELAY_TIME_ON_IN			(6)
/*--- Define for audio ---*/
#define SAMPLE_RATE (44100)

typedef enum {
  BUFFER_OFFSET_NONE = 0,  
  BUFFER_OFFSET_HALF,  
  BUFFER_OFFSET_FULL,     
}BUFFER_StateTypeDef;

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

typedef enum
{
	NO_CHANGE = 0x00,
	UP = 0xF0,
	DOWN = 0x0F
} DialDirection_t;

typedef struct _biquad{
	float a0;
	float a1;
	float a2;
	float b0;
	float b1;
	float b2;
	float prev_input_1;
	float prev_input_2;
	float prev_output_1;
	float prev_output_2;
	char* type;
}biquad;

typedef enum {
	NONE = 0,
	LOWPASS,
	HIGHPASS,
	BANDPASS,
	NOTCH,
	PEAK,
	LOWSHELF,
	HIGHSHELF,
} FILTER_TYPES;

typedef enum
{
	NO_EFFECT = 0,
	REVERB,
} EFFECT_TYPES;

typedef enum
{
	FREQUENCY = 0,
	GAIN,
	Q,
	MAX_FILTER_CONFIG
} FilterConfigType_t;

typedef enum
{
	DRYWET = 0,
	DELAYTIME,
	MAX_REVERB_CONFIG,
} ReverbConfigType_t;
#endif // _OP_HEADER_DEFINE_H_

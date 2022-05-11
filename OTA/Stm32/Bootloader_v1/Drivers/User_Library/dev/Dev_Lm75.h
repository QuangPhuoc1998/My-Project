#ifndef _DEV_LM75_H_
#define _DEV_LM75_H_

#include "main.h"
#include "Op_Header_Main.h"
#include "i2c.h"

#define LM75_ADRESS 			(0x48<<1)
#define LM75_TEMP_REG		 	0x00
#define LM75_CONFIG_REG	 	0x01
#define LM75_THYST_REG 		0x02
#define LM75_TOS_REG 			0x03

#define sbi(str,bit) (str |= (1<<bit)) // set bit in register
#define cbi(str,bit) (str &= ~(1<<bit)) // clear bit in register
#define tbi(str,bit) (str ^= (1<<bit)) // toggle bit in register

typedef enum
{
	FAULT_QUEUE_1,
	FAULT_QUEUE_2,
	FAULT_QUEUE_4,
	FAULT_QUEUE_6
} ConfigFault_t;

typedef enum
{
	OS_HIGH,
	OS_LOW
} ConfigOS_t;

typedef enum
{
	MODE_COMPARATOR,
	MODE_INTERRUPT
} OperationMode_t;

void Dev_Lm75Init(ConfigFault_t FaultMode, ConfigOS_t OSMode, OperationMode_t OperationMOde, uint16_t HYSTValue, uint16_t OSValue);
void Dev_Lm75Handler(void);
uint16_t Dev_Lm75GetTemperature(void);


#endif // _DEV_LM75_H_

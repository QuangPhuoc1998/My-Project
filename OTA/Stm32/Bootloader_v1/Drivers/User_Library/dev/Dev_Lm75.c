#include "Dev_Lm75.h"

#define MAX_DATA_LEN 		7
#define MAX_DATA_CONFIG 5

uint8_t aubI2CData[MAX_DATA_LEN] = {0};
uint16_t uwTemperature = 0;
uint8_t ConfigRegValue[MAX_DATA_CONFIG] = {0};

static void _Dev_Lm75WriteRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size);
static void _Dev_Lm75ReadRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size);
static void _Dev_lm75ReadTemperature(void);

void Dev_Lm75Init(ConfigFault_t FaultMode, ConfigOS_t OSMode, OperationMode_t OperationMOde, uint16_t HYSTValue, uint16_t OSValue)
{
	/*--- Set Fault mode ---*/
	switch (FaultMode)
	{
		case FAULT_QUEUE_1:
			cbi(ConfigRegValue[0], 4);
			cbi(ConfigRegValue[0], 3);
			break;
		case FAULT_QUEUE_2:
			cbi(ConfigRegValue[0], 4);
			sbi(ConfigRegValue[0], 3);
			break;
		case FAULT_QUEUE_4:
			sbi(ConfigRegValue[0], 4);
			cbi(ConfigRegValue[0], 3);
			break;
		case FAULT_QUEUE_6:
			sbi(ConfigRegValue[0], 4);
			sbi(ConfigRegValue[0], 3);
			break;
		default:
			break;
	}
	/*--- Set OS level ---*/
	(OSMode == OS_LOW) ? (cbi(ConfigRegValue[0], 2)) : (sbi(ConfigRegValue[0], 2));
	/*--- Set Operation mode ---*/
	(OperationMOde == MODE_COMPARATOR) ? (cbi(ConfigRegValue[0], 1)) : (sbi(ConfigRegValue[0], 1));
	/*--- Set OS value > Up value ---*/
	ConfigRegValue[1] = OSValue;
	/*--- Set THYST value > Down value ---*/
	ConfigRegValue[2] = HYSTValue;
	/*--- Send data ---*/
	_Dev_Lm75WriteRegister(LM75_CONFIG_REG, &ConfigRegValue[0], 1);
	_Dev_Lm75WriteRegister(LM75_TOS_REG,    &ConfigRegValue[1], 1);
	_Dev_Lm75WriteRegister(LM75_THYST_REG,  &ConfigRegValue[2], 1);
}
void Dev_Lm75Handler(void)
{
	_Dev_lm75ReadTemperature();
}
uint16_t Dev_Lm75GetTemperature(void)
{
	return uwTemperature;
}
static void _Dev_Lm75WriteRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
	HAL_I2C_Mem_Write(&hi2c1, LM75_ADRESS, MemAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, 1);
}
static void _Dev_Lm75ReadRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
	HAL_I2C_Mem_Read(&hi2c1, LM75_ADRESS, MemAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, 1);
}
static void _Dev_lm75ReadTemperature(void)
{
	_Dev_Lm75ReadRegister(LM75_TEMP_REG, &aubI2CData[0], 2);
	
	uwTemperature = (aubI2CData[0] & 0x7F) * 10 + ((aubI2CData[1] & 0x80) >> 7)* 5;
	/*
	_Dev_Lm75ReadRegister(LM75_CONFIG_REG, &aubI2CData[2], 1);
	_Dev_Lm75ReadRegister(LM75_THYST_REG, &aubI2CData[3], 2);
	_Dev_Lm75ReadRegister(LM75_TOS_REG, &aubI2CData[5], 2);
	*/
}

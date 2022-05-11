#include "Dev_Gy30.h"

#define GY30_ADRESS (0x23<<1)
#define GY30_REG 		0x00

#define CONT_H_RESOLUTION_MODE 0x13

#define MAX_LEN (11)

uint8_t g_ubI2CData[MAX_LEN] = {0};
uint16_t g_ubLightIntensityData = 0;

static void _Dev_Gy30riteRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size);
static void _Dev_Gy30ReadRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size);
static void _Dev_Gy30ReadLightIntensity(void);

void Dev_Gy30Init(void)
{
	
}
void Dev_Gy30Handler(void)
{
	_Dev_Gy30ReadLightIntensity();
}
uint16_t Dev_Gy30GetLightIntensity(void)
{
	return g_ubLightIntensityData;
}

static void _Dev_Gy30riteRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
	HAL_I2C_Mem_Write(&hi2c1, GY30_ADRESS, MemAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, 1);
}
static void _Dev_Gy30ReadRegister(uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
	HAL_I2C_Mem_Read(&hi2c1, GY30_ADRESS, MemAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, 1);
}
static void _Dev_Gy30ReadLightIntensity(void)
{
	_Dev_Gy30ReadRegister(CONT_H_RESOLUTION_MODE, g_ubI2CData, 2);
	g_ubLightIntensityData = ((g_ubI2CData[0]<<8)+g_ubI2CData[1])/1.2;
}

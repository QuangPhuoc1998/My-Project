#include "Mid_FlashControl.h"

uint8_t _FlashEraseDataBySector(uint8_t ubSectorNumber, uint8_t ubNumberOfSector);
uint8_t _FlashWriteData(uint8_t * pData, uint32_t uwMemAddress, uint32_t uwLen);
void _FlashReadData(uint8_t * pDataBuffer, uint32_t uwMemAddress, uint32_t uwLen);
uint32_t _FlashGetSector(uint32_t Address);

void Mid_FlashEraseProcess(void)
{
	if(FLASH_ERASE_SECTOR == C_ON)
	{
		_FlashEraseDataBySector(sDataToErase.ubSectorNumber, sDataToErase.ubNumberOfSector);
		FLASH_ERASE_SECTOR = C_OFF;
		FLASH_READ_DONE = C_ON;
		PCUBE_RESPONSE_START = C_ON;
	}
}
void Mid_FlashReadProcess(void)
{

}
void Mid_FlashWriteProcess(void)
{
	if(FLASH_ERASE_REQUEST == C_OFF)
	{
		if(FLASH_WRITE_PROGRAM == C_ON)
		{
			_FlashWriteData(sDataToWrite.pData, sDataToWrite.uwMemAddress, sDataToWrite.uwLen);
			FLASH_WRITE_PROGRAM = C_OFF;
			FLASH_WRITE_DONE = C_ON;
			PCUBE_RESPONSE_START = C_ON;
		}
	}
}
uint8_t _FlashEraseDataBySector(uint8_t ubSectorNumber, uint8_t ubNumberOfSector)
{
	uint8_t ubRemainingSector = 0;
	HAL_StatusTypeDef status;
	uint32_t uwsectorError;
	FLASH_EraseInitTypeDef flashErase_handle;
	
	if(ubNumberOfSector > STM32F769_NUM_OF_SECTOR)
	{
		return INVALID_SECTOR;
	}
	if(ubSectorNumber == ERASE_FULL || ubSectorNumber <= (STM32F769_NUM_OF_SECTOR-1))
	{
		if(ubSectorNumber == (uint8_t) ERASE_FULL)
		{
			flashErase_handle.TypeErase = FLASH_TYPEERASE_MASSERASE;
		}
		else
		{
			ubRemainingSector = STM32F769_NUM_OF_SECTOR - ubSectorNumber;
			if(ubNumberOfSector > ubRemainingSector)
			{
				ubNumberOfSector = ubRemainingSector;
			}
			flashErase_handle.TypeErase = FLASH_TYPEERASE_SECTORS;
			flashErase_handle.Sector = ubSectorNumber; // this is the initial sector
			flashErase_handle.NbSectors = ubNumberOfSector;
		}
		flashErase_handle.Banks = FLASH_BANK_1;
		
		HAL_FLASH_Unlock();
		flashErase_handle.VoltageRange = FLASH_VOLTAGE_RANGE_3;  // our mcu will work on this voltage range
		status = (uint8_t) HAL_FLASHEx_Erase(&flashErase_handle, &uwsectorError);
		HAL_FLASH_Lock();
		
		return status;
	}
	
	return INVALID_SECTOR;
}

uint8_t _FlashWriteData(uint8_t * pData, uint32_t uwMemAddress, uint32_t uwLen)
{
	uint8_t status=HAL_OK;

	HAL_FLASH_Unlock();

	for(uint32_t i = 0 ; i <uwLen ; i++)
	{
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,uwMemAddress+i,pData[i] );
	}

	HAL_FLASH_Lock();

	return status;
}

void _FlashReadData(uint8_t * pDataBuffer, uint32_t uwMemAddress, uint32_t uwLen)
{
	for(uint32_t i = 0 ; i < uwLen ; i++)
	{
		pDataBuffer[i] = *(__IO uint32_t *)uwMemAddress;
		uwMemAddress += 4;
	}
}

uint32_t _FlashGetSector(uint32_t Address)
{
  uint32_t sector = 0;

  /* BANK 1 */
  if((Address >= 0x08000000) && (Address < 0x08008000))
  {
    sector = FLASH_SECTOR_0;
  }

  else if((Address >= 0x08008000) && (Address < 0x08010000))
  {
    sector = FLASH_SECTOR_1;
  }

  else if((Address >= 0x08010000) && (Address < 0x08018000))
  {
    sector = FLASH_SECTOR_2;
  }

  else if((Address >= 0x08018000) && (Address < 0x08020000))
  {
    sector = FLASH_SECTOR_3;
  }

  else if((Address >= 0x08020000) && (Address < 0x08040000))
  {
    sector = FLASH_SECTOR_4;
  }

  else if((Address >= 0x08040000) && (Address < 0x08080000))
  {
    sector = FLASH_SECTOR_5;
  }

  else if((Address >= 0x08080000) && (Address < 0x080C0000))
  {
    sector = FLASH_SECTOR_6;
  }

  else if((Address >= 0x080C0000) && (Address < 0x08100000))
  {
    sector = FLASH_SECTOR_7;
  }
  return sector;
}

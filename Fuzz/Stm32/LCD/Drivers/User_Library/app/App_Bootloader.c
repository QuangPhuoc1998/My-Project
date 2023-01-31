#include "App_Bootloader.h"
#include "Mid_FileOperation.h"
#include "Mid_Debug.h"

#define FILE_NAME "BIN/lcd.bin"

#define FLASH_SECTOR0_BASE_ADDRESS 0x08000000U
#define FLASH_SECTOR1_BASE_ADDRESS 0x08008000U
#define FLASH_SECTOR2_BASE_ADDRESS 0x08010000U
#define FLASH_SECTOR3_BASE_ADDRESS 0x08018000U
#define FLASH_SECTOR4_BASE_ADDRESS 0x08020000U
#define FLASH_SECTOR5_BASE_ADDRESS 0x08040000U
#define FLASH_SECTOR6_BASE_ADDRESS 0x08080000U
#define FLASH_SECTOR7_BASE_ADDRESS 0x080C0000U

#define APPLICATION_BASE_ADDRESS FLASH_SECTOR2_BASE_ADDRESS

uint32_t IndexCount = 0;
uint32_t bytes_remaining=0;
uint32_t t_len_of_file=0;
uint32_t bytes_so_far_sent = 0,len_to_read=0;
uint32_t base_mem_address = FLASH_SECTOR2_BASE_ADDRESS;
uint32_t probar = 0;
uint32_t ulFileSize;
uint32_t Offset = 0;

void _BootLoaderErase(void);
void _BootLoaderWrite(void);
void App_BootloaderInit(void)
{
	HAL_UART_Receive_IT(&huart1, &g_ubRxDataBuffer, 1);
}
void App_BootLoaderStart(void)
{
	BOOTLOADER_START_FLAG = C_ON;
	BOOTLOADER_STEP_ERASE = C_ON;
	BOOTLOADER_STEP_ERASE_DONE = C_OFF;
	BOOTLOADER_STEP_FLASH = C_ON;
	BOOTLOADER_STEP_FLASH_DONE = C_OFF;
	BOOTLOADER_FIRST_INIT = C_ON;
	BOOTLOADER_ERASE_FIRST_INIT = C_ON;
	BOOTLOADER_PROGRAM_DONE = C_ON;
	BOOTLOADER_TIMEOUT_FLAG = C_OFF;
	BOOTLOADER_RUNNING_FLAG = C_ON;
	BOOTLOADER_FINISH_FLAG = C_OFF;
}
void App_BootloaderProcess(void)
{
	if(BOOTLOADER_START_FLAG == C_ON)
	{
		if(BOOTLOADER_STEP_ERASE == C_ON)
		{
			_BootLoaderErase();
		}
		else if(BOOTLOADER_STEP_ERASE_DONE == C_ON)
		{
			_BootLoaderWrite();
		}
	}
}
void App_BootloaderJumpToUserApp(void)
{
	SCB_DisableDCache();
	SCB_DisableICache();
	SysTick->CTRL = 0;
	
	BSP_LCD_MspDeInit();
	HAL_UART_DeInit(&huart1);
	HAL_RCC_DeInit();
	HAL_DeInit();
	
	SCB->SHCSR &= ~(SCB_SHCSR_USGFAULTENA_Msk |\
	SCB_SHCSR_BUSFAULTENA_Msk |\
	SCB_SHCSR_MEMFAULTACT_Msk);
	
	void (*app_reset_handler)(void);
	
	__set_MSP(*(__IO uint32_t*) APPLICATION_BASE_ADDRESS);
	
	uint32_t resethandler_address = *(volatile uint32_t *) (APPLICATION_BASE_ADDRESS + 4);
	
	app_reset_handler = (void *)resethandler_address;
	
	SCB->VTOR = APPLICATION_BASE_ADDRESS;
	
	app_reset_handler();
}

void _BootLoaderErase(void)
{
	if(BOOTLOADER_ERASE_FIRST_INIT == C_ON)
	{
		ulFileSize = Mid_FileGetSize((const char*)g_aubFileName);
		sDataToErase.ubSectorNumber = 2;
		sDataToErase.ubNumberOfSector = CalculateSector(ulFileSize);
		
		FLASH_ERASE_REQUEST = C_ON;
		FLASH_ERASE_SECTOR = C_ON;
		
		BOOTLOADER_ERASE_FIRST_INIT = C_OFF;
	}
	
	if(BOOTLOADER_TIMEOUT_FLAG == C_ON)
	{
			BOOTLOADER_STEP_FLASH = C_OFF;
			BOOTLOADER_START_FLAG = C_OFF;
			BOOTLOADER_FIRST_INIT = C_OFF;
			BOOTLOADER_ERASE_FIRST_INIT = C_OFF;
	}
}
void _BootLoaderWrite(void)
{
	if(BOOTLOADER_FIRST_INIT == C_ON)
	{
		ulFileSize = Mid_FileGetSize((const char*)g_aubFileName);
		t_len_of_file = ulFileSize;
		bytes_remaining = t_len_of_file - bytes_so_far_sent;
		probar = (t_len_of_file / 128) + 1;
		BOOTLOADER_FIRST_INIT = C_OFF;
		Mid_DebugShow((uint8_t *)"Start flash");
	}
	
	if(BOOTLOADER_TIMEOUT_FLAG == C_OFF && BOOTLOADER_PROGRAM_DONE == C_ON && bytes_remaining != 0)
	{
		if(bytes_remaining >= 128)
		{
			 len_to_read = 128;
		}else
		{
			 len_to_read = bytes_remaining;
		}
		IndexCount++;
		/*---*/
		 
		Mid_FileRead((const char*)g_aubFileName, Offset, g_aubDataToWrite, len_to_read);
		Offset += len_to_read;
		sDataToWrite.pData = g_aubDataToWrite;
		sDataToWrite.uwMemAddress = base_mem_address;
		sDataToWrite.uwLen = len_to_read;
		
		FLASH_WRITE_REQUEST = C_ON;
		FLASH_WRITE_PROGRAM = C_ON;
		/*---*/
		base_mem_address+=len_to_read;
		bytes_so_far_sent+=len_to_read;
		bytes_remaining = t_len_of_file - bytes_so_far_sent;

		BOOTLOADER_PROGRAM_DONE = C_OFF;
	}
	
	if(bytes_remaining == 0 && BOOTLOADER_TIMEOUT_FLAG == C_OFF && BOOTLOADER_PROGRAM_DONE == C_ON)
	{
		 Mid_DebugShow((uint8_t  * )"=> Flash done\n");
		 BOOTLOADER_STEP_FLASH = C_OFF;
		 BOOTLOADER_START_FLAG = C_OFF;
		 BOOTLOADER_FIRST_INIT = C_OFF;

		 IndexCount = 0;
		 bytes_remaining=0;
		 t_len_of_file=0;
		 bytes_so_far_sent = 0,len_to_read=0;
		 base_mem_address = FLASH_SECTOR2_BASE_ADDRESS;
		 probar = 0;
		 Offset = 0;
		
		 BOOTLOADER_FINISH_FLAG = C_ON;
		 BOOTLOADER_RUNNING_FLAG = C_OFF;
		 LCD_CHANGE_SCREEN_FLAG = C_ON;
		 LCD_CONSENT_INIT_FLAG = C_OFF;
	}
	if(BOOTLOADER_TIMEOUT_FLAG == C_ON)
	{
		Mid_DebugShow((uint8_t  * )"=> Time out\n");
		BOOTLOADER_STEP_FLASH = C_OFF;
		BOOTLOADER_START_FLAG = C_OFF;
		BOOTLOADER_FIRST_INIT = C_OFF;

		IndexCount = 0;
		bytes_remaining=0;
		t_len_of_file=0;
		bytes_so_far_sent = 0,len_to_read=0;
		base_mem_address = FLASH_SECTOR2_BASE_ADDRESS;
		probar = 0;
		Offset = 0;
		
		BOOTLOADER_RUNNING_FLAG = C_OFF;
	}
}

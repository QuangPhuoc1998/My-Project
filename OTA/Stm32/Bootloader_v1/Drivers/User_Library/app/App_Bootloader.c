#include "App_Bootloader.h"

#define FLASH_SECTOR2_BASE_ADDRESS 0x08008000U


void App_BootloaderInit(void)
{
	HAL_UART_Receive_IT(&huart1, &g_ubRxDataBuffer, 1);
}
void App_BootloaderProcess(void)
{
	
}
void App_BootloaderJumpToUserApp(void)
{
	
	HAL_UART_DeInit(&huart1);
	HAL_RCC_DeInit();
	HAL_DeInit();
	
	SCB->SHCSR &= ~(SCB_SHCSR_USGFAULTENA_Msk |\
	SCB_SHCSR_BUSFAULTENA_Msk |\
	SCB_SHCSR_MEMFAULTACT_Msk);
	
	void (*app_reset_handler)(void);
	
	__set_MSP(*(__IO uint32_t*) FLASH_SECTOR2_BASE_ADDRESS);
	
	uint32_t resethandler_address = *(volatile uint32_t *) (FLASH_SECTOR2_BASE_ADDRESS + 4);
	
	app_reset_handler = (void *)resethandler_address;
	
	SCB->VTOR = FLASH_SECTOR2_BASE_ADDRESS;
	
	app_reset_handler();
}

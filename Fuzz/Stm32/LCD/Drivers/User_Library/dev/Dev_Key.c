#include "Dev_Key.h"

void Dev_KeyInit(void)
{
	
}
void Dev_KeyScan(void)
{
	if(BSP_PB_GetState(BUTTON_WAKEUP) == 1)
	{
		sbi(g_ulKeyInValue, 0);
	}
	else
	{
		cbi(g_ulKeyInValue, 0);
	}
	
	if(HAL_GPIO_ReadPin(GPIOJ, GPIO_PIN_1) == 0)
	{
		sbi(g_ulKeyInValue, 1);
	}
	else
	{
		cbi(g_ulKeyInValue, 1);
	}
}

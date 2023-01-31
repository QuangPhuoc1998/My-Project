#include "Mid_Debug.h"

void Mid_DebugShow(uint8_t * pData)
{
	HAL_UART_Transmit(&huart1, pData, strlen((char *)pData), HAL_MAX_DELAY);
}

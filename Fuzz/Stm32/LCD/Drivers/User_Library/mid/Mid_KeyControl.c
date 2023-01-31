#include "Mid_KeyControl.h"

static uint32_t g_aulKeyBuffer[3];
static uint8_t 	g_ubKeyBufferIndex;
static uint16_t g_uwKeyNotSameCount;

void ClearLongBuffer(uint32_t * pulBuffer, uint8_t ubIndex);
void Mid_KeyHandler(void)
{
	if(g_ulKeyInValue == 0)
	{
		g_ubKeyOffCount++;
		if(g_ubKeyOffCount >= KEY_OFF_DEBOUCE)
		{
			g_ubKeyOffCount = KEY_OFF_DEBOUCE;
			g_ubKeyBufferIndex = 0;
			if(g_uwKeyContinousCount > 0 && g_uwKeyContinousCount < KEY_3SEC_COUNT)
			{
				if(KEY_RELEASE_CLICK_FLAG == C_OFF)
				{
					KEY_RELEASE_CLICK_FLAG = C_ON;
					g_ulKeyInValue = g_aulKeyBuffer[0];
				}
			}
			g_uwKeyContinousCount = 0;
		}
	}
	
	if(g_ulKeyInValue != 0 && g_ubKeyBufferIndex < KEY_ON_DEBOUNCE)
	{
		if(g_ubKeyBufferIndex == 0)
		{
			g_aulKeyBuffer[g_ubKeyBufferIndex] = g_ulKeyInValue;
			g_ubKeyBufferIndex++;
		}
		else if(g_ubKeyBufferIndex > 0)
		{
			if(g_aulKeyBuffer[g_ubKeyBufferIndex-1] != g_ulKeyInValue)
			{
				ClearLongBuffer(g_aulKeyBuffer, 3);
				g_aulKeyBuffer[0] = g_ulKeyInValue;
				g_ubKeyBufferIndex = 0;
			}
			else
			{
				g_aulKeyBuffer[g_ubKeyBufferIndex] = g_ulKeyInValue;
				g_ubKeyBufferIndex++;
			}
		}
	}
	else if(g_ulKeyInValue != 0 && g_ubKeyBufferIndex >= KEY_ON_DEBOUNCE)
	{
		if(g_ubKeyBufferIndex == 0)
		{
			g_aulKeyBuffer[g_ubKeyBufferIndex] = g_ulKeyInValue;
			g_ubKeyBufferIndex++;
			g_uwKeyContinousCount++;
		}
		else
		{
			if(g_aulKeyBuffer[g_ubKeyBufferIndex - 1] == g_ulKeyInValue)
			{
				g_uwKeyContinousCount++;
				g_uwKeyNotSameCount = 0;
			}
			else if(g_aulKeyBuffer[g_ubKeyBufferIndex - 1] != g_ulKeyInValue)
			{
				g_uwKeyNotSameCount++;
				g_uwKeyContinousCount = 0;
			}
			else
			{
				g_uwKeyNotSameCount = 0;
				g_uwKeyContinousCount = 0;
			}
		}
		// 1 Click
		if(g_uwKeyContinousCount == KEY_1CLICK_COUNT && g_ubKeyOffCount == KEY_OFF_DEBOUCE)
		{
			if(KEY_1CLICK_FLAG == C_OFF)
			{
				KEY_1CLICK_FLAG = C_ON;
				g_ubKeyOffCount = 0;
			}
		}
		// Click for 0.5 sec
		else if(g_uwKeyContinousCount == KEY_0_5SEC_COUNT && g_ubKeyOffCount == 0)
		{
			if(KEY_0_5SEC_CLICK_FLAG == C_OFF)
			{
				KEY_0_5SEC_CLICK_FLAG = C_ON;
			}
		}
		// Click for 1 sec
		else if(g_uwKeyContinousCount == KEY_1SEC_COUNT && g_ubKeyOffCount == 0)
		{
			if(KEY_1SEC_CLICK_FLAG == C_OFF)
			{
				KEY_1SEC_CLICK_FLAG = C_ON;
			}
		}
		// Click for 1.5 sec
		else if(g_uwKeyContinousCount == KEY_1_5SEC_COUNT && g_ubKeyOffCount == 0)
		{
			if(KEY_1_5SEC_CLICK_FLAG == C_OFF)
			{
				KEY_1_5SEC_CLICK_FLAG = C_ON;
			}
		}
		// Click for 2 sec
		else if(g_uwKeyContinousCount == KEY_2SEC_COUNT && g_ubKeyOffCount == 0)
		{
			if(KEY_2SEC_CLICK_FLAG == C_OFF)
			{
				KEY_2SEC_CLICK_FLAG = C_ON;
			}
		}
		// Click for 3 sec
		else if(g_uwKeyContinousCount == KEY_3SEC_COUNT && g_ubKeyOffCount == 0)
		{
			if(KEY_3SEC_CLICK_FLAG == C_OFF)
			{
				KEY_3SEC_CLICK_FLAG = C_ON;
			}
		}
		// Click for 5 sec
		else if(g_uwKeyContinousCount == KEY_5SEC_COUNT && g_ubKeyOffCount == 0)
		{
			if(KEY_5SEC_CLICK_FLAG == C_OFF)
			{
				KEY_5SEC_CLICK_FLAG = C_ON;
			}
		}
		// Click for 7 sec
		else if(g_uwKeyContinousCount == KEY_7SEC_COUNT && g_ubKeyOffCount == 0)
		{
			if(KEY_7SEC_CLICK_FLAG == C_OFF)
			{
				KEY_7SEC_CLICK_FLAG = C_ON;
			}
		}
		// Short error
		else if(g_uwKeyContinousCount == KEY_SHORTERROR_COUNT && g_ubKeyOffCount == 0)
		{
			if(ERROR_KEYSHORT_FLAG == C_OFF)
			{
				ERROR_KEYSHORT_FLAG = C_ON;
			}
		}
		
		if(g_uwKeyNotSameCount == KEY_SHORTERROR_COUNT && g_ubKeyOffCount == 0)
		{
			if(ERROR_KEYSHORT_FLAG == C_OFF)
			{
				ERROR_KEYSHORT_FLAG = C_ON;
				g_ubKeyBufferIndex = 0;
			}
		}
	}
}
void ClearLongBuffer(uint32_t * pulBuffer, uint8_t ubIndex)
{
	for(uint8_t i = 0 ; i < ubIndex ; i++)
	{
		pulBuffer[i] = 0;
	}
}


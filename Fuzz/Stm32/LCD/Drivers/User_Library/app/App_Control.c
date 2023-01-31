#include "App_Control.h"
#include "App_Bootloader.h"

void _App_ProcessUpDownSetting(uint8_t ubUpDownMoveValue);

void App_ControlHandler(void)
{
	if(KEY_1CLICK_FLAG == C_ON)
	{
		if(g_ulKeyInValue == 0x00000002)
		{
			switch (g_tLcdStatus.LayOutIndex)
			{
				case LCD_LAYOUT_REVERB:
					if(g_tLcdStatus.Operation == MODE_SETTING_ON_IN)
					{
						g_tLcdStatus.Operation = REVERB_TIME_ON_IN;
					} 
					else if(g_tLcdStatus.Operation == REVERB_TIME_ON_IN)
					{
						g_tLcdStatus.Operation = REVERB_WET_ON_IN;
					}
					else if(g_tLcdStatus.Operation == REVERB_WET_ON_IN)
					{
						g_tLcdStatus.Operation = MODE_SETTING_ON_IN;
					}
					break;
				case LCD_LAYOUT_CHORUS:
					if(g_tLcdStatus.Operation == MODE_SETTING_ON_IN)
					{
						g_tLcdStatus.Operation = CHORUS_OFFSET_ON_IN;
					} 
					else if(g_tLcdStatus.Operation == CHORUS_OFFSET_ON_IN)
					{
						g_tLcdStatus.Operation = CHORUS_DEPTH_ON_IN;
					}
					else if(g_tLcdStatus.Operation == CHORUS_DEPTH_ON_IN)
					{
						g_tLcdStatus.Operation = MODE_SETTING_ON_IN;
					}
					break;
				case LCD_LAYOUT_DELAY:
					if(g_tLcdStatus.Operation == MODE_SETTING_ON_IN)
					{
						g_tLcdStatus.Operation = DELAY_TIME_ON_IN;
					} 
					else if(g_tLcdStatus.Operation == DELAY_TIME_ON_IN)
					{
						g_tLcdStatus.Operation = MODE_SETTING_ON_IN;
					}
					break;
				case LCD_LAYOUT_OVERDRIVE:
					break;
				case LCD_LAYOUT_LOOP:
					break;
				default:
					break;
		}
	}
		}
	
	if(g_ubUpDownMoveValue != NO_CHANGE)
	{
		_App_ProcessUpDownSetting(g_ubUpDownMoveValue);
		g_ubUpDownMoveValue = NO_CHANGE;
	}
	KEY_1CLICK_FLAG = C_OFF;
	KEY_0_5SEC_CLICK_FLAG = C_OFF;
	KEY_1SEC_CLICK_FLAG = C_OFF;
	KEY_1_5SEC_CLICK_FLAG = C_OFF;
	KEY_2SEC_CLICK_FLAG = C_OFF;
	KEY_3SEC_CLICK_FLAG = C_OFF;
	KEY_5SEC_CLICK_FLAG = C_OFF;
	KEY_7SEC_CLICK_FLAG = C_OFF;
	KEY_RELEASE_CLICK_FLAG = C_OFF;
}

void _App_ProcessUpDownSetting(uint8_t ubUpDownMoveValue)
{
	switch (g_tLcdStatus.Operation)
	{
		case MODE_SETTING_ON_IN:
		{
			if(ubUpDownMoveValue == UP)
			{
				g_tLcdStatus.DotNavi++;
				if(g_tLcdStatus.DotNavi == 3)
				{
				g_tLcdStatus.DotNavi = 0;
				}
				g_tLcdStatus.LayOutIndex = g_tLcdStatus.DotNavi + 1;
			}
			else
			{
				if(g_tLcdStatus.DotNavi == 0)
				{
					g_tLcdStatus.DotNavi = 2;
				}
				else
				{
					g_tLcdStatus.DotNavi--;
				}

				g_tLcdStatus.LayOutIndex = g_tLcdStatus.DotNavi + 1;
			}
			break;
		}
		case REVERB_TIME_ON_IN:
		{
			if(ubUpDownMoveValue == UP)
			{
				g_tLcdStatus.ReverbTime++;
				if(g_tLcdStatus.ReverbTime == 101)
				{
				g_tLcdStatus.ReverbTime = 0;
				}
			}
			else
			{
				if(g_tLcdStatus.ReverbTime == 0)
				{
					g_tLcdStatus.ReverbTime = 100;
				}
				else
				{
					g_tLcdStatus.ReverbTime--;
				}
			}
			break;
		}
		case REVERB_WET_ON_IN:
		{
			if(ubUpDownMoveValue == UP)
			{
				g_tLcdStatus.ReverbWet++;
				if(g_tLcdStatus.ReverbWet == 101)
				{
				g_tLcdStatus.ReverbWet = 0;
				}
			}
			else
			{
				if(g_tLcdStatus.ReverbWet == 0)
				{
					g_tLcdStatus.ReverbWet = 100;
				}
				else
				{
					g_tLcdStatus.ReverbWet--;
				}
			}
			break;
		}
		case CHORUS_OFFSET_ON_IN:
		{
			if(ubUpDownMoveValue == UP)
			{
				g_tLcdStatus.ChorusOffset++;
				if(g_tLcdStatus.ChorusOffset == 101)
				{
				g_tLcdStatus.ChorusOffset = 0;
				}
			}
			else
			{
				if(g_tLcdStatus.ChorusOffset == 0)
				{
					g_tLcdStatus.ChorusOffset = 100;
				}
				else
				{
					g_tLcdStatus.ChorusOffset--;
				}
			}
			break;
		}
		case CHORUS_DEPTH_ON_IN:
		{
			if(ubUpDownMoveValue == UP)
			{
				g_tLcdStatus.ChorusDepth++;
				if(g_tLcdStatus.ChorusDepth == 101)
				{
				g_tLcdStatus.ChorusDepth = 0;
				}
			}
			else
			{
				if(g_tLcdStatus.ChorusDepth == 0)
				{
					g_tLcdStatus.ChorusDepth = 100;
				}
				else
				{
					g_tLcdStatus.ChorusDepth--;
				}
			}
			break;
		}
		case DELAY_TIME_ON_IN:
		{
			if(ubUpDownMoveValue == UP)
			{
				g_tLcdStatus.DelayTime++;
				if(g_tLcdStatus.DelayTime == 101)
				{
				g_tLcdStatus.DelayTime = 0;
				}
			}
			else
			{
				if(g_tLcdStatus.DelayTime == 0)
				{
					g_tLcdStatus.DelayTime = 100;
				}
				else
				{
					g_tLcdStatus.DelayTime--;
				}
			}
			break;
		}
	}
}

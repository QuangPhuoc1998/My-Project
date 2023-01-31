#include "App_LCDControl.h"

void App_LCDControlHandler(void)
{
	uint8_t aubDisplayData[8] = {0};
	
	if(g_tLcdStatus.LayOutIndex != g_tLcdPreStatus.LayOutIndex ||
		 g_tLcdStatus.DotNavi != g_tLcdPreStatus.DotNavi)
	{
		/*---*/
		if(g_tLcdStatus.DotNavi != g_tLcdPreStatus.DotNavi)
		{
			Dev_LcdDotNaviDisplay(g_tLcdStatus.DotNavi);
		}
		/*---*/
		if(g_tLcdStatus.LayOutIndex != g_tLcdPreStatus.LayOutIndex)
		{
			BSP_LCD_SetFont(&Font50);
			BSP_LCD_SetBackColor(BACK_GROUND_COLOR);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			switch (g_tLcdStatus.LayOutIndex)
			{
				case LCD_LAYOUT_REVERB:
					BSP_LCD_DisplayStringAt(580, 20, (uint8_t * )"Reverb ", LEFT_MODE);
					break;
				case LCD_LAYOUT_CHORUS:
					BSP_LCD_DisplayStringAt(580, 20, (uint8_t * )"Chorus ", LEFT_MODE);
					break;
				case LCD_LAYOUT_DELAY:
					BSP_LCD_DisplayStringAt(580, 20, (uint8_t * )"Delay  ", LEFT_MODE);
					break;
				case LCD_LAYOUT_OVERDRIVE:
					BSP_LCD_DisplayStringAt(580, 20, (uint8_t * )"Over   ", LEFT_MODE);
					break;
				case LCD_LAYOUT_LOOP:
					BSP_LCD_DisplayStringAt(580, 20, (uint8_t * )"Loop  ", LEFT_MODE);
					break;
				default:
					break;
			}
		}
		/*---*/
		g_tLcdPreStatus.LayOutIndex = g_tLcdStatus.LayOutIndex;
		g_tLcdPreStatus.DotNavi = g_tLcdStatus.DotNavi;
		DISPLAY_FIRST_TIME_FLAG = C_ON;
	}
	
	switch (g_tLcdStatus.LayOutIndex)
	{
		case LCD_LAYOUT_REVERB:
		{
			BSP_LCD_SetFont(&Font24);
			BSP_LCD_SetBackColor(BACK_GROUND_COLOR);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			
			if(g_tLcdPreStatus.ReverbTime != g_tLcdStatus.ReverbTime || DISPLAY_FIRST_TIME_FLAG == C_ON)
			{
				
				BSP_LCD_DisplayStringAt(10, 150, (uint8_t * )"Time:   ", LEFT_MODE);
				snprintf((char *)aubDisplayData,8 , "%0.2f  ", g_tLcdStatus.ReverbTime);
				BSP_LCD_DisplayStringAt(640, 150, aubDisplayData, LEFT_MODE);
				
				Dev_LcdDrawProgressBar(125, 150, 500, 20, g_tLcdStatus.ReverbTime);
				g_tLcdPreStatus.ReverbTime = g_tLcdStatus.ReverbTime;
			}
			
			BSP_LCD_SetFont(&Font24);
			BSP_LCD_SetBackColor(BACK_GROUND_COLOR);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			
			if(g_tLcdPreStatus.ReverbWet != g_tLcdStatus.ReverbWet || DISPLAY_FIRST_TIME_FLAG == C_ON)
			{
				
				BSP_LCD_DisplayStringAt(10, 250, (uint8_t * )"Wet:   ", LEFT_MODE);
				snprintf((char *)aubDisplayData,8 , "%0.2f  ", g_tLcdStatus.ReverbWet);
				BSP_LCD_DisplayStringAt(640, 250, aubDisplayData, LEFT_MODE);
				
				Dev_LcdDrawProgressBar(125, 250, 500, 20, g_tLcdStatus.ReverbWet);
				g_tLcdPreStatus.ReverbWet = g_tLcdStatus.ReverbWet;
			}
			break;
		}
		case LCD_LAYOUT_CHORUS:
		{
			BSP_LCD_SetFont(&Font24);
			BSP_LCD_SetBackColor(BACK_GROUND_COLOR);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			
			if(g_tLcdPreStatus.ChorusOffset != g_tLcdStatus.ChorusOffset || DISPLAY_FIRST_TIME_FLAG == C_ON)
			{
				
				BSP_LCD_DisplayStringAt(10, 150, (uint8_t * )"Offset:   ", LEFT_MODE);
				snprintf((char *)aubDisplayData,8 , "%0.2f  ", g_tLcdStatus.ChorusOffset);
				BSP_LCD_DisplayStringAt(640, 150, aubDisplayData, LEFT_MODE);
				
				Dev_LcdDrawProgressBar(125, 150, 500, 20, g_tLcdStatus.ChorusOffset);
				g_tLcdPreStatus.ChorusOffset = g_tLcdStatus.ChorusOffset;
			}
			
			BSP_LCD_SetFont(&Font24);
			BSP_LCD_SetBackColor(BACK_GROUND_COLOR);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			
			if(g_tLcdPreStatus.ChorusDepth != g_tLcdStatus.ChorusDepth || DISPLAY_FIRST_TIME_FLAG == C_ON)
			{
				
				BSP_LCD_DisplayStringAt(10, 250, (uint8_t * )"Depth:   ", LEFT_MODE);
				snprintf((char *)aubDisplayData,8 , "%0.2f  ", g_tLcdStatus.ChorusDepth);
				BSP_LCD_DisplayStringAt(640, 250, aubDisplayData, LEFT_MODE);
				
				Dev_LcdDrawProgressBar(125, 250, 500, 20, g_tLcdStatus.ChorusDepth);
				g_tLcdPreStatus.ChorusDepth = g_tLcdStatus.ChorusDepth;
			}
			break;
		}
		case LCD_LAYOUT_DELAY:
		{
			BSP_LCD_SetFont(&Font24);
			BSP_LCD_SetBackColor(BACK_GROUND_COLOR);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			
			if(g_tLcdPreStatus.DelayTime != g_tLcdStatus.DelayTime || DISPLAY_FIRST_TIME_FLAG == C_ON)
			{
				
				BSP_LCD_DisplayStringAt(10, 150, (uint8_t * )"Time:   ", LEFT_MODE);
				snprintf((char *)aubDisplayData,8 , "%0.2f  ", g_tLcdStatus.DelayTime);
				BSP_LCD_DisplayStringAt(640, 150, aubDisplayData, LEFT_MODE);
				
				Dev_LcdDrawProgressBar(125, 150, 500, 20, g_tLcdStatus.DelayTime);
				
				BSP_LCD_DisplayStringAt(10, 250, (uint8_t * )"      ", LEFT_MODE);
				BSP_LCD_DisplayStringAt(640, 250, (uint8_t * )"      ", LEFT_MODE);

				BSP_LCD_SetTextColor(BACK_GROUND_COLOR);
				BSP_LCD_FillRect(125, 250, 500, 20);
				
				g_tLcdPreStatus.DelayTime = g_tLcdStatus.DelayTime;
			}
		}
		default:
			break;
	}	
	DISPLAY_FIRST_TIME_FLAG = C_OFF;
}

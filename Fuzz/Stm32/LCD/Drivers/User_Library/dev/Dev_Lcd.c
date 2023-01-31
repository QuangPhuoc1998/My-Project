#include "Dev_Lcd.h"

void Dev_LcdInit(void)
{
  uint8_t lcd_status = LCD_OK;
  
  /* LCD DSI initialization in mode Video Burst */
  /* Initialize DSI LCD */
  BSP_LCD_Init();
  while(lcd_status != LCD_OK);
  
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_BACKGROUND, LCD_FB_START_ADDRESS);
  
  /* Select the LCD Background Layer */
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_BACKGROUND);
  
  /* Clear the Background Layer */
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_FOREGROUND, LCD_BG_LAYER_ADDRESS); 
  
  /* Select the LCD Foreground Layer */
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_FOREGROUND);
  
  /* Clear the Foreground Layer */
  BSP_LCD_SetBrightness(100);
	
	BSP_LCD_Clear(BACK_GROUND_COLOR);
  
  /* Configure the transparency for foreground and background :
  Increase the transparency */
  BSP_LCD_SetTransparency(LTDC_ACTIVE_LAYER_BACKGROUND, 0);
  BSP_LCD_SetTransparency(LTDC_ACTIVE_LAYER_FOREGROUND, 100);
	
	/* Load */
	g_tLcdStatus.LayOutIndex = LCD_LAYOUT_REVERB;
	Dev_LcdDotNaviDisplay(0);
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(0,70, 800, 5);
}
void Dev_LcdDrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t RGB_Code)
{
	
}
void Dev_LcdFillScreen(void)
{

}
void Dev_LcdDotNaviDisplay(uint8_t ubDotNaviIndex)
{
	for(uint8_t i = 0 ; i < MAX_DOT_NAVI ; i++)
	{
		if(i == ubDotNaviIndex)
		{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_FillRect(20+i*110,30, 100, 20);
		}
		else
		{
			BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
			BSP_LCD_FillRect(20+i*110,30, 100, 20);
		}
	}
}

void Dev_LcdDrawProgressBar(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint16_t Percent)
{
	uint16_t ulChangePoint = ((Width/100) * Percent);
	
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(x0,y0, ulChangePoint, Height);
	
	BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
	BSP_LCD_FillRect(x0+ulChangePoint,y0, Width-ulChangePoint, Height);
}

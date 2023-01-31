#ifndef _Dev_LCD_H_
#define _Dev_LCD_H_

#include "main.h"

void Dev_LcdInit(void);
void Dev_LcdDrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t RGB_Code);
void Dev_LcdFillScreen(void);
void Dev_LcdDotNaviDisplay(uint8_t ubDotNaviIndex);
void Dev_LcdDrawProgressBar(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint16_t Percent);
#endif // _Dev_LCD_H_

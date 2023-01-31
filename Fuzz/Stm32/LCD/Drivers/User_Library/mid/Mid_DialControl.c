#include "Mid_DialControl.h"

uint8_t g_ubEncoderValue[3] = {0};
uint8_t g_ubEncoderBuffer[3][2] = {0};
uint8_t g_bMoveEncoderCount = 0;
uint8_t g_ubEncoderCount = 0;

void _DialScan(void);
void _DialClearBuffer(void);

void Mid_DialHandler(void)
{
	_DialScan();
	/*--- state 1 ---*/
	if(g_ubEncoderCount == 0)
	{
		if(g_ubEncoderValue[0] == g_ubEncoderValue[1])
		{
			g_ubEncoderBuffer[g_ubEncoderCount][0] = g_ubEncoderValue[0];
			g_ubEncoderBuffer[g_ubEncoderCount][1] = g_ubEncoderValue[1];
			g_ubEncoderCount++;
		}
	}
	else if(g_ubEncoderCount < 3)
	{
		if(g_ubEncoderBuffer[g_ubEncoderCount-1][0] != g_ubEncoderValue[0] || g_ubEncoderBuffer[g_ubEncoderCount-1][1] != g_ubEncoderValue[1])
		{
			g_ubEncoderBuffer[g_ubEncoderCount][0] = g_ubEncoderValue[0];
			g_ubEncoderBuffer[g_ubEncoderCount][1] = g_ubEncoderValue[1];
			g_ubEncoderCount++;
		}
	}
	else if(g_ubEncoderCount < 4)
	{
		if(g_ubEncoderBuffer[0][0] == 0 && g_ubEncoderBuffer[0][1] == 0)
		{
			if  ((g_ubEncoderBuffer[1][0] == 0 && g_ubEncoderBuffer[1][1] == 1)
				&& (g_ubEncoderBuffer[2][0] == 1 && g_ubEncoderBuffer[2][1] == 1))
			{
				g_ubUpDownMoveValue = DOWN;
				g_bMoveEncoderCount--;
			}
			else if ((g_ubEncoderBuffer[1][0] == 1 && g_ubEncoderBuffer[1][1] == 0)
						&& (g_ubEncoderBuffer[2][0] == 1 && g_ubEncoderBuffer[2][1] == 1))
			{
				g_ubUpDownMoveValue = UP;
				g_bMoveEncoderCount++;
			}
		}
		else if(g_ubEncoderBuffer[0][0] == 1 && g_ubEncoderBuffer[0][1] == 1)
		{
			if  ((g_ubEncoderBuffer[1][0] == 0 && g_ubEncoderBuffer[1][1] == 1)
				&& (g_ubEncoderBuffer[2][0] == 0 && g_ubEncoderBuffer[2][1] == 0))
			{
				g_ubUpDownMoveValue = UP;
				g_bMoveEncoderCount++;
			}
			else if ((g_ubEncoderBuffer[1][0] == 1 && g_ubEncoderBuffer[1][1] == 0)
						&& (g_ubEncoderBuffer[2][0] == 0 && g_ubEncoderBuffer[2][1] == 0))
			{
				g_ubUpDownMoveValue = DOWN;
				g_bMoveEncoderCount--;
			}
			else
			{
				g_ubUpDownMoveValue = NO_CHANGE;
			}
		}
		g_ubEncoderCount = 0;
		_DialClearBuffer();
		
	}
}
uint8_t Mid_DialGetDirection(void)
{
	return 0;
}


void _DialScan(void)
{
	g_ubEncoderValue[0] = DIAL_READ_CHANNEL_A;
	g_ubEncoderValue[1] = DIAL_READ_CHANNEL_B;
	g_ubEncoderValue[2] = DIAL_READ_CHANNEL_P;
	
}
void _DialClearBuffer(void)
{
	g_ubEncoderBuffer[0][0] = 0;
	g_ubEncoderBuffer[1][0] = 0;
	g_ubEncoderBuffer[2][0] = 0;
	g_ubEncoderBuffer[0][1] = 0;
	g_ubEncoderBuffer[1][1] = 0;
	g_ubEncoderBuffer[2][1] = 0;
}

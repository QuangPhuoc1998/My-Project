#ifndef _MID_DIAL_CONTROL_H_
#define _MID_DIAL_CONTROL_H_

#include "main.h"

#define DIAL_READ_CHANNEL_A HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)
#define DIAL_READ_CHANNEL_B HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)
#define DIAL_READ_CHANNEL_P HAL_GPIO_ReadPin(GPIOJ, GPIO_PIN_1)

void Mid_DialHandler(void);
uint8_t Mid_DialGetDirection(void);

#endif // _MID_DIAL_CONTROL_H_

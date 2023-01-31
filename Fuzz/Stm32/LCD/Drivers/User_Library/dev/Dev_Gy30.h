#ifndef _GY_30_H_
#define _GY_30_H_

#include "main.h"
#include "Op_Header_Main.h"
#include "i2c.h"

void Dev_Gy30Init(void);
void Dev_Gy30Handler(void);
uint16_t Dev_Gy30GetLightIntensity(void);

#endif // _GY_30_H_

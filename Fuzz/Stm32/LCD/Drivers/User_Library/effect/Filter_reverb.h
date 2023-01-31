#ifndef _FILTER_REVERB_H_
#define _FILTER_REVERB_H_

#include "main.h"

void Filter_ReverbInit(float fl_SetTime, float fl_SetWet);
float Do_Comb0(float inSample); 
float Do_Comb1(float inSample); 
float Do_Comb2(float inSample); 
float Do_Comb3(float inSample);
float Do_Allpass0(float inSample);
float Do_Allpass1(float inSample);
float Do_Allpass2(float inSample);
float Do_Reverb(float inSample) ;

#endif // _FILTER_REVERB_H_

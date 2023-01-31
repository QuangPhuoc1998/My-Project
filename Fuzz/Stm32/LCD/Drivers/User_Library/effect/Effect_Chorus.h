#ifndef _EFFECT_CHORUS_H_
#define _EFFECT_CHORUS_H_

#include "main.h"
#include <stdbool.h>

void Effect_ChorusInit(float SetOffSet, float SetDepth);
int  Effect_ChorusDelayLen(uint16_t nglob);
void Effect_ChorusProcess(int16_t *pIn, int16_t *pOut, uint16_t size, BUFFER_StateTypeDef buffterstatus);

#endif // _EFFECT_CHORUS_H_

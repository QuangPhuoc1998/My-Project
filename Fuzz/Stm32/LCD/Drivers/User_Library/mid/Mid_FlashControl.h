#ifndef _MID_FLASH_CONTROL_H_
#define _MID_FLASH_CONTROL_H_

#include "main.h"
#include "Op_HeaderFlag.h"
#include "Op_HeaderVariable.h"
#include "Op_HeaderDefine.h"

void Mid_FlashEraseProcess(void);
void Mid_FlashReadProcess(void);
void Mid_FlashWriteProcess(void);

#endif //_MID_FLASH_CONTROL_H_

#ifndef _APP_BOOTLOADER_H_
#define _APP_BOOTLOADER_H_

#include "main.h"
#include "usart.h"
#include "Op_HeaderMain.h"

void App_BootloaderInit(void);
void App_BootLoaderStart(void);
void App_BootloaderProcess(void);
void App_BootloaderJumpToUserApp(void);

#endif // _APP_BOOTLOADER_H_

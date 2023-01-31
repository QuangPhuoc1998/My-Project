#include "Mid_FileOperation.h"

char SD_Path[4]; /* SD card logical drive path */
uint8_t sector[512];
FATFS fs;
FILINFO fno;
DIR dir;
FIL F;

void Mid_FileInit(void)
{
	if(FATFS_LinkDriver(&SD_Driver, SD_Path) == 0)
  {
    /*##-3- Initialize the Directory Files pointers (heap) ###################*/
    for (uint8_t counter = 0; counter < MAX_BIN_FILE; counter++)
    {
      g_pubFileName[counter] = malloc(MAX_BIN_FILE);
      if(g_pubFileName[counter] == NULL)
      {
        /* Set the Text Color */
        BSP_LCD_SetTextColor(LCD_COLOR_RED);

        BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"  Cannot allocate memory ");
				
        SD_CARD_INIT_SUCCESS_FLAG = C_OFF;
      }
    }
		SD_CARD_INIT_SUCCESS_FLAG = C_ON;
	}
	else
	{
		SD_CARD_INIT_SUCCESS_FLAG = C_OFF;
	}
}
uint32_t Mid_FileGetSize(const char* FileName)
{
	uint32_t ulFileSize = 0;
	if(SD_CARD_INIT_SUCCESS_FLAG == C_OFF)
	{
		return 0;
	}
	if(f_open(&F, (TCHAR const*)FileName, FA_READ) != FR_OK)
	{
		return 0;
	}
	
	ulFileSize = f_size(&F);
	
	f_close (&F);
	
	return ulFileSize;
}
void Mid_FileRead(const char* FileName, uint32_t ulOffset, uint8_t * pubData, uint16_t uwDataLen)
{
	unsigned int DataLenReport = 0;
	
	if(SD_CARD_INIT_SUCCESS_FLAG == C_OFF)
	{
		return ;
	}
	if(f_open(&F, (TCHAR const*)FileName, FA_READ) != FR_OK)
	{
		return;
	}
	if(ulOffset != 0)
	{
		if(f_lseek(&F, ulOffset) != FR_OK)
		{
			return;
		}
	}
	if(f_read(&F, pubData, uwDataLen, &DataLenReport) != FR_OK)
	{
		f_close (&F);
		return;
	}
	
	f_close (&F);
}
void Mid_FileWrite(const char* FileName, uint32_t ulOffset, uint8_t * pubData, uint16_t uwDataLen)
{
	unsigned int DataLenReport = 0;
	
	if(SD_CARD_INIT_SUCCESS_FLAG == C_OFF)
	{
		return ;
	}
	if(f_open(&F, (TCHAR const*)FileName, FA_CREATE_ALWAYS | FA_READ | FA_WRITE ) != FR_OK)
	{
		return;
	}
	if(ulOffset != 0)
	{
		if(f_lseek(&F, ulOffset) != FR_OK)
		{
			return;
		}
	}
	if(f_write(&F, pubData, uwDataLen, &DataLenReport) != FR_OK)
	{
		f_close (&F);
		return;
	}
	
	f_close (&F);
}
uint8_t Mid_FileGetFindName(const char* DirName, char* Files[])
{
	FRESULT res;
  uint32_t index = 0;

	if(SD_CARD_INIT_SUCCESS_FLAG == C_OFF)
	{
		return 0;
	}
  /* Open filesystem */
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return 0;
  }

  /* Start to search for wave files */
  res = f_findfirst(&dir, &fno, DirName, "*.bin");

  /* Repeat while an item is found */
  while (fno.fname[0])
  {
    if(res == FR_OK)
    {
      if(index < MAX_BIN_FILE)
      {
        sprintf (Files[index++], "%s", fno.fname);
      }
      /* Search for next item */
      res = f_findnext(&dir, &fno);
    }
    else
    {
      index = 0;
      break;
    }
  }

  f_closedir(&dir);

  return index;
}

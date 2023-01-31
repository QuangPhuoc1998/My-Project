#ifndef _MID_FILE_OPERATION_H_
#define _MID_FILE_OPERATION_H_

#include "main.h"

void Mid_FileInit(void);
uint32_t Mid_FileGetSize(const char* FileName);
void Mid_FileRead(const char* FileName, uint32_t ulOffset, uint8_t * pubData, uint16_t uwDataLen);
void Mid_FileWrite(const char* FileName, uint32_t ulOffset, uint8_t * pubData, uint16_t uwDataLen);
uint8_t Mid_FileGetFindName(const char* DirName, char* Files[]);

#endif // _MID_FILE_OPERATION_H_

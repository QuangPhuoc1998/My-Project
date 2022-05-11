#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdint.h>
#include <QDebug>
#include <QFileDialog>

uint32_t Mid_ProcessFileCalcLen(void);
void Mid_ProcessFileOpen(void);
uint32_t Mid_ProcessFileRead(uint8_t *buffer, uint32_t len);
void Mid_ProcessFileClose(void);
uint8_t Mid_ExWordtoByte(uint32_t addr, uint8_t index);
void Mid_ProcessSetFile(QString file_name);

#endif // READ_FILE_H

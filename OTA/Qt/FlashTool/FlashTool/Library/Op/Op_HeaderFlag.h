#ifndef OP_HEADERFLAG_H
#define OP_HEADERFLAG_H

#include "iostream"
#include "Library/Op/Op_HeaderDefine.h"

#ifndef GLOBAL_DEFINE
#define HEADER_FLAG extern
#else
#define HEADER_FLAG
#endif

typedef struct
{
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
} BYTE_T;

typedef union
{
    uint8_t origin;
    BYTE_T member;
} BYTE_FIELD_T;
/*--- Flag for Serial ---*/
HEADER_FLAG BYTE_FIELD_T Flag1;
#define SERIALPORT_IS_RUNNING Flag1.member.bit0
#define SERIALPROT_IS_SELECT  Flag1.member.bit1
#define SERIALPORT_CHECK_CONNECT Flag1.member.bit2
/*--- Flag for PCube ---*/
HEADER_FLAG BYTE_FIELD_T PcubeFlag1;
#define PCUBE_RECEIVE_DONE_FLAG PcubeFlag1.member.bit0
#define PCUBE_CHECKSUM_OK				PcubeFlag1.member.bit1
#define PCUBE_CHECKSUM_ERROR		PcubeFlag1.member.bit2
#define PCUBE_RESPONSE_START		PcubeFlag1.member.bit3
#define PCUBE_WRITE_START				PcubeFlag1.member.bit4
#define PCUBE_WRITE_DONE				PcubeFlag1.member.bit5

/*--- Flag for PCube Thread ---*/
HEADER_FLAG BYTE_FIELD_T PCubeThreadFlag1;
#define PCUBE_THREAD_FLAG_STOP PCubeThreadFlag1.member.bit0
/*--- Flag fop Operation ---*/
HEADER_FLAG BYTE_FIELD_T OperationFlag1;
#define APP_PROGRAM_REQUEST OperationFlag1.member.bit0
#define APP_PROGRAM_DONE    OperationFlag1.member.bit1
#define APP_PROGRAM_STEP1_ERASE    OperationFlag1.member.bit2
#define APP_PROGRAM_STEP2_FLASH    OperationFlag1.member.bit3
#define APP_PROGRAM_STEP1_ERASE_DONE    OperationFlag1.member.bit4
#define APP_PROGRAM_STEP2_FLASH_DONE    OperationFlag1.member.bit5
#define APP_PROGRAM_TIMEOUT_FLAG         OperationFlag1.member.bit6
#define APP_PROGRAM_FIRST_INIT         OperationFlag1.member.bit7
HEADER_FLAG BYTE_FIELD_T OperationFlag2;
#define FILE_IS_CHOOSE OperationFlag2.member.bit0
#define APP_ERASE_FIRST_INIT         OperationFlag2.member.bit1

#endif // OP_HEADERFLAG_H

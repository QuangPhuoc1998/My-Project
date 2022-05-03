#ifndef OP_HEADERFLAG_H
#define OP_HEADERFLAG_H

#include "iostream"
#include "Library/Op/Op_HeaderDefine.h"

#ifndef GLOBAL_DEFINE
#define HEAER_FLAG extern
#else
#define HEAER_FLAG
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

HEAER_FLAG BYTE_FIELD_T Flag1;
#define SERIALPORT_IS_RUNNING Flag1.member.bit0
#define SERIALPROT_IS_SELECT  Flag1.member.bit1

#endif // OP_HEADERFLAG_H

#ifndef _SETUP_H_
#define _SETUP_H_

#include "def_var.h"

//Sets an optional structure alignment
#pragma pack(1)

typedef struct
{
    U08 bVersion;
    U08 bRunMode;               // mode timer/continue
    U08 bLotCount;              // lot count
    U32 lModeTimerOnTime;
    U32 lModeTimerOffTime;
    U08 bReserved[21];
} _SETUP;

void Setup_GetConfig(void);
void Setup_SetConfig(void);
void Setup_Default(void);

#endif

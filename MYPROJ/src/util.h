#ifndef UTIL_H

#include "def_var.h"

#ifdef USER_DEBUG
#include <stdio.h>
#define _dprintf(arg) printf arg
#else
#define _dprintf(arg)
#endif // USER_DEBUG


#define _GetBitBandAlias(a_pByteAddr,a_lBitNum) \
    (U32*)((((U32)(a_pByteAddr)&0xF0000000)|0x02000000) + (((U32)(a_pByteAddr)&0x000FFFFF)<<5) + ((a_lBitNum)<<2))

U32 *GetBitBandAlias(void *a_pByteAddr, U32 a_lBitNum);


void TimerDelay_Init(void);
TOF  TimerDelay(U32 a_ulDelayCnt);

#define TimerDelayUs(ulDelayUs) TimerDelay(ulDelayUs)
#define TimerDelayMs(ulDelayMs) TimerDelay((ulDelayMs)*1000UL)

void Delay(U32 a_ulDelayCnt);

#define DelayUs(ulDelayUs) Delay((ulDelayUs)*4UL)
#define DelayMs(ulDelayMs) Delay((ulDelayMs)*4000UL)

#endif // UTIL_H
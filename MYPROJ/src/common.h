#ifndef _COMMON_H_
#define _COMMON_H_

#include "gdefine.h"
#include "setup.h"

#define MAX_AVAILABLE_OUT_PORT  0x3FFF
const U16 aruPortTbl[16] =
{
    0,
    0x0001,
    0x0003,
    0x0007,
    0x000F,
    0x001F,
    0x003F,
    0x007F,
    0x00FF,
    0x01FF,
    0x03FF,
    0x07FF,
    0x0FFF,
    0x1FFF,
    0x3FFF,
    0x7FFF,
};

#endif

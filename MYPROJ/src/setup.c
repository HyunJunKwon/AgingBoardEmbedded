#include <string.h>
#include "setup.h"
#include "flash.h"

const _SETUP oSetup_Default =
{
    0xA1,       // bVersion
    0,          // bRunMode
    0,          // bLotCount
    30,         // lModeTimerOnTime
    30,         // lModeTimerOffTime
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

_SETUP stSetup;

void Setup_GetConfig(void)
{
    U08 bData[sizeof(_SETUP)];

    Flash_Read(bData, sizeof(_SETUP));

    memcpy(&stSetup, bData, sizeof(_SETUP));

    if( stSetup.bVersion != 0xA1 )
    {
        memcpy(&stSetup, &oSetup_Default, sizeof(_SETUP));
    }
}

void Setup_SetConfig(void)
{
    U08 bData[sizeof(_SETUP)];

    memcpy(bData, &stSetup, sizeof(_SETUP));

    Flash_Write(bData, sizeof(_SETUP));
}

void Setup_Default(void)
{
    memcpy(&stSetup, &oSetup_Default, sizeof(_SETUP));
    Setup_SetConfig();
}

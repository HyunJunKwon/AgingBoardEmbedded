#include <intrinsics.h>

#include "def_var.h"

void Delay(U32 a_ulDelayCnt)
{
    asm("       CBZ     R0,DelayAsm_0   \n"
        "DelayAsm_1:                    \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       NOP                     \n"
        "       SUBS    R0,R0,#+1       \n"
        "       BNE.N   DelayAsm_1      \n"
        "DelayAsm_0:                    \n"
        );
}

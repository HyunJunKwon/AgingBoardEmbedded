#ifndef _MENU_H_
#define _MENU_H_

#include "def_var.h"

#define MENU_MODE_NULL      0
#define MENU_MODE_TIMER     1

#define MENU_RUN_TIMER      0
#define MENU_RUN_CONTI      1

#define MENU_NONE           0
#define MENU_RUN            1
#define MENU_SRART          2
#define MENU_STOP           3
#define MENU_NUM_UP         4
#define MENU_NUM_DN         5
#define MENU_SHIFT_L        6
#define MENU_SHIFT_R        7

void Menu_Init(void);
U08 Menu_Run(U16 uKey);
void Menu_Mode_Display(U08 bMode);
void Menu_Run_Display(U08 bMode);

#endif

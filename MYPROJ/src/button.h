#ifndef _BTN_H_
#define _BTN_H_

#include "def_var.h"

#define BTN_CHECK_INTERVAL		20
#define SHORT_KEY_COUNT			1
#define LONG_KEY_COUNT			80

#define BTN_CLEAR				0x0000
#define BTN_MENU			    0x0001
#define BTN_UP			        0x0002
#define BTN_DOWN			    0x0004
#define BTN_STOP                0x0008
#define BTN_START               0x0010
#define BTN_RIGHT			    0x0020
#define BTN_LEFT		        0x0040
#define BTN_MODE_TIMER			0x0080
#define BTN_MODE_CONTI			0x0100

#define BTN_ALL    				(BTN_MENU | BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT | BTN_START | BTN_STOP | BTN_MODE_TIMER | BTN_MODE_CONTI)
#define BTN_LONG				0x8000

void Btn_Init(void);
void Btn_Read(void);


#endif

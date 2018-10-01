#include "def_var.h"

#define LCD_LINE1           0
#define LCD_LINE2           1
#define LCD_LINE3           2
#define LCD_LINE4           3

#define MAX_DIGIT           20

#define LCD_CMD_MODE        0x00
#define LCD_DATA_MODE       0x01

#define DIS_MODE_TIME       0
#define DIS_MODE_CNT        1
#define DIS_MODE_MAX        2

void Lcd_Init(void);
void Lcd_String(const char *strData);
void Lcd_Blink_Control(U08 bMode);
void Lcd_Send(U08 bMode, U08 bData);
void Lcd_SetLocation(U08 x, U08 y);
void Lcd_Write_CGRam(void);

void Lcd_Display_Logo();
void Lcd_Display_ProgressTime(U08 x, U08 y, U32 lValue);
void Lcd_Display_Run_OnTime(U32 lValue);
void Lcd_Display_Repeat(U32 lValue);
void Lcd_Display_LotCount(U08 x, U08 y, U32 lValue);
void Lcd_Display_RunState(U08 x, U08 y, U08 bMode);

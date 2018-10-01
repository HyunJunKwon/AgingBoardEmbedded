#include "stm32f10x_rcc.h"
#include "lcd.h"
#include "control.h"

U08 arbLcdLineAddr[4] = {0x00, 0x40, 0x14, 0x54};
U16 aruTimeIndexTbl[11][5] =
{
    // digit, line, devide, seconds, max value
    { 13, LCD_LINE2,     0,    1, 14},

    { 12, LCD_LINE3, 36000, 3600, 9 },
    { 14, LCD_LINE3,  3600,  600, 5 },
    { 15, LCD_LINE3,   600,   60, 9 },
    { 17, LCD_LINE3,    60,   10, 5 },
    { 18, LCD_LINE3,    10,    1, 9 },

    { 12, LCD_LINE4, 36000, 3600, 9 },
    { 14, LCD_LINE4,  3600,  600, 5 },
    { 15, LCD_LINE4,   600,   60, 9 },
    { 17, LCD_LINE4,    60,   10, 5 },
    { 18, LCD_LINE4,    10,    1, 9 }
};

const char arbRunState[3][8] =
{
    {0x10, 0x18, 0x1C, 0x1E, 0x1C, 0x18, 0x10, 0x00},
    {0x00, 0x12, 0x12, 0x12, 0x12, 0x12, 0x00, 0x00},
    {0x00, 0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x00, 0x00}
};

void Lcd_Send(U08 bMode, U08 bData)
{
    _LCD_RS = bMode;
    _LCD_RW = 0;
    _LCD_EN = 1;

    LCD_DATA = bData;
    DelayMs(1);
    

    _LCD_EN = 0;
    _LCD_RW = 1;
    _LCD_RS = 1;
}

void Lcd_Init(void)
{
    LCD_DATA = 0xFF;
    _LCD_EN = 0;

    DelayMs(40);

    Lcd_Send(LCD_CMD_MODE, 0x38);
    DelayMs(10);

    Lcd_Send(LCD_CMD_MODE, 0x0C);
    DelayMs(10);

    Lcd_Send(LCD_CMD_MODE, 0x01);
    DelayMs(10);

    Lcd_Send(LCD_CMD_MODE, 0x14);
    DelayMs(10);

    Lcd_Send(LCD_CMD_MODE, 0x02);
}

void Lcd_Blink_Control(U08 bMode)
{
    Lcd_Send(LCD_CMD_MODE, 0x0C | bMode);
}

void Lcd_String(const char *strData)
{
    char *pStr = 0;

    pStr = (char *)strData;
    while(*pStr != '\0')
    {
        Lcd_Send(LCD_DATA_MODE, *pStr++);
    }
}

void Lcd_SetLocation(U08 x, U08 y)
{
    U08 bAddress;
    
    bAddress = arbLcdLineAddr[y] + x;
    bAddress |= 0x80;
    Lcd_Send(LCD_CMD_MODE, bAddress);
}

void Lcd_Display_Logo()
{
    U08 i;
    
    for(i = 0; i < 20; i++)
    {
        Lcd_SetLocation(i, LCD_LINE1);
        Lcd_String("-");
        DelayMs(100);
      
    }
    for(i = 0; i < 20; i++)
    {
        Lcd_SetLocation(i, LCD_LINE2);
        Lcd_String("-");
        DelayMs(100);
      
    }
    for(i = 0; i < 20; i++)
    {
        Lcd_SetLocation(i, LCD_LINE3);
        Lcd_String("-");
        DelayMs(100);
      
    }
    for(i = 0; i < 20; i++)
    {
        Lcd_SetLocation(i, LCD_LINE4);
        Lcd_String("-");
        DelayMs(100);
      
    }

  //  for( i = 0 ; i < 80 ; i++ ) DelayMs(10);
}

void Lcd_Display_Number(U08 x, U08 y, U08 bData)
{
    Lcd_SetLocation(x, y);
    Lcd_Send(LCD_DATA_MODE, bData);
}

void Lcd_Write_CGRam(void)
{
    U08 i, j;

    Lcd_Send(LCD_CMD_MODE, 0x40);

    for( i = 0 ; i < 3 ; i++ )
    {
        for( j = 0 ; j < 8 ; j++ )
        {
            Lcd_Send(LCD_DATA_MODE, arbRunState[i][j]);
        }
    }
}

void Lcd_Display_RunState(U08 x, U08 y, U08 bMode)
{
    Lcd_SetLocation(x, y);
    Lcd_Send(LCD_DATA_MODE, bMode);
}

void Lcd_Display_ProgressTime(U08 x, U08 y, U32 lValue)
{
    U08 bData;
    U08 bIndexX;
    U08 bIndexY;

    bIndexX = x;
    bIndexY = y;

    bData = (U08)(lValue / 3600);
    Lcd_Display_Number(bIndexX + 0, bIndexY, (bData % 10) + '0');

    Lcd_Display_Number(bIndexX + 1, bIndexY, ':');

    bData = (U08)((lValue / 60) % 60);
    Lcd_Display_Number(bIndexX + 2, bIndexY, (bData / 10) + '0');
    Lcd_Display_Number(bIndexX + 3, bIndexY, (bData % 10) + '0');

    Lcd_Display_Number(bIndexX + 4, bIndexY, ':');

    bData = (U08)(lValue % 60);
    Lcd_Display_Number(bIndexX + 5, bIndexY, (bData / 10) + '0');
    Lcd_Display_Number(bIndexX + 6, bIndexY, (bData % 10) + '0');
}

void Lcd_Display_Run_OnTime(U32 lValue)
{
    U08 bData;
    U32 lData;

    lData = (U08)((lValue / 3600) % 10000);
    Lcd_Display_Number(10, LCD_LINE1, ((lData / 1000) % 10) + '0');
    Lcd_Display_Number(11, LCD_LINE1, ((lData / 100) % 10) + '0');
    Lcd_Display_Number(12, LCD_LINE1, ((lData / 10) % 10) + '0');
    Lcd_Display_Number(13, LCD_LINE1, (lData % 10) + '0');

    Lcd_Display_Number(14, LCD_LINE1, ':');

    bData = (U08)((lValue / 60) % 60);
    Lcd_Display_Number(15, LCD_LINE1, (bData / 10) + '0');
    Lcd_Display_Number(16, LCD_LINE1, (bData % 10) + '0');

    Lcd_Display_Number(17, LCD_LINE1, ':');

    bData = (U08)(lValue % 60);
    Lcd_Display_Number(18, LCD_LINE1, (bData / 10) + '0');
    Lcd_Display_Number(19, LCD_LINE1, (bData % 10) + '0');
}

void Lcd_Display_Repeat(U32 lValue)
{
    U08 bData;
    U08 bIndexX;
    U08 bIndexY;

    bIndexX = 15;
    bIndexY = LCD_LINE2;

    bData = (U08)(lValue / 10000);
    Lcd_Display_Number(bIndexX + 0, bIndexY, (bData % 10) + '0');

    bData = (U08)(lValue / 1000);
    Lcd_Display_Number(bIndexX + 1, bIndexY, (bData % 10) + '0');

    bData = (U08)(lValue / 100);
    Lcd_Display_Number(bIndexX + 2, bIndexY, (bData % 10) + '0');

    bData = (U08)(lValue / 10);
    Lcd_Display_Number(bIndexX + 3, bIndexY, (bData % 10) + '0');

    bData = (U08)(lValue / 1);
    Lcd_Display_Number(bIndexX + 4, bIndexY, (bData % 10) + '0');
}

void Lcd_Display_LotCount(U08 x, U08 y, U32 lValue)
{
    U08 bData;
    U08 bIndexX;
    U08 bIndexY;

    bIndexX = x;
    bIndexY = y;

    bData = (U08)(lValue / 10);
    Lcd_Display_Number(bIndexX + 0, bIndexY, (bData % 10) + '0');

    bData = (U08)(lValue / 1);
    Lcd_Display_Number(bIndexX + 1, bIndexY, (bData % 10) + '0');
}

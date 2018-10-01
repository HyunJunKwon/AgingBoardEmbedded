#include "menu.h"
#include "lcd.h"
#include "button.h"

U08 bMenu_on;
U08 bMenu_Index;
U08 bMenu_RunMode;

void Menu_Init(void)
{
    bMenu_on = 0;
    bMenu_Index = 0;
    bMenu_RunMode = 0;
}

void Menu_Mode_Display(U08 bMode)
{
    if( bMode == MENU_MODE_TIMER )
    {
        Lcd_SetLocation(0, LCD_LINE1);
        Lcd_String("MENU    [TIMER]     ");

        Lcd_SetLocation(0, LCD_LINE2);
        Lcd_String(" LOT NUM. = 00/14   ");

        Lcd_SetLocation(0, LCD_LINE3);
        Lcd_String("  ON TIME = 0:00:00 ");

        Lcd_SetLocation(0, LCD_LINE4);
        Lcd_String(" OFF TIME = 0:00:00 ");
    }
}

void Menu_Run_Display(U08 bMode)
{
    if( bMode == MENU_RUN_TIMER )
    {
        Lcd_SetLocation(0, LCD_LINE1);
        Lcd_String("TIMER     0000:00:00");

        Lcd_SetLocation(0, LCD_LINE2);
        Lcd_String("LOT 00  REPEAT 00000");

        Lcd_SetLocation(0, LCD_LINE3);
        Lcd_String("ON  0:00:00  0:00:00");

        Lcd_SetLocation(0, LCD_LINE4);
        Lcd_String("OFF 0:00:00  0:00:00");
    }
    else if( bMode == MENU_RUN_CONTI )
    {
        Lcd_SetLocation(0, LCD_LINE1);
        Lcd_String("ALWAYS    0000:00:00");

        Lcd_SetLocation(0, LCD_LINE2);
        Lcd_String("LOT 00  REPEAT NONE ");

        Lcd_SetLocation(0, LCD_LINE3);
        Lcd_String("                    ");

        Lcd_SetLocation(0, LCD_LINE4);
        Lcd_String("     ALWAYS ON      ");
    }
}

U08 Menu_Run(U16 uKey)
{
    if( bMenu_on == 0 )
    {
        if( uKey == BTN_MENU )
        {
            bMenu_on = true;
            bMenu_Index = 0;

            Menu_Mode_Display(MENU_MODE_TIMER);
            return MENU_SRART;
        }
    }
    else
    {
        if( uKey == BTN_MENU )
        {
            bMenu_on = false;
            bMenu_Index = 0;

            Menu_Run_Display(bMenu_RunMode);
            Lcd_Blink_Control(false);

            return MENU_STOP;
        }
        else if( uKey == BTN_LEFT )
        {
            if( bMenu_Index > 0 ) bMenu_Index--;
            else bMenu_Index = 11 - 1;
            return MENU_SHIFT_L;
        }
        else if( uKey == BTN_RIGHT )
        {
            bMenu_Index++;
            if( bMenu_Index >= 11 ) bMenu_Index = 0;
            return MENU_SHIFT_R;
        }
        else if( uKey == BTN_UP )
        {
            return MENU_NUM_UP;
        }
        else if( uKey == BTN_DOWN )
        {
            return MENU_NUM_DN;
        }
    }

    return bMenu_on;
}

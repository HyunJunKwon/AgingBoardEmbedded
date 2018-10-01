#include <stdio.h>
#include <string.h>
//#include "sys_set.h"
#include "timer.h"
#include "main.h"
#include "control.h"
#include "common.h"
//#include "iwdt.h"
#include "lcd.h"
#include "button.h"
#include "menu.h"
#include "setup.h"

U08 bModeRun;
U08 bTurnOnMode;
U32 lModeTimerOnTime;
U32 lModeTimerOffTime;
U32 lCountTimer;
U32 lOnCounter;
U32 lOffCounter;
U32 lCountRunTimer;
U08 bDisplayMode;
U08 bDisplayUpdate;
U08 bDigitValue;
U16 uPortSense;
U32 gulPreSystemTick;


extern U08 bToggle;
extern U32 gulSystemTick;
extern U16 uBtn_Press;
extern U08 bMenu_on;
extern U08 bMenu_Index;
extern U08 bMenu_RunMode;
extern U08 b1Sec;
extern _SETUP stSetup;
extern U16 aruTimeIndexTbl[11][5];


void CheckTimeProc(void)
{
    if(b1Sec)
    {
        b1Sec = 0;

        if((bMenu_on == FALSE) && (bModeRun == MODE_RUN))
        {
            lCountRunTimer++;
            Lcd_Display_Run_OnTime(lCountRunTimer);

            if(bMenu_RunMode == MENU_RUN_TIMER)
            {
                lCountTimer++;

                if(bTurnOnMode == 0)
                {
                    if(lModeTimerOnTime == lCountTimer)
                    {
                        lCountTimer = 0;

                        if(lModeTimerOffTime)
                        {
                            bTurnOnMode = 1;
                            Control_PowerOut(0);

                            lOffCounter++;
                            if(lOffCounter >= 100000) lOffCounter = 0;
                        }
                    }
                }
                else if(bTurnOnMode == 1)
                {
                    if(lModeTimerOffTime == lCountTimer)
                    {
                        bTurnOnMode = 0;
                        lCountTimer = 0;
                        Control_PowerOut(aruPortTbl[stSetup.bLotCount]);

                        lOnCounter++;
                        if( lOnCounter >= 100000) lOnCounter = 0;

                        Lcd_Display_Repeat(lOnCounter);
                    }
                }
                bDisplayUpdate = 1;
            }
        }
    }
}

void CheckDisplayProc(void)
{
    if(bDisplayUpdate)
    {
        bDisplayUpdate = 0;

        if(bModeRun != MODE_STOP)
        {
            if(bTurnOnMode == 0)
            {

                Lcd_Display_ProgressTime(13, LCD_LINE3, lModeTimerOnTime - lCountTimer);
                Lcd_Display_ProgressTime(13, LCD_LINE4, lModeTimerOffTime);
            }
            else
            {
                Lcd_Display_ProgressTime(13, LCD_LINE3, lModeTimerOnTime);
                Lcd_Display_ProgressTime(13, LCD_LINE4, lModeTimerOffTime - lCountTimer);
            }
        }
        else
        {
            Lcd_Display_ProgressTime(4, LCD_LINE3, lModeTimerOnTime);
            Lcd_Display_ProgressTime(4, LCD_LINE4, lModeTimerOffTime);
        }
    }
}

void CheckLedProc(void)
{
    if(bMenu_on == TRUE) return;

    if(bToggle)
    {
        LED_MODE_IN();

        _nSNS_OE = 0;
        uPortSense = LED_DATA_IN;
        _nSNS_OE = 1;

        uPortSense &= MAX_AVAILABLE_OUT_PORT;
        if(uPortSense == MAX_AVAILABLE_OUT_PORT)
        {
            LED_MODE_OUT();

    	    _nLEDG_WE = 0;
    	    LED_DATA_OUT = MAX_AVAILABLE_OUT_PORT;
    	    _nLEDG_WE = 1;
        }
        else
        {
            LED_MODE_OUT();

    	    _nLEDG_WE = 0;
    	    LED_DATA_OUT = uPortSense;
    	    _nLEDG_WE = 1;

            DelayMs(10);

    	    _nLEDR_WE = 0;
    	    LED_DATA_OUT = (uPortSense ^ MAX_AVAILABLE_OUT_PORT);
    	    _nLEDR_WE = 1;
        }
    }
}

void CheckButtonProc(void)
{
    U08 bRet;

    if(!(uBtn_Press & BTN_LONG))
    {
        if(uBtn_Press == BTN_MENU)
        {
            bRet = Menu_Run(uBtn_Press);
            if(bRet == MENU_SRART)
            {
                Lcd_Display_LotCount(12, LCD_LINE2, stSetup.bLotCount);
                Lcd_Display_ProgressTime(12, LCD_LINE3, stSetup.lModeTimerOnTime);
                Lcd_Display_ProgressTime(12, LCD_LINE4, stSetup.lModeTimerOffTime);

                Lcd_SetLocation(aruTimeIndexTbl[bMenu_Index][0], aruTimeIndexTbl[bMenu_Index][1]);
                Lcd_Blink_Control(TRUE);
            }
            else if(bRet == MENU_STOP)
            {
                lModeTimerOnTime = stSetup.lModeTimerOnTime;
                lModeTimerOffTime = stSetup.lModeTimerOffTime;

                Lcd_Display_Run_OnTime(lCountRunTimer);
                Lcd_Display_LotCount(4, LCD_LINE2, stSetup.bLotCount);
                Lcd_Display_RunState(7, LCD_LINE1, bModeRun);

                if(bMenu_RunMode == MENU_RUN_TIMER)
                {
                    Lcd_Display_Repeat(lOnCounter);
                    Lcd_Display_ProgressTime(4, LCD_LINE3, lModeTimerOnTime);
                    Lcd_Display_ProgressTime(4, LCD_LINE4, lModeTimerOffTime);
                    bDisplayUpdate = 1;
                }
                Setup_SetConfig();
            }
        }
        else if(uBtn_Press == BTN_UP)
        {
            if(bMenu_on == TRUE)
            {
                bRet = Menu_Run(uBtn_Press);
                if(bRet == MENU_NUM_UP)
                {
                    if( bMenu_Index < 1 )
                    {
                        bDigitValue = (U08)(stSetup.bLotCount % (aruTimeIndexTbl[bMenu_Index][4] + 1));
                        if(bDigitValue < aruTimeIndexTbl[bMenu_Index][4])
                        {
                            stSetup.bLotCount += aruTimeIndexTbl[bMenu_Index][3];
                            Lcd_Display_LotCount(12, LCD_LINE2, stSetup.bLotCount);
                        }
                    }
                    else if( bMenu_Index < 6 )
                    {
                        bDigitValue = (U08)(((stSetup.lModeTimerOnTime % aruTimeIndexTbl[bMenu_Index][2]) / aruTimeIndexTbl[bMenu_Index][3]) % 10);
                        if(bDigitValue < aruTimeIndexTbl[bMenu_Index][4])
                        {
                            stSetup.lModeTimerOnTime += aruTimeIndexTbl[bMenu_Index][3];
                            Lcd_Display_ProgressTime(12, LCD_LINE3, stSetup.lModeTimerOnTime);
                        }
                    }
                    else
                    {
                        bDigitValue = (U08)(((stSetup.lModeTimerOffTime % aruTimeIndexTbl[bMenu_Index][2]) / aruTimeIndexTbl[bMenu_Index][3]) % 10);
                        if(bDigitValue < aruTimeIndexTbl[bMenu_Index][4])
                        {
                            stSetup.lModeTimerOffTime += aruTimeIndexTbl[bMenu_Index][3];
                            Lcd_Display_ProgressTime(12, LCD_LINE4, stSetup.lModeTimerOffTime);
                        }
                    }
                    Lcd_SetLocation(aruTimeIndexTbl[bMenu_Index][0], aruTimeIndexTbl[bMenu_Index][1]);
                }
            }
        }
        else if(uBtn_Press == BTN_DOWN)
        {
            if(bMenu_on == TRUE)
            {
                bRet = Menu_Run(uBtn_Press);
                if(bRet == MENU_NUM_DN)
                {
                    if(bMenu_Index < 1)
                    {
                        bDigitValue = (U08)(stSetup.bLotCount % (aruTimeIndexTbl[bMenu_Index][4] + 1));
                        if(bDigitValue > 0)
                        {
                            stSetup.bLotCount -= aruTimeIndexTbl[bMenu_Index][3];
                            Lcd_Display_LotCount(12, LCD_LINE2, stSetup.bLotCount);
                        }
                    }
                    else if(bMenu_Index < 6)
                    {
                        bDigitValue = (U08)(((stSetup.lModeTimerOnTime % aruTimeIndexTbl[bMenu_Index][2]) / aruTimeIndexTbl[bMenu_Index][3]) % 10);
                        if(bDigitValue > 0)
                        {
                            stSetup.lModeTimerOnTime -= aruTimeIndexTbl[bMenu_Index][3];
                            Lcd_Display_ProgressTime(12, LCD_LINE3, stSetup.lModeTimerOnTime);
                        }
                    }
                    else
                    {
                        bDigitValue = (U08)(((stSetup.lModeTimerOffTime % aruTimeIndexTbl[bMenu_Index][2]) / aruTimeIndexTbl[bMenu_Index][3]) % 10);
                        if(bDigitValue > 0)
                        {
                            stSetup.lModeTimerOffTime -= aruTimeIndexTbl[bMenu_Index][3];
                            Lcd_Display_ProgressTime(12, LCD_LINE4, stSetup.lModeTimerOffTime);
                        }
                    }
                    Lcd_SetLocation(aruTimeIndexTbl[bMenu_Index][0], aruTimeIndexTbl[bMenu_Index][1]);
                }
            }
        }
        else if(uBtn_Press == BTN_LEFT)
        {
            if(bMenu_on == TRUE)
            {
                bRet = Menu_Run(uBtn_Press);
                Lcd_SetLocation(aruTimeIndexTbl[bMenu_Index][0], aruTimeIndexTbl[bMenu_Index][1]);
            }
        }
        else if(uBtn_Press == BTN_RIGHT)
        {
            if(bMenu_on == TRUE)
            {
                bRet = Menu_Run(uBtn_Press);
                Lcd_SetLocation(aruTimeIndexTbl[bMenu_Index][0], aruTimeIndexTbl[bMenu_Index][1]);
            }
        }
        else if(uBtn_Press == BTN_START)
        {
            if(bMenu_on == FALSE)
            {
                if(bModeRun == MODE_STOP)
                {
                    lOnCounter = 0;
                    lOffCounter = 0;
                    lCountRunTimer = 0;
                    Lcd_Display_Run_OnTime(lCountRunTimer);

                    if(bMenu_RunMode == MENU_RUN_TIMER)
                    {
                        if(lModeTimerOnTime)
                        {
                            Control_PowerOut(aruPortTbl[stSetup.bLotCount]);
                            lOnCounter++;

                            Lcd_Display_Repeat(lOnCounter);
                            bModeRun = MODE_RUN;
                        }
                    }
                    else
                    {
                        Control_PowerOut(aruPortTbl[stSetup.bLotCount]);
                        bModeRun = MODE_RUN;
                    }
                }
                else if(bModeRun == MODE_RUN)
                {
                    bModeRun = MODE_PAUSE;
                }
                else if(bModeRun == MODE_PAUSE)
                {
                    bModeRun = MODE_RUN;
                }
                Lcd_Display_RunState(7, LCD_LINE1, bModeRun);
            }
        }
        else if(uBtn_Press == BTN_STOP)
        {
            if(bMenu_on == FALSE)
            {
                if(bModeRun != MODE_STOP)
                {
                    bModeRun = MODE_STOP;
                    Lcd_Display_RunState(7, LCD_LINE1, bModeRun);

                    lCountTimer = 0;
                    lOnCounter = 0;
                    lOffCounter = 0;

                    Lcd_Display_Run_OnTime(lCountRunTimer);
                    Lcd_Display_Repeat(lOnCounter);

                    if(bMenu_RunMode == MENU_RUN_TIMER)
                    {
                        Lcd_Display_ProgressTime(4, LCD_LINE3, stSetup.lModeTimerOnTime);
                        Lcd_Display_ProgressTime(13, LCD_LINE3, 0);
                        Lcd_Display_ProgressTime(4, LCD_LINE4, stSetup.lModeTimerOffTime);
                        Lcd_Display_ProgressTime(13, LCD_LINE4, 0);
                    }
                    Control_PowerOut(0);
                }
            }
        }
        else if(uBtn_Press == BTN_MODE_TIMER)
        {
            if(bMenu_on == FALSE)
            {
                if(bModeRun != MODE_RUN)
                {
                    if(bMenu_RunMode != MENU_RUN_TIMER)
                    {
                        bMenu_RunMode = MENU_RUN_TIMER;
                        Menu_Run_Display(bMenu_RunMode);

                        bModeRun = MODE_STOP;
                        Lcd_Display_RunState(7, LCD_LINE1, bModeRun);

                        lCountTimer = 0;
                        lOnCounter = 0;
                        lOffCounter = 0;

                        Lcd_Display_Run_OnTime(lCountRunTimer);
                        Lcd_Display_Repeat(lOnCounter);
                        Lcd_Display_LotCount(4, LCD_LINE2, stSetup.bLotCount);

                        if(bMenu_RunMode == MENU_RUN_TIMER)
                        {
                            Lcd_Display_ProgressTime(4, LCD_LINE3, stSetup.lModeTimerOnTime);
                            Lcd_Display_ProgressTime(13, LCD_LINE3, 0);
                            Lcd_Display_ProgressTime(4, LCD_LINE4, stSetup.lModeTimerOffTime);
                            Lcd_Display_ProgressTime(13, LCD_LINE4, 0);
                        }
                    }
                }
            }
        }
        else if(uBtn_Press == BTN_MODE_CONTI)
        {
            if(bMenu_on == FALSE)
            {
                if(bModeRun != MODE_RUN)
                {
                    if(bMenu_RunMode != MENU_RUN_CONTI)
                    {
                        bMenu_RunMode = MENU_RUN_CONTI;
                        Menu_Run_Display(bMenu_RunMode);

                        bModeRun = MODE_STOP;
                        Lcd_Display_RunState(7, LCD_LINE1, bModeRun);

                        lCountTimer = 0;
                        lOnCounter = 0;
                        lOffCounter = 0;

                        Lcd_Display_Run_OnTime(lCountRunTimer);
                        Lcd_Display_LotCount(4, LCD_LINE2, stSetup.bLotCount);
                    }
                }
            }
        }
        uBtn_Press = BTN_CLEAR;
    }
}

int main(void)
{
   // U32 gulPreSystemTick;

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x8000);

	Gpio_Init();
    TIM2_Init();
    Lcd_Init();
    Btn_Init();
    Lcd_Write_CGRam();

    Lcd_Display_Logo();
       
    //Setup_Default();
    //Setup_SetConfig();
    Setup_GetConfig();

    lModeTimerOnTime = stSetup.lModeTimerOnTime;
    lModeTimerOffTime = stSetup.lModeTimerOffTime;
    lCountTimer = 0;
    lOnCounter = 0;
    lOffCounter = 0;
    lCountRunTimer = 0;

    bModeRun = 0;
    bTurnOnMode = 0;
    bDisplayMode = 0;
    bDisplayUpdate = 0;
    bDigitValue = 0;

    Menu_Init();

    bMenu_RunMode = MENU_RUN_TIMER;
    Menu_Run_Display(bMenu_RunMode);

    Lcd_Display_RunState(7, LCD_LINE1, bModeRun);
    Lcd_Display_Run_OnTime(lCountRunTimer);
    Lcd_Display_Repeat(lOnCounter);
    Lcd_Display_LotCount(4, LCD_LINE2, stSetup.bLotCount);

    if( bMenu_RunMode == MENU_RUN_TIMER )
    {
        Lcd_Display_ProgressTime(4, LCD_LINE3, lModeTimerOnTime);
        Lcd_Display_ProgressTime(13, LCD_LINE3, 0);
        Lcd_Display_ProgressTime(4, LCD_LINE4, lModeTimerOffTime);
        Lcd_Display_ProgressTime(13, LCD_LINE4, 0);
    }

    while(true)
    {
        gulPreSystemTick = gulSystemTick;
    	IWDG_ReloadCounter();
		Btn_Read();
        CheckButtonProc();
        CheckTimeProc();
        CheckDisplayProc();
		CheckLedProc();

        while(gulPreSystemTick == gulSystemTick);
    }
}

#ifndef _LED_H_
#define _LED_H_


#include "common.h"

////U16 uPortSense;
////U08 arbLcdLineAddr[4] = {0x00, 0x40, 0x14, 0x54};
//U08 lcdLineAddrTbl[4] = {0x00, 0x40, 0x14, 0x54};
////U16 aruTimeIndexTbl[11][5] =
////{
////    // digit, line, devide, seconds, max value
////    { 13, LCD_LINE2,     0,    1, 14},
////
////    { 12, LCD_LINE3, 36000, 3600, 9 },
////    { 14, LCD_LINE3,  3600,  600, 5 },
////    { 15, LCD_LINE3,   600,   60, 9 },
////    { 17, LCD_LINE3,    60,   10, 5 },
////    { 18, LCD_LINE3,    10,    1, 9 },
////
////    { 12, LCD_LINE4, 36000, 3600, 9 },
////    { 14, LCD_LINE4,  3600,  600, 5 },
////    { 15, LCD_LINE4,   600,   60, 9 },
////    { 17, LCD_LINE4,    60,   10, 5 },
////    { 18, LCD_LINE4,    10,    1, 9 }
////};
//U16 LcdTimeIndexTbl[11][5] =
//{
//    // digit, line, devide, seconds, max value
//    { 13, LCD_LINE2,     0,    1, 14},
//
//    { 12, LCD_LINE3, 36000, 3600, 9 },
//    { 14, LCD_LINE3,  3600,  600, 5 },
//    { 15, LCD_LINE3,   600,   60, 9 },
//    { 17, LCD_LINE3,    60,   10, 5 },
//    { 18, LCD_LINE3,    10,    1, 9 },
//
//    { 12, LCD_LINE4, 36000, 3600, 9 },
//    { 14, LCD_LINE4,  3600,  600, 5 },
//    { 15, LCD_LINE4,   600,   60, 9 },
//    { 17, LCD_LINE4,    60,   10, 5 },
//    { 18, LCD_LINE4,    10,    1, 9 }
//};
////const char arbRunState[3][8] =
////{
////    {0x00, 0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x00, 0x00},     // stop     address = 0x00
////    {0x10, 0x18, 0x1C, 0x1E, 0x1C, 0x18, 0x10, 0x00},     // play     address = 0x01
////    {0x00, 0x12, 0x12, 0x12, 0x12, 0x12, 0x00, 0x00}      // pause    address = 0x02
////};
//const char bRunStateChar[3][8] = 
//{
//    {0x10, 0x18, 0x1C, 0x1E, 0x1C, 0x18, 0x10, 0x00},     // play     address = 0x00
//    {0x00, 0x12, 0x12, 0x12, 0x12, 0x12, 0x00, 0x00},      // pause    address = 0x01
//    {0x00, 0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x00, 0x00}     // stop     address = 0x02
//};
//
////void Lcd_Send(U08 bMode, U08 bData)
////{
////    // 8-bit
////    _LCD_RS = bMode; // LCD SETTING SIGNAL 0: CMD, 1: DATA
////    _LCD_RW = 0; // 0: WRITE, 1: READ
////    _LCD_EN = 1; // ENABLE
////
////    LCD_DATA = bData;
////    DelayMs(1);
////
////    _LCD_EN = 0;
////    _LCD_RW = 1;
////    _LCD_RS = 1;
////}

//U08 bModeRun; // bRunModeChar delete
//extern U08 bRunModeChar;
//extern U08 bTurnOnMode;
////U08 bDisplayMode;
//extern U08 bDisplayUpdate;
//U08 bDigitValue;
////U16 uPortSense;
//extern U32 lModeTimerOnTime;
//extern U32 lModeTimerOffTime;
//extern U32 lCountTimer;
//U32 lRepeatCounter;
//U32 lOffCounter;
//U32 lTimeCounter;
//extern U08 bMenu_on;
//extern U08 bToggle;

void CheckLedProc(void);


#endif
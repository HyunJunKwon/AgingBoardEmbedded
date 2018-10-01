#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "gpio.h"
#include "util.h"
#include "gdefine.h"

/////////////////////////////////////////////////////////////
// PORTA

/////////////////////////////////////////////////////////////
// PORTB
#define nLEDG_WE            (_PB+_PIN00)
#define nLEDR_WE            (_PB+_PIN01)
#define BUZZER              (_PB+_PIN05)
#define nSNS_OE             (_PB+_PIN06)
#define LCD_EN              (_PB+_PIN07)
#define LCD_RW              (_PB+_PIN08)
#define LCD_RS              (_PB+_PIN09)
#define LED1                (_PB+_PIN10)
#define LED2                (_PB+_PIN11)
#define nDRV_WE             (_PB+_PIN12)

#define _nLEDG_WE           *_GetBitBandAlias(&GPIOB->ODR, 0)
#define _nLEDR_WE           *_GetBitBandAlias(&GPIOB->ODR, 1)
#define _BUZZER             *_GetBitBandAlias(&GPIOB->ODR, 5)
#define _nSNS_OE            *_GetBitBandAlias(&GPIOB->ODR, 6)
#define _LCD_EN             *_GetBitBandAlias(&GPIOB->ODR, 7)
#define _LCD_RW             *_GetBitBandAlias(&GPIOB->ODR, 8)
#define _LCD_RS             *_GetBitBandAlias(&GPIOB->ODR, 9)
#define _LED1               *_GetBitBandAlias(&GPIOB->ODR, 10)
#define _LED2               *_GetBitBandAlias(&GPIOB->ODR, 11)
#define _nDRV_WE            *_GetBitBandAlias(&GPIOB->ODR, 12)

/////////////////////////////////////////////////////////////
// PORTC
#define KEY_MENU            (_PC+_PIN00)
#define KEY_UP              (_PC+_PIN01)
#define KEY_DOWN            (_PC+_PIN02)
#define KEY_STOP            (_PC+_PIN03)
#define KEY_START           (_PC+_PIN04)
#define KEY_RIGHT           (_PC+_PIN05)
#define KEY_LEFT            (_PC+_PIN06)
#define KEY_TIMER           (_PC+_PIN07)
#define KEY_CONTI           (_PC+_PIN08)

#define _KEY_MENU           *_GetBitBandAlias(&GPIOC->IDR, 0)
#define _KEY_UP             *_GetBitBandAlias(&GPIOC->IDR, 1)
#define _KEY_DOWN           *_GetBitBandAlias(&GPIOC->IDR, 2)
#define _KEY_STOP           *_GetBitBandAlias(&GPIOC->IDR, 3)
#define _KEY_START          *_GetBitBandAlias(&GPIOC->IDR, 4)
#define _KEY_RIGHT          *_GetBitBandAlias(&GPIOC->IDR, 5)
#define _KEY_LEFT           *_GetBitBandAlias(&GPIOC->IDR, 6)
#define _KEY_TIMER          *_GetBitBandAlias(&GPIOC->IDR, 7)
#define _KEY_CONTI          *_GetBitBandAlias(&GPIOC->IDR, 8)

#define KEY_DATA_IN()       GPIOC->IDR

/////////////////////////////////////////////////////////////
// PORTD
#define LCD_D0              (_PD+_PIN00)
#define LCD_D1              (_PD+_PIN01)
#define LCD_D2              (_PD+_PIN02)
#define LCD_D3              (_PD+_PIN03)
#define LCD_D4              (_PD+_PIN04)
#define LCD_D5              (_PD+_PIN05)
#define LCD_D6              (_PD+_PIN06)
#define LCD_D7              (_PD+_PIN07)

#define _LCD_D0             *_GetBitBandAlias(&GPIOD->ODR, 0)
#define _LCD_D1             *_GetBitBandAlias(&GPIOD->ODR, 1)
#define _LCD_D2             *_GetBitBandAlias(&GPIOD->ODR, 2)
#define _LCD_D3             *_GetBitBandAlias(&GPIOD->ODR, 3)
#define _LCD_D4             *_GetBitBandAlias(&GPIOD->ODR, 4)
#define _LCD_D5             *_GetBitBandAlias(&GPIOD->ODR, 5)
#define _LCD_D6             *_GetBitBandAlias(&GPIOD->ODR, 6)
#define _LCD_D7             *_GetBitBandAlias(&GPIOD->ODR, 7)

#define LCD_DATA            GPIOD->ODR

/////////////////////////////////////////////////////////////
// PORTE
#define LED_DATA_D00        (_PE+_PIN00)
#define LED_DATA_D01        (_PE+_PIN01)
#define LED_DATA_D02        (_PE+_PIN02)
#define LED_DATA_D03        (_PE+_PIN03)
#define LED_DATA_D04        (_PE+_PIN04)
#define LED_DATA_D05        (_PE+_PIN05)
#define LED_DATA_D06        (_PE+_PIN06)
#define LED_DATA_D07        (_PE+_PIN07)
#define LED_DATA_D08        (_PE+_PIN08)
#define LED_DATA_D09        (_PE+_PIN09)
#define LED_DATA_D10        (_PE+_PIN10)
#define LED_DATA_D11        (_PE+_PIN11)
#define LED_DATA_D12        (_PE+_PIN12)
#define LED_DATA_D13        (_PE+_PIN13)


#define _LED_DATA_D00       *_GetBitBandAlias(&GPIOE->ODR, 0)
#define _LED_DATA_D01       *_GetBitBandAlias(&GPIOE->ODR, 1)
#define _LED_DATA_D02       *_GetBitBandAlias(&GPIOE->ODR, 2)
#define _LED_DATA_D03       *_GetBitBandAlias(&GPIOE->ODR, 3)
#define _LED_DATA_D04       *_GetBitBandAlias(&GPIOE->ODR, 4)
#define _LED_DATA_D05       *_GetBitBandAlias(&GPIOE->ODR, 5)
#define _LED_DATA_D06       *_GetBitBandAlias(&GPIOE->ODR, 6)
#define _LED_DATA_D07       *_GetBitBandAlias(&GPIOE->ODR, 7)
#define _LED_DATA_D08       *_GetBitBandAlias(&GPIOE->ODR, 8)
#define _LED_DATA_D09       *_GetBitBandAlias(&GPIOE->ODR, 9)
#define _LED_DATA_D10       *_GetBitBandAlias(&GPIOE->ODR, 10)
#define _LED_DATA_D11       *_GetBitBandAlias(&GPIOE->ODR, 11)
#define _LED_DATA_D12       *_GetBitBandAlias(&GPIOE->ODR, 12)
#define _LED_DATA_D13       *_GetBitBandAlias(&GPIOE->ODR, 13)

#define LED_MODE_OUT()      GPIOE->CRH = 0x00333333; GPIOE->CRL = 0x33333333    // Set to general purpose output push-pull
#define LED_MODE_IN()       GPIOE->CRH = 0x00444444; GPIOE->CRL = 0x44444444    // Set to floating input

#define LED_DATA_OUT        GPIOE->ODR
#define LED_DATA_IN         GPIOE->IDR


void Gpio_Init(void);
void Control_PowerOut(U16 uData);

#endif


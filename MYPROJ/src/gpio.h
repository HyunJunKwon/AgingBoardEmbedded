#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f10x_gpio.h"
#include "def_var.h"

#define _PA     (0ul<<16)
#define _PB     (1ul<<16)
#define _PC     (2ul<<16)
#define _PD     (3ul<<16)
#define _PE     (4ul<<16)
#define _PF     (5ul<<16)
#define _PG     (6ul<<16)

#define _PIN00  (0x00000001<< 0)
#define _PIN01  (0x00000001<< 1)
#define _PIN02  (0x00000001<< 2)
#define _PIN03  (0x00000001<< 3)
#define _PIN04  (0x00000001<< 4)
#define _PIN05  (0x00000001<< 5)
#define _PIN06  (0x00000001<< 6)
#define _PIN07  (0x00000001<< 7)
#define _PIN08  (0x00000001<< 8)
#define _PIN09  (0x00000001<< 9)
#define _PIN10  (0x00000001<<10)
#define _PIN11  (0x00000001<<11)
#define _PIN12  (0x00000001<<12)
#define _PIN13  (0x00000001<<13)
#define _PIN14  (0x00000001<<14)
#define _PIN15  (0x00000001<<15)

#define _GPIO_GetPort(PORT_PIN) ((PORT_PIN)>>16)
#define _GPIO_GetPin(PORT_PIN)  ((PORT_PIN)&0x0000FFFF)

extern GPIO_TypeDef* const arpGpioPort    [7];
extern U32           const arlGpioApbClock[7];

#define _GPIO_Pin_On(PORT_PIN) \
            arpGpioPort[_GPIO_GetPort(PORT_PIN)]->BSRR = _GPIO_GetPin(PORT_PIN)

#define _GPIO_Pin_Off(PORT_PIN) \
            arpGpioPort[_GPIO_GetPort(PORT_PIN)]->BRR = _GPIO_GetPin(PORT_PIN)

#define _GPIO_Pin_Toggle(PORT_PIN) \
            arpGpioPort[_GPIO_GetPort(PORT_PIN)]->ODR ^= _GPIO_GetPin(PORT_PIN)


#endif // _GPIO_H
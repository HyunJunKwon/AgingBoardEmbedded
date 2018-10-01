#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "def_var.h"
#include "gpio.h"

GPIO_TypeDef* const arpGpioPort[7] =
{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG
};

U32 const arlGpioApbClock[7] =
{
    RCC_APB2Periph_GPIOA,
    RCC_APB2Periph_GPIOB,
    RCC_APB2Periph_GPIOC,
    RCC_APB2Periph_GPIOD,
    RCC_APB2Periph_GPIOE,
    RCC_APB2Periph_GPIOF,
    RCC_APB2Periph_GPIOG
};

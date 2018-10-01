#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "timer.h"
#include "control.h"

U08 b1Sec;
U08 bToggle;
U32 gulSystemTick;

//
// 10ms interval
//
void TIM2_IRQHandler(void)
{
	gulSystemTick += 10;

	if( (gulSystemTick % 500) == 0 )
	{
	    bToggle ^= 0x01;
	}

    if( (gulSystemTick % 1000) == 0 )
    {
        b1Sec = 1;
    }

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void TIM2_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

    b1Sec = 0;
    bToggle = 0;
	gulSystemTick = 0;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Time base configuration
	//72MHz / 7200(Prescaler) / 100(Period) = 100Hz = 10ms
	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

#if 0
	//72MHz / 7200(Prescaler) / 40(Period) = 200Hz = 4ms
	TIM_TimeBaseStructure.TIM_Period = 39;
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
#endif

#if 0
	//72MHz / 7200(Prescaler) / 50(Period) = 200Hz = 5ms
	TIM_TimeBaseStructure.TIM_Period = 49;
	// Enable the TIM2 gloabal Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

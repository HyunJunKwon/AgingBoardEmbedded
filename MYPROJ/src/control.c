#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "control.h"

typedef struct
{
    U32 lPortPin;
    GPIOMode_TypeDef iMode;
} GPIO_MODE_SET;


static GPIO_MODE_SET const arCtrlPortPin[] =
{
    // PORTA

    // PORTB
	{nLEDG_WE,	            GPIO_Mode_Out_PP},
	{nLEDR_WE,	            GPIO_Mode_Out_PP},
	{BUZZER,	            GPIO_Mode_Out_PP},
	{nSNS_OE,	            GPIO_Mode_Out_PP},
	{LCD_EN,	            GPIO_Mode_Out_PP},
	{LCD_RW,	            GPIO_Mode_Out_PP},
	{LCD_RS,	            GPIO_Mode_Out_PP},
	{LED1,	                GPIO_Mode_Out_PP},
	{LED2,	                GPIO_Mode_Out_PP},
	{nDRV_WE,	            GPIO_Mode_Out_PP},

    // PORTC
    {KEY_MENU,              GPIO_Mode_IN_FLOATING},
    {KEY_UP,                GPIO_Mode_IN_FLOATING},
    {KEY_DOWN,              GPIO_Mode_IN_FLOATING},
    {KEY_STOP,              GPIO_Mode_IN_FLOATING},
    {KEY_START,             GPIO_Mode_IN_FLOATING},
    {KEY_RIGHT,             GPIO_Mode_IN_FLOATING},
    {KEY_LEFT,              GPIO_Mode_IN_FLOATING},
    {KEY_TIMER,             GPIO_Mode_IN_FLOATING},
    {KEY_CONTI,             GPIO_Mode_IN_FLOATING},

    // PORTD
    {LCD_D0,	            GPIO_Mode_Out_PP},
    {LCD_D1,	            GPIO_Mode_Out_PP},
    {LCD_D2,	            GPIO_Mode_Out_PP},
    {LCD_D3,	            GPIO_Mode_Out_PP},
    {LCD_D4,	            GPIO_Mode_Out_PP},
    {LCD_D5,	            GPIO_Mode_Out_PP},
    {LCD_D6,	            GPIO_Mode_Out_PP},
    {LCD_D7,	            GPIO_Mode_Out_PP},

    // PORTE
    {LED_DATA_D00,	        GPIO_Mode_Out_PP},
    {LED_DATA_D01,	        GPIO_Mode_Out_PP},
    {LED_DATA_D02,	        GPIO_Mode_Out_PP},
    {LED_DATA_D03,	        GPIO_Mode_Out_PP},
    {LED_DATA_D04,	        GPIO_Mode_Out_PP},
    {LED_DATA_D05,	        GPIO_Mode_Out_PP},
    {LED_DATA_D06,	        GPIO_Mode_Out_PP},
    {LED_DATA_D07,	        GPIO_Mode_Out_PP},
    {LED_DATA_D08,	        GPIO_Mode_Out_PP},
    {LED_DATA_D09,	        GPIO_Mode_Out_PP},
    {LED_DATA_D10,	        GPIO_Mode_Out_PP},
    {LED_DATA_D11,	        GPIO_Mode_Out_PP},
    {LED_DATA_D12,	        GPIO_Mode_Out_PP},
    {LED_DATA_D13,	        GPIO_Mode_Out_PP}
};

void Gpio_Init(void)
{
    S16 nPin;
    U32 lPortPin;
    GPIO_InitTypeDef  GPIO_InitStructure;

    for( nPin = 0 ; nPin < sizeof(arCtrlPortPin)/sizeof(arCtrlPortPin[0]) ; nPin++ )
    {
        lPortPin = arCtrlPortPin[nPin].lPortPin;

		// Enable the control port Clock
        RCC_APB2PeriphClockCmd(arlGpioApbClock[_GPIO_GetPort(lPortPin)], ENABLE);

		// Configure the control port pin
        GPIO_InitStructure.GPIO_Pin   = _GPIO_GetPin(lPortPin);
        GPIO_InitStructure.GPIO_Mode  = arCtrlPortPin[nPin].iMode;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_Init(arpGpioPort[_GPIO_GetPort(lPortPin)], &GPIO_InitStructure);
    }

    _nLEDG_WE = 1;
    _nLEDR_WE = 1;
    _nSNS_OE = 1;
    _nDRV_WE = 1;

    _BUZZER = 0;

    _LCD_EN = 0;
    _LCD_RW = 0;
    _LCD_RS = 0;

    _LED1 = 0;
    _LED2 = 0;

    LCD_DATA = 0;
    LED_DATA_OUT = 0;

}

void Control_PowerOut(U16 uData)
{
    LED_MODE_OUT();

    _nDRV_WE = 0;
    LED_DATA_OUT = uData;
    _nDRV_WE = 1;
}

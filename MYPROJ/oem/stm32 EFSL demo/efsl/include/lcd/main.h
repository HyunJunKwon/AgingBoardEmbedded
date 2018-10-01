/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.h
* Author             : MCD Application Team
* Version            : V1.0
* Date               : xx/xx/2008
* Description        : Header for main.c module
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32f10x_it.h"
#include "lcd.h"
#include "spi_flash.h"


/* Exported types ------------------------------------------------------------*/

typedef struct
{
  u32 F_Size;
  char F_Name[60];

}F_Numx;

 typedef struct
 { char D_Name [60];
 }D_Numx;






/* Exported constants --------------------------------------------------------*/
#define USE_USART1
//#define USE_USART2
//#define USE_USART3

#ifdef USE_USART1
  #define  USARTy                   USART1
  #define  GPIOy                    GPIOA
  #define  RCC_APB2Periph_GPIOy     RCC_APB2Periph_GPIOA
  #define  GPIO_RyPin               GPIO_Pin_10
  #define  GPIO_TyPin               GPIO_Pin_9
#elif defined USE_USART2
  #define  USARTy                   USART2
  #define  GPIOy                    GPIOD
  #define  RCC_APB2Periph_GPIOy     RCC_APB2Periph_GPIOD
  #define  RCC_APB1Periph_USARTy    RCC_APB1Periph_USART2
  #define  GPIO_RyPin               GPIO_Pin_6
  #define  GPIO_TyPin               GPIO_Pin_5
#elif defined USE_USART3
  #define  USARTy                   USART3
  #define  GPIOy                    GPIOB
  #define  RCC_APB2Periph_GPIOy     RCC_APB2Periph_GPIOB
  #define  RCC_APB1Periph_USARTy    RCC_APB1Periph_USART3
  #define  GPIO_RyPin               GPIO_Pin_11
  #define  GPIO_TyPin               GPIO_Pin_10
#endif 

#define  FRAME_ENC_SIZE 20     // @8kbps
#define  FRAME_DEC_SIZE 160    // @8kbps	
#define  NB_WAV_BUFFERS 2
#define  BUSY			0
#define  FREE           1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Demo_Init(void);
void InterruptConfig(void);
void GPIO_Config(void);
void SysTick_Config(void);
void Decrement_TimingDelay(void);
void Delay(u32 nCount);
void IntExtOnOffConfig(FunctionalState NewState);
ErrorStatus Get_HSEStartUpStatus(void);



#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

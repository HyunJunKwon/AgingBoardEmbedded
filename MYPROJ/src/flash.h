#ifndef _FLASH_H_
#define _FLASH_H_

#include "def_var.h"

#define FLASH_START_ADDR        0x08007800

// Define the STM32F10x FLASH Page Size depending on the used STM32 device
#ifdef STM32F10X_LD_VL
  #define FLASH_PAGE_SIZE    	((uint16_t)0x400)
#elif defined STM32F10X_LD
  #define FLASH_PAGE_SIZE    	((uint16_t)0x400)
#elif defined STM32F10X_MD_VL
  #define FLASH_PAGE_SIZE    	((uint16_t)0x400)
#elif defined STM32F10X_MD
  #define FLASH_PAGE_SIZE    	((uint16_t)0x400)
#elif defined STM32F10X_HD
  #define FLASH_PAGE_SIZE    	((uint16_t)0x800)
#elif defined STM32F10X_CL
  #define FLASH_PAGE_SIZE    	((uint16_t)0x800)       // 2KB
#endif

void Flash_Write(U08 *pbBuf, U16 uLen);
void Flash_Read(U08 *pbBuf, U16 uLen);

#endif

#include "stm32f10x_flash.h"
#include "flash.h"

volatile FLASH_Status FLASHStatus;

U08 Flash_Erase(void)
{
	FLASHStatus = FLASH_COMPLETE;

	FLASH_Unlock();

	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

	FLASHStatus = FLASH_ErasePage(FLASH_START_ADDR);
	if( FLASHStatus == FLASH_COMPLETE )
	{
	    return TRUE;
	}

	return FALSE;
}

void Flash_Write(U08 *pbBuf, U16 uLen)
{
    U16 i;
    U16 uLoop;
    U32 *pFlashBuf;
    U32 ulCodeData;
    U32 ulAddress;

    if( Flash_Erase() == TRUE )
    {
        ulAddress = FLASH_START_ADDR;
        pFlashBuf = (U32 *)pbBuf;

        uLoop = uLen >> 2;
        for( i = 0 ; i < uLoop ; i++ )
        {
            ulCodeData = pFlashBuf[i];
            FLASHStatus = FLASH_ProgramWord(ulAddress, ulCodeData);
            ulAddress += 4;
        }
    }
}

void Flash_Read(U08 *pbBuf, U16 uLen)
{
    U16 i;
    U16 uLoop;
    U32 *pFlashBuf;
    U32 ulAddress;
    
	FLASH_Unlock();

    ulAddress = FLASH_START_ADDR;
    pFlashBuf = (U32 *)pbBuf;

    uLoop = uLen >> 2;
    for( i = 0 ; i < uLoop ; i++ )
    {
        *(pFlashBuf + i) = (*(__IO uint32_t*)ulAddress);
        ulAddress += 4;
    }
}

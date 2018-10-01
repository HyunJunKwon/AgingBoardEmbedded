#include "led.h"

void CheckLedProc(void)
{
    if( bMenu_on == TRUE ) return;

    if( bToggle )
    {
        LED_MODE_IN();

        _nSNS_OE = 0;
        uPortSense = LED_DATA_IN;
        _nSNS_OE = 1;

        uPortSense &= MAX_AVAILABLE_OUT_PORT;
        if( uPortSense == MAX_AVAILABLE_OUT_PORT )
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
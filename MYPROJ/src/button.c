#include "button.h"
#include "control.h"

U16 uBtn_State;
U16 uBtn_Press;
U16 uKey_Input;
U16 uCount_Key;
U16 uApply_Key;

U16 Btn_Port(void)
{
	U16 uKeyData;

	uKeyData = KEY_DATA_IN();
	uKeyData = ~uKeyData;
	uKeyData &= BTN_ALL;

	return uKeyData;
}

void Btn_Init(void)
{
	Btn_Read();

	uBtn_State = 0;
	uBtn_Press = 0;
	uKey_Input = 0;
	uCount_Key = 0;
    uApply_Key = 0;
}

void Btn_Read(void)
{
	uBtn_State = Btn_Port();

	if( uBtn_State == 0 )
	{
		if( uKey_Input != BTN_CLEAR )
		{
			if( uCount_Key > SHORT_KEY_COUNT )
			{
				uBtn_Press = uKey_Input;
			}
			uKey_Input = BTN_CLEAR;
		}

		uCount_Key = 0;
        uApply_Key = 0;
	}
	else
	{
        if( uApply_Key == BTN_CLEAR )
		{
			if( uBtn_State == uKey_Input )
			{
				uCount_Key++;

				if( uCount_Key > LONG_KEY_COUNT )
				{
					uBtn_Press = (uKey_Input | BTN_LONG);
                    uApply_Key = uBtn_Press;
                    uCount_Key = 0;
				}
			}
			else
			{
				uCount_Key = 0;
			}

			uKey_Input = uBtn_State;
		}
	}
}

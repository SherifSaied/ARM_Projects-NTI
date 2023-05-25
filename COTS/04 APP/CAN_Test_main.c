/*
 * main.c
 *
 *  Created on: Jul 3, 2021
 *      Author: Ali_Mahrez
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LIB.h"

#include "RCC_interface.h"
#include "RCC_private.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"

#include "SYSTICK_interface.h"

#include "CAN_interface.h"
#include "CAN_private.h"




int main()
{
	MRCC_voidClkInit();

	MSYSTICk_voidEnable();
	   /* Enable the Rcc for the GPIOA */
	MGPIO_voidIntialization(IOPA);//

	MGPIO_voidSetPinMode(PIN0,GPIO_PORTA,Output10_PushPull);
//	MGPIO_ErrorStatusSetPinMode(PIN9,GPIO_PORTA,Output2_AFPushPull);
//	MGPIO_ErrorStatusSetPinMode(PIN10,GPIO_PORTA,Input_Floating);

	MCAN_voidInit();
	CAN_Msg x,y;
	MCAN_voidCreateMessage(100,99,0,1,CAN_MSG_Standard_Format,CAN_MSG_DataFrame,CAN_TSR_TME0,&x);
	MSYSTICK_voidSetBusyWait(1000000,MICRO_SEC);

//	volatile u32 recmsg = 0;

	while(1)
	{
		MCAN_voidSendMessage(&x);
		MSYSTICK_voidSetBusyWait(1000000,MICRO_SEC);
		MCAN_voidReadMessage(&y, 0);
		if(y.Data[0] == 99)
		{
			MGPIO_voidSetPinValue(PIN0, GPIO_PORTA, 1);
		}
	}

return 0;
}

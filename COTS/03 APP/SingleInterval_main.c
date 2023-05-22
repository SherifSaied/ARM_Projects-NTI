#include	"stdTypes.h"
#include	"BITMATH.h"

#include	"RCC_interface.h"
#include	"DIO_interface.h"
#include	"STK_interface.h"

void	ToggleLed(void)
{
	static	u8 flag	=	0;
	if(flag	==	0)
	{
		/*		Led On		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_LOW);
		flag	=	1;
	}
	else
	{
		/*		Led Off		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_HIGH);
		flag	=	0;
	}
}

/*	C13 ==> Built in led (Toggle Led)		*/
//int main()
//{
//	/*	System Clock Init			*/
//	RCC_enuSysClkInit();
//	/*	Enable RCC for GPIOC 		*/
//	RCC_voidEnablePerClk(RCC_APB2,4);
//
//	/*	C13 Direction 	"Output @ 2MHz Push Pull"	*/
//	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN13,GPIO_OUTPUT_2MHZ_PP);
//	/*	SysTick	Init				*/
//	STK_voidInit();
//
//	/*	Call Single Interval 		*/
//	/*	LED ON in the CallBack		*/
//	STK_voidSetIntervalSingle(1000000,TIME_MS, ToggleLed);
//	/*	LED OFF in the CallBack		*/
//	STK_voidSetIntervalSingle(1000000,TIME_MS, ToggleLed);
//
//	while(1)
//	{
//
//	}
//	return 0;
//}




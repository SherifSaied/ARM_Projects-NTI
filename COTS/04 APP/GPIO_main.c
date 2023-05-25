#include	"stdTypes.h"
#include	"BITMATH.h"
#include    "errorStates.h"


#include	"RCC_interface.h"
#include	"DIO_interface.h"


/*	C13 ==> Built in led (Toggle Led)		*/
int main(void)
{
	/*	System Clock Init			*/
	RCC_enuSysClkInit();
	/*	Enable RCC for GPIOC 		*/
	RCC_enuEnablePerClk(RCC_APB2,4);
	
	/*	C13 Direction 	"Output @ 2MHz Push Pull"	*/
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN13,GPIO_OUTPUT_2MHZ_PP);
	
	while(1)
	{
		/*		Led On		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_LOW);
		for(u32 i = 0; i < 50000 ; i++)
		{
			asm("NOP");
		}
		/*		Led Off		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_HIGH);
		for(u32 i = 0; i < 50000 ; i++)
		{
			asm("NOP");
		}		
	}
	return 0;
}



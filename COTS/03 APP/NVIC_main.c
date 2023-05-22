#include	"stdTypes.h"
#include	"BITMATH.h"

#include	"RCC_interface.h"
#include	"DIO_interface.h"

#include "NVIC_interface.h"

#include "NVIC_config.h"
#include "NVIC_private.h"


void	EXTI0_IRQHandler(void);
void	EXTI1_IRQHandler(void);

int main(void)
{
	/*	System Clock Init			*/
	RCC_enuSysClkInit();
	
	/*	Enable RCC for GPIOC 		*/
	RCC_enuEnablePerClk(RCC_APB2,4);

	/*	C13 Direction 	"Output @ 2MHz Push Pull"	*/
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN13, GPIO_OUTPUT_2MHZ_PP);

	/*Activate input for switch as Pull-up*/
	//DIO_voidSetPinValue(DIO_PORTA,DIO_PIN, GPIO_HIGH);

	/*	Interrupt Initialization	*/
	NVIC_voidInit();
	
	/*make SW_prioority for EXTI0 after making 4 groups and 4 subgroups*/
	NVIC_voidSetSwIntPriority(6, 0b1100);  // kda 7ateet l Int f group 3 w sub 0 "lower prio"

	/*make SW_prioority for EXTI1 after making 4 groups and 4 subgroups*/
	NVIC_voidSetSwIntPriority(7, 0b0010);  // kda 7ateet l Int f group 0 w sub 2 "kda dh higher prio"

	/*	Set pending Flag EXTI0	//just to test software "when using hardware we don't do this"	*/
	NVIC_voidSetPendingFlag(6);
	
	/*	Set pending Flag EXTI1	//just to test software "when using hardware we don't do this"	*/
	NVIC_voidSetPendingFlag(7);

	/*	NVIC EXTI0 "IntNum 6 from vector table " Enable 			*/
	NVIC_voidEnablePerInt(6);

	_delay_ms(500); // delay between 2 Int

	/*	NVIC EXTI1 "IntNum 7 from vector table " Enable 			*/
	NVIC_voidEnablePerInt(7);


	while(1)
	{
		
	}
	return 0;
}



//void 	__vector_1(void) dh for avr compiler dependant
void	EXTI0_IRQHandler(void)  //ay 7aga bra cpu l arm btkon namefrom vector table_IRQHandler(void)
{
		/*		Led On		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_LOW);
		_delay_ms(1000);
		/*tested the nested Int for higher prio */
		/*	NVIC EXTI1 "IntNum 7 from vector table " Enable 			*/
		NVIC_voidEnablePerInt(7);
		while(1); // 3shan nshof hay5rog w msh hayro7 l while(1)
		/*		Led Off		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_HIGH);
		_delay_ms(1000);
	/*	Clear EXTI0 Flag	to repeat INT*/
}

void	EXTI1_IRQHandler(void)
{
		/*		Led On		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_LOW);
		_delay_ms(1000);
		while(1); // kda hayfdl m stuck hna 3shan mafesh 7aga a3la prio mn EXT1
		/*		Led Off		*/
		DIO_voidSetPinValue(DIO_PORTC,DIO_PIN13,GPIO_HIGH);
		_delay_ms(1000);
	/*	Clear EXTI0 Flag	to repeat INT*/
}



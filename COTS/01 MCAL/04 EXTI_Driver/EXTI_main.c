#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"
#include "RCC_interface.h"
#include "DIO_interface.h"

#include "NVIC_interface.h"
#include "EXTI_interface.h"

#include "EXTI_private.h"



void	EXTI0_IRQHandler(void);

int main(void)
{
	/*call the setcallback function for INT*/
	//EXTI0_voidSetCallBack(EXTI0_IRQHandler);
	/* clock init*/
	RCC_enuSysClkInit();
	/*Enable clock peri for IOPORTC */
	RCC_enuEnablePerClk(RCC_APB2, IOPC_PERIPHERAL);
	/*GPIOA*/
	RCC_enuEnablePerClk(RCC_APB2, IOPA_PERIPHERAL);
	/*AFIO  like  EXTI0*/
	RCC_enuEnablePerClk(RCC_APB2, AFIO_PERIPHERAL);
//test for led on PORTA pin2
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN2, GPIO_OUTPUT_2MHZ_PP);

//for switch PORTA pin0 as input
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, GPIO_INPUT_PULL_UP_DOWN);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_LOW);

	//Falling edge interrupt
	EXTI_voidChangeSenseMode(EXTI_0, RISING_EDGE);

	/*INT Initialization*/
	NVIC_voidInit();
	NVIC_voidEnablePerInt(6); //6 di mn vector table for name of interrrupt
	EXTI_voidInit(EXTI_0, DIO_PORTB);
	EXTI_voidEnableInt(EXTI_0);
    /* Loop forever */
	while (1)
	{

	}
	return 0;
}






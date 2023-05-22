#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"
#include "RCC_interface.h"
#include "DIO_interface.h"

#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"



void userLEDINT(void);
void userLEDINT(void)
{
			/*		Led On		*/
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,GPIO_HIGH);
			_delay_ms(500);

			/*		Led Off		*/
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,GPIO_LOW);
			_delay_ms(500);
}

int main(void)
{
	/* clock init*/
	RCC_enuSysClkInit();

	/*Enable clock peri for IOPORTC */
	RCC_enuEnablePerClk(RCC_APB2, IOPC_PERIPHERAL);

	/*GPIOA*/
	RCC_enuEnablePerClk(RCC_APB2, IOPA_PERIPHERAL);

	/*Enable clock peri for IOPORTB */
	RCC_enuEnablePerClk(RCC_APB2, IOPB_PERIPHERAL);

	/*AFIO  like  EXTI0*/
	RCC_enuEnablePerClk(RCC_APB2, AFIO_PERIPHERAL);

//test for led on PORTA pin2
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN2, GPIO_OUTPUT_10MHZ_PP);

//for switch PORTA pin0 as input
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, GPIO_INPUT_PULL_UP_DOWN);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_HIGH);

	//Falling or rising edge interrupt
	EXTI_voidChangeSenseMode(EXTI0, FALLING_EDGE);

	/*call the setcallback function for INT*/
	EXTI_voidSetCallBack(userLEDINT, EXTI0);

	/*INT Initialization*/
	NVIC_voidInit();

	NVIC_voidEnablePerInt(6); //6 di mn vector table for name of interrrupt

	EXTI_voidInit(EXTI0, DIO_PORTA);

	EXTI_voidEnableInt(EXTI0);
	
    /* Loop forever */
	while (1)
	{

	}
	return 0;
}









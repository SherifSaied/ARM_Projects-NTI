#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "LCD_int.h"
#include "SevSeg_interface.h"

#include "EXTI_private.h"




void userLEDINT(void);
void userLEDINT(void)
{



	LCD_enuSendString("HiPedestrianWait!");

	/*toggle yellow*/
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN12, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN14, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN9, GPIO_LOW);
	_delay_ms(500);

	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
	_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
	_delay_ms(500);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
	_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
	_delay_ms(500);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);


	/*ped green and car red*/
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN12, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN14, GPIO_HIGH); // car red on
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, GPIO_HIGH); // ped green on
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN9, GPIO_LOW);

	_delay_ms(1000);


	/*toggle yellow*/
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN12, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN14, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN9, GPIO_LOW);
	_delay_ms(500);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
	_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
	_delay_ms(500);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
	_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
	_delay_ms(500);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);

	LCD_enuClear();
	//while (((DIO_PORTA>>DIO_PIN0) & 1)==0); //busy wait until button is released
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
	/*AFIO */
	RCC_enuEnablePerClk(RCC_APB2, AFIO_PERIPHERAL);

	//cars leds on PORTB pins 12,13,14
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN12, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN13, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN14, GPIO_OUTPUT_10MHZ_PP);
	//pedestrian leds on PORTB pins 7,8,9
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN8, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN9, GPIO_OUTPUT_10MHZ_PP);

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

	LCD_enuInit();
	_delay_ms(50);

//	SevSeg_voidInit();
//	SevSeg_voidStart();
	while (1)
	{

		LCD_enuClear();
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN12, GPIO_HIGH); //car green on
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN14, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN9, GPIO_HIGH); //ped red on


		_delay_ms(800);


		/*toggle yellow*/
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN12, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN14, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN9, GPIO_LOW);
		_delay_ms(300);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
		_delay_ms(200);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
		_delay_ms(300);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
		_delay_ms(200);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
		_delay_ms(300);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);



		/*car red and green ped*/
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN12, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN14, GPIO_HIGH); // car red on
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, GPIO_HIGH); // ped green on
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN9, GPIO_LOW);

		_delay_ms(800);

		/*toggle yellow*/
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN12, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN14, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN9, GPIO_LOW);
		_delay_ms(300);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
		_delay_ms(200);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
		_delay_ms(300);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
		_delay_ms(200);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_HIGH);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_HIGH);
		_delay_ms(300);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN13, GPIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN8, GPIO_LOW);
		LCD_enuClear();
	}



}

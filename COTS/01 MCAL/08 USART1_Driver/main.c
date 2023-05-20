#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "USART1_interface.h"

#include "USART1_config.h"
#include "USART1_private.h"


int main(void)
{
	RCC_enuSysClkInit();
	RCC_enuEnablePerClk(RCC_APB2, 2); //PORTA
	RCC_enuEnablePerClk(RCC_APB2, 14);  //USART1
	RCC_enuEnablePerClk(RCC_APB2, 0);   //AFIO
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN9, GPIO_OUTPUT_2MHZ_AFPP); //TX on it
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN10, GPIO_INPUT_FLOAT); //RX on this PApin10
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, GPIO_OUTPUT_10MHZ_PP); //direction for LED
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_LOW);
	UART_init();
	UART_enableRX();
	UART_enableTX();


	while (1)
	{
		UART_voidSendchar('A');
		u8 Rx=0;
		UART_voidRecieveChar(&Rx);
		 if (Rx == 'A')
		  {
			 DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_HIGH);
			 _delay_ms(500);
			 DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_LOW);
			 _delay_ms(500);

		  }
	}
}



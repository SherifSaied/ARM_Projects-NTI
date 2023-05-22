#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"

#include "SPI_interface.h"
#include "RCC_interface.h"
#include "DIO_interface.h"

#include "SPI_config.h"
#include "SPI_private.h"

int main(void)
{
	RCC_enuSysClkInit();
	RCC_enuEnablePerClk(RCC_APB2,2); //PORTA
	RCC_enuEnablePerClk(RCC_APB2,0); //AFIO
	RCC_enuEnablePerClk(RCC_APB2,12); //SPI1

	/*DIO directions for PA pin4,5,6,7*/


	//NSS as output and value 0 "for slave select to GND care to shall get it high after recieve data"
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN4, GPIO_OUTPUT_2MHZ_AFPP);

	// SCK SPI as output AFPP
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN5, GPIO_OUTPUT_2MHZ_AFPP);
	//MOSI transmit on it
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN7, GPIO_OUTPUT_2MHZ_AFPP); //MOSI transmit on it
	//MISO as input float >>>A6
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN6, GPIO_INPUT_FLOAT);

	//direction for LED
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_LOW);

	SPI1_voidInit();
	/*only you can enable your MC as master if you need slave you will  */
		//enable MOSI as MASTER
	SPI_voidMasterEnable();

	while (1)
	{
		u8 RecieveMISO=0;
		/*SS to GND*/
		DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, GPIO_LOW);
		RecieveMISO = SPI1_u8SendRecievedChar('A');
		/*return SS to HIGH*/
		DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, GPIO_HIGH);

		 if (RecieveMISO == 'A')
		  {
			 DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_HIGH);
			 _delay_ms(500);
			 DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, GPIO_LOW);
			 _delay_ms(500);

		  }
	}

}

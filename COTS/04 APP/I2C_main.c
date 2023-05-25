#include "stdTypes.h"
#include "errorStates.h"


#include "DIO_interface.h"
#include "RCC_interface.h"
#include "LCD_int.h"
#include "I2C_interface.h"

#include "I2C_config.h"
#include "I2C_private.h"

int main(void)
{
		RCC_enuSysClkInit();
		RCC_enuEnablePerClk(RCC_APB2,3);//PORTB which I2C on it
		RCC_enuEnablePerClk(RCC_APB2,0); //AFIO
		RCC_enuEnablePerClk(RCC_APB1, 21); //enable RCC for I2C1
		/*******set pins SDA and SCL (7,6)  PORTB Alternate output open drain as I2C works***********/
		DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN6, GPIO_OUTPUT_50MHZ_AFOD);
		DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN7, GPIO_OUTPUT_50MHZ_AFOD);

//		/*pull-up value for I2C pins 6,7 PORTB*/
//		DIO_voidSetPinValue(DIO_PORTB,DIO_PIN6, GPIO_HIGH); /*found in cortex M4 so hardware only in cortex M3*/

		u8 data[16] = "I2C works :)";
		u8 R_data[16]={0};

		/*select address for EEPROM*/
u8 EEPROM_ADD = 0b10101000; /*last bit is 0 to indicate write*/
/*init LCD*/
LCD_enuInit();
_delay_ms(50);
/*init I2C*/
I2C_voidInit();
_delay_ms(10);
/*start I2C generation*/
I2C_voidStart();
/*select address*/
I2C_voidAddressSelect(EEPROM_ADD);
_delay_ms(10);
/*write data to zero for masking*/
I2C_voidWriteByte(0x00);
_delay_ms(10);
/*write actual data byte by byte*/
for(int i=0 ; i<16; i++)
{
I2C_voidWriteByte(data[i]);
_delay_ms(10);
}
/*stop I2C generation*/
I2C_voidStop();
_delay_ms(10);

/*start again I2C for read*/
I2C_voidStart();

/*select address to read  */
I2C_voidAddressSelect(EEPROM_ADD+1);
_delay_ms(10);

/*read byte by byte*/
for(int i=0 ; i<16; i++)
{
I2C_voidReadByte(&R_data[i]);
_delay_ms(10);
}

I2C_voidStop();

		while (1)
		{
			LCD_enuSendCommand(LCD_CLEAR_CMD);
			LCD_enuSendString(R_data);
			_delay_ms(10);
		}
return 0;
}

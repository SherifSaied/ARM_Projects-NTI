/*



 * LCD_prog.c
 *
 *  Created on: May 6, 2023
 *      Author: Sherif Ahmed
*/
/*#include mn ta7t titititittiti l fooo2*/
#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"

#include "DIO_interface.h"

#include "LCD_int.h"

#include "LCD_config.h"
#include "LCD_priv.h"



ES_t LCD_enuInit(void)
{
	ES_t local_u8ErrorState = ES_NOK;


/*Define direction for control PINS*/
	DIO_voidSetPinDirection(RS_PORT, RS_PIN, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(RW_PORT, RW_PIN, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(EN_PORT, EN_PIN, GPIO_OUTPUT_10MHZ_PP);

#if LCD_MODE == BIT_4
    /*Define Direction for Data PINS*/
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D4 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D5 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D6 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D7 , GPIO_OUTPUT_10MHZ_PP);

	/*!comment: Delay more than 30ms*/
	_delay_ms(50);
	/*Function Set for 4_BIT MODE  */
	LCD_enuSendCommand(FUNC_SET_BIT_4);

#endif
#if LCD_MODE == BIT_8
    /*Define Direction for Data PINS*/
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D0 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D1 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D2 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D3 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D4 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D5 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D6 , GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_Data_PORT,LCD_D7 , GPIO_OUTPUT_10MHZ_PP);

	/*!comment: Delay more than 30ms*/
	_delay_ms(50);
	/*Function Set for 8_BIT MODE  */
	LCD_enuSendCommand(FUNC_SET_BIT_8);
#endif
	/*commands for 4 bit will be same as 8 bit and will be shifted in command function bit by bit*/

		_delay_ms(20);
	/*for Display on and  cursor off blinking>>0x0C or Display on and  cursor on blinking 0x0E */
		LCD_enuSendCommand(0x0C);
		_delay_ms(20);
	/*Display Clear*/
		LCD_enuSendCommand(0x01);
		_delay_ms(20);
		/*set entry mode*/
		LCD_enuSendCommand(0x06);

	return local_u8ErrorState;


}
/****************************************************************************************************/

ES_t LCD_enuSendCommand(u8 copy_u8Command)
{
	ES_t local_u8ErrorState = ES_NOK;

	u8 local_LCD_PINS[8]={LCD_D0, LCD_D1, LCD_D2,LCD_D3,LCD_D4,LCD_D5,LCD_D6,LCD_D7};

	DIO_voidSetPinValue(RS_PORT, RS_PIN, GPIO_LOW);
	DIO_voidSetPinValue(RW_PORT, RW_PIN, GPIO_LOW);

#if LCD_MODE == BIT_4
	/*send 4 high bits*/
	for (int i=0;i<4;i++)
	{
		DIO_voidSetPinValue(LCD_Data_PORT,local_LCD_PINS[i+4], ((copy_u8Command>>(i+4) ) & 1) );
	}

	/*Latch 1.high and low  2.set data  3.high and low */
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_HIGH);
	_delay_ms(5);
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_LOW);
	/*send 4 low bits*/
	for (int i=0;i<4;i++)
	{
		DIO_voidSetPinValue(LCD_Data_PORT,local_LCD_PINS[i+4], ((copy_u8Command>>i ) & 1) );
	}
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_HIGH);
	_delay_ms(5);


#endif
#if LCD_MODE == BIT_8
	/*Masking first "deleted as BSRR set seperate about BRR clr"*/
	for (int i=0;i<8;i++)
	{
		DIO_voidSetPinValue(LCD_Data_PORT,local_LCD_PINS[i], ((copy_u8Command>>i ) & 1) );
	}

	/*Latch 1.high and low  2.set data  3.high and low */
	DIO_voidSetPinValue(EN_PORT,EN_PIN, DIO_HIGH);
	_delay_ms(5);

#endif

	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_LOW);
	_delay_ms(5);
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_HIGH);
	return local_u8ErrorState;
}

/***********************************************************************************************************/
ES_t LCD_enuSendChar(u8 copy_u8Char)
{
	u8 local_LCD_PINS[8]={LCD_D0, LCD_D1, LCD_D2,LCD_D3,LCD_D4,LCD_D5,LCD_D6,LCD_D7};

	DIO_voidSetPinValue(RS_PORT, RS_PIN, GPIO_HIGH);
	DIO_voidSetPinValue(RW_PORT, RW_PIN, GPIO_LOW);
	_delay_ms(5);

#if LCD_MODE == BIT_4
	/*send 4 high bits*/
	for (int i=0;i<4;i++)
	{
		DIO_voidSetPinValue(LCD_Data_PORT,local_LCD_PINS[i+4], ((copy_u8Char>>(i+4) ) & 1) );
	}

	/*Latch 1.high and low  2.set data  3.high and low */
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_HIGH);
	_delay_ms(5);
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_LOW);
	/*send 4 low bits*/
	for (int i=0;i<4;i++)
	{
		DIO_voidSetPinValue(LCD_Data_PORT,local_LCD_PINS[i+4], ((copy_u8Char>>i ) & 1) );
	}
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_HIGH);
	_delay_ms(5);

#endif
#if LCD_MODE == BIT_8
	/*Masking first "deleted as BSRR set seperate about BRR clr"*/
	for (int i=0;i<8;i++)
	{
		DIO_voidSetPinValue(LCD_Data_PORT,local_LCD_PINS[i], ((copy_u8Char>>i ) & 1) );
	}

	/*Latch 1.high and low  2.set data  3.high and low */
	DIO_voidSetPinValue(EN_PORT,EN_PIN, DIO_HIGH);
	_delay_ms(5);
#endif

	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_LOW);
	_delay_ms(5);
	DIO_voidSetPinValue(EN_PORT,EN_PIN, GPIO_HIGH);

}

/********************************************************************************************************************/
ES_t LCD_enuSendString(char * copy_u8Data)
{
	for (int i=0;i<strlen(copy_u8Data);i++)
	{
		if (i==16)
		{
			LCD_enuSendCommand(NEXT_LINE);
		}
		LCD_enuSendChar(copy_u8Data[i]);
		_delay_ms(20);
	}

}
/******************************************************************************************************************/
ES_t LCD_enuGoToCursor(u8 lineNumber, u8 Column)
{
	if (lineNumber<3 && Column <17 )
	{
		switch(lineNumber)
		{
			case 1: LCD_enuSendCommand(0x80 + Column);  break;
			case 2: LCD_enuSendCommand(0xC0 + Column);  break;

		}
	}

}

ES_t LCD_enuCreateCustomChar(u8 *pattern, u8 location)
{
	LCD_enuSendCommand(CGRAM_ADDRESS + (location*8));
	for (u8 i=0; i<8;i++)
	{
		LCD_enuSendChar(pattern[i]);
	}
}

ES_t LCD_enuClear(void)
{
	LCD_enuSendCommand(0x01);
}

void LCD_voidWriteNumber(u32 number)
{
	u8 num[10];
	itoa(number, num, 10);  //convert Long int to string
	LCD_enuSendString(num);
}



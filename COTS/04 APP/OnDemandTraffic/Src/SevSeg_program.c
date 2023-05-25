/*
 * SevSeg_program.c
 *
 *  Created on: May 25, 2023
 *      Author: Sherif Ahmed
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_interface.h"
#include "SevSeg_interface.h"
void SevSeg_voidInit()
{

	/*output directions for SevSeg pins*/
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN8, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN9, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN10, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN11, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN12, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN15, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN3, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN15, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN4, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN5, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN6, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN11, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN10, GPIO_OUTPUT_10MHZ_PP);
	/*set normal mode is 0*/
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN8, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN9, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN10, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN11, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN12, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN15, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN3, GPIO_LOW);

	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN15, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN3, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN5, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN6, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN11, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN10, GPIO_LOW);
}

void SevSeg_voidStart()
{
	//sevSeg with common cathode
	u8 segCthd[] = {0x3F, 0x06, 0x5B,
					0x4F, 0x66, 0x6D,
					0x7D, 0x07, 0x7F,
					0x6F};
	u8 one,deci ;
	u8 counter;
	for (counter=10 ; counter >= 0; counter--)
	{
		one = counter%10 ;
		deci= counter/10 ;

	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN8,(segCthd[one]>>0)&1);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN9,(segCthd[one]>>1)&1);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN10,(segCthd[one]>>2)&1);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN11,(segCthd[one]>>3)&1);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN12,(segCthd[one]>>4)&1);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN15,(segCthd[one]>>5)&1);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN3,(segCthd[one]>>6)&1);

	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN15,(segCthd[deci]>>0)&1);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN3,( segCthd[deci]>>1)&1);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4,( segCthd[deci]>>2)&1);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN5,( segCthd[deci]>>3)&1);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN6,( segCthd[deci]>>4)&1);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN11,(segCthd[deci]>>5)&1);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN10,(segCthd[deci]>>6)&1);


	}


}


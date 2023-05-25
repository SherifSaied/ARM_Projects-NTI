#ifndef		DIO_INTERFACE_H
#define		DIO_INTERFACE_H

#include "DIO_private.h"


void	DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction);
void	DIO_voidSetPinValue(u8 port, u8 pin, u8 Value);
u8		DIO_u8GetPinValue(u8 port, u8 pin);

#define		GPIO_HIGH		1
#define		GPIO_LOW		0



#define		GPIO_INPUT_ANALOG				0b0000
#define		GPIO_INPUT_FLOAT				0b0100
#define		GPIO_INPUT_PULL_UP_DOWN			0b1000

#define		GPIO_OUTPUT_10MHZ_PP			0b0001
#define		GPIO_OUTPUT_10MHZ_OD			0b0101
#define		GPIO_OUTPUT_10MHZ_AFPP			0b1001
#define		GPIO_OUTPUT_10MHZ_AFOD			0b1101

#define		GPIO_OUTPUT_2MHZ_PP				0b0010
#define		GPIO_OUTPUT_2MHZ_OD				0b0110
#define		GPIO_OUTPUT_2MHZ_AFPP			0b1010
#define		GPIO_OUTPUT_2MHZ_AFOD			0b1110

#define		GPIO_OUTPUT_50MHZ_PP			0b0011
#define		GPIO_OUTPUT_50MHZ_OD			0b0111
#define		GPIO_OUTPUT_50MHZ_AFPP			0b1011
#define		GPIO_OUTPUT_50MHZ_AFOD			0b1111




#endif

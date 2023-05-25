#include	"stdTypes.h"
//#include	"BITMATH.h"
#include   "errorStates.h"

#include	"DIO_interface.h"
#include	"DIO_private.h"





void	DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction)
{
	/*		Range Check 		*/
	if(port < 3 && pin < 16)
	{
		if(pin<8)	/*		Low	(PIN0:PIN7) CRL	*/
		{
			switch(port)
			{
				case	DIO_PORTA	:
				/*		Clear the 4 bits before writing		*/
					GPIOA_CRL &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
					GPIOA_CRL |=  ((Direction)<<(pin * 4));
				break;
				
				case	DIO_PORTB	:
				/*		Clear the 4 bits before writing		*/
				GPIOB_CRL &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOB_CRL |=  ((Direction)<<(pin * 4));
				break;
				
				case	DIO_PORTC	:
				/*		Clear the 4 bits before writing		*/
				GPIOC_CRL &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOC_CRL |=  ((Direction)<<(pin * 4));
				break;
			}
		}else if(pin<16)	/*		high	(pin8:PIN15) CRH	*/
		{
			pin -= 8;
			switch(port)
			{
				case	DIO_PORTA	:
				/*		Clear the 4 bits before writing		*/
				GPIOA_CRH &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOA_CRH |=  ((Direction)<<(pin * 4));
				break;
				
				case	DIO_PORTB	:
				/*		Clear the 4 bits before writing		*/
				GPIOB_CRH &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOB_CRH |=  ((Direction)<<(pin * 4));
				break;
				
				case	DIO_PORTC	:
				/*		Clear the 4 bits before writing		*/
				GPIOC_CRH &= ~((0b1111)<<(pin * 4));
				/*		Assign the Direction value			*/
				GPIOC_CRH |=  ((Direction)<<(pin * 4));
				break;
			}

		}
	}else{/*	Return Error	*/}
}
void	DIO_voidSetPinValue(u8 port, u8 pin, u8 Value)
{
	/*		Range Check 		*/
	if(port < 3 && pin < 16)
	{
		if(Value == GPIO_HIGH)
		{
			switch(port)
			{
				case	DIO_PORTA	:	GPIOA_BSRR= (1<<pin);   break;
				case	DIO_PORTB	:	GPIOB_BSRR= (1<<pin);	break;
				case	DIO_PORTC	:	GPIOC_BSRR= (1<<pin);	break;
			}
		}
		else if(Value == GPIO_LOW)
		{
			switch(port)
			{
				case	DIO_PORTA	:	GPIOA_BRR= (1<<pin);	break;
				case	DIO_PORTB	:	GPIOB_BRR= (1<<pin);	break;
				case	DIO_PORTC	:	GPIOC_BRR= (1<<pin);	break;
			}			
		}
		
	}else{/*	Return Error	*/}
	
}
u8		DIO_u8GetPinValue(u8 port, u8 pin)
{
	/*		Range Check 		*/
	u8	Local_u8Val = 0x99;
	if(port < 3 && pin < 16)
	{
		u8	Local_u8Val = 0x99;
			switch(port)
			{
				case	DIO_PORTA	:	Local_u8Val	=	GET_BIT(GPIOA_IDR,pin);	break;
				case	DIO_PORTB	:	Local_u8Val	=	GET_BIT(GPIOB_IDR,pin);	break;
				case	DIO_PORTC	:	Local_u8Val	=	GET_BIT(GPIOC_IDR,pin);	break;
			}
	}
	else
	{/*	Return Error	*/}
	return Local_u8Val;
}

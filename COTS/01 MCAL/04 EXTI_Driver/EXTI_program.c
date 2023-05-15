
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_interface.h"
#include "NVIC_interface.h"


#include "EXTI_config.h"
#include "EXTI_private.h"



#ifndef		NULL
#define		NULL			((void *)0)
#endif


//static	void	(*(EXTI_CallBack[16])) (void)	= {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
static	void	(*EXTI0_CallBack) (void)	= NULL;

//// delay function
//void _delay_ms(u32 ticks)
//{
//	u32 i;
//	for( i = 0; i < (ticks * 500) ; i++)
//		{
//			asm("NOP");
//		}
//}

void		EXTI_voidInit(u8 EXTI_line ,u8 line_PORT)
{

#ifndef			AFIO_EXTICR1
	#define		AFIO_BASE_ADD		(0x40010000)
	#define		AFIO_EXTICR1			*((u32 *)(AFIO_BASE_ADD+0x08))
#endif

#ifndef			AFIO_EXTICR2
	#define		AFIO_BASE_ADD		(0x40010000)
	#define		AFIO_EXTICR2			*((u32 *)(AFIO_BASE_ADD+0x0C))
#endif

#ifndef			AFIO_EXTICR3
	#define		AFIO_BASE_ADD		(0x40010000)
	#define		AFIO_EXTICR3			*((u32 *)(AFIO_BASE_ADD+0x10))
#endif

#ifndef			AFIO_EXTICR4
	#define		AFIO_BASE_ADD		(0x40010000)
	#define		AFIO_EXTICR4			*((u32 *)(AFIO_BASE_ADD+0x14))
#endif

	/*********************EXTI_line********************/
switch (EXTI_line)
{
	case EXTI_0:
		switch (line_PORT)
		{
			AFIO_EXTICR1 &=  ~(0b1111 << 0);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR1 |=  (0b0000 << 0);
			case DIO_PORTB:		AFIO_EXTICR1 |=  (0b0001 << 0);
			case DIO_PORTC:		AFIO_EXTICR1 |=  (0b0010 << 0);
		}
	case EXTI_1:
		switch (line_PORT)
		{
			AFIO_EXTICR1 &=  ~(0b1111 << 4);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR1 |=  (0b0000 << 4);
			case DIO_PORTB:		AFIO_EXTICR1 |=  (0b0001 << 4);
			case DIO_PORTC:		AFIO_EXTICR1 |=  (0b0010 << 4);
		}
	case EXTI_2:
		switch (line_PORT)
		{
			AFIO_EXTICR1 &=  ~(0b1111 << 8);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR1 |=  (0b0000 << 8);
			case DIO_PORTB:		AFIO_EXTICR1 |=  (0b0001 << 8);
			case DIO_PORTC:		AFIO_EXTICR1 |=  (0b0010 << 8);
		}
	case EXTI_3:
		switch (line_PORT)
		{
			AFIO_EXTICR1 &=  ~(0b1111 << 12);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR1 |=  (0b0000 << 12);
			case DIO_PORTB:		AFIO_EXTICR1 |=  (0b0001 << 12);
			case DIO_PORTC:		AFIO_EXTICR1 |=  (0b0010 << 12);
		}
	case EXTI_4:
		switch (line_PORT)
		{
			AFIO_EXTICR2 &=  ~(0b1111 << 0);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR2 |=  (0b0000 << 0);
			case DIO_PORTB:		AFIO_EXTICR2 |=  (0b0001 << 0);
			case DIO_PORTC:		AFIO_EXTICR2 |=  (0b0010 << 0);
		}
	case EXTI_5:
		switch (line_PORT)
		{
			AFIO_EXTICR2 &=  ~(0b1111 << 4);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR2 |=  (0b0000 << 4);
			case DIO_PORTB:		AFIO_EXTICR2 |=  (0b0001 << 4);
			case DIO_PORTC:		AFIO_EXTICR2 |=  (0b0010 << 4);
		}
	case EXTI_6:
		switch (line_PORT)
		{
			AFIO_EXTICR2 &=  ~(0b1111 << 8);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR2 |=  (0b0000 << 8);
			case DIO_PORTB:		AFIO_EXTICR2 |=  (0b0001 << 8);
			case DIO_PORTC:		AFIO_EXTICR2 |=  (0b0010 << 8);
		}
	case EXTI_7:
		switch (line_PORT)
		{
			AFIO_EXTICR2 &=  ~(0b1111 << 12);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR2 |=  (0b0000 << 12);
			case DIO_PORTB:		AFIO_EXTICR2 |=  (0b0001 << 12);
			case DIO_PORTC:		AFIO_EXTICR2 |=  (0b0010 << 12);
		}
	case EXTI_8:
		switch (line_PORT)
		{
			AFIO_EXTICR3 &=  ~(0b1111 << 0);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR3 |=  (0b0000 << 0);
			case DIO_PORTB:		AFIO_EXTICR3 |=  (0b0001 << 0);
			case DIO_PORTC:		AFIO_EXTICR3 |=  (0b0010 << 0);
		}
	case EXTI_9:
		switch (line_PORT)
		{
			AFIO_EXTICR3 &=  ~(0b1111 << 4);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR3 |=  (0b0000 << 4);
			case DIO_PORTB:		AFIO_EXTICR3 |=  (0b0001 << 4);
			case DIO_PORTC:		AFIO_EXTICR3 |=  (0b0010 << 4);
		}
	case EXTI_10:
		switch (line_PORT)
		{
			AFIO_EXTICR3 &=  ~(0b1111 << 8);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR3 |=  (0b0000 << 8);
			case DIO_PORTB:		AFIO_EXTICR3 |=  (0b0001 << 8);
			case DIO_PORTC:		AFIO_EXTICR3 |=  (0b0010 << 8);
		}
	case EXTI_11:
		switch (line_PORT)
		{
			AFIO_EXTICR3 &=  ~(0b1111 << 12);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR3 |=  (0b0000 << 12);
			case DIO_PORTB:		AFIO_EXTICR3 |=  (0b0001 << 12);
			case DIO_PORTC:		AFIO_EXTICR3 |=  (0b0010 << 12);
		}
	case EXTI_12:
		switch (line_PORT)
		{
			AFIO_EXTICR4 &=  ~(0b1111 << 0);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR4 |=  (0b0000 << 0);
			case DIO_PORTB:		AFIO_EXTICR4 |=  (0b0001 << 0);
			case DIO_PORTC:		AFIO_EXTICR4 |=  (0b0010 << 0);
		}
	case EXTI_13:
		switch (line_PORT)
		{
			AFIO_EXTICR4 &=  ~(0b1111 << 4);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR4 |=  (0b0000 << 4);
			case DIO_PORTB:		AFIO_EXTICR4 |=  (0b0001 << 4);
			case DIO_PORTC:		AFIO_EXTICR4 |=  (0b0010 << 4);
		}
	case EXTI_14:
		switch (line_PORT)
		{
			AFIO_EXTICR4 &=  ~(0b1111 << 8);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR4 |=  (0b0000 << 8);
			case DIO_PORTB:		AFIO_EXTICR4 |=  (0b0001 << 8);
			case DIO_PORTC:		AFIO_EXTICR4 |=  (0b0010 << 8);
		}
	case EXTI_15:
		switch (line_PORT)
		{
			AFIO_EXTICR4 &=  ~(0b1111 << 12);   //masking for the 4 bits first
			case DIO_PORTA:		AFIO_EXTICR4 |=  (0b0000 << 12);
			case DIO_PORTB:		AFIO_EXTICR4 |=  (0b0001 << 12);
			case DIO_PORTC:		AFIO_EXTICR4 |=  (0b0010 << 12);
		}

}

}


void		EXTI_voidEnableInt(u8 EXTI_line)
{
	//SET_BIT(EXTI -> IMR,line_num);
	EXTI -> IMR |= (1<<EXTI_line);   /*Int Mask Register*/
}
void		EXTI_voidDisableInt(u8 EXTI_line)
{
	//CLR_BIT(EXTI -> IMR,line_num);
	EXTI -> IMR &= ~(1<<EXTI_line);
}

void		EXTI_voidEnableSWI(u8 EXTI_line)
{
	//SET_BIT(EXTI -> SWIER,line_num);
	EXTI -> SWIER |= (1<<EXTI_line);
}


void		EXTI_voidChangeSenseMode(u8 EXTI_line, u8 Sense_Mode)
{
	switch(Sense_Mode)
	{
		case	RISING_EDGE		:
									EXTI -> RTSR |=  (1<<EXTI_line);
									EXTI -> FTSR &= ~(1<<EXTI_line);	    break;
		case	FALLING_EDGE	:
									EXTI -> FTSR |=  (1<<EXTI_line);
									EXTI -> RTSR &= ~(1<<EXTI_line);    	break;

		case	IOC				:
									EXTI -> RTSR |= (1<<EXTI_line);
									EXTI -> FTSR |= (1<<EXTI_line);			break;

	}


	EXTI -> IMR |= (1<<EXTI_line);  //enable for INT tani bs daman msh aktr
}

void		EXTI0_voidSetCallBack(void (*Fptr)(void))
{
	if(Fptr != NULL)
	{
		EXTI0_CallBack=Fptr;
	}
}


void	EXTI0_IRQHandler(void)
{
//	if (DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0)==1)
//	{


		//EXTI0_CallBack();

		/*		Led On		*/
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,GPIO_HIGH);
		_delay_ms(500);

		/*		Led Off		*/
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,GPIO_LOW);
		_delay_ms(500);
		/*	Clear EXTI0 Flag	to not repeat INT*/
			//EXTI->PR |= (1<<EXTI_0); //EXTI0 so put bit 0

//	}

}


//
//void		EXTI_voidSetCallBack(void (*Fptr)(void),u8 EXTI_line)
//{
//	if(Fptr != NULL)
//	{
//		EXTI_CallBack[EXTI_line]= Fptr ;
//
//	}
//}


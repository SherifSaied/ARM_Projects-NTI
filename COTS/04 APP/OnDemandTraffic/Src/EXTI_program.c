
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_interface.h"
#include "NVIC_interface.h"


#include "EXTI_config.h"
#include "EXTI_private.h"



#ifndef		NULL
#define		NULL			((void *)0)
#endif

static	void	(*EXTI_CallBack[16]) (void)	= {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

//static	void	(*EXTI0_CallBack) (void)	= NULL;



void		EXTI_voidInit(u8 EXTI_line ,u8 line_PORT)
{

#ifndef      AFIO
#define     AFIO_base_add       (0x40010000)
#define     AFIO_EXTICR1       *((u32*)(AFIO_base_add +0x08))
#define     AFIO_EXTICR2       *((u32*)(AFIO_base_add +0x0C))
#define     AFIO_EXTICR3	   *((u32*)(AFIO_base_add +0x10))
#define     AFIO_EXTICR4	   *((u32*)(AFIO_base_add +0x14))
#endif

	/*********************EXTI_line********************/

//	/*choose port       */
//		#if   EXTI_PORT  ==   PA
//		AFIO_EXTICR1=0x0000 ;
//		AFIO_EXTICR2=0x0000 ;
//		AFIO_EXTICR3=0x0000 ;
//		AFIO_EXTICR4=0x0000 ;
//	 #elif  EXTI_PORT  ==   PB
//		AFIO_EXTICR1=0x0000 ;
//			AFIO_EXTICR2=0x1111 ;
//			AFIO_EXTICR3=0x1111 ;
//			AFIO_EXTICR4=0x1111 ;
//	 #elif  EXTI_PORT  ==   PC
//			AFIO_EXTICR4=0x2220 ;
//	#else
//	#error  "Error chose wrong Port"
//	#endif

switch (line_PORT)
{
	case DIO_PORTA:
		switch (EXTI_line)
		{
			AFIO_EXTICR1 &=  ~(0x0000<< 0);   //masking for the register all first
			case EXTI0:			AFIO_EXTICR1  =  0x0000;
			case EXTI_1:		AFIO_EXTICR1  =  0x0000;
			case EXTI_2:		AFIO_EXTICR1  =  0x0000;
			case EXTI_3:		AFIO_EXTICR1  =  0x0000;
			case EXTI_4:		AFIO_EXTICR2  =  0x0000;
			case EXTI_5:		AFIO_EXTICR2  =  0x0000;
			case EXTI_6:		AFIO_EXTICR2  =  0x0000;
			case EXTI_7:		AFIO_EXTICR2  =  0x0000;
			case EXTI_8:		AFIO_EXTICR3  =  0x0000;
			case EXTI_9:		AFIO_EXTICR3  =  0x0000;
			case EXTI_10:		AFIO_EXTICR3  =  0x0000;
			case EXTI_11:		AFIO_EXTICR3  =  0x0000;
			case EXTI_12:		AFIO_EXTICR4  =  0x0000;
			case EXTI_13:		AFIO_EXTICR4  =  0x0000;
			case EXTI_14:		AFIO_EXTICR4  =  0x0000;
			case EXTI_15:		AFIO_EXTICR4  =  0x0000;
		}
	case DIO_PORTB:
		switch (EXTI_line)
		{
		AFIO_EXTICR1 &=  ~(0x0000<< 0);   //masking for the register all first
		case EXTI0:			AFIO_EXTICR1  =  0x0001;
		case EXTI_1:		AFIO_EXTICR1  =  0x0001;
		case EXTI_2:		AFIO_EXTICR1  =  0x0001;
		case EXTI_3:		AFIO_EXTICR1  =  0x0001;
		case EXTI_4:		AFIO_EXTICR2  =  0x0001;
		case EXTI_5:		AFIO_EXTICR2  =  0x0001;
		case EXTI_6:		AFIO_EXTICR2  =  0x0001;
		case EXTI_7:		AFIO_EXTICR2  =  0x0001;
		case EXTI_8:		AFIO_EXTICR3  =  0x0001;
		case EXTI_9:		AFIO_EXTICR3  =  0x0001;
		case EXTI_10:		AFIO_EXTICR3  =  0x0001;
		case EXTI_11:		AFIO_EXTICR3  =  0x0001;
		case EXTI_12:		AFIO_EXTICR4  =  0x0001;
		case EXTI_13:		AFIO_EXTICR4  =  0x0001;
		case EXTI_14:		AFIO_EXTICR4  =  0x0001;
		case EXTI_15:		AFIO_EXTICR4  =  0x0001;
		}
	case DIO_PORTC:
		switch (EXTI_line)
		{
			AFIO_EXTICR1 &=  ~(0x0000<< 0);   //masking for the register all first
		case EXTI0:			AFIO_EXTICR1  =  0x0010;
		case EXTI_1:		AFIO_EXTICR1  =  0x0010;
		case EXTI_2:		AFIO_EXTICR1  =  0x0010;
		case EXTI_3:		AFIO_EXTICR1  =  0x0010;
		case EXTI_4:		AFIO_EXTICR2  =  0x0010;
		case EXTI_5:		AFIO_EXTICR2  =  0x0010;
		case EXTI_6:		AFIO_EXTICR2  =  0x0010;
		case EXTI_7:		AFIO_EXTICR2  =  0x0010;
		case EXTI_8:		AFIO_EXTICR3  =  0x0010;
		case EXTI_9:		AFIO_EXTICR3  =  0x0010;
		case EXTI_10:		AFIO_EXTICR3  =  0x0010;
		case EXTI_11:		AFIO_EXTICR3  =  0x0010;
		case EXTI_12:		AFIO_EXTICR4  =  0x0010;
		case EXTI_13:		AFIO_EXTICR4  =  0x0010;
		case EXTI_14:		AFIO_EXTICR4  =  0x0010;
		case EXTI_15:		AFIO_EXTICR4  =  0x0010;
		}
}

}


void		EXTI_voidEnableInt(u8 EXTI_line)
{
	//set
	(EXTI -> IMR) |= (1<<EXTI_line);   /*Int Mask Register*/
}
void		EXTI_voidDisableInt(u8 EXTI_line)
{
	//clear
	(EXTI -> IMR) &=  ~(1<<EXTI_line);
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

void		EXTI_voidSetCallBack(void (*Fptr)(void), u8 ID_EXTI)
{
	if(Fptr != NULL)
	{
		EXTI_CallBack[ID_EXTI] = Fptr;
	}
}



void	EXTI0_IRQHandler(void)
{


	if(EXTI_CallBack[0] !=NULL)
	{
		   EXTI_CallBack[0]();
			/*	Clear EXTI0 Flag	to not repeat INT*/
			EXTI->PR |= (1<<EXTI0); //EXTI0 so put bit 0
	}

//		/*		Led On		*/
//		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,GPIO_HIGH);
//		_delay_ms(500);
//
//		/*		Led Off		*/
//		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,GPIO_LOW);
//		_delay_ms(500);




}



///*****************dh for all EXTI_lines*/
//void		EXTI_voidSetCallBack(void (*Fptr)(void),u8 EXTI_line)
//{
//	if(Fptr != NULL)
//	{
//		EXTI_CallBack[EXTI_line]= Fptr ;
//
//	}
//}


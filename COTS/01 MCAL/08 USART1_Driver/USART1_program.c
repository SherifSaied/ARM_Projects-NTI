/*
 * USART_program.c
 *
 *  Created on: May 14, 2023
 *      Author: Sherif Ahmed
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "USART1_interface.h"

#include "USART1_config.h"
#include "USART1_private.h"

/*
in the main:
1- Enable UART(1,2,3) RCC
2- GPIO => Alternate Function A9 (Tx) Direction OUTPUT AF_PP
3- GPIO A10 (Rx) Direction INPUT_FLOAT
*/
void UART_init()
{

#if USART_F_clk==8
    #if  USART_BAUD_RATE==9600
		/*from equation of BAUD RATE you get DIV=52.083 so fraction=.083*16=1.328 =1 >>0x1 and MANTISA= 52>>0x34 so >BRR=0x341*/
	USART1->BRR= 0x341;

	#elif USART_BAUD_RATE==115200   /*DIV= 32.89*/
	USART1->BRR= 0x20E;

	#else
	#error ("Config error")
	#endif
#endif
#if USART_F_clk==72
	#if  USART_BAUD_RATE==9600 /*DIV=468.75*/
	USART1->BRR=0x1D4C ;

	#elif USART_BAUD_RATE==115200   /*DIV= 39.06*/
	USART1->BRR=0x271 ;

	#else
	#error ("Config error")
	#endif
#endif

	/*USART Enable*/
	USART1->CR1 |= (1<<13);
}


void UART_enableTX(void)
{

	/*transmitter enable  */
	USART1->CR1 |= (1<<3);

}

void UART_enableRX(void)
{
	/*reciever enable  */
	USART1->CR1 |= (1<<2);

}

//transmit data
void UART_voidSendchar(u8 data)
{

		while(((USART1->SR)>>7 &1) == 0) ; //check if register is empty
    	 USART1->DR = data ;
		 while(((USART1->SR)>>6 &1) == 0) ;
}

//receive data
void UART_voidRecieveChar (u8 *data )
{

	while(((USART1->SR)>>5 &1) == 0) ;
	*data = USART1->DR;

}

void UART1_voidSendString(u8 * str)
{
	while (*str != '\0')
	{
		UART_voidSendchar(*str);
		str++;
	}
}
void UART1_StrReceiveString(u8 *str)
{
	while (*str != '\0')
	{
		UART_voidRecieveChar(str);
		str++;
	}

}

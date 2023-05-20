/*
 * SPI_program.c
 *
 *  Created on: May 15, 2023
 *      Author: Sherif Ahmed
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "SPI_config.h"
#include "SPI_private.h"

void SPI1_voidInit(void)
{

#if SPI1_BAUD_RATE_CONTROL== F_PCLK_2
	SPI1->CR1 &= ~(0b111<<3);
	SPI1->CR1 |=  (0b000<<3);
#elif SPI1_BAUD_RATE_CONTROL== F_PCLK_4

	SPI1->CR1 &= ~(0b111<<3);
	SPI1->CR1 |=  (0b001<<3);

#else
#error ("Config error")
#endif

#if SPI1_FRAME_FORMAT==LSB
	SPI1->CR1 |=  (1<<7);
#elif SPI1_FRAME_FORMAT==MSB
	SPI1->CR1 &=  ~(1<<7);
#else
#error ("Config error")
#endif

#if SPI1_RECIEVE_ONLY== Full_Duplex
	SPI1->CR1 &=  ~(1<<10);
#elif SPI1_RECIEVE_ONLY== Full_Duplex
	SPI1->CR1 |=  (1<<10);
#else
#error ("Config error")
#endif

#if SPI1_DATA_FRAME_FORMAT == BIT_8
	SPI1->CR1 &=  ~(1<<11);
#elif SPI1_DATA_FRAME_FORMAT == BIT_16
	SPI1->CR1 |=  (1<<11);
#else
#error ("Config error")
#endif

	//clear clock phase=0
	SPI1->CR1 &= ~(1<<0);

	//polarity=0
	SPI1->CR1 &= ~(1<<1);

	// SSI and SSM =1
	SPI1->CR1 |=  (1<<8);
	SPI1->CR1 |=  (1<<9);

	//enable SPI
	SPI1->CR1 |= (1<<6);

	//Disable all interrupts
	SPI1->CR2=0;

}

void SPI_voidMasterEnable()
{
	SPI1->CR1 |= (1<<2);
}

void SPI_voidSlaveEnable()
{
	SPI1->CR1 &= ~(1<<2);
}

u8 SPI1_u8SendRecievedChar(u8 byte)
{
	while(((SPI1->SR)>>1 &1) == 0) ; //check Transmit buffer "not empty 0" ?
	SPI1->DR = byte ;
	while(((SPI1->SR)>>7 &1) == 1) ; //check busy
	u8 MISO =0;
	MISO = SPI1->DR;
	//while(((SPI1->SR)>>0 &1) == 0) ; //check recieve buffer "not empty 0" ?

return MISO;
}


void SPI1_voidSendString(u8 * str)
{
	while (*str != '\0')
	{
		SPI1_voidSendChar(*str);
		str++;
	}
}
void SPI1_voidReceiveString(u8 *str)
{
	while (*str != '\0')
	{
		SPI1_voidRecieveChar(str);
		str++;
	}

}



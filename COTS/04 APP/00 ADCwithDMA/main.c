






#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"



#include "ADC_private.h"


void ADC_voidInit(void)
{
	/***** STEPS TO FOLLOW ******
		1. Enable ADC and GPIO clock
		2. Set the prescalar in the Clock configuration register (RCC_CFGR)
		3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)
		4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
		5. Set the Sampling Time for the channels in ADC_SMPRx
		6. Set the Regular channel sequence length in ADC_SQR1
		7. Set the Respective GPIO PINs in the Analog Mode
		****************/
//1.
	RCC_APB2ENR |= (1<<9);
	RCC_APB2ENR |= (1<<2);

//2.
	RCC_CFGR |= (2<<14);

//3.
	ADC1_CR1 |= (1<<8);


//4.
	ADC1_CR2 |= (1<<1);

	//

	ADC1_CR2 |= (7<<17);
	ADC1_CR2 &= ~(1<<11);

//5.

	ADC1_SMPR2 &= ~((7<<3) | (7<<12));    // Sampling time of 1.5 cycles for channel 1 and channel 4


//6.
	ADC1_SQR1 |= (2<<20);

//7.
	GPIOA_CRL &= ~(0xf<<4);
	GPIOA_CRL &= ~(0xf<<16);


	ADC1_SMPR1 |= (7<<18);

	ADC1_CR2 |= (1<<23);

	ADC1_CR2 |= (1<<8);

	ADC1_CR2 |= (1<<9);


	ADC1_SQR3 |= (1<<0);

	ADC1_SQR3 |= (4<<5);

	ADC1_SQR3 |= (16<<10);


}

void ADC_voidEnable(void)
{


	ADC1_CR2 |= (1<<0);
    //_delay_ms(100);  //about 10us

	u32 delay = 10000;

    while(delay--);

}

void ADC_voidStart(void)
{
	ADC1_SR = 0;
	ADC1_CR2 |= (1<<20);
	ADC1_CR2 |= (1<<22);

}

void DMA_voidInit(void)
{
//1.
	RCC_AHBENR |= (1<<0);

//2.
//	//	DMA1_Channel7->CCR |= (1<<4);   // Read From Memory
//		DMA1_Channel1->CCR &= ~(1<<4);   // Read From Peripheral
//
//		// 2. Enable the circular mode (CIRC)
//		DMA1_Channel1->CCR |= 1<<5;
//
//		// 3. Enable the Memory Increment (MINC)
//		DMA1_Channel1->CCR |= 1<<7;
//
//		// 4. Set the Peripheral data size (PSIZE)
//		DMA1_Channel1->CCR |= (1<<8);  // 01 : 8 Bit Data
//
//		// 5. Set the Memory data size (MSIZE)
//		DMA1_Channel1->CCR |= (1<<10);  // 01 : 8 Bit Data

}

//void DMA_Config (uint32_t srcAdd, uint32_t destAdd, uint16_t size)
//{
//
//	/***** STEPS TO FOLLOW ******
//	1. Set the Data Size in the CNDTR Register
//	2. Set the Peripheral Address and the Memory Address
//	3. Enable the DMA Stream
//
//		 Some peripherals don't need a start condition, like UART, So as soon as you enable the DMA, the transfer will begin
//		 While Peripherals like ADC needs the Start condition, so Start the ADC later in the program, to enable the transfer
//	****************/
//
//	DMA1_Channel1->CNDTR = size;   // Set the size of the transfer
//
//	DMA1_Channel1->CPAR = srcAdd;  // Source address is peripheral address
//
//	DMA1_Channel1->CMAR = destAdd;  // Destination Address is memory address
//
//	// Enable the DMA Stream
//	DMA1_Channel1->CCR |= (1<<0);  // EN =1
//}

  u16 RxData[3];
  float Temperature;



int main(void)
{

	RCC_enuSysClkInit();

	ADC_voidInit();
	ADC_voidEnable();
	ADC_voidStart();


	while(1)
	{

		Temperature = ((1.43 - ((float)(3.3*RxData[2]/(float)4095))) / 0.0043) + 25;

		_delay_ms(1000);
	}
}

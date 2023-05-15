/*
 * ADC_program.c
 *
 *  Created on: May 13, 2023
 *      Author: Sherif Ahmed
 */
#include "stdTypes.h"
#include "errorStates.h"
#include "delay.h"

#include "RCC_interface.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"




void ADC_voidInit(void)
{
	/*Enable ADC and GPIO clock*/
	RCC_APB2ENR |= (1<<9);  // enable ADC1 clock
	RCC_APB2ENR |= (1<<2);	// enable GPIOA clock

	/*Set the prescalar in the Clock configuration register (RCC_CFGR)	*/
	//chosen prescaller 2 in RCC config

	/************** Enable ADC *****************
	1. Enable the ADC by setting ADON bit in CR2
	2. Wait for ADC to stabilize (approx 10us)
	************************************************/
	ADC1->CR2 |= (1<<0);
	_delay_ms(20);
	/************** Clear and Start conversion *****************
	1. Clear the Status register
	2. Start the Conversion by Setting the SWSTART bit in CR2
	*************************************************/
	/*clear all status register flags*/
	ADC1->SR &= ~(1<<0);
	ADC1->SR &= ~(1<<1);
	ADC1->SR &= ~(1<<2);
	ADC1->SR &= ~(1<<3);
	ADC1->SR &= ~(1<<4);
	/*External trigger conversion mode for regular channels enabled*/
	ADC1->CR2 |= (1<<20);
	/*set external event select for regular group>> SWSTART: 111 */
#if ADC_EeventS_Rgroup==Timer_1_CC1
	ADC1->CR2 &= ~(1<<17);
	ADC1->CR2 &= ~(1<<18);
	ADC1->CR2 &= ~(1<<19);
#elif ADC_EeventS_Rgroup==Timer_1_CC2
	ADC1->CR2 |=  (1<<17);
	ADC1->CR2 &= ~(1<<18);
	ADC1->CR2 &= ~(1<<19);
#elif ADC_EeventS_Rgroup==Timer_1_CC3
	ADC1->CR2 &= ~(1<<17);
	ADC1->CR2 |=  (1<<18);
	ADC1->CR2 &= ~(1<<19);
#elif ADC_EeventS_Rgroup==SWSTART
	ADC1->CR2 |=  (1<<17);
	ADC1->CR2 |=  (1<<18);
	ADC1->CR2 |=  (1<<19);
#else
#error ("error in EeventS_Rgroup config")
#endif

	/*Start conversion of regular channels for SWSTART*/
	ADC1->CR2 |= (1<<22);
	/***********************************************/
/*set Data alignment ->> right alignment-> ALIGN > 0 */
    ADC1->CR2  &= ~(1<<11);
/*set single conversion mode->CONT->0*/
    ADC1->CR2 &= ~(1<<1);
/*Enable DMA mode*/
#if ADC_DMAMode == Enable
    ADC1->CR2 |=  (1<<8);
#elif ADC_DMAMode == Disable
    ADC1->CR2 &=  ~(1<<8);
#else
#error ("error in DMA config")
#endif
/*Temperature sensor and VREFINT enable*/
    ADC1->CR2 |=  (1<<23);
/*External event select for injected group*/


/***********start calliberation*******/
    ADC1->CR2 |= (1<<2);
    while(((ADC1->CR2)>>2) != 0);
/*wa2ef hnaaaaaaaaa*/


}

u16 ADC_u16Read()
{

}

/*set channel x sample time selection ->*/
void ADC_voidSetupTimeChannels(u8 channel , u8 sampleTime)
{
	switch (channel)
	{
		case channel_0:	 ADC1->SMPR2 |= (sampleTime<<0);  break;
		case channel_1:	 ADC1->SMPR2 |= (sampleTime<<3);  break;
		case channel_2:  ADC1->SMPR2 |= (sampleTime<<6);  break;
		case channel_3:  ADC1->SMPR2 |= (sampleTime<<9);  break;
		case channel_4:  ADC1->SMPR2 |= (sampleTime<<12); break;
		case channel_5:  ADC1->SMPR2 |= (sampleTime<<15); break;
		case channel_6:  ADC1->SMPR2 |= (sampleTime<<18); break;
		case channel_7:  ADC1->SMPR2 |= (sampleTime<<21); break;
		case channel_8:  ADC1->SMPR2 |= (sampleTime<<24); break;
		case channel_9:  ADC1->SMPR2 |= (sampleTime<<27); break;
		case channel_10: ADC1->SMPR1 |= (sampleTime<<0);  break;
		case channel_11: ADC1->SMPR1 |= (sampleTime<<3);  break;
		case channel_12: ADC1->SMPR1 |= (sampleTime<<6);  break;
		case channel_13: ADC1->SMPR1 |= (sampleTime<<9);  break;
		case channel_14: ADC1->SMPR1 |= (sampleTime<<12); break;
		case channel_15: ADC1->SMPR1 |= (sampleTime<<15); break;
		case channel_16: ADC1->SMPR1 |= (sampleTime<<18); break;
		case channel_17: ADC1->SMPR1 |= (sampleTime<<21); break;
	}
}









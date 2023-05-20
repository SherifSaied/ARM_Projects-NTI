/*
 * DMA_program.c
 *
 *  Created on: May 13, 2023
 *      Author: Sherif Ahmed
 */

#include "stdTypes.h"
#include "errorStates.h"

#include "DMA_interface.h"

#include "DMA_config.h"
#include "DMA_priv.h"

#ifndef		NULL
#define		NULL			((void *)0)
#endif

/****** Global Variables *********/
static void (*callBackFunc[7]) (void)={NULL,NULL,NULL,NULL,NULL,NULL,NULL};
/***************************************************/

void DMA_voidConfigChannel (DMA_Channels_t copy_ch , DMA_configCh_t *copy_config)
{
	/* Disable channel  and reset register */
		DMA->CH[copy_ch].CCR  = 0 ;

	/* Set channel priority */
		DMA->CH[copy_ch].CCR |=   ( (copy_config -> p_level) << DMA_PL0 );

	/* Set transfer mode */
		switch (copy_config -> tr_mode)
		{
			case MEM2MEM :
				/* Enable MEM2MEM and make the peripheral rigster source */
				DMA->CH[copy_ch].CCR |= (1<<14);
				//CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_DIR);
				DMA->CH[copy_ch].CCR &= ~(1<< 4);
				break;
			case PER2MEM :
				/* Peripheral rigster as source */
				//CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_DIR);
				DMA->CH[copy_ch].CCR &= ~(1<< 4);
				break;
			case MEM2PER :
				/* Memory rigster as source */
				//SET_BIT  (DMA->CH[copy_ch].CCR , DMA_DIR);
				DMA->CH[copy_ch].CCR |= (1<< 4);
				break;
			case PER2PER :
				/* Peripheral rigster as source */
				//CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_DIR);
				DMA->CH[copy_ch].CCR &= ~(1<< 4);
				break;
			default : /* transfer mode error */ break;
		}

		/* Set memroy element size */
			DMA->CH[copy_ch].CCR |=   ( (copy_config -> mem_size) << 10 );

		/* Set peripheral elemnt size */
			DMA->CH[copy_ch].CCR |=   ( copy_config -> per_size << DMA_PSIZE0 );

		/* Memory address increment */
			DMA->CH[copy_ch].CCR |=   ( copy_config -> mem_increment << DMA_MINC );

			/* Peripheral address increment */
			DMA->CH[copy_ch].CCR |=   ( copy_config -> per_increment << DMA_PINC );

			/* Circular mode  */
			DMA->CH[copy_ch].CCR |=   ( (copy_config -> circular_mode) << DMA_CIRC );

			/* Interrupst mangement */
			DMA->CH[copy_ch].CCR |=   ( (copy_config -> TF_interrupt) << DMA_TCIE );
			DMA->CH[copy_ch].CCR |=   ( (copy_config -> HTF_interrupt) << DMA_HTIE );
			DMA->CH[copy_ch].CCR |=   ( (copy_config -> ETF_interrupt) << DMA_TEIE );

}
/*************************************************************************************/
void DMA_voidTransfer (DMA_Channels_t copy_ch  , DMA_TransData_t *copy_trans)
{
	/* Disable channel */
		//CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_EN);
	DMA->CH[copy_ch].CCR &= ~(1<<DMA_EN);

	/* Set source and distination */
	if (copy_trans ->tr_mode == MEM2PER )
	{
		/* Set MEM as source address */
		DMA->CH[copy_ch].CMAR = copy_trans -> u32SourceAdress ;

		/* Set PER as distination address */
		DMA->CH[copy_ch].CPAR = copy_trans -> u32DistAddress ;
	}
	else if(copy_trans ->tr_mode == PER2MEM)
	{
		/* Set PER as source address */
		DMA->CH[copy_ch].CPAR = copy_trans -> u32SourceAdress ;
		/* Set MEM as distination address */
		DMA->CH[copy_ch].CMAR = copy_trans -> u32DistAddress ;
	}


	/* Configure block size */
	DMA->CH[copy_ch].CNDTR = copy_trans -> u16BlockSize ;

	/* Enable channel */
	SET_BIT(DMA->CH[copy_ch].CCR , DMA_EN);
}
/*********************************************************/
u8 DMA_u8GetStatus(DMA_Channels_t copy_ch)
{
	u8 local_u8TC = DMA_TCIF1 + (copy_ch  * 4 );   //for transfer complete bits for every channel
	u8 local_u8TE = DMA_TEIF1 + (copy_ch  * 4 );  // for transfer error for bits for every channel
	u8 local_u8State  ;
	if ((((DMA-> ISR)>>local_u8TC) & 1)==1)
	{
		local_u8State = DMA_TC ;
	}
	else if ((((DMA-> ISR)>>local_u8TE) & 1)==1)
	{
		local_u8State = DMA_TE ;
	}
	else
	{
		local_u8State = DMA_NT ;
	}
	return local_u8State ;
}
/*********************************************************************************/
void DMA_voidSetHandler (DMA_Channels_t copy_ch , void(*func)(void))
{
	if (func != NULL)
	{
		callBackFunc[copy_ch] = func ;
	}

}


/************ ISR Handlers *****************/
void DMA1_channel1_IRQHandler(void)
{
	callBackFunc[0]();
	/*clear flags*/
	DMA->IFCR = (15<<DMA_GIF1);    //1111 on first 4 bits

}

void DMA1_channel2_IRQHandler(void)
{
	callBackFunc[1]();
	/*clear flags*/
	DMA->IFCR = (15<<DMA_GIF2);    //1111 on first 4 bits

}

void DMA1_channel3_IRQHandler(void)
{
	callBackFunc[2]();
	/*clear flags*/
	DMA->IFCR = (15<<DMA_GIF3);    //1111 on first 4 bits

}

void DMA1_channel4_IRQHandler(void)
{
	callBackFunc[3]();
	/*clear flags*/
	DMA->IFCR = (15<<DMA_GIF4);    //1111 on first 4 bits

}
void DMA1_channel5_IRQHandler(void)
{
	callBackFunc[4]();
	/*clear flags*/
	DMA->IFCR = (15<<DMA_GIF5);    //1111 on first 4 bits

}

void DMA1_channel6_IRQHandler(void)
{
	callBackFunc[5]();
	/*clear flags*/
	DMA->IFCR = (15<<DMA_GIF6);    //1111 on first 4 bits

}
void DMA1_channel7_IRQHandler(void)
{
	callBackFunc[6]();
	/*clear flags*/
	DMA->IFCR = (15<<DMA_GIF7);    //1111 on first 4 bits

}


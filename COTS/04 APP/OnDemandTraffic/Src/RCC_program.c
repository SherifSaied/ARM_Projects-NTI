#include  "errorStates.h"
#include	"stdTypes.h"

#include "RCC_interface.h"

#include	"RCC_config.h"
#include	"RCC_private.h"


ES_t		RCC_enuSysClkInit(void)
{
	ES_t local_enuErrorstate=ES_OK;

	// choose system clock from (HSI - HSE crystal - HSE RC- PLL)
#if SYS_CLOCK == RCC_HSI
	RCC_CR |= (1<<RCC_HSI_ON);
	while(((RCC_CR>>RCC_HSI_RDY)&1)== 0); //wait till ready
	/*CHOOSE HSI AS SYS_CLOCK*/
	RCC_CFGR &= ~(1<<RCC_SW0);
	RCC_CFGR &= ~(1<<RCC_SW1);

#elif SYS_CLOCK == RCC_HSE_CRYSTAL
	RCC_CR |=  (1<<RCC_HSE_ON);
	while(((RCC_CR>>RCC_HSE_RDY)&1)== 0);
	/*DISABLE BYPASS*/
	RCC_CR &= ~(1<<RCC_HSE_BYP);
	/*CHOOSE HSE*/
	RCC_CFGR &= ~(1<<RCC_SW1);
	RCC_CFGR |= (1<<RCC_SW1);

#elif SYS_CLOCK == RCC_HSE_RC
	RCC_CR |= (1<<RCC_HSE_ON);
	while (((RCC_CR>>RCC_HSE_RDY)&1)==0);
	/*enable bypass*/
	RCC_CR |= (1<<RCC_HSE_BYP);
	/*Choosing HSE*/
	RCC_CFGR &= ~(1<<RCC_SW1);
	RCC_CFGR |= (1<<RCC_SW0);

#elif SYS_CLOCK == PLL_CLOCK
	RCC_CFGR &= ~(15<<RCC_PLL_MUL0);  //masking >>put 15 to put 1111 in 4 bits for RCC_PLL_MUL0 then clear them
	RCC_CFGR |= ((RCC_PLL_MUL - 2 ) << RCC_PLL_MUL0); ////load the new multiplication value

	#if   RCC_PLL_SOURCE == RCC_PLL_HSI_BY2
	RCC_CR   |= (1<<RCC_HSI_ON); //HSI on
	RCC_CFGR &= ~(1<<RCC_PLL_SRC);

	#elif RCC_PLL_SOURCE == RCC_PLL_HSE
	RCC_CR   |= (1<<RCC_HSE_ON); //HSE on
	RCC_CFGR   |= (1<<RCC_PLL_SRC); // choose HSE as PLL source

	#elif RCC_PLL_SOURCE == RCC_PLL_HSE_BY2
	RCC_CR   |= (1<<RCC_HSE_ON);     //HSE on
	RCC_CFGR |= (1<<RCC_PLL_XTPRE);  // Enable prescaller by 2
	RCC_CFGR |= (1<<RCC_PLL_SRC);	 // choose HSE as PLL source

	#else
			#error("Configuration error")
	#endif

	while (((RCC_CR>>RCC_PLL_RDY)&1)== 0); // wait till ready
	RCC_CR   |= (1<<RCC_PLL_ON);             //PLL on
	/*Choosing PLL*/
	RCC_CFGR &= ~(1<<RCC_SW0);
	RCC_CFGR |= (1<<RCC_SW1);
#else
	#error("Configuration error")
#endif

	/*set the correction factor*/
#if HSI_STEP_CORRECTION != 0
	RCC_CR &= ~(31 << RCC_HSI_TRIM0);      //masking>> clear the five bits
	RCC_CR |= ((HSI_STEP_CORRECTION + 16 ) << RCC_HSI_TRIM0);
#endif

/********choosing output on MCO********/
#if   RCC_MCO_PIN == NO_CLOCK
	RCC_CFGR &= ~(1<<RCC_MCO_2);

#elif RCC_MCO_PIN == HSI_CLOCK
	RCC_CR |= (1<<RCC_HSI_ON);  //HSI on
	RCC_CFGR |=  (1<<RCC_MCO_0);
	RCC_CFGR &= ~(1<<RCC_MCO_1);
	RCC_CFGR |=  (1<<RCC_MCO_2);

#elif RCC_MCO_PIN == HSE_CLOCK
	RCC_CR 	|= (1<<RCC_HSE_ON);
	RCC_CFGR &= ~(1<<RCC_MCO_0);
	RCC_CFGR |=  (1<<RCC_MCO_1);
	RCC_CFGR |=  (1<<RCC_MCO_2);

#elif RCC_MCO_PIN == PLL_CLOCK
	RCC_CFGR |=  (1<<RCC_MCO_0);
	RCC_CFGR |=  (1<<RCC_MCO_1);
	RCC_CFGR |=  (1<<RCC_MCO_2);

#elif RCC_MCO_PIN == SYSTEM_CLOCK
	RCC_CFGR &= ~(1<<RCC_MCO_0);
	RCC_CFGR &= ~(1<<RCC_MCO_1);
	RCC_CFGR |=  (1<<RCC_MCO_2);
#endif

	// To enable or disable Clock security system
#if CSS_ON == ENABLE
	RCC_CR |= (1<<RCC_CSS_ON);
#elif CSS_ON == DISABLE
	RCC_CR &= ~(1<<RCC_CSS_ON);
#endif

/************Choosing a prescaller for the ADC */

#if   RCC_ADC_PRESCALLER == RCC_PRESCALLER_2
	RCC_CFGR &= ~(1<<RCC_ADCPRE0);
	RCC_CFGR &= ~(1<<RCC_ADCPRE2);
#elif RCC_ADC_PRESCALLER == RCC_PRESCALLER_4
	RCC_CFGR |= (1<<RCC_ADCPRE0);
	RCC_CFGR &= ~(1<<RCC_ADCPRE2);
#elif RCC_ADC_PRESCALLER == RCC_PRESCALLER_6
	RCC_CFGR &= ~(1<<RCC_ADCPRE0);
	RCC_CFGR |= (1<<RCC_ADCPRE2);
#elif RCC_ADC_PRESCALLER == RCC_PRESCALLER_8
	RCC_CFGR |= (1<<RCC_ADCPRE0);
	RCC_CFGR |= (1<<RCC_ADCPRE2);
#else
	#error("ADC prescaller Configuration error")
#endif

/*************** Choosing a prescaller for the APB2 */
#if   RCC_APB2_PRESCALLER == RCC_PRESCALLER_0
	RCC_CFGR &= ~(1<<RCC_PPRE2_2);
#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_2
	RCC_CFGR &= ~(1<<RCC_PPRE2_0);
	RCC_CFGR &= ~(1<<RCC_PPRE2_1);
	RCC_CFGR |=  (1<<RCC_PPRE2_2);
#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_4
	RCC_CFGR |= (1<<RCC_PPRE2_0);
	RCC_CFGR &= ~(1<<RCC_PPRE2_1);
	RCC_CFGR |=  (1<<RCC_PPRE2_2);
#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_8
	RCC_CFGR &= ~(1<<RCC_PPRE2_0);
	RCC_CFGR |=  (1<<RCC_PPRE2_1);
	RCC_CFGR |=  (1<<RCC_PPRE2_2);
#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_16
	RCC_CFGR |=  (1<<RCC_PPRE2_0);
	RCC_CFGR |=  (1<<RCC_PPRE2_1);
	RCC_CFGR |=  (1<<RCC_PPRE2_2);
#else
	#error("Configuration error")
#endif

/********** Choosing a prescaller for the APB1 */
#if   RCC_APB1_PRESCALLER == RCC_PRESCALLER_0
	RCC_CFGR &= ~(1<<RCC_PPRE1_2);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_2
	RCC_CFGR &= ~(1<<RCC_PPRE1_0);
	RCC_CFGR &= ~(1<<RCC_PPRE1_1);
	RCC_CFGR |=  (1<<RCC_PPRE1_2);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_4
	RCC_CFGR |=  (1<<RCC_PPRE1_0);
	RCC_CFGR &= ~(1<<RCC_PPRE1_1);
	RCC_CFGR |=  (1<<RCC_PPRE1_2);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_8
	RCC_CFGR &= ~(1<<RCC_PPRE1_0);
	RCC_CFGR |=  (1<<RCC_PPRE1_1);
	RCC_CFGR |=  (1<<RCC_PPRE1_2);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_16
	RCC_CFGR |=  (1<<RCC_PPRE1_0);
	RCC_CFGR |=  (1<<RCC_PPRE1_1);
	RCC_CFGR |=  (1<<RCC_PPRE1_2);
#else
	#error("Configuration error")
#endif


/****** Choosing a prescaller for the AHB */
#if   RCC_APB1_PRESCALLER == RCC_PRESCALLER_0
	RCC_CFGR &= ~(1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_2
	RCC_CFGR &= ~(1<<RCC_HPRE0);
	RCC_CFGR &= ~(1<<RCC_HPRE1);
	RCC_CFGR &= ~(1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_4
	RCC_CFGR |=  (1<<RCC_HPRE0);
	RCC_CFGR &= ~(1<<RCC_HPRE1);
	RCC_CFGR &= ~(1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_8
	RCC_CFGR &= ~(1<<RCC_HPRE0);
	RCC_CFGR |=  (1<<RCC_HPRE1);
	RCC_CFGR &= ~(1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_16
	RCC_CFGR |=  (1<<RCC_HPRE0);
	RCC_CFGR |=  (1<<RCC_HPRE1);
	RCC_CFGR &= ~(1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_64
	RCC_CFGR &= ~(1<<RCC_HPRE0);
	RCC_CFGR &= ~(1<<RCC_HPRE1);
	RCC_CFGR |=  (1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_128
	RCC_CFGR |=  (1<<RCC_HPRE0);
	RCC_CFGR &= ~(1<<RCC_HPRE1);
	RCC_CFGR |=  (1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_256
	RCC_CFGR &= ~(1<<RCC_HPRE0);
	RCC_CFGR |=  (1<<RCC_HPRE1);
	RCC_CFGR |=  (1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_512
	RCC_CFGR |=  (1<<RCC_HPRE0);
	RCC_CFGR |=  (1<<RCC_HPRE1);
	RCC_CFGR |=  (1<<RCC_HPRE2);
	RCC_CFGR |=  (1<<RCC_HPRE3);
#else
	#error("Configuration error")
#endif

}

ES_t		RCC_enuEnablePerClk(u8 BusId , u8 copy_u8PerID)
{
	ES_t local_enuErrorstate = ES_NOK ;
	/*		Range Check			*/
	if(copy_u8PerID <= 31)
	{
		switch(BusId)
		{
			case	RCC_AHB		:	RCC_AHBENR  |= (1<<copy_u8PerID);	break;
			case	RCC_APB1	:	RCC_APB1ENR |= (1<<copy_u8PerID);	break;
			case	RCC_APB2	:	RCC_APB2ENR |= (1<<copy_u8PerID);	break;

		}
		local_enuErrorstate = ES_OK ;
	}
	else
	{

		local_enuErrorstate = ES_OUT_OF_RANGE ;

	}

	return local_enuErrorstate ;
}

ES_t		RCC_enuDisablePerClk(u8 BusId , u8 copy_u8PerID)
{
	ES_t local_enuErrorstate = ES_NOK ;
	/*		Range Check							*/
	if(copy_u8PerID <= 31)
	{
		switch(BusId)
		{
			case	RCC_AHB		:	RCC_AHBENR &=  ~(1<<copy_u8PerID);	break;
			case	RCC_APB1	:	RCC_APB1ENR &= ~(1<<copy_u8PerID);	break;
			case	RCC_APB2	:	RCC_APB2ENR &= ~(1<<copy_u8PerID);	break;
		}
		local_enuErrorstate = ES_OK ;
	}
	else
	{	
		local_enuErrorstate = ES_OUT_OF_RANGE ;	
	}	

return local_enuErrorstate ;
}







	/*******itt_1*********/

//#if  (Micro_ClkOutput == HSI_Clk_S)
//	RCC_CFGR |= ((HSI_Clk_S | 0b000)<<24);
//#elif (Micro_ClkOutput == NoClk_S)
//	RCC_CFGR |= ((NoClk_S | 0b000)<<24);
//#endif
//
//
//#if   (USB_prescaler == PLL_ClkDiv)
//	RCC_CFGR &= ~(1<<USBPRE);
//#elif (USB_prescaler == PLL_ClkNotDiv)
//	RCC_CFGR |= (1<<USBPRE);
//#endif
//
//
//	/*SW system clock switch
//	 *  00: HSI selected as system clock
//		01: HSE selected as system clock
//		10: PLL selected as system clock
//		11: not allowed*/
//#if   (SYSCLK_SW == RCC_PLL)
//	#if  (HSE_DivPLLentry == HSE_NotDiv)
//
//	 	RCC_CFGR &= ~(1<<PLLXTPRE);
//	#elif     (HSE_DivPLLentry == HSE_Div2)
//	 	RCC_CFGR |= (1<<PLLXTPRE);
//	#endif
//
//     #if   (PLL_entryClk==RCC_HSI/2)
//		RCC_CFGR &= ~(1<<PLLSRC);
//     #elif (PLL_entryClk==RCC_HSE)
//		RCC_CFGR |= (1<<PLLSRC);
//     #endif
//
//
//	#if   (PLL_multiF == PLL_inputClk2)
//		RCC_CFGR |= (PLL_inputClk2 | 0b0000) << 18);
//
//	#elif (PLL_multiF == PLL_inputClk3)
//		RCC_CFGR |= (PLL_inputClk3 | 0b0000) << 18);
//    #endif
//
//		RCC_CFGR |= (1<<SW1);
//#endif
//#if (SYSCLK_SW == RCC_HSE)
//
//		RCC_CFGR |= (1<<SW0);
//		RCC_CFGR &= ~(1<<SW1);
//
//#elif (RCC_SYS_CLK == RCC_HSI)
//
//		RCC_CFGR &= ~(1<<SW0);
//		RCC_CFGR &= ~(1<<SW1);
//#else
//		local_enuErrorstate = ES_OUT_OF_RANGE;
//
//#endif
///** Bits 3:2 SWS: System clock switch status
// * Set and cleared by hardware to indicate which clock source is used as system clock.
//00: HSI oscillator used as system clock
//01: HSE oscillator used as system clock
//10: PLL used as system clock
//11: not applicable */
//	u8 SysClkStatus= ((RCC_CFGR>>SWS0) & 0b11);
//
//#if   (SysClkStatus == 0b00)
//		/*SysClk is HSI oscillator*/
//	local_enuErrorstate = ES_OK;
//#elif (SysClkStatus == 0b01)
//		/*SysClk is HSE oscillator*/
//	local_enuErrorstate = ES_OK;
//#elif (SysClkStatus == 0b10)
//		/*SysClk is PLL oscillator*/
//	local_enuErrorstate = ES_OK;
//#else
//		local_enuErrorstate = ES_OUT_OF_RANGE;
//#endif
//		/*Bits 7:4 HPRE: AHB prescaler
//		Set and cleared by software to control the division factor of the AHB clock.
//		0xxx: SYSCLK not divided
//		1000: SYSCLK divided by 2
//		1001: SYSCLK divided by 4
//		1010: SYSCLK divided by 8
//		1011: SYSCLK divided by 16
//		1100: SYSCLK divided by 64
//		1101: SYSCLK divided by 128
//		1110: SYSCLK divided by 256
//		1111: SYSCLK divided by 512*/
//#if   (AHB_prescaler == SYSCLK_2)
//
//	/*	RCC_CFGR &= ~(1<<HPRE0);
//		RCC_CFGR &= ~(1<<HPRE1);
//		RCC_CFGR &= ~(1<<HPRE2);
//		RCC_CFGR &= ~(1<<HPRE3);*/
//		RCC_CFGR |= ((SYSCLK_2 | 0b0000) << 4); // masking 4 bits together then set them to bits which start at 4
//		local_enuErrorstate = ES_OK;
//#elif (AHB_prescaler == SYSCLK_8)
//
//		RCC_CFGR |= ((SYSCLK_8 | 0b0000) << 4);
//		local_enuErrorstate = ES_OK;
//#else
//		local_enuErrorstate = ES_OUT_OF_RANGE;
//
//#endif
//#if   (APB1_prescaler == HCLK_8)
//		RCC_CFGR |=  ((HCLK_8 | 0b000) << 8);
//		local_enuErrorstate = ES_OK;
//
//#elif (APB1_prescaler == HCLK_16)
//		RCC_CFGR |=  ((HCLK_16 | 0b000) << 8);
//		local_enuErrorstate = ES_OK;
//#else
//		local_enuErrorstate = ES_OUT_OF_RANGE;
//#endif
//
//#if  (APB2_prescaler == HCLK_2)
//		RCC_CFGR |=  ((HCLK_2 | 0b000) << 11);
//		local_enuErrorstate = ES_OK;
//#elif (APB2_prescaler == HCLK_8)
//		RCC_CFGR |=  ((HCLK_2 | 0b000) << 11);
//		local_enuErrorstate = ES_OK;
//#else
//		local_enuErrorstate = ES_OUT_OF_RANGE;
//#endif
//
//#if (ADC_prescaler == PCLK2_4)
//		RCC_CFGR |=  ((PCLK2_4 | 0b00) << 14);
//		local_enuErrorstate = ES_OK;
//#elif (ADC_prescaler == PCLK2_2)
//		RCC_CFGR |=  ((PCLK2_2 | 0b00) << 14);
//		local_enuErrorstate = ES_OK;
//#else
//		local_enuErrorstate = ES_OUT_OF_RANGE;
//#endif
//
//
//
//
//
//	return local_enuErrorstate;
//}
//
//ES_t		RCC_enuEnablePerClk(u8 BusId , u8 copy_u8PerID)
//{
//	ES_t local_enuErrorstate = ES_NOK ;
//	/*		Range Check			*/
//	if(copy_u8PerID < 32)
//	{
//		switch(BusId)
//		{
//			case	RCC_AHB		:	RCC_AHBENR  |= (1<<copy_u8PerID);	break;
//			case	RCC_APB1	:	RCC_APB1ENR |= (1<<copy_u8PerID);	break;
//			case	RCC_APB2	:	RCC_APB2ENR |= (1<<copy_u8PerID);	break;
//		}
//		local_enuErrorstate = ES_OK ;
//	}
//	else
//	{
//
//		local_enuErrorstate = ES_OUT_OF_RANGE ;
//
//	}
//
//	return local_enuErrorstate ;
//}
//ES_t		RCC_enuDisablePerClk(u8 BusId , u8 copy_u8PerID)
//{
//	ES_t local_enuErrorstate = ES_NOK ;
//	/*		Range Check							*/
//	if(copy_u8PerID < 32)
//	{
//		switch(BusId)
//		{
//			case	RCC_AHB		:	RCC_AHBENR &=  ~(1<<copy_u8PerID);	break;
//			case	RCC_APB1	:	RCC_APB1ENR &= ~(1<<copy_u8PerID);	break;
//			case	RCC_APB2	:	RCC_APB2ENR &= ~(1<<copy_u8PerID);	break;
//		}
//		local_enuErrorstate = ES_OK ;
//	}
//	else
//	{
//		local_enuErrorstate = ES_OUT_OF_RANGE ;
//	}
//
//return local_enuErrorstate ;
//}

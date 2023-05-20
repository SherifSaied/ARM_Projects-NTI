#ifndef		RCC_CONFIG_H_
#define		RCC_CONFIG_H_





/*
  Options :
			RCC_PRESCALLER_0
			RCC_PRESCALLER_2
			RCC_PRESCALLER_4
			RCC_PRESCALLER_8
			RCC_PRESCALLER_16
			RCC_PRESCALLER_64
			RCC_PRESCALLER_128
			RCC_PRESCALLER_256
			RCC_PRESCALLER_512
*/
#define RCC_AHB_PRESCALLER    RCC_PRESCALLER_0


/*
  Options :
			RCC_PRESCALLER_0
			RCC_PRESCALLER_2
			RCC_PRESCALLER_4
			RCC_PRESCALLER_8
			RCC_PRESCALLER_16
*/
/* Note : this bus clock must not exceed 36 MHZ*/
#define RCC_APB1_PRESCALLER   RCC_PRESCALLER_0

/*
  Options :
			RCC_PRESCALLER_0
			RCC_PRESCALLER_2
			RCC_PRESCALLER_4
			RCC_PRESCALLER_8
			RCC_PRESCALLER_16
*/
#define RCC_APB2_PRESCALLER   RCC_PRESCALLER_0


/*
  Options :
			RCC_PRESCALLER_2
			RCC_PRESCALLER_4
			RCC_PRESCALLER_6
			RCC_PRESCALLER_8
*/
#define RCC_ADC_PRESCALLER    RCC_PRESCALLER_2
/*
  Options :
			NO_CLOCK
			HSI_CLOCK
			HSE_CLOCK
			PLL_CLOCK
			SYSTEM_CLOCK
*/
#define   RCC_MCO_PIN       NO_CLOCK

/*
  Options : 2 : 16
*/
#define RCC_PLL_MUL       2
/*
  Options :
			RCC_PLL_HSI_BY2
			RCC_PLL_HSE
			RCC_PLL_HSE_BY2
*/
#define  RCC_PLL_SOURCE    RCC_PLL_HSI_BY2
/*
  Options : -16 : 15
*/
#define  HSI_STEP_CORRECTION   0
/*
 Clock security system : (ENABLE - DISABLE)
 */
#define    CSS_ON            DISABLE

/* Options :
			RCC_HSI
			RCC_HSE_CRYSTAL
			RCC_HSE_RC
			RCC_PLL
*/
#define   SYS_CLOCK         RCC_HSI


/**************itt_1***********/
//                              /*you can choose between RCC_AHB,,,RCC_APB1,,,HRCC_APB2*/
//
//#define     Micro_ClkOutput     HSI_Clk_S   							/*MCO: Microcontroller clock output
//																		Set and cleared by software.
//																		0xx: No clock
//																		100: System clock (SYSCLK) selected
//																		101: HSI clock selected
//																		110: HSE clock selected
//																		111: PLL clock divided by 2 selected
//																		*/
//#define		USB_prescaler      PLL_ClkDiv
//
//#define     PLL_multiF         PLL_inputClk2
//
//
//#define     HSE_DivPLLentry    HSE_NotDiv				  /*you can choose between HSE_NotDiv,,,HSE_Div2*/
//#define     PLL_entryClk       RCC_HSI_2                  /*you can choose between HSI/2,,,HSE*/
//
//
//
////#define		SYSCLK_SW			RCC_HSI                   /*you can choose between HSI,,,HSE,,,PLL*/
//
//#define     AHB_prescaler       SYSCLK_8                  /*you can choose between   SYSCLK_notD
//																					 SYSCLK_2
//																					 SYSCLK_4
//																					 SYSCLK_8
//																					 SYSCLK_16
//																					 SYSCLK_64
//																					 SYSCLK_128
//																					 SYSCLK_256
//																					 SYSCLK_512 */
//#define     Int_RC                 	ON						/*you can choose between ON or OFF*/
//#define   	HSE_ClkEnable 			ON                      /*you can choose between ON or OFF*/
//#define    	PLL_enable              OFF						/*you can choose between ON or OFF*/
//#define    	APB1_prescaler        	HCLK_16					/*you can choose between  HCLK_notD
//																					  HCLK_2
//																					  HCLK_4
//																					  HCLK_8
//																					  HCLK_16 */
//
//#define    APB2_prescaler        HCLK_8                     /*you can choose between  HCLK_notD
//																					  HCLK_2
//																					  HCLK_4
//																					  HCLK_8
//																					  HCLK_16 */
//#define     ADC_prescaler         PCLK2_2
//
//
//







#endif

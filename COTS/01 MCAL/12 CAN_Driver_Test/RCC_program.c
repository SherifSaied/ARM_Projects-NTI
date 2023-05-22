/*******************************************************************************************
* ! Title : RCC_program
* ! File Name : RCC_program.c
* ! Description : This file has the definition of the RCC functions and
* the usage of the global variables.
* ! Compiler : GNU ARM Cross Compiler
* ! Target : STM32F103xxxx
********************************************************************************************/
/*******************************************************************************************
* LOG :
* VERSION    AUTHOR              DATE              DESCRIPTION
* v1.0       Abdelrahman Hossam  15 JUL,2020       - Initial creation
* v2.0       Abdelrahman Hossam  24 JAN,2021	   - Edit All Driver APIs and Documentation
********************************************************************************************/

/*
 * This file is part of the OP Coders Graduation Project.
 * ******************************************************************************************************************
 * This module contains the RCC APIs Implementation for all CLK Configurations Needed in any Other Peripheral
 * This file provoides Four functions to be called from user application
 * 1- MRCC_voidClkInit(void) :-  Setups the system clock (System clock source, PLL Multiplier
 *                    		   factors, AHB/APBx prescalers and Flash settings).
 *                     	   This function is called at start of code after reset and
 *                      	   before using any Functions in main program. This call is made inside
 *                            the "main.c" file.
 * 2- MRCC_voidSetClkSource (u32 Copy_u32Source):-  Set the Clock source for my Micro-Controller, must be used after
 * 												  enable the CLK source using the next Function  This call is made inside
 *                            					  the "main.c" file.
 * 3- MRCC_voidSetClkStatus (u32 Copy_u32Source, u8 Copy_u8State):- Enable or Disable the clock Source you Enter
 *  															  This call is made inside the "main.c" file.
 * 4- MRCC_voidSetPeripheralclock (u8 Copy_u8Bus, u32 Copy_u32peripheral, u8 Copy_u8State):- Enable the CLK for a peripheral
 *     This call is made inside the "main.c" file.
 * ******************************************************************************************************************
 * The Startup Code Sets the Clock to 72 MHz using HSI as a Source.
 * ******************************************************************************************************************
 * Sequence To initialize System CLock
 * - Set the CLK Source(ClkSource) in Configuration File
 * - In case You want to Use a Division Factor Set it in the Configuration File from the options
 * - In Case of PLL you must choose the PLL Source and division Factor From the Options
 * ******************************************************************************************************************
 * To change the CLK source you must enable the new CLK source before you disable the old one
 * use this Sequence
 * 1- MRCC_voidSetClkStatus (New Source, ON)
 * 2- MRCC_voidSetClkSource (New Source)
 * 3- MRCC_voidSetClkStatus (Old Source, OFF)
 * Note In Case of PLL two Sources must be ON
 * ******************************************************************************************************************
 * To SET the Clock State for a peripheral you must choose the BUS which the Peripheral is connected to.
 */


/****************************************/
/* 			     Directives 			*/
/****************************************/
#include "BIT_MATH.h"
#include "LIB.h"
#include "STD_TYPES.h"
#include "RCC_configuration.h"
#include "RCC_interface.h"
#include "RCC_private.h"



/******************************************************************************/
/*Function: MRCC_voidClkInit		                     						  */
/*I/P Parameters: nothing						 							  */
/*Returns:void                              				  */
/*Desc:This Function to enable The Clock due to pre-configurations	   	      */
/******************************************************************************/
void MRCC_voidClkInit(void)
{
  #if ClkSource == HSE
	/*HSE ON*/
		MRCC_voidSetClkStatus(HSE_Enable,ON);
	/*pull on Flag to check on the HSE if ready or not*/
	while(((RCC ->RCC_CR>>17)& 0x00000001)!=1);
		MRCC_voidSetClkSource(HSE);
	/*PLL OFF*/
		MRCC_voidSetClkStatus(PLL_Enable,OFF);

  #endif

  #if ClkSource == HSI
	/*HSI ON*/
		 MRCC_voidSetClkStatus(HSI_Enable,ON);
	/*pull on Flag to check on the HSE if ready or not*/
	while(((RCC ->RCC_CR>>1)& 0x00000001)!=1);
		MRCC_voidSetClkSource(HSI);
	/*PLL OFF*/
		MRCC_voidSetClkStatus(PLL_Enable,OFF);
	/*HSE OFF*/
		MRCC_voidSetClkStatus(HSE_Enable,OFF);
  #endif

  #if ClkSource == PLL

	switch (PLL_Source) {
		case HSE_Src:
			           /*Switch to HSI*/
					   MRCC_voidSetClkSource(HSE);
					   /*PLL OFF*/
					   MRCC_voidSetClkStatus(PLL_Enable,OFF);
					   /* Setting The prescaler of the PLL */
					   RCC ->RCC_CFGR &= Prescaler_ResetMask;
					   RCC ->RCC_CFGR |= PLL_Prescaler;
					   /*Setting the Division Factor*/
					   RCC ->RCC_CFGR2 &= divisionfactor_ResetMask;
					   RCC ->RCC_CFGR2 |= inputDivisionFactor;
					   /* Setting the source to HSI */
					   RCC ->RCC_CFGR |= (Src_bit);
					   /*PLL ON*/
					   MRCC_voidSetClkStatus(PLL_Enable,ON);
					   /*pull on Flag to check on the HSE if ready or not*/
					   while(((RCC ->RCC_CR>>25)& 0x00000001)!=1);
					   /*Switch to PLL*/
					   MRCC_voidSetClkSource(PLL);
					    break;
		case HSI_Src:
						/*HSI ON*/
			            MRCC_voidSetClkStatus(HSI_Enable,ON);
						/*pull on Flag to check on the HSE if ready or not*/
						while(((RCC ->RCC_CR>>1)& 0x00000001)!=1);
						/*Switch to HSI*/
						MRCC_voidSetClkSource(HSI);
						/*PLL OFF*/
						MRCC_voidSetClkStatus(PLL_Enable,OFF);
						/*HSE OFF*/
						MRCC_voidSetClkStatus(HSE_Enable,OFF);
						/* Setting The prescaler of the PLL */
						RCC ->RCC_CFGR &= Prescaler_ResetMask;
						RCC ->RCC_CFGR |= PLL_Prescaler;
						/* Setting the source to HSI/2 */
						RCC ->RCC_CFGR &= ~(Src_bit);
						/*PLL ON*/
						MRCC_voidSetClkStatus(PLL_Enable,ON);
						/*pull on Flag to check on the HSE if ready or not*/
						while(((RCC ->RCC_CR>>25)& 0x00000001)!=1);
						/*Switch to PLL*/
						MRCC_voidSetClkSource(PLL);
						break;
		default:
			break;
	}
  #endif

}


/******************************************************************************/
/*Function: MRCC_voidSetClkSource                          					  */
/*I/P Parameters: Copy_u32Source            								  */
/*Returns:void                              				  */
/*Desc:This Function Set the Clock source for my micro-controller	          */
/******************************************************************************/
/*Options:-   - HSI 	  - HSE		   - PLL				 				  */
/******************************************************************************/
void MRCC_voidSetClkSource (u32 Copy_u32Source)
{
	/* Switching on the clock sources */
  switch (Copy_u32Source)
  {
	/*IF the clock source is HSI the bits 0,1 are cleared */
	/* then updated with the corresponding value of HSI   */
    case HSI:
				RCC ->RCC_CFGR &= SW_Resetmask;
				RCC ->RCC_CFGR |= Copy_u32Source;
				break;
	/*IF the clock source is HSE the bits 0,1 are cleared */
	/* then updated with the corresponding value of HSE   */
	case HSE:
			    RCC ->RCC_CFGR &= SW_Resetmask;
				RCC ->RCC_CFGR |= Copy_u32Source;
				break;
	/*IF the clock source is PLL the bits 0,1 are cleared */
	/* then updated with the corresponding value of PLL   */
	case PLL:
				RCC ->RCC_CFGR &= SW_Resetmask;
				RCC ->RCC_CFGR |= Copy_u32Source;
				break;
	default:
		break;
}
	}

/******************************************************************************/
/*Function: MRCC_voidSetPeripheralclock                     					  */
/*I/P Parameters: Copy_u8Bus , Copy_u32peripheral , Copy_u8State  			  */
/*Returns:void                              				  */
/*Desc:This Function to enable or disable the clock for a peripheral 	      */
/******************************************************************************/
/* Copy_u8Bus         :-    - AHB   - APB1   - APB2							  */
/* Copy_u32peripheral :-    Choose peripheral From Configuration File		  */
/* Copy_u8State       :-    - ON    - OFF									  */
/******************************************************************************/
void MRCC_voidSetPeripheralclock (u8 Copy_u8Bus, u32 Copy_u32peripheral, u8 Copy_u8State)
{
	/* Switching on buses of peripherals (AHB, APB1, APB2) */
	switch (Copy_u8Bus)
	{
	    /* The AHB Bus is Chosen */
		case AHB:
			      /* checking on the state of the peripheral */
				  if (Copy_u8State==ON)
				  {
					  /* Setting the peripheral bit with one to enable the peripheral */
					  RCC ->RCC_AHBENR |= Copy_u32peripheral;
				  }
				  else
				  {
					  /* Setting the peripheral bit with zero to disable the peripheral */
					  RCC ->RCC_AHBENR &= ~Copy_u32peripheral;
				  }
				  break;
		/* The APB1 Bus is Chosen */
		case APB1:
			      /* checking on the state of the peripheral */
				  if (Copy_u8State==ON)
				  {
					  /* Setting the peripheral bit with one to enable the peripheral */
					  RCC ->RCC_APB1ENR |= Copy_u32peripheral;
				  }
				  else
				  {
					  /* Setting the peripheral bit with zero to disable the peripheral */
					  RCC ->RCC_APB1ENR &= ~Copy_u32peripheral;
				  }
				  break;
		/* The APB2 Bus is Chosen */
		case APB2:
				  /* checking on the state of the peripheral */
				  if (Copy_u8State==ON)
				  {
					  /* Setting the peripheral bit with one to enable the peripheral */
					  RCC ->RCC_APB2ENR |= Copy_u32peripheral;
				  }
				  else
				  {
					  /* Setting the peripheral bit with zero to disable the peripheral */
					  RCC ->RCC_APB2ENR &= ~Copy_u32peripheral;
				  }
				  break;
		default:
			break;
	}
}


/******************************************************************************/
/*Function: RCC_voidSetClkStatus                     						  */
/*I/P Parameters: Copy_u32Source , Copy_u8State  							  */
/*Returns:void                                			  */
/*Desc:This Function to enable or disable the clock Source	        	      */
/******************************************************************************/
/* Copy_u32Source :-  - HSI_Enable    - HSE_Enable    - PLL_Enable		      */
/* Copy_u8State   :-  - ON            - OFF									  */
/******************************************************************************/
void MRCC_voidSetClkStatus (u32 Copy_u32Source, u8 Copy_u8State)
{
	/* Switching on the clock sources (HSI, HSE, PLL) */
	switch (Copy_u32Source) {
		case HSI_Enable:
			             /* checking on the state of the peripheral */
						 if (Copy_u8State==ON)
					     {
						  /* Setting the HSI on bit with one to enable it */
						  RCC ->RCC_CR |= Copy_u32Source;
						 }
						 else
						 {
						  /* Setting the HSI bit with zero to disable it */
						  RCC ->RCC_CR &= ~Copy_u32Source;
						 }
						 break;
		case HSE_Enable:
			             /* checking on the state of the peripheral */
						 if (Copy_u8State==ON)
					     {
						  /* Setting the HSE on bit with one to enable it */
						  RCC ->RCC_CR |= Copy_u32Source;
						 }
						 else
						 {
						  /* Setting the HSE bit with zero to disable it */
						  RCC ->RCC_CR &= ~Copy_u32Source;
						 }
						 break;
		case PLL_Enable:
			             /* checking on the state of the peripheral */
						 if (Copy_u8State==ON)
					     {
						  /* Setting the PLL on bit with one to enable it */
						  RCC ->RCC_CR |= Copy_u32Source;
						 }
						 else
						 {
						  /* Setting the PLL bit with zero to disable it */
						  RCC ->RCC_CR &= ~Copy_u32Source;
						 }
						 break;
		default:
			break;
	}
}


// ----------------------------------------------------------------------------

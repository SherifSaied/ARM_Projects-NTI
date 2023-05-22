/****************************************************************************************
* ! Title : SYSTICK_program
* ! File Name : SYSTICK_program.c
* ! Description : This file has the definition of the SYSTICK functions and
* the usage of the global variables.
* ! Compiler : GNU ARM Cross Compiler
* ! Target : STM32F103xxxx & STM32F446xxxx Micro-controller
****************************************************************************************/
/****************************************************************************************
* LOG :
* VERSION    AUTHOR              DATE              DESCRIPTION
* v1.0       Abdelrahman Hossam  29 AUG,2020       - Initial creation
* v2.0       Seif Al-dein Ahmed  24 Jan,2021       - Modifying STK Driver, Adding APIs
****************************************************************************************/

/*
 * This file is part of the OP Coders Graduation Project.
 * ******************************************************************************************************************
 * This module contains the STK APIs Implementation for all Timer Configurations Needed in any Other Peripheral
 * This file provides ELEVEN functions to be called from user 
 * 1- MSYSTICk_voidConfig(void) :-  Setups the Systick Configurations ( Interrupt Initialization,
 * 										  Systick clock source and Pre-Load setting during initialization).
 *                     	                  This function is called inside the "main.c" file.
 * 2- MSYSTICk_voidEnable(void):-   Enables The STK Pripheral, must be used if you want to enable it.
 * 										  
 * 3- MSYSTICk_voidDisable(void):-  Disables The STK Pripheral, must be used if you want to disable it.
 * 
 * 4- MSYSTICk_voidPreLoad(u32 copy_u32PreloadValue):- Controls SYSTICK Timer Preload.
 * 5- Mdelay_ms(u32 copy_u32Time):- If you want a delay of 100ms as an example, just pass 100 in this function's argument.
 * 6- MSYSTICK_voidSetBusyWait(u32 copy_u32Ticks, u8 copy_TickType): Holds the processor for a period of time.
 * 7- MSYSTICK_voidSetIntervalSingle( u32 copy_u32Ticks, u8 copy_u8TickType ,void (*Copy_ptr)(void) ): Makes Async function fires an 
 * 																									  interrupt after specific time period.
 * 8- MSYSTICK_voidSetIntervalPeriodic( u32 copy_u32Ticks, u8 copy_u32Ticks, void (*Copy_ptr)(void) ):- Makes Async function fires an 
 *																									   interrupt after specific time period.
 * 9-  MSYSTICK_voidStopInterval(void): stops the periodic events of the SYSTICK timer.
 * 10- MSYSTICK_u32GetElapsedTime(void): Gets the Elapsed Time from the start of the Timer.
 * 11- MSYSTICK_u32GetRemainingTime(void): Get the remaining Time for the Timer to overflow.
 * ******************************************************************************************************************
 */

/****************************************/
/* 			     Directives 			*/
/****************************************/
#include "LIB.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_configuration.h"
#include "SYSTICK_private.h"
// ----------------------------------------------------------------------------


/******************************************************************************/
/*Function: MSYSTICk_voidConfig                          			  */
/*I/P Parameters: no thing		            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function control SYSTICK Timer depend on pre-configurations	      */
/******************************************************************************/
void MSYSTICk_voidInit(void)
{
	/* Enable The SYSTICK Timer Interrupt */
	#if (SYSTICK_TICKINT == ENABLE)
			SET_BIT(STK->CTRL, STK_CTRL_TICKINT_BIT);
	/* Disable The SYSTICK Timer Interrupt */
    #elif (SYSTICK_TICKINT == DISABLE)
			CLR_BIT(STK->CTRL, STK_CTRL_TICKINT_BIT);
	#endif

	#if (SYSTICK_CLK == AHB_CLK)
			/* The SYSTICK Timer Clock Source is AHB */
			SET_BIT(STK->CTRL, STK_CTRL_CLKSOURCE_BIT);


	#elif (SYSTICK_CLK == AHB_DIVIDED_BY_8_CLK)
			/* The SYSTICK Timer Clock Source is AHB/8 */
			CLR_BIT(STK->CTRL, STK_CTRL_CLKSOURCE_BIT);
    #endif

    /*Pre-Load setting during initialization */
    #if(PRELOAD_ENABLE)
		    STK->LOAD = PRELOAD_VALUE;
    #endif


}


/******************************************************************************/
/*Function: MSYSTICk_voidEnable                     					  */
/*I/P Parameters: void			            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function enables the SYSTICK Timer						          */
/******************************************************************************/
void MSYSTICk_voidEnable(void)
{
	/* Enable The SYSTICK Timer */
	SET_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

}

/******************************************************************************/
/*Function: MSYSTICk_voidDisable                     				  */
/*I/P Parameters: void			            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function disables the SYSTICK Timer						          */
/******************************************************************************/
void MSYSTICk_voidDisable(void)
{

	/* Disable The SYSTICK Timer */
	CLR_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);


}
/******************************************************************************/
/*Function: MSYSTICk_voidPreLoad                          			  */
/*I/P Parameters: copy_u32PreloadValue		            					  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function control SYSTICK Timer Preload						      */
/******************************************************************************/
void MSYSTICk_voidPreLoad(u32 copy_u32PreloadValue)
{
	/*IF required immediately update the value register*/
    #if (PRELOAD_IMMEDIATE)

		STK->LOAD = copy_u32PreloadValue;
		STK->VAL  = PRELOAD_VALUE;

	/*After this iteration required to change the pre-load value*/
    #else
	{
		STK->LOAD = copy_u32PreloadValue;
	}
    #endif
}


/******************************************************************************/
/*Function: Mdelay_ms					                          			  */
/*I/P Parameters: copy_u32Time				            					  */
/*Returns:it returns nothing	                            				  */
/*Desc:This Function makes a delay for number of m sec up to 16 sec		      */
/******************************************************************************/
void Mdelay_ms(u32 copy_u32Time)
{
	/* Calculation of the pre load value to count specific number of m sec */
	u32 local_u32preLoad = 16777216 * (1-((copy_u32Time*1000)/16777216));

	/* Update the Load registers with number of m sec i want to count */
	STK->LOAD = local_u32preLoad;
	STK->VAL  = PRELOAD_VALUE;

	/* Enable the Timer */
	SET_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

	/* Polling on the flag of the timer */
	while (GET_BIT(STK->CTRL,STK_CTRL_COUNTFLAG_BIT)==0);

	/* Disable the counter */
	CLR_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

	/* update the pre-load value with 0 */
	STK->LOAD = 0;
	STK->VAL  = 0;
}

/******************************************************************************/
/*Function: MSYSTICK_voidSetBusyWait		                          		  */
/*I/P Parameters: u32 copy_u32Ticks, u8 copy_TickType						  */
/*copy_TickType OPTIONS: NANO_SEC, MILLI_SEC, MICRO_SEC, SEC				  */
/*Returns:it returns nothing	                            				  */
/*Desc:Makes a delay for number of ticks(This holds the processor)		      */
/******************************************************************************/
void MSYSTICK_voidSetBusyWait(u32 copy_u32Ticks, u8 copy_u8TickType)
{

	#if (SYSTICK_CLK == AHB_CLK)
	{
		if(copy_u8TickType   == NANO_SEC)
			copy_u32Ticks *= (1/125);
		
		else if(copy_u8TickType == MILLI_SEC)
			copy_u32Ticks *= 8;
		
		else if (copy_u8TickType == MICRO_SEC)
			copy_u32Ticks *= 8000;
		
		else if( copy_u8TickType == SEC)
			copy_u32Ticks *= 8000000;
	}
	#elif	(SYSTICK_CLK == AHB_DIVIDED_BY_8_CLK)
		if (copy_u8TickType   == NANO_SEC)
			copy_u32Ticks *= (10^(-3));
		
		else if (copy_u8TickType == MILLI_SEC)
			copy_u32Ticks *= 1000;
		
		else if (copy_u8TickType == MICRO_SEC)
			copy_u32Ticks *= 1;
		
		else if (copy_u8TickType == SEC)
			copy_u32Ticks *= 1000000;
		else
		{

		}
	#endif
	if(copy_u32Ticks < 16777216)
	{
		/* Update the Load registers with number of Ticks or counts */
		STK->LOAD  =  0x00000000;
		STK->LOAD = copy_u32Ticks;
		STK->VAL  = PRELOAD_VALUE;

		/* Enable the Timer */
		SET_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

		/* Polling on the flag of the timer */
		while (GET_BIT(STK->CTRL,STK_CTRL_COUNTFLAG_BIT)==0);

		/* Disable the counter */
		CLR_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

		/* update the pre-load value with 0 */
		STK->LOAD = 0;
		STK->VAL  = 0;
	}
}

/***************************************************************************************************/
/*Function: MSYSTICK_voidSetIntervalSingle	                       			    				   */
/*I/P Parameters: u32 copy_u32Ticks, u8 copy_u8TickType ,void (*Copy_ptr)(void) 				   */
/*copy_TickType OPTIONS: NANO_SEC, MILLI_SEC, MICRO_SEC, SEC				    				   */
/*Returns:it returns nothing	                            				    				   */
/*Desc:Makes Async function fires an interrupt after specific time once	        				   */
/***************************************************************************************************/
void MSYSTICK_voidSetIntervalSingle( u32 copy_u32Ticks, u8 copy_u8TickType ,void (*Copy_ptr)(void) )
{
	#if (SYSTICK_CLK == AHB_CLK)
	{
		if(copy_u8TickType   == NANO_SEC)
			copy_u32Ticks *= (1/125);
		
		else if(copy_u8TickType == MILLI_SEC)
			copy_u32Ticks *= 8;
		
		else if (copy_u8TickType == MICRO_SEC)
			copy_u32Ticks *= 8000;
		
		else if( copy_u8TickType == SEC)
			copy_u32Ticks *= 8000000;
	}
	#elif	(SYSTICK_CLK == AHB_DIVIDED_BY_8_CLK)
		if (copy_u8TickType   == NANO_SEC)
			copy_u32Ticks *= (10^(-3));
		
		else if (copy_u8TickType == MILLI_SEC)
			copy_u32Ticks *= 1000;
		
		else if (copy_u8TickType == MICRO_SEC)
			copy_u32Ticks *= 1;
		
		else if (copy_u8TickType == SEC)
			copy_u32Ticks *= 1000000;
		else
		{

		}
	#endif
	
	if(copy_u32Ticks < 16777216)
	{
	/* Disable the counter */
	CLR_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);
	STK->VAL =0;
	/* Update the Load registers with number of Ticks or counts */
	STK->LOAD=copy_u32Ticks;


	/* Enable the Timer */
	SET_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

	/* Save CallBack */
	SYSTICK_CallBack = Copy_ptr;
	/* Set Mode to Single */
	SYSTICK_u8ModeOfInterval = SYSTICK_SINGLE_INTERVAL;

	/* Enable the interrupt */
	SET_BIT(STK->CTRL, STK_CTRL_TICKINT_BIT);
	}
}

/***************************************************************************************************/
/*Function: MSYSTICK_voidSetIntervalPeriodic	                       			  				   */
/*I/P Parameters: u32 copy_u32Ticks, u8 copy_u32Ticks, void (*Copy_ptr)(void)      				   */
/*copy_TickType OPTIONS: NANO_SEC, MILLI_SEC, MICRO_SEC, SEC				    				   */
/*Returns:it returns nothing	                            				  					   */
/*Desc:Makes Async function fires an interrupt after specific time 		      					   */
/***************************************************************************************************/
void MSYSTICK_voidSetIntervalPeriodic( u32 copy_u32Ticks, u8 copy_u8TickType, void (*Copy_ptr)(void) )
{
	#if (SYSTICK_CLK == AHB_CLK)
	{
		if(copy_u8TickType   == NANO_SEC)
			copy_u32Ticks *= (1/125);
		
		else if(copy_u8TickType == MILLI_SEC)
			copy_u32Ticks *= 8;
		
		else if (copy_u8TickType == MICRO_SEC)
			copy_u32Ticks *= 8000;
		
		else if( copy_u8TickType == SEC)
			copy_u32Ticks *= 8000000;
	}
	#elif	(SYSTICK_CLK == AHB_DIVIDED_BY_8_CLK)
		if (copy_u8TickType   == NANO_SEC)
			copy_u32Ticks *= (10^(-3));
		
		else if (copy_u8TickType == MILLI_SEC)
			copy_u32Ticks *= 1000;
		
		else if (copy_u8TickType == MICRO_SEC)
			copy_u32Ticks *= 1;
		
		else if (copy_u8TickType == SEC)
			copy_u32Ticks *= 1000000;
		else
		{

		}
	#endif
	if(copy_u32Ticks < 16777216)
	{
	/* Update the Load registers with number of Ticks or counts */
	STK->LOAD = copy_u32Ticks;

	/* Enable the Timer */
	SET_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

	/* Save CallBack */
	SYSTICK_CallBack = Copy_ptr;

	/* Set Mode to Single */
	SYSTICK_u8ModeOfInterval = SYSTICK_PERIOD_INTERVAL;

	/* Enable the Interrupt */
	SET_BIT(STK->CTRL, STK_CTRL_TICKINT_BIT);
	}
}

/******************************************************************************/
/*Function: MSYSTICK_voidStopInterval		                       			  */
/*I/P Parameters: void						            					  */
/*Returns:it returns nothing	                            				  */
/*Desc:Makes This function stops the periodic events of the SYSTICK timer     */
/******************************************************************************/
void MSYSTICK_voidStopInterval(void)
{
	/* Disable the Interrupt */
	CLR_BIT(STK->CTRL, STK_CTRL_TICKINT_BIT);

	/* Disable the Timer */
	CLR_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

	/* update the pre-load value with 0 */
	STK->LOAD = 0;
	STK->VAL  = 0;
}

/******************************************************************************/
/*Function: MSYSTICK_u32GetElapsedTime		                       			  */
/*I/P Parameters: void						            					  */
/*Returns:it returns u32		                            				  */
/*Desc:Makes This function Get the Elapsed Time from the start of the Timer   */
/******************************************************************************/
u32 MSYSTICK_u32GetElapsedTime(void)
{
	/* Local variable to get the elapsed time in it */
	u32 Local_u32ElapsedTime = 0;

	/*Reading the elapsed time form SYSTICK registers*/
	Local_u32ElapsedTime = ( (STK->LOAD) - (STK->VAL) );

	/*Returning the Control to the caller function with the elapsed time*/
	return Local_u32ElapsedTime;
}

/******************************************************************************/
/*Function: MSYSTICK_u32GetRemainingTime		                       		  */
/*I/P Parameters: void						            					  */
/*Returns:it returns u32		                            				  */
/*Desc:Makes This function Get the remaining Time for the Timer to overflow   */
/******************************************************************************/
u32 MSYSTICK_u32GetRemainingTime(void)
{
	/* Local variable to get the remaining time in it */
	u32 Local_u32RemainTime;

	/*Reading the remaining time form SYSTICK registers*/
	Local_u32RemainTime = STK->VAL;

	/*Returning the Control to the caller function with the remaining time*/
	return Local_u32RemainTime;
}

/******************************************************************************/
/*Function: MSysTick_Handler		                       			          */
/*I/P Parameters: void						            					  */
/*Returns:it returns Nothing		                            			  */
/*Desc: ISR Handler of Systick												  */
/******************************************************************************/
void MSysTick_Handler(void)
{
	/* Local Variable to clear the flag with it */
	u8 Local_u8Temporary;

	if (SYSTICK_u8ModeOfInterval == SYSTICK_SINGLE_INTERVAL)
	{
		/* Disable the Interrupt */
		CLR_BIT(STK->CTRL, STK_CTRL_TICKINT_BIT);

		/* Disable the Timer */
		CLR_BIT(STK->CTRL, STK_CTRL_ENABLE_BIT);

		/* update the pre-load value with 0 */
		STK->LOAD = 0;
		STK->VAL  = 0;
	}

	/* Callback notification */
	SYSTICK_CallBack();

	/* Clear interrupt flag */
	Local_u8Temporary = GET_BIT(STK->CTRL,STK_CTRL_COUNTFLAG_BIT);
}
// ----------------------------------------------------------------------------

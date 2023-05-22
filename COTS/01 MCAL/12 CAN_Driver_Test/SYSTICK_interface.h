/****************************************************************************************
* ! Title : SYSTICK_interface
* ! File Name : SYSTICK_interface.h
* ! Description : This file has the Prototypes of the Public functions
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTICK_INT_H
#define __SYSTICK_INT_H


#define NANO_SEC	0
#define	MILLI_SEC	1
#define MICRO_SEC	2
#define SEC			(u8)3

/******************************************************************************/
/*Function: MSYSTICk_voidConfig                         				  */
/*I/P Parameters: no thing		            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function control SYSTICK Timer depend on pre-configurations	      */
/******************************************************************************/
void MSYSTICk_voidInit(void);

/******************************************************************************/
/*Function: MSYSTICk_voidEnable                     					  */
/*I/P Parameters: void			            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function enables the SYSTICK Timer						          */
/******************************************************************************/
void MSYSTICk_voidEnable(void);


/******************************************************************************/
/*Function: MSYSTICk_voidDisable                    					  */
/*I/P Parameters: void			            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function disables the SYSTICK Timer						          */
/******************************************************************************/
void MSYSTICk_voidDisable(void);

/******************************************************************************/
/*Function: MSYSTICk_voidPreLoad                          			  */
/*I/P Parameters: copy_u32PreloadValue		            					  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function control SYSTICK Timer Preload						      */
/******************************************************************************/
void MSYSTICk_voidPreLoad(u32 copy_u32PreloadValue);

/******************************************************************************/
/*Function: Mdelay_ms					                          			  */
/*I/P Parameters: copy_u32Time				            					  */
/*Returns:it returns nothing	                            				  */
/*Desc:This Function makes a delay for number of m sec up to 16 sec		      */
/******************************************************************************/
void Mdelay_ms(u32 copy_u32Time);

/******************************************************************************/
/*Function: MSYSTICK_voidSetBusyWait		                       			  */
/*I/P Parameters: u32 copy_u32Ticks, u8 copy_TickType						  */
/*Returns:it returns nothing	                            				  */
/*Desc:Makes a delay for number of ticks(This holds the processor)		      */
/******************************************************************************/
void MSYSTICK_voidSetBusyWait(u32 copy_u32Ticks, u8 copy_TickType);

/***************************************************************************************************/
/*Function: MSYSTICK_voidSetIntervalSingle	                       			    				   */
/*I/P Parameters: u32 copy_u32Ticks, u8 copy_u8TickType ,void (*Copy_ptr)(void) 				   */
/*copy_TickType OPTIONS: NANO_SEC, MILLI_SEC, MICRO_SEC, SEC				    				   */
/*Returns:it returns nothing	                            				    				   */
/*Desc:Makes Async function fires an interrupt after specific time once	        				   */
/***************************************************************************************************/
void MSYSTICK_voidSetIntervalSingle( u32 copy_u32Ticks, u8 copy_u8TickType ,void (*Copy_ptr)(void) );

/***************************************************************************************************/
/*Function: MSYSTICK_voidSetIntervalPeriodic                       			  					   */
/*I/P Parameters: u32 copy_u32Ticks, u8 copy_u32Ticks, void (*Copy_ptr)(void)      				   */
/*copy_TickType OPTIONS: NANO_SEC, MILLI_SEC, MICRO_SEC, SEC				    				   */
/*Returns:it returns nothing	                            				  					   */
/*Desc:Makes Async function fires an interrupt after specific time 		      					   */
/***************************************************************************************************/
void MSYSTICK_voidSetIntervalPeriodic( u32 copy_u32Ticks, u8 copy_u8TickType, void (*Copy_ptr)(void) );

/******************************************************************************/
/*Function: MSYSTICK_voidStopInterval		                       			  */
/*I/P Parameters: void						            					  */
/*Returns:it returns nothing	                            				  */
/*Desc:Makes This function stops the periodic events of the SYSTICK timer     */
/******************************************************************************/
void MSYSTICK_voidStopInterval(void);

/******************************************************************************/
/*Function: MSYSTICK_u32GetElapsedTime		                       			  */
/*I/P Parameters: void						            					  */
/*Returns:it returns u32		                            				  */
/*Desc:Makes This function Get the Elapsed Time from the start of the Timer   */
/******************************************************************************/
u32 MSYSTICK_u32GetElapsedTime(void);
/******************************************************************************/
/*Function: MSYSTICK_u32GetRemainingTime	                       			  */
/*I/P Parameters: void						            					  */
/*Returns:it returns u32		                            				  */
/*Desc:Makes This function Get the remaining Time for the Timer to overflow   */
/******************************************************************************/
u32 MSYSTICK_u32GetRemainingTime(void);
/******************************************************************************/

#endif /* __SYSTICK_INT_H */

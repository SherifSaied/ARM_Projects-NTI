/*******************************************************************************************
* ! Title : RCC_interface
* ! File Name : RCC_interface.h
* ! Description : This file has the Prototypes of the Public functions
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
 * This module contains the RCC APIs Definitions for all CLK Configurations Needed in any Other Peripheral
 * This file provides Four functions be called from user application
 * 1- MRCC_vidClkInit(void) :-  Setups the system clock (System clock source, PLL Multiplier
 *                    		   factors, AHB/APBx prescalers and Flash settings).
 *                     	   This function is called at start of code after reset and
 *                      	   before using any Functions in main program. This call is made inside
 *                            the "main.c" file.
 * 2- MRCC_vidSetClkSource (u32 copy_u32Source):-  Set the Clock source for my Micro-Controller, must be used after
 * 												  enable the CLK source using the next Function  This call is made inside
 *                            					  the "main.c" file.
 * 3- MRCC_vidSetClkStatus (u32 copy_u32Source, u8 copy_u8State):- Enable or Disable the clock Source you Enter
 *  															  This call is made inside the "main.c" file.
 * 4- MRCC_vidSetPeripheralclock (u8 copy_u8Bus, u32 copy_u32peripheral, u8 copy_u8State):- Enable the CLK for a peripheral
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
 * 1- MRCC_vidSetClkStatus (New Source, ON)
 * 2- MRCC_vidSetClkSource (New Source)
 * 3- MRCC_vidSetClkStatus (Old Source, OFF)
 * Note In Case of PLL two Sources must be ON
 * ******************************************************************************************************************
 * To SET the Clock State for a peripheral you must choose the BUS which the Peripheral is connected to.
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MCAL_RCC_INT_H
#define _MCAL_RCC_INT_H


/******************************************************************************/
/*Function: MRCC_vidClkInit		                     						  */
/*I/P Parameters: nothing						 							  */
/*Returns:void                          				  */
/*Desc:This Function to enable The Clock due to Pre-configurations	   	      */
/******************************************************************************/
void MRCC_voidClkInit(void);

/******************************************************************************/
/*Function: RCC_vidSetClkSource                          					  */
/*I/P Parameters: copy_u32Source            								  */
/*Returns:void                           				  */
/*Desc:This Function Set the Clock source for my Micro-Controller	          */
/******************************************************************************/
/*Options:-   - HSI 	  - HSE		   - PLL				 				  */
/******************************************************************************/
void MRCC_voidSetClkSource (u32 copy_u32Source);


/******************************************************************************/
/*Function: RCC_vidSetClkStatus                     						  */
/*I/P Parameters: copy_u32Source , copy_u8State  							  */
/*Returns:void                             			  */
/*Desc:This Function to enable or disable the clock Source	        	      */
/******************************************************************************/
/* copy_u32Source :-  - HSI_Enable    - HSE_Enable    - PLL_Enable		      */
/* copy_u8State   :-  - ON            - OFF									  */
/******************************************************************************/
void RCC_voidSetClkStatus (u32 copy_u32Source, u8 copy_u8State);

/******************************************************************************/
/*Function: MRCC_vidSetPeripheralclock                     					  */
/*I/P Parameters: copy_u8Bus , copy_u32peripheral , copy_u8State  			  */
/*Returns:void                           				  */
/*Desc:This Function to enable or disable the clock for a peripheral 	      */
/******************************************************************************/
/* copy_u8Bus         :-    - AHB   - APB1   - APB2							  */
/* copy_u32peripheral :-    Choose peripheral From Configuration File		  */
/* copy_u8State       :-    - ON    - OFF									  */
/******************************************************************************/
void MRCC_voidSetPeripheralclock (u8 copy_u8Bus, u32 copy_u32peripheral, u8 copy_u8State);

#endif /* __RCC_INT_H */

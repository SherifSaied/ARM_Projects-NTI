/****************************************************************************************
* ! Title : SYSTICK_private
* ! File Name : SYSTICK_private.h
* ! Description : This file has the Prototypes of the private functions
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
 * This File contains the STK Privates for all Timer Configurations Needed in any Other Peripheral
 * ******************************************************************************************************************
 */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTICK_PRIV_H
#define __SYSTICK_PRIV_H

/******************************************************/
/* Description : Definitions for ENABLE, DISABLE	  */
/******************************************************/
#define ENABLE              				1
#define DISABLE				  				0

/******************************************************/
/* Description : Definitions for SYSTICK Clock Source */
/******************************************************/
#define AHB_CLK              				1
#define AHB_DIVIDED_BY_8_CLK  				0



/******************************************************/
/* Define a macro for Single Time Event 			  */
/******************************************************/
#define     SYSTICK_SINGLE_INTERVAL    0

/******************************************************/
/* Define a macro for Periodic Events 				  */
/******************************************************/
#define     SYSTICK_PERIOD_INTERVAL    1


/******************************************************/
/* Define Variable for interval mode 				  */
/******************************************************/
static u8 SYSTICK_u8ModeOfInterval;

/******************************************************/
/* Define Callback Global Variable 					  */
/******************************************************/
static void(*SYSTICK_CallBack)(void);

/************************************************************/
/* Description : SYSTICK Registers mapping using structure  */
/************************************************************/
typedef struct
{
	/*SysTick control and status register (STK_CTRL)*/
	volatile u32 CTRL;
	/*SysTick reload value register (STK_LOAD)*/
	volatile u32 LOAD;
	/*SysTick current value register (STK_VAL)*/
	volatile u32 VAL;
	/*SysTick calibration value register (STK_CALIB)*/
	volatile u32 CALIB;
}STK_t;

/******************************************************/
/* Description : Definitions for SYSTICK Base Address */
/******************************************************/
#define STK ((volatile STK_t*) 0xE000E010)

#endif /* __SYSTICK_PRIV_H */

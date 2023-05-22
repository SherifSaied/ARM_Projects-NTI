/****************************************************************************************
* ! Title : SYSTICK_configuration
* ! File Name : SYSTICK_configuration.c
* ! Description : This file has the Configurations we need in STK driver.
* ! Compiler : GNU ARM Cross Compiler
* ! Target : STM32F103xxxx & STM32F446xxxx Micro-controller
****************************************************************************************/
/****************************************************************************************
* LOG :
* VERSION    AUTHOR              DATE              DESCRIPTION
* v1.0       Abdelrahman Hossam  29 AUG,2020       - Initial creation
* v2.0       Seif Al-dein Ahmed  24 Jan,2021       - Modifying STK Driver, Editing APIs
****************************************************************************************/

/*
 * This file is part of the OP Coders Graduation Project.
 * ******************************************************************************************************************
 * This File contains the STK Configurations Needed in any Other Peripheral
 * ******************************************************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTICK_CONF_H
#define __SYSTICK_CONF_H

/*********************************************/
/* SYSTICK_ENABLE OPTIONS:  ENABLE           */
/*                          DISABLE          */
/*********************************************/
#define SYSTICK_ENABLE	        ENABLE

/*********************************************/
/* SYSTICK_TICKINT OPTIONS:  ENABLE          */
/*                           DISABLE         */
/*********************************************/
#define SYSTICK_TICKINT         ENABLE


/*********************************************/
/* SYSTICK_CLK OPTIONS: AHB_CLK              */
/*			            AHB_DIVIDED_BY_8_CLK */
/*********************************************/
#define SYSTICK_CLK		AHB_DIVIDED_BY_8_CLK
/*********************************************/

/*********************************************/
/*  	CTRL_REG Bit Mapping                 */
/*********************************************/
#define STK_CTRL_ENABLE_BIT 	  0
#define STK_CTRL_TICKINT_BIT      1
#define STK_CTRL_CLKSOURCE_BIT    2
#define STK_CTRL_COUNTFLAG_BIT    16
/*********************************************/

/*********************************************/
/*Returns 1 if timer counted to 0 since last */
/* time this was read.						 */
/*********************************************/
#define SYSTICK_COUNT_FLAG        1

/*********************************************/
/*  	Pre-Load configurations              */
/*********************************************/
#define PRELOAD_ENABLE            0
#define PRELOAD_VALUE             10000
#define PRELOAD_IMMEDIATE		  1



#endif /* __SYSTICK_CONF_H */

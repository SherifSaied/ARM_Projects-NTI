/*******************************************************************************************
* ! Title : GPIO_private
* ! File Name : GPIO_private.h
* ! Description : This file has the Prototypes of the private functions and configurations
* ! needed to implement this driver
* ! Compiler : GNU ARM Cross Compiler
* ! Target : STM32F103xxxx Micro-controller
*********************************************************************************************/
/********************************************************************************************
* LOG :
* VERSION    AUTHOR              DATE              DESCRIPTION
* v1.0       Abdelrahman Hossam  22 JUL,2020       - Initial creation
* v2.0       Abdelrahman Hossam  24 JAN,2021	   - Edit All Driver APIs and Documentation
*********************************************************************************************/

/*
 * This file is part of the OP Coders Graduation Project.
 * ********************************************************************************************************************************
 * This module contains the GPIO Private Configurations Needed in Source Code
 * ********************************************************************************************************************************
 * To SET the Clock State for a peripheral you must choose the BUS which the Peripheral is connected to.
 */



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_PRIV_H
#define __GPIO_PRIV_H

#define GPIO_ResetMask (0b1111)
/**************************************************/
/* Description : Definitions for GPIO Base Address */
/**************************************************/
#define GPIOA ((volatile GPIOX*) 0x40010800)
#define GPIOB ((volatile GPIOX*) 0x40010C00)
#define GPIOC ((volatile GPIOX*) 0x40011000)

/********************************************************/
/* Description : GPIO Registers mapping using structure */
/********************************************************/
typedef struct
{
	/*Port configuration register low*/
	volatile u32 GPIO_CRL;
	/*Port configuration register high*/
	volatile u32 GPIO_CRH;
	/*Port input data register*/
	volatile u32 GPIO_IDR;
	/*Port output data register*/
	volatile u32 GPIO_ODR;
	/*Port bit set/reset register*/
	volatile u32 GPIO_BSRR;
	/*Port bit reset register*/
	volatile u32 GPIO_BRR;
	/*Port configuration lock register*/
	volatile u32 GPIO_LCKR;
}GPIOX;



#endif /* __GPIO_PRIV_H */

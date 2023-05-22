/****************************************************************************************
* ! Title : RCC_configuration
* ! File Name : RCC_configuration.h
* ! Description : This file has the Configurations we need in RCC driver.
* ! Compiler : GNU ARM Cross Compiler
* ! Target : STM32F103xxxx
****************************************************************************************/
/****************************************************************************************
* LOG :
* VERSION    AUTHOR              DATE              DESCRIPTION
* v1.0       Abdelrahman Hossam  15 JUL,2020       - Initial creation
* v2.0       Abdelrahman Hossam  24 JAN,2021	   - Edit All Driver APIs
****************************************************************************************/

/*
 * This file is part of the OP Coders Graduation Project.
 * ******************************************************************************************************************
 * This File contains the RCC Configurations for all CLK Configurations Needed in any Other Peripheral
 * ******************************************************************************************************************
 * To SET the Clock State for a peripheral you must choose the BUS which the Peripheral is connected to.
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MCAL_RCC_conf_H
#define _MCAL_RCC_conf_H

/* This refers to the current clock required to work on       */
/* Options Available for the system clock ( HSE , HSI , PLL ) */
#define ClkSource HSI

/*This will refer to the PLL input clock source*/
/* Options Available for the system clock ( HSE_Src , HSI_Src , HSI2_Src ) */
#define PLL_Source HSE_Src


/*PLL Source bit value for masking  */
#define Src_bit  32768


/***************************************************************************
Bits 3:0
0000: PREDIV1 input clock not divided
0001: PREDIV1 input clock divided by 2
0010: PREDIV1 input clock divided by 3
0011: PREDIV1 input clock divided by 4
0100: PREDIV1 input clock divided by 5
0101: PREDIV1 input clock divided by 6
0110: PREDIV1 input clock divided by 7
0111: PREDIV1 input clock divided by 8
1000: PREDIV1 input clock divided by 9
1001: PREDIV1 input clock divided by 10
1010: PREDIV1 input clock divided by 11
1011: PREDIV1 input clock divided by 12
1100: PREDIV1 input clock divided by 13
1101: PREDIV1 input clock divided by 14
1110: PREDIV1 input clock divided by 15
1111: PREDIV1 input clock divided by 16
 *****************************************************************************/
#define inputDivisionFactor 0
#define divisionfactor_ResetMask (~0x8)

/***************************************************************************
Bits 21:18
000x: Reserved
0010: PLL input clock x 4
0011: PLL input clock x 5
0100: PLL input clock x 6
0101: PLL input clock x 7
0110: PLL input clock x 8
0111: PLL input clock x 9
10xx: Reserved
1100: Reserved
1101: PLL input clock x 6.5
111x: Reserved
Caution: The PLL output frequency must not exceed 72 MHz
*****************************************************************************/
/* X 4 */
#define PLL_Prescaler		524288


/**************************************************/
/*Description: Definitions for Peripheral Buses   */
/**************************************************/
//                     AHB  					  //
//                     APB1 		    		  //
//                     APB2						  //
/**************************************************/
/*Description: Definitions for Peripheral         */
/**************************************************/
/**************************************************/
/********************AHB***************************/
//  ETHMACRXEN                                    //
//  ETHMACTXEN                                    //
//  ETHMACEN                                      //
//  OTGFSEN                                       //
//  CRCEN                                         //
//  FLITFEN                                       //
//  SRAMEN                                        //
//  DMA2EN                                        //
//  DMA1EN                                        //
/**************************************************/
/********************ABP1**************************/
//  DACEN                                         //
//  PWREN                                         //
//  BKPEN                                         //
//  CAN2EN                                        //
//  CAN1EN                                        //
//  I2C2EN                                        //
//  I2C1EN                                        //
//  UART5EN                                       //
//  UART4EN                                       //
//  USART3EN                                      //
//  UART2EN                                       //
//  SPI3EN                                        //
//  SPI2EN                                        //
//  WWDGEN                                        //
//  TIM7EN                                        //
//  TIM6EN                                        //
//  TIM5EN                                        //
//  TIM4EN                                        //
//  TIM3EN                                        //
//  TIM2EN                                        //
/**************************************************/
/********************ABP2**************************/
// AFIOEN                                         //
// IOPA                                           //
// IOPB                                           //
// IOPC                                           //
// IOPD                                           //
// SPI1EN                                         //
// USARTEN                                        //



#endif /* __RCC_conf_H */

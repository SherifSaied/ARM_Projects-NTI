/*******************************************************************************************
* ! Title : GPIO_interface
* ! File Name : GPIO_interface.h
* ! Description : This file has the Prototypes of the Public functions
* ! Compiler : GNU ARM Cross Compiler
* ! Target : STM32F103xxxx Micro-controller
********************************************************************************************/
/*******************************************************************************************
* LOG :
* VERSION    AUTHOR              DATE              DESCRIPTION
* v1.0       Abdelrahman Hossam  22 JUL,2020       - Initial creation
* v2.0       Abdelrahman Hossam  24 JAN,2021	   - Edit All Driver APIs and Documentation
********************************************************************************************/

/*
 * This file is part of the OP Coders Graduation Project.
 * ********************************************************************************************************************************
 * This module contains the GPIO APIs Decleration
 * ********************************************************************************************************************************
 * This file provoides Eleven functions be called from user application
 * 1- MGPIO_voidIntialization (u8 Copy_u8GPIONumber):- This Function Enables the CLK for GPIOs Peripherals
 * 2- MGPIO_voidOFF (u8 Copy_u8GPIONumber):- This Function Disables the CLK for GPIOs Peripherals
 * 3- MGPIO_voidSetPinMode (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber ,u8 Copy_u8Direction): Set Pin Status
 *    in the Choosed Port (Set the Status to Input or Output with any of the selected Options)
 * 4- MGPIO_voidSetPortMode (u8 Copy_u8PinNumberStart, u8 Copy_u8PinNumberEnd, u8 Copy_u8PortNumber ,u8 Copy_u8Direction)
 *    Set sequence of Pins Status in the Choosed Port
 *    (Set the Status to Input or Output with any of the selected Options)
 * 5- MGPIO_u32GetPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber):- Read A GPIO Pin Value
 * 6- MGPIO_voidSetPinValue (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Value):-Set Pin Value
 *    in the Choosed Port (To High or Low)
 * 7- MGPIO_voidSetPortValue (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u8 Copy_u8Value):-
 *    Set  sequence of Pins value the Choosed Port (To High or Low for all Pins)
 * 8- MGPIO_AtomicSet(u8 Copy_PinNumber, u8 Copy_u8PortNumber):- This Function Sets the Pin Value (High) Using
 * 																Atomic Access
 * 9- MGPIO_AtomicReset(u8 Copy_PinNumber, u8 Copy_u8PortNumber):- This Function Clears the Pin Value (Low) Using
 * 																  Atomic Access
 * 10-MGPIO_voidLockPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Statue):- This Function lock or unlock
 * 																					the GPIO pin from being configured
 * 11-MGPIO_voidSetPortDiffValues (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u16 Copy_u8Value):-
 *    Set  sequence of Pins value the Choosed Port (To High or Low each pin is separated)
 * ********************************************************************************************************************************
 * The Startup Code Sets all the GPIOs to be OFF.
 * ********************************************************************************************************************************
 * Sequence To initialize GPIO CLock
 * - use GPIO Initialization Function with the needed 'IOPA,B,C' using GPIO_voidIntialization(IOP Number)
 * - In case you need to Switch The CLK to OFF for the GPIOs use GPIO_voidOFF (IOP Number)
 * ********************************************************************************************************************************
 * To SET the Clock State for a peripheral you must choose the BUS which the Peripheral is connected to.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_INT_H
#define __GPIO_INT_H

/********************************************************/
/* Description : GPIO PINS Definition					*/
/********************************************************/
#define PIN0  0
#define PIN1  1
#define PIN2  2
#define PIN3  3
#define PIN4  4
#define PIN5  5
#define PIN6  6
#define PIN7  7
#define PIN8  8
#define PIN9  9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

#define LCKK         16
#define GPIO_Lock    1
#define GPIO_Unlock  0

#define GPIO_PORTA 1
#define GPIO_PORTB 2
#define GPIO_PORTC 3

/********************************************************/
/* Description : GPIO Direction Modes Definition		*/
/********************************************************/
#define Input        0
#define Output_10MHz 1
#define Output_2MHz  2
#define Output_50MHz 3

/********************************************************/
/* Description : GPIO Input Modes Definition     		*/
/********************************************************/
#define Analog         0
#define Floating_Input 1
#define Pull_Input     2

/********************************************************/
/* Description : GPIO Output Modes Definition     		*/
/********************************************************/
#define General_PushPull  0
#define General_OpenDrain 1
#define AF_PushPull       2
#define AF_OpenDrain      3

/*****************************************/
/* 			    Input Modes				 */
/*****************************************/
#define Input_Analog      0b0000
#define Input_Floating    0b0100
#define Input_Pull        0b1000

/*****************************************/
/* 			    Output Modes			 */
/*****************************************/
#define Output10_PushPull    0b0001
#define Output10_OpenDrain   0b0101
#define Output10_AFPushPull  0b1001
#define Output10_AFOpenDrain 0b1101

#define Output2_PushPull     0b0010
#define Output2_OpenDrain    0b0110
#define Output2_AFPushPull   0b1010
#define Output2_AFOpenDrain  0b1110

#define Output50_PushPull    0b0011
#define Output50_OpenDrain   0b0111
#define Output50_AFPushPull  0b1011
#define Output50_AFOpenDrain 0b1111


#define IOPA       1<<2
#define IOPB       1<<3
#define IOPC       1<<4
#define IOPD       1<<5



/******************************************************************************/
/*Function: MGPIO_voidIntialization                         			  */
/*I/P Parameters: Copy_u8GPIONumber            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function initialize the GPIO using the RCC Enable		          */
/******************************************************************************/
/*Input IOPA , IOPB , IOPC													  */
/******************************************************************************/
void MGPIO_voidIntialization (u8 Copy_u8GPIONumber);

/******************************************************************************/
/*Function: GPIO_voidOFF			                         			  */
/*I/P Parameters: Copy_u8GPIONumber            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function turn off the GPIO using the RCC Enable		  	          */
/******************************************************************************/
/*Input IOPA , IOPB , IOPC*/
/******************************************************************************/
void MGPIO_voidOFF (u8 Copy_u8GPIONumber);

/**********************************************************************************************/
/*Function: MGPIO_voidSetPort                          								  */
/*I/P Parameters: Copy_PinNumberStart  Copy_u8PortNumber					                  */
/*                Copy_u8Direction     Copy_u8Mode											  */
/*Returns:it returns Error Status                            								  */
/*Desc:This Function Set the GPIO pin direction and mode			         				  */
/**********************************************************************************************/
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTC      							  		      */
/*Direction: Input_Analog, Input_Floating, Input_Pull										  */
/*           Output10_PushPull, Output10_OpenDrain, Output10_AFPushPull, Output10_AFOpenDrain */
/*           Output2_PushPull,  Output2_OpenDrain,  Output2_AFPushPull,  Output2_AFOpenDrain  */
/*           Output50_PushPull, Output50_OpenDrain, Output50_AFPushPull, Output50_AFOpenDrain */
/**********************************************************************************************/
void MGPIO_voidSetPinMode (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber ,u8 Copy_u8Direction);

/**********************************************************************************************/
/*Function: MGPIO_voidSetPort                          								  */
/*I/P Parameters: Copy_PinNumberStart Copy_PinNumberEnd Copy_u8PortNumber					  */
/*                Copy_u8Direction  Copy_u8Mode												  */
/*Returns:it returns Error Status                            								  */
/*Desc:This Function Set the GPIO port direction and mode			         				  */
/**********************************************************************************************/
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTC      							  		      */
/*Direction: Input_Analog, Input_Floating, Input_Pull										  */
/*           Output10_PushPull, Output10_OpenDrain, Output10_AFPushPull, Output10_AFOpenDrain */
/*           Output2_PushPull,  Output2_OpenDrain,  Output2_AFPushPull,  Output2_AFOpenDrain  */
/*           Output50_PushPull, Output50_OpenDrain, Output50_AFPushPull, Output50_AFOpenDrain */
/**********************************************************************************************/
void MGPIO_voidSetPortMode (u8 Copy_u8PinNumberStart, u8 Copy_u8PinNumberEnd, u8 Copy_u8PortNumber ,u8 Copy_u8Direction);

/**********************************************************************************************/
/*Function: MGPIO_u32GetPin			                          								  */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns u32		                            				                  */
/*Desc:This Function Set the GPIO pin direction and mode			                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
u8 MGPIO_u32GetPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber);

/**********************************************************************************************/
/*Function: MGPIO_voidSetPinValue			                          					  */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber	Copy_u8Value							  */
/*Returns:it returns void		                            				          */
/*Desc:This Function Set the GPIO pin output value					                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Value High or Low																	  */
void MGPIO_voidSetPinValue (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Value);

/**********************************************************************************************/
/*Function: MGPIO_u32SetPinValue			                          						      */
/*I/P Parameters: Copy_PinNumber Copy_PinNumberEnd   Copy_u8PortNumber	Copy_u8Value		  */
/*Returns:it returns void		                            				          */
/*Desc:This Function Set the GPIO pin output value					                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Value High or Low																	  */
void MGPIO_voidSetPortValue (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u8 Copy_u8Value);

/**********************************************************************************************/
/*Function: MGPIO_AtomicSet				                          						      */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns nothing			                            				          */
/*Desc:This Function Set the GPIO pin output value using atomic access                        */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
void MGPIO_AtomicSet(u8 Copy_PinNumber, u8 Copy_u8PortNumber);

/**********************************************************************************************/
/*Function: MGPIO_AtomicReset				                          					      */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns nothing			                            				          */
/*Desc:This Function Reset the GPIO pin output value using atomic access                      */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/**********************************************************************************************/
void MGPIO_AtomicReset(u8 Copy_PinNumber, u8 Copy_u8PortNumber);

/**********************************************************************************************/
/*Function: MGPIO_voidLockPin  				                          					      */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns nothing			                            				          */
/*Desc:This Function lock or unlock the GPIO pin from being configured                        */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Statues GPIO_Lock, GPIO_Unlock                                                       */
/**********************************************************************************************/
void MGPIO_voidLockPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Statue);

/**********************************************************************************************/
/*Function: MGPIO_voidSetPortDiffValues			                          			  */
/*I/P Parameters: Copy_PinNumber Copy_PinNumberEnd   Copy_u8PortNumber	Copy_u8Value		  */
/*Returns:it returns void		                            				          */
/*Desc:This Function Set the GPIO port output value					                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Value High or Low																	  */
/**********************************************************************************************/
void MGPIO_voidSetPortDiffValues (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u16 Copy_u8Value);


#endif /* __GPIO_INT_H */

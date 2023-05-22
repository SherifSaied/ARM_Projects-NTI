/*******************************************************************************************
* ! Title : GPIO_program
* ! File Name : GPIO_program.c
* ! Description : This file has the definition of the GPIO functions and
* the usage of the global variables.
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
 * This module contains the GPIO APIs Implementation
 * ********************************************************************************************************************************
 * This file provoides Eleven functions be called from user application
 * 1- MGPIO_ERRORSTATUSIntialization (u8 Copy_u8GPIONumber):- This Function Enables the CLK for GPIOs Peripherals
 * 2- MGPIO_ERRORSTATUSOFF (u8 Copy_u8GPIONumber):- This Function Disables the CLK for GPIOs Peripherals
 * 3- MGPIO_ERRORSTATUSSetPinMode (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber ,u8 Copy_u8Direction): Set Pin Status
 *    in the Choosed Port (Set the Status to Input or Output with any of the selected Options)
 * 4- MGPIO_ERRORSTATUSSetPortMode (u8 Copy_u8PinNumberStart, u8 Copy_u8PinNumberEnd, u8 Copy_u8PortNumber ,u8 Copy_u8Direction)
 *    Set sequence of Pins Status in the Choosed Port
 *    (Set the Status to Input or Output with any of the selected Options)
 * 5- MGPIO_u32GetPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber):- Read A GPIO Pin Value
 * 6- MGPIO_ERRORSTATUSSetPinValue (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Value):-Set Pin Value
 *    in the Choosed Port (To High or Low)
 * 7- MGPIO_ERRORSTATUSSetPortValue (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u8 Copy_u8Value):-
 *    Set  sequence of Pins value the Choosed Port (To High or Low for all Pins)
 * 8- MGPIO_AtomicSet(u8 Copy_PinNumber, u8 Copy_u8PortNumber):- This Function Sets the Pin Value (High) Using
 * 																Atomic Access
 * 9- MGPIO_AtomicReset(u8 Copy_PinNumber, u8 Copy_u8PortNumber):- This Function Clears the Pin Value (Low) Using
 * 																  Atomic Access
 * 10-MGPIO_voidLockPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Statue):- This Function lock or unlock
 * 																					the GPIO pin from being configured
 * 11-MGPIO_ERRORSTATUSSetPortDiffValues (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u16 Copy_u8Value):-
 *    Set  sequence of Pins value the Choosed Port (To High or Low each pin is separated)
 * ********************************************************************************************************************************
 * The Startup Code Sets all the GPIOs to be OFF.
 * ********************************************************************************************************************************
 * Sequence To initialize GPIO CLock
 * - use GPIO Initialization Function with the needed 'IOPA,B,C' using GPIO_ERRORSTATUSIntialization(IOP Number)
 * - In case you need to Switch The CLK to OFF for the GPIOs use GPIO_ERRORSTATUSOFF (IOP Number)
 * ********************************************************************************************************************************
 * To SET the Clock State for a peripheral you must choose the BUS which the Peripheral is connected to.
 */


/****************************************/
/* 			     Directives 			*/
/****************************************/

#include "BIT_MATH.h"
#include "LIB.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "RCC_configuration.h"
#include "RCC_interface.h"
#include "RCC_private.h"

// ----------------------------------------------------------------------------

/******************************************************************************/
/*Function: MGPIO_ERRORSTATUSIntialization                         			  */
/*I/P Parameters: Copy_u8GPIONumber            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function initialize the GPIO using the RCC Enable		          */
/******************************************************************************/
/*Input IOPA , IOPB , IOPC													  */
/******************************************************************************/
void MGPIO_voidIntialization (u8 Copy_u8GPIONumber)
{
	MRCC_voidSetPeripheralclock(APB2,Copy_u8GPIONumber,ON); // Enable the CLk for the I/P and get the Error Status
}

/******************************************************************************/
/*Function: GPIO_ERRORSTATUSOFF			                         			  */
/*I/P Parameters: Copy_u8GPIONumber            								  */
/*Returns:it returns Error Status                            				  */
/*Desc:This Function turn off the GPIO using the RCC Enable					  */
/******************************************************************************/
/*Input IOPA , IOPB , IOPC*/
/******************************************************************************/
void MGPIO_voidOFF (u8 Copy_u8GPIONumber)
{
	/* Enable the GPIO throw the RCC peripheral */
	MRCC_voidSetPeripheralclock(APB2,Copy_u8GPIONumber,OFF);
	/*Returning the call to the caller function*/
}

/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_ERRORSTATUSSetPort                          								  */
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
void MGPIO_voidSetPinMode (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber ,u8 Copy_u8Direction)
{
	/**************************************************************************************/
	/**************************************************************************************/
	/*									Inputs Validation								  */
	/**************************************************************************************/

	if ( (Copy_u8PortNumber==GPIO_PORTC && (Copy_u8PinNumber < 13 || Copy_u8PinNumber > 15) ) ||
				 (Copy_u8PortNumber==GPIO_PORTB && (Copy_u8PinNumber == 2) ) ||
				 (Copy_u8PortNumber==GPIO_PORTA && (Copy_u8PinNumber == 13 ||Copy_u8PinNumber == 14) ))
	{
		if ( Copy_u8PinNumber > 15  )
			{
			}
	}
	else
	{
	/**************************************************************************************/
	/**************************************************************************************/
		/* Switching on the GPIO Ports */
		switch (Copy_u8PortNumber) {
			/* GPIOA Port */
			case GPIO_PORTA:
				/* Check on the the pin number */
				if (Copy_u8PinNumber < 8)
				{
					/* Clear the corresponding bits for the required pin using the reset mask */
					GPIOA->GPIO_CRL &=~ ( GPIO_ResetMask << (Copy_u8PinNumber * 4) );
					/* Set the mode and direction of the required pin */
					GPIOA->GPIO_CRL |=  ( Copy_u8Direction << (Copy_u8PinNumber * 4) );
				}
				else
				{
					/* Subtraction 8 from the pin number for the high register */
					Copy_u8PinNumber -= 8;
					/* Clear the corresponding bits for the required pin using the reset mask */
					GPIOA->GPIO_CRH &=~ ( GPIO_ResetMask << (Copy_u8PinNumber * 4) );
					/* Set the mode and direction of the required pin */
					GPIOA->GPIO_CRH |=  ( Copy_u8Direction << (Copy_u8PinNumber * 4) );
				}
				break;
			/* GPIOA Port */
			case GPIO_PORTB:
				/* Check on the the pin number */
				if (Copy_u8PinNumber < 8)
				{
					/* Clear the corresponding bits for the required pin using the reset mask */
					GPIOB->GPIO_CRL &=~ ( GPIO_ResetMask << (Copy_u8PinNumber * 4) );
					/* Set the mode and direction of the required pin */
					GPIOB->GPIO_CRL |=  ( Copy_u8Direction << (Copy_u8PinNumber * 4) );
				}
				else
				{
					/* Subtraction 8 from the pin number for the high register */
					Copy_u8PinNumber -= 8;
					/* Clear the corresponding bits for the required pin using the reset mask */
					GPIOB->GPIO_CRH &=~ ( GPIO_ResetMask << (Copy_u8PinNumber * 4) );
					/* Set the mode and direction of the required pin */
					GPIOB->GPIO_CRH |=  ( Copy_u8Direction << (Copy_u8PinNumber * 4) );
				}
				break;
			/* GPIOA Port */
			case GPIO_PORTC:
				/* Check on the the pin number */
				if (Copy_u8PinNumber < 8)
				{
					/* Clear the corresponding bits for the required pin using the reset mask */
					GPIOC->GPIO_CRL &=~ ( GPIO_ResetMask << (Copy_u8PinNumber * 4) );
					/* Set the mode and direction of the required pin */
					GPIOC->GPIO_CRL |=  ( Copy_u8Direction << (Copy_u8PinNumber * 4) );
				}
				else
				{
					/* Subtraction 8 from the pin number for the high register */
					Copy_u8PinNumber -= 8;
					/* Clear the corresponding bits for the required pin using the reset mask */
					GPIOC->GPIO_CRH &=~ ( GPIO_ResetMask << (Copy_u8PinNumber * 4) );
					/* Set the mode and direction of the required pin */
					GPIOC->GPIO_CRH |=  ( Copy_u8Direction << (Copy_u8PinNumber * 4) );
				}
				break;
			default:
				break;
		 }
	}
	/**************************************************************************************/
	/**************************************************************************************/
	/*Returning the control to the caller function*/
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_ERRORSTATUSSetPort                          								  */
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
void MGPIO_voidSetPortMode (u8 Copy_u8PinNumberStart, u8 Copy_u8PinNumberEnd, u8 Copy_u8PortNumber ,u8 Copy_u8Direction)
{

	for ( ; Copy_u8PinNumberStart <= Copy_u8PinNumberEnd ; Copy_u8PinNumberStart++)
	{

		MGPIO_ERRORSTATUSSetPinMode(Copy_u8PinNumberStart,Copy_u8PortNumber,Copy_u8Direction);
	}
	/**************************************************************************************/
	/**************************************************************************************/
	/*Returning the control to the caller function*/
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_u32GetPin			                          								  */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns u32	                                				                  */
/*Desc:This Function get the GPIO pin value							                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
u8 MGPIO_u8GetPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber)
{
	u8 Local_u8Value;
	/**************************************************************************************/
	/**************************************************************************************/
	/*									Inputs Validation								  */
	if ( (Copy_PinNumber > 15) )
	{
	}

	/**************************************************************************************/
	/**************************************************************************************/
	else
	{
    	/* Switching on the port number */
		switch (Copy_u8PortNumber)
		{
			/*Port A configuration to read a value*/
			case GPIO_PORTA:
						/*Reading the value from the IDR*/
						Local_u8Value= GET_BIT( GPIOA-> GPIO_IDR,Copy_PinNumber );
						break;
			/*Port B configuration to read a value*/
			case GPIO_PORTB:
						/*Reading the value from the IDR*/
						Local_u8Value= GET_BIT( GPIOB-> GPIO_IDR,Copy_PinNumber );
						break;
			/*Port C configuration to read a value*/
			case GPIO_PORTC:
						/*Reading the value from the IDR*/
						Local_u8Value= GET_BIT( GPIOC-> GPIO_IDR,Copy_PinNumber );
						break;
			default:
				break;
		}
	}
	/*Returning The required value*/
	return Local_u8Value;
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_ERRORSTATUSSetPinValue			                          				  */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber	Copy_u8Value							  */
/*Returns:it returns ERRORSTATUS		                            				          */
/*Desc:This Function Set the GPIO pin output value					                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Value High or Low																	  */
void MGPIO_voidSetPinValue (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Value)
{
	/**************************************************************************************/
	/**************************************************************************************/
	/*									Inputs Validation								  */
	if ( (Copy_PinNumber > 15) )
	{
	}

	/**************************************************************************************/
	/**************************************************************************************/
	else
	{
		/* Switching on the port number */
		switch (Copy_u8PortNumber)
		{
			/* GPIOA */
			case GPIO_PORTA:
				/* Checking on High Signal */
				if (Copy_u8Value==High)
				{
					GPIOA ->GPIO_ODR |= (1 << Copy_PinNumber);    //Setting the ODR Value
				}
				/* Checking on Low Signal */
				else if (Copy_u8Value==Low)
				{
					GPIOA ->GPIO_ODR &=~ (1 << Copy_PinNumber);  //Setting the ODR Value
				}
				else
				{
				}
				break;
			/* GPIOB */
			case GPIO_PORTB:

				if (Copy_u8Value==High)							  //Checking on High Signal
				{
					GPIOB ->GPIO_ODR |= (1 << Copy_PinNumber);    //Setting the ODR Value
				}
				else if (Copy_u8Value==Low)                       //Checking on Low Signal
				{
					GPIOB ->GPIO_ODR &=~ (1 << Copy_PinNumber);   //Setting the ODR Value
				}
				else
				{
				}
				break;
			/* GPIOC */
			case GPIO_PORTC:
				/* Checking on High Signal */
				if (Copy_u8Value==High)
				{
					GPIOC ->GPIO_ODR |= (1 << Copy_PinNumber); //Setting the ODR Value
				}
				/* Checking on Low Signal */
				else if (Copy_u8Value==Low)
				{
					GPIOC ->GPIO_ODR &=~ (1 << Copy_PinNumber);   //Setting the ODR Value
				}
				else
				{
				}
				break;
			default:
				break;
		}
	}
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_u32SetPinValue			                          						  */
/*I/P Parameters: Copy_PinNumber Copy_PinNumberEnd   Copy_u8PortNumber	Copy_u8Value		  */
/*Returns:it returns ERRORSTATUS		                            				          */
/*Desc:This Function Set the GPIO port output value					                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Value High or Low																	  */
void MGPIO_SetPortValue (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u8 Copy_u8Value)
{
	/**************************************************************************************/
	/**************************************************************************************/
	/*									Inputs Validation								  */
	if ( (Copy_PinNumber > 15) || (Copy_PinNumberEnd > 15) || (Copy_PinNumberEnd <Copy_PinNumber))
	{
	}

	/**************************************************************************************/
	/**************************************************************************************/
	else
	{
		for ( ; Copy_PinNumber<=Copy_PinNumberEnd ;Copy_PinNumber++ )
		{
			/* Switching on the port number */
			switch (Copy_u8PortNumber)
			{
				case GPIO_PORTA:
					if (Copy_u8Value==High)							 //Check if The Entered Value is High
					{
						GPIOA ->GPIO_ODR |= (1 << Copy_PinNumber);	 //Set The Register PIN
					}
					else if (Copy_u8Value==Low)						 //Check if The Entered Value is Low
					{
						GPIOA ->GPIO_ODR &=~( 1 << Copy_PinNumber);  //Clear The Register PIN
					}
					else
					{
					}
					break;
				case GPIO_PORTB:
					if (Copy_u8Value==High)                                //Check if The Entered Value is High
					{
						GPIOB ->GPIO_ODR |= (1 << Copy_PinNumber);         //Set The Register PIN
					}
					else if (Copy_u8Value==Low)                            //Check if The Entered Value is Low
					{
						GPIOB ->GPIO_ODR &=~ (1 << Copy_PinNumber);        //Clear The Register PIN
					}
					else
					{
					}
					break;
				case GPIO_PORTC:
					if (Copy_u8Value==High)                                //Check if The Entered Value is High
					{
						GPIOC ->GPIO_ODR |= (1 << Copy_PinNumber);         //Set The Register PIN
					}
					else if (Copy_u8Value==Low)                            //Check if The Entered Value is Low
					{
						GPIOC ->GPIO_ODR &=~ (1 << Copy_PinNumber);        //Clear The Register PIN
					}
					else
					{
					}
					break;
				default:
					break;
			}
		}
	}
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_AtomicSet				                          						      */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns nothing			                            				          */
/*Desc:This Function Set the GPIO pin output value using atomic access                        */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
void MGPIO_AtomicSet(u8 Copy_PinNumber, u8 Copy_u8PortNumber)
{
		/**************************************************************************************/
		/**************************************************************************************/
		/*									Inputs Validation								  */
		if ( (Copy_PinNumber > 15) )
		{
			return ;
		}

		/**************************************************************************************/
		/**************************************************************************************/
		/* Switching on the port number */
		switch (Copy_u8PortNumber)
		{
			case GPIO_PORTA:
							GPIOA->GPIO_BSRR = 1<<Copy_PinNumber;   //set the required pin to be Set with 1
							break;
			case GPIO_PORTB:
							GPIOB->GPIO_BSRR = 1<<Copy_PinNumber;   //set the required pin to be Set with 1
							break;
			case GPIO_PORTC:
							GPIOC->GPIO_BSRR = 1<<Copy_PinNumber;   //set the required pin to be Set with 1
							break;
			default:

				break;
		}
		return ;
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_AtomicReset				                          					      */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns nothing			                            				          */
/*Desc:This Function Reset the GPIO pin output value using atomic access                      */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
void MGPIO_AtomicReset(u8 Copy_PinNumber, u8 Copy_u8PortNumber)
{
	/**************************************************************************************/
	/**************************************************************************************/
	/*									Inputs Validation								  */
	if ((Copy_PinNumber < 0) || (Copy_PinNumber > 15) )
	{
		return ;
	}

	/**************************************************************************************/
	/**************************************************************************************/
	/* Switching on the port number */
	switch (Copy_u8PortNumber)
	{
		case GPIO_PORTA:
						GPIOA->GPIO_BRR = 1<<Copy_PinNumber;   //set the required pin to be cleared with 1
						break;
		case GPIO_PORTB:
						GPIOB->GPIO_BRR = 1<<Copy_PinNumber;   //set the required pin to be cleared with 1
						break;
		case GPIO_PORTC:
						GPIOC->GPIO_BRR = 1<<Copy_PinNumber;   //set the required pin to be cleared with 1
						break;
		default:

			break;
	}
	return ;
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_voidLockPin  				                          					      */
/*I/P Parameters: Copy_PinNumber Copy_u8PortNumber											  */
/*Returns:it returns nothing			                            				          */
/*Desc:This Function lock or unlock the GPIO pin from being configured                        */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Statues GPIO_Lock, GPIO_Unlock                                                       */
void MGPIO_voidLockPin (u8 Copy_PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Statue)
{
	/**************************************************************************************/
	/**************************************************************************************/
	/*									Inputs Validation								  */
	if ((Copy_PinNumber < 0) || (Copy_PinNumber > 15) )
	{
		return ;
	}

	/**************************************************************************************/
	/**************************************************************************************/
	/* Switching on the port number */
	switch (Copy_u8PortNumber)
	{
		case GPIO_PORTA:
			/* Sequence for the LCKK bit */
			SET_BIT(GPIOA->GPIO_LCKR,LCKK);
			CLR_BIT(GPIOA->GPIO_LCKR,LCKK);
			SET_BIT(GPIOA->GPIO_LCKR,LCKK);
			if( ~ GET_BIT(GPIOA->GPIO_LCKR,LCKK) )
			{
				/*Switching on lock or unlock*/
				switch (Copy_u8Statue)
				{
					/*Lock Case*/
					case GPIO_Lock:
							SET_BIT(GPIOA->GPIO_LCKR,Copy_PinNumber);
							break;
					/*Unlock Case*/
					case GPIO_Unlock:
							CLR_BIT(GPIOA->GPIO_LCKR,Copy_PinNumber);
							break;
					default:
						break;
				}
				/* Sequence for the LCKK bit */
				SET_BIT(GPIOA->GPIO_LCKR,LCKK);
				CLR_BIT(GPIOA->GPIO_LCKR,LCKK);
				SET_BIT(GPIOA->GPIO_LCKR,LCKK);
			}
			break;
		case GPIO_PORTB:
			/* Sequence for the LCKK bit */
			SET_BIT(GPIOB->GPIO_LCKR,LCKK);
			CLR_BIT(GPIOB->GPIO_LCKR,LCKK);
			SET_BIT(GPIOB->GPIO_LCKR,LCKK);
			if( ~ GET_BIT(GPIOB->GPIO_LCKR,LCKK) )
			{
				switch (Copy_u8Statue)
				{
					case GPIO_Lock:
							SET_BIT(GPIOB->GPIO_LCKR,Copy_PinNumber);
							break;
					case GPIO_Unlock:
							CLR_BIT(GPIOB->GPIO_LCKR,Copy_PinNumber);
							break;
					default:
						break;
				}
				/* Sequence for the LCKK bit */
				SET_BIT(GPIOB->GPIO_LCKR,LCKK);
				CLR_BIT(GPIOB->GPIO_LCKR,LCKK);
				SET_BIT(GPIOB->GPIO_LCKR,LCKK);
			}
			break;
		case GPIO_PORTC:
			/* Sequence for the LCKK bit */
			SET_BIT(GPIOC->GPIO_LCKR,LCKK);
			CLR_BIT(GPIOC->GPIO_LCKR,LCKK);
			SET_BIT(GPIOC->GPIO_LCKR,LCKK);
			if( ~ GET_BIT(GPIOC->GPIO_LCKR,LCKK) )
			{
				switch (Copy_u8Statue)
				{
					case GPIO_Lock:
							SET_BIT(GPIOC->GPIO_LCKR,Copy_PinNumber);
							break;
					case GPIO_Unlock:
							CLR_BIT(GPIOC->GPIO_LCKR,Copy_PinNumber);
							break;
					default:
						break;
				}
				/* Sequence for the LCKK bit */
				SET_BIT(GPIOC->GPIO_LCKR,LCKK);
				CLR_BIT(GPIOC->GPIO_LCKR,LCKK);
				SET_BIT(GPIOC->GPIO_LCKR,LCKK);
			}
			break;
		default:
				break;
	}

}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
/*Function: MGPIO_ERRORSTATUSSetPortDiffValues			                          			  */
/*I/P Parameters: Copy_PinNumber Copy_PinNumberEnd   Copy_u8PortNumber	Copy_u8Value		  */
/*Returns:it returns ERRORSTATUS		                            				          */
/*Desc:This Function Set the GPIO port output value					                          */
/**********************************************************************************************/
/*Input  Pins from PIN0 to PIN15					             						      */
/*		 Port Number GPIO_PORTA, GPIO_PORTB, GPIO_PORTAC      							      */
/*       Value High or Low																	  */
void MGPIO_voidSetPortDiffValues (u8 Copy_PinNumber,u8 Copy_PinNumberEnd, u8 Copy_u8PortNumber, u16 Copy_u8Value)
{
	u8 Local_u8Counter=0;
	/**************************************************************************************/
	/**************************************************************************************/
	/*									Inputs Validation								  */
	if ( (Copy_PinNumber > 15) || (Copy_PinNumberEnd > 15) || (Copy_PinNumberEnd < Copy_PinNumber))
	{
	}

	/**************************************************************************************/
	/**************************************************************************************/
	for ( ; Copy_PinNumber<=Copy_PinNumberEnd ;Copy_PinNumber++ )
	{
		/* Switching on the port number */
		switch (Copy_u8PortNumber)
		{
			case GPIO_PORTA:
							if (GET_BIT(Copy_u8Value,Local_u8Counter)==High)       //check if this PIN Value is High
							{
								GPIOA ->GPIO_ODR |= (1 << Copy_PinNumber);		   //Set this bit to High
							}
							else if (GET_BIT(Copy_u8Value,Local_u8Counter)==Low)   //check if this PIN Value is Low
							{
								GPIOA ->GPIO_ODR &=~ (1 << Copy_PinNumber);        //Set this bit to Low
							}
							else
							{
							}
							break;
			case GPIO_PORTB:
							if (GET_BIT(Copy_u8Value,Local_u8Counter)==High)       //check if this PIN Value is High
							{
								GPIOB ->GPIO_ODR |= (1 << Copy_PinNumber);         //Set this bit to High
							}
							else if (GET_BIT(Copy_u8Value,Local_u8Counter)==Low)   //check if this PIN Value is Low
							{
								GPIOB ->GPIO_ODR &=~ (1 << Copy_PinNumber);        //Set this bit to Low
							}
							else
							{
							}
							break;
			case GPIO_PORTC:
							if (GET_BIT(Copy_u8Value,Local_u8Counter)==High)        //check if this PIN Value is High
							{
								GPIOC ->GPIO_ODR |= (1 << Copy_PinNumber);          //Set this bit to High
							}
							else if (GET_BIT(Copy_u8Value,Local_u8Counter)==Low)    //check if this PIN Value is Low
							{
								GPIOC ->GPIO_ODR &=~ (1 << Copy_PinNumber);         //Set this bit to Low
							}
							else
							{
							}
							break;
			default:
				break;
		}
		Local_u8Counter++;
	}
}





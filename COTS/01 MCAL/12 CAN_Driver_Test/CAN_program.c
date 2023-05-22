/*******************************************************************************************
* ! Title : CAN_program
* ! File Name : CAN_program.c
* ! Description : This file has the definition of the CAN functions and
* the usage of the global variables.
* ! Compiler : GNU ARM Cross Compiler
* ! Target : STM32F103xxxx Micro-controller
********************************************************************************************/
/*******************************************************************************************
* LOG :
* VERSION    AUTHOR              DATE              DESCRIPTION
* v1.0       Abdelrahman Hossam  22 SEP,2020       - Initial creation
* v2.0       Abdullah Mustafa    03 OCT,2020       - Adding the receive API
* v3.0       Abdelrahman Hossam  11 JAN,2021	   - Add Filters Configurations
* v4.0       Seif Al-dein Ahmed  17 Jan,2021       - Modifying CAN_PROG API
* v5.0       Abdelrahman Hossam  24 JAN,2021	   - Edit All Driver APIs and Documentation
********************************************************************************************/

/*
 * This file is part of the OP Coders Graduation Project.
 * ******************************************************************************************************************
 * This module contains the CAN APIs Implementation
 * This file provides Six functions to be called from user application amd Ten Private Functions.
 * ----------> Functions to be used at Main
 * 1- MCAN_voidInit(void) :-  Setups the CAN Peripheral with all needed Configurations This call is made inside
 *                           the "main.c" file.
 * 2- MCAN_voidSendMessage (CAN_Msg *msg) :-  This Functions Sets the Message on the CAN BUS. This call is made inside
 *                            			     the "main.c" file.
 * 3- MCAN_voidReadMessage(CAN_Msg *msg, u8 Copy_u8FIFONumber) :-This Function Read mesage from Specific FIFO after the Message
 *  															passes the filters. This call is made inside the "main.c" file.
 * 4- MCAN_u8CheckReady(u8 copy_u8MailBoxNum):- This Function CHeck on the State of Mailbox
 *										       This call is made inside the "main.c" file anf it is used in Send Message Function.
 * 5- MCAN_voidCreateMessage (u32 copy_u32ID, u32 copy_u32LowData, u32 copy_u32HighData, u8 copy_u8Length, u8 copy_u8Format,
 *		                     u8 copy_u8Type, u8 copy_u8Mailbox, CAN_Msg *msg): This Function Creates A CAN Message
 * 6- MCAN_voidPendingMSG(void):- This Function checks on the number of pending Messages.
 * ----------> Private Functions to be used at the Main Functions
 * 1- MCAN_voidFiltersInit(void): This Function Initializes the Filter due to the Configurations File.
 * 								  This call is made at can Initialize.
 * 2- MCAN_u32FiltersEnable(void):- This Function Returns the Value Corresponding to the required
 * 								   Filter to be enabled Filters. This function is used in Filter Initialize
 * 3- MCAN_u32FiltersMode(void):- This Function Returns the Value Corresponding to the required
 * 								 Filter modes(LIST or MASK). This function is used in Filter Initialize
 * 4- MCAN_u32FiltersConf(void):- This Function Returns the Value Corresponding to the required
 * 								 Filter modes(Single mode or Dual mode). This function is used in Filter Initialize
 * 5- MCAN_u32FiltersAssign(void):- This Function Returns the Value Corresponding to the required
 * 								   Filter Assignation (FIFO0-FIFO1). This function is used in Filter Initialize
 * 6- MCAN_voidSetIDs(void):- This Function Returns the Value Corresponding to the required
 * 							 Filter IDs. This function is used in Filter Initialize
 * 7- MCAN_voidSetup(void):- This Function Sets the Configurations of the CAN Peripheral.
 * 							This Function is used in CAN Initialize
 * 8- MCAN_voidMode(void):- This Function Sets the mode of the CAN Peripheral (Test or Normal).
 * 							This Function is used in CAN Initialize
 * 9- MCAN_voidInitializationMode(void):- This Function Sets the CAN in the Initialize Mode,
 * 										 This Function is used in CAN Initialize
 * 10- MCAN_voidStart(void):- This Function Sets the CAN in the Normal Mode (Participate in the Network),
 * 							 This Function is used in CAN Initialize
 * ******************************************************************************************************************
 * ******************************************************************************************************************
 * Sequence To Send a Message throw CAN
 * - Create Message with all required Fields
 * - Send this Message with send Message Function.
 * ******************************************************************************************************************
 * Sequence To Read a Message throw CAN
 * - Set the Filter Configuration From the Configuration File
 * - check on the number of Messages using CAN Pending message
 * - Read the Message From the required FIFO that is Assigned to the ID
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LIB.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "CAN_interface.h"
#include "CAN_configuration.h"
#include "CAN_private.h"

#include "SYSTICK_interface.h"

/*********************************************************************************************/
/*Function: MCAN_voidInitialization  				                            			 */
/*I/P Parameters: void																		 */
/*Returns:it returns nothing	                            							     */
/*Desc:This Function allows CAN to work with all the needed setups		                     */
/*********************************************************************************************/
void MCAN_voidInit()
{
	MCAN_voidSetup();               // Setup the CAN Registers with Configurations
	MCAN_voidInitializationMode();  // Leave the Sleep mode and Enter The Initialization Mode
	MCAN_voidMode();			       // Initialize the Mode to enter Test-Mode or not
	MCAN_voidFiltersInit();         // Initialize The Filters
	MCAN_voidStart();		       // Leave the Initialization Mode and Enter The Normal Mode
}
/********************************************************************************************/
/*Function: MCAN_voidSendMessage						                            			*/
/*I/P Parameters: CAN_Msg *msg																*/
/*Returns:it returns nothing	                            							    */
/*Desc:This Function Sends a message over the CAN Network			                        */
/********************************************************************************************/
void MCAN_voidSendMessage (CAN_Msg *msg)
{
	if ( MCAN_u8CheckReady(msg->MailBoxNum) )
	{
		/*Reset the value of TIR Register*/
		CAN->TxMailBox[((msg->MailBoxNum)-MailBox_Shift)].TIR = 0;

		/* Reset the value of DLC bits before setting it*/
		( CAN->TxMailBox[(msg->MailBoxNum-MailBox_Shift)].TDTR ) &= ~ (CAN_TIDR_DLC_ResetMask) ;

		/* Set the Data Length Code Value */
		( CAN->TxMailBox[(msg->MailBoxNum-MailBox_Shift)].TDTR ) |=  (msg->Len) ;

		/* Check on the ID format Standard or Extended */
		/* Standard Format Execution program */
		if(msg->Format == CAN_MSG_Standard_Format)
		{
			   /* configure TIR for the required mail box
			   * Set the ID
			   * Set the Frame Remote Transmission Request
			   * Set the Standard Frame Format
			   */
			  CAN->TxMailBox[(msg->MailBoxNum-MailBox_Shift)].TIR =
				  (  (msg->ID << CAN_TIR_Standard_StartBit) | (CAN_MSG_Standard_Format << CAN_TIR_IDE_Bit)
				   | (msg->Type << CAN_TIR_RTR_Bit		  ));
		}
		/* Extended Format Execution program */
		else
		{
			   /* configure TIR for the required mail box
			   * Set the ID
			   * Set the Frame Remote Transmission Request
			   * Set the Extended Frame Format
			   */
			  CAN->TxMailBox[(msg->MailBoxNum-MailBox_Shift)].TIR=
				  (  (msg->ID << CAN_TIR_Standard_StartBit) | (CAN_MSG_Extended_Format << CAN_TIR_IDE_Bit)
				   | (msg->Type << CAN_TIR_RTR_Bit));
		}

		/* Data Input in the Low Data Register */
		CAN->TxMailBox[((msg->MailBoxNum)-MailBox_Shift)].TDLR = ( (msg->Data[0] << CAN_DATA_BYTE0_Shift)
				 	 	 	 	 	 	 	 	 	 	 	 	 | (msg->Data[1] << CAN_DATA_BYTE1_Shift)
																 | (msg->Data[2] << CAN_DATA_BYTE2_Shift)
																 | (msg->Data[3] << CAN_DATA_BYTE3_Shift) );
		/* Data Input in the High Data Register */
		CAN->TxMailBox[((msg->MailBoxNum)-MailBox_Shift)].TDHR = ( (msg->Data[4] << CAN_DATA_BYTE0_Shift)
						 	 	 	 	 	 	 	 	 	 	 | (msg->Data[5] << CAN_DATA_BYTE1_Shift)
																 | (msg->Data[6] << CAN_DATA_BYTE2_Shift)
																 | (msg->Data[7] << CAN_DATA_BYTE3_Shift) );

		/* Transmit MailBox Request (Send Message) */
		SET_BIT(CAN->TxMailBox[((msg->MailBoxNum)-MailBox_Shift)].TIR ,CAN_TIR_TXRQ_Bit);

	}
	else
	{
		//Do Nothing
	}

}

/********************************************************************************************/
/*Function: MCAN_voidReadMessage						                            			*/
/*I/P Parameters: CAN_Msg *msg																*/
/*Returns:it returns nothing	                            							    */
/*Desc:This Function Receives a message throw the CAN 				                        */
/********************************************************************************************/
void MCAN_voidReadMessage(CAN_Msg *msg, u8 Copy_u8FIFONumber)
{
	/* Input Validation */
	if (Copy_u8FIFONumber > 1)
	{
		return;
	}

	if (GET_BIT(CAN->RxFIFOMailBox[Copy_u8FIFONumber].RIR,CAN_RIR_IDE_Bit)==0)
	{
		/* Standard Format Assign to the message */
		msg->Format= CAN_MSG_Standard_Format;
		/* Assign ID to the Message ID */
		msg->ID=CAN_Standard_formatMask & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RIR >> CAN_FIFO_SID_Shift);
	}
	else
	{
		/* Extended Format Assign to the message */
		msg->Format= CAN_MSG_Extended_Format;
		/* Assign ID to the Message ID */
		msg->ID=CAN_Extended_formatMask & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RIR >> CAN_FIFO_EID_Shift);
	}

	/* Assign the message type if DATA or REQUEST */
	msg->Type=GET_BIT(CAN->RxFIFOMailBox[Copy_u8FIFONumber].RIR,CAN_RIR_RTR_Bit);
	/* Assign the Data Size */
	msg->Len=CAN_DLC_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDTR);

	/* Assigning the Low Register Data in the Data Array */
	msg->Data[0]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDLR >>CAN_DATA_BYTE0_Shift);
	msg->Data[1]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDLR >>CAN_DATA_BYTE1_Shift);
	msg->Data[2]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDLR >>CAN_DATA_BYTE2_Shift);
	msg->Data[3]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDLR >>CAN_DATA_BYTE3_Shift);
	/* Assigning the High Register Data in the Data Array */
	msg->Data[4]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDHR >>CAN_DATA_BYTE0_Shift);
	msg->Data[5]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDHR >>CAN_DATA_BYTE1_Shift);
	msg->Data[6]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDHR >>CAN_DATA_BYTE2_Shift);
	msg->Data[7]= CAN_DATA_MASK & (CAN->RxFIFOMailBox[Copy_u8FIFONumber].RDHR >>CAN_DATA_BYTE3_Shift);

	/* Release the FIFO Mailbox */
	if (Copy_u8FIFONumber==0)
	{
		SET_BIT(CAN->RF0R,CAN_RF0R_RFOM0); //Release FIFO 0
	}
	else if (Copy_u8FIFONumber==1)
	{
		SET_BIT(CAN->RF1R,CAN_RF1R_RFOM1); //Release FIFO 1
	}
}

/********************************************************************************************/
/*Function: MCAN_voidPendingMSG						                            		    */
/*I/P Parameters: void																	    */
/*Returns:it returns nothing	                            							    */
/*Desc:This Function reads number of pending MSG    					                    */
/********************************************************************************************/
void MCAN_voidPendingMSG(void)
{

	CAN_RxRd[0]=(CAN->RF0R & 0x0003); // Number of pending MSGs in FIFO 0
	CAN_RxRd[1]=(CAN->RF1R & 0x0003); // Number of pending MSGs in FIFO 1
}


/********************************************************************************************/
/*Function: MCAN_u8CheckReady						                            			*/
/*I/P Parameters: u8 copy_u8MailBoxNum														*/
/*Returns:it returns u8 value	                            							    */
/*Desc:This Function checks on the mailbox ready to transmit or not                         */
/********************************************************************************************/
/* Number of Mailbox Options    :- CAN_TSR_TME0	- CAN_TSR_TME1 - CAN_TSR_TME2				*/
/********************************************************************************************/
u8 MCAN_u8CheckReady(u8 copy_u8MailBoxNum)
{

	CAN_TxRdy[(copy_u8MailBoxNum-MailBox_Shift)]= CAN_Rdy; // Set the Ready Transmission to Ready
	u16 local_u16Counter=0; 							   // Local Counter for Time Run out Error
    while(GET_BIT(CAN->TSR,copy_u8MailBoxNum)==0)          // Pull on the Flag
	{
    	/*That's means that MailBox isn't empty*/
		local_u16Counter++;                                // Update the Local Counter
		if (local_u16Counter == TimeOut)	 			   // Check on the value of the Local Counter
		{
			/* If Time Ran out the Ready Transmission will be not Ready */
			CAN_TxRdy[(copy_u8MailBoxNum-MailBox_Shift)]= CAN_NotRdy;
			break;                                         // break the loops because of infinity loop
		}
	}
	return CAN_TxRdy[(copy_u8MailBoxNum-MailBox_Shift)];   // Return the Call to the caller Function
}


/********************************************************************************************/
/*Function: MCAN_voidCreateMessage					                            			*/
/*I/P Parameters: u32 copy_u32ID, f64 copy_f64Data, u8 copy_u8Length, u8 copy_u8Format,     */
/*		          u8 copy_u8Type, u8 copy_u8Mailbox, CAN_Msg *msg)            			    */
/*Returns:it returns nothing	                            							    */
/*Desc:This Function Create a message to be sent					                        */
/********************************************************************************************/
/* ID                           :- 29 bit identifier										*/
/* Data field                   :- up to 64 Bit Data										*/
/* Length of data field in bytes:- From  0  to  8											*/
/* Format                       :- CAN_MSG_Standard_Format - CAN_MSG_Extended_Format		*/
/* Data Type                    :- CAN_MSG_DataFrame - CAN_MSG_RemoteFram					*/
/* Number of Mailbox            :- CAN_TSR_TME0	- CAN_TSR_TME1 - CAN_TSR_TME2				*/
/********************************************************************************************/
void MCAN_voidCreateMessage (u32 copy_u32ID, u32 copy_u32LowData, u32 copy_u32HighData, u8 copy_u8Length, u8 copy_u8Format,
		                     u8 copy_u8Type, u8 copy_u8Mailbox, CAN_Msg *msg)
{
	/* Assigning The ID in the Structure */
	msg->ID         = copy_u32ID;
	/* Assigning The Data Length Code in the Structure */
	msg->Len        = copy_u8Length;
	/* Assigning The Format Standard or Extended in the Structure */
	msg->Format     = copy_u8Format;
	/* Assigning The Type of message in the Structure */
	msg->Type       = copy_u8Type;
	/* Assigning The Mailbox number in the Structure */
	msg->MailBoxNum = copy_u8Mailbox;
	/********************************************************/
	/* Assigning The Data number in the Structure           */
	/********************************************************/
	/* Data Byte Number 1 Assign in the data array          */
	msg->Data[0]=(copy_u32LowData >>  CAN_DATA_BYTE0_Shift);
	/* Data Byte Number 2 Assign in the data array          */
	msg->Data[1]=(copy_u32LowData >>  CAN_DATA_BYTE1_Shift);
	/* Data Byte Number 3 Assign in the data array          */
	msg->Data[2]=(copy_u32LowData >>  CAN_DATA_BYTE2_Shift);
	/* Data Byte Number 4 Assign in the data array          */
	msg->Data[3]=(copy_u32LowData >>  CAN_DATA_BYTE3_Shift);
	/* Data Byte Number 5 Assign in the data array          */
	msg->Data[4]=(copy_u32HighData >> CAN_DATA_BYTE0_Shift);
	/* Data Byte Number 6 Assign in the data array          */
	msg->Data[5]=(copy_u32HighData >> CAN_DATA_BYTE1_Shift);
	/* Data Byte Number 7 Assign in the data array          */
	msg->Data[6]=(copy_u32HighData >> CAN_DATA_BYTE2_Shift);
	/* Data Byte Number 8 Assign in the data array          */
	msg->Data[7]=(copy_u32HighData >> CAN_DATA_BYTE3_Shift);
	/********************************************************/
}

/********************************************************************************************/
/*Function: MCAN_voidSetup							                            		    */
/*I/P Parameters: void																	    */
/*Returns:it returns nothing	                            							    */
/*Desc:This Function setup the CAN Registers	     					                    */
/********************************************************************************************/
static void MCAN_voidSetup(void)
{

	MRCC_voidSetPeripheralclock(APB1,CAN1EN,ON); // Enable the clock for the CAN Peripheral
	/*********************************************/
	/* need to make AFIO for the pins p8,9       */
	/*********************************************/
	MGPIO_voidSetPinMode(Can_Tx,Output2_AFPushPull);  //Set TX pin to Alternative Function Pushpull
	MGPIO_voidSetPinMode(Can_Rx,Input_Floating);      //Set RX pin to Input Floating

	/* Interrupt Enable For the Can */
	#if (Interrupt_Enable==Enable)
		/* Enable the NVIC for the TX and RX */
		MNVIC_ErrorStatusEnable(USB_HP_CAN_TX);
		MNVIC_ErrorStatusEnable(USB_LP_CAN_RX0);
	#endif

	 /* The Re-transmition on
	 * Enter the initialization mode
	 * Set automatic bus-off management
	 * Set transmit FIFO priority driven by the request order
	 * Receive FIFO not locked on overrun
	 * Out of Sleep mode request
	 * Time triggered communication mode off
	 * The Sleep mode is left on software request.
	 * CAN reception/transmission frozen during debug. */
   CAN->MCR = (  ( CAN_MCR_NART << CAN_MCR_NART_Bit )  | ( CAN_MCR_ABOM << CAN_MCR_ABOM_Bit )
   		    | ( CAN_MCR_RFLM << CAN_MCR_RFLM_Bit )  | ( CAN_MCR_TTCM << CAN_MCR_TTCM_Bit )
				| ( CAN_MCR_TXFP << CAN_MCR_TXFP_BIt )  | ( CAN_MCR_AWUM << CAN_MCR_AWUM_Bit ) | ( CAN_MCR_DBFG << CAN_MCR_DBFG_Bit   ) );


   /* Enable the Empty mailbox interrupt & FIFO message pending interrupt enable */
  // CAN->IER= ( ( CAN_IER_TMEIE << CAN_IER_TMEIE_Bit ) | ( CAN_IER_FMPIE0 << CAN_IER_FMPIE0_Bit ) ) ;

}

/*********************************************************************************************/
/*Function: MCAN_voidMode							                            			 */
/*I/P Parameters: void																		 */
/*Returns:it returns nothing	                            							     */
/*Desc:This Function setup the CAN Mode Test Mode or Not     			                     */
/*********************************************************************************************/
static void MCAN_voidMode(void)
{
	/* Test Mode Configuration */
	#if(Test_Mode==Disable)                     // Test mode Is Disabled
		{
			CAN->BTR= CAN_BaudRate; 			// BaudRate = 1 Mbps
			CLR_BIT(CAN->BTR,CAN_BTR_LBKM_BIT); // Loop Back Mode Disable
			CLR_BIT(CAN->BTR,CAN_BTR_SILM_BIT); // Silent Mode Disable
		}
  #elif (Test_Mode==Enable)					// Test mode Is Enabled
		{
			CAN->BTR= CAN_BaudRate; 			// BaudRate = 1 Mbps
			SET_BIT(CAN->BTR,CAN_BTR_LBKM_BIT); // Loop Back Mode Enable
			SET_BIT(CAN->BTR,CAN_BTR_SILM_BIT); // Silent Mode Enable
		}
   #endif

}

/*********************************************************************************************/
/*Function: MCAN_voidInitializationMode				                            			 */
/*I/P Parameters: void																		 */
/*Returns:it returns nothing	                            							     */
/*Desc:This Function allows CAN to Enter Initialization Mode   			                     */
/*********************************************************************************************/
static void MCAN_voidInitializationMode(void)
{
	   /* Initialization Mode Entry */
	    SET_BIT(CAN->MCR,CAN_MCR_INRQ_Bit);  // Initialization Mode Request
	    CLR_BIT(CAN->MCR,CAN_MCR_SLEEP_BIT); // Leave Sleep Mode Request

	    // wait till the INAK is cleared and also the SLAK
	    while ((GET_BIT(CAN->MSR,CAN_MSR_INAK_Bit)) && (GET_BIT(CAN->MSR,CAN_MSR_SLAK_Bit)));
}

/*********************************************************************************************/
/*Function: MCAN_voidStart           				                            			 */
/*I/P Parameters: void																		 */
/*Returns:it returns nothing	                            							     */
/*Desc:This Function allows CAN to Enter Normal Mode		   			                     */
/*********************************************************************************************/
static void MCAN_voidStart(void)
{
   /* Normal Mode Entry */
   CLR_BIT(CAN->MCR,CAN_MCR_INRQ_Bit); // Leave Initialization Mode Request
   while ((GET_BIT(CAN->MSR,CAN_MSR_INAK_Bit)) && (GET_BIT(CAN->MSR,CAN_MSR_SLAK_Bit))); //wait ACK for Normal Mode

}

/********************************************************************************/
/*Function: CAN_voidFiltersInit						                           	*/
/*I/P Parameters: void															*/
/*Returns:it returns nothing                       							    */
/*Desc:This Function Initialize all the CAN Filters         		            */
/********************************************************************************/
static void MCAN_voidFiltersInit(void)
{
	SET_BIT(CAN->FMR,CAN_FMR_FINIT_BIT);	// SET bit FINIT to initialize the filter
	CAN->FA1R=Reset_Value;					// inactive All filters
	CAN->FM1R=MCAN_u32FiltersMode();         // Set the Filters Mode
	CAN->FS1R=MCAN_u32FiltersScale();        // Set the Filters Scale
	CAN->FFA1R=MCAN_u32FiltersAssign();      // Set the assign of each filter to One of the FIFOs (0 or 1)
	MCAN_voidSetIDs();                       // Set the IDs to the Filters
	CAN->FA1R=MCAN_u32FiltersEnable();       // Enable The Filters
	CLR_BIT(CAN->FMR,CAN_FMR_FINIT_BIT);	// CLEAR bit FINIT to Activate the filter
}

/********************************************************************************/
/*Function: MCAN_u32FiltersEnable					                           	*/
/*I/P Parameters: void															*/
/*Returns:it returns u32 Variable                  							    */
/*Desc:This Function returns the value to the Enabled Filters  		            */
/********************************************************************************/
static u32 MCAN_u32FiltersEnable(void)
{
	u32 Local_u32Value=0;   //Local Variable For Data Read
	/*Assemble Filters Values*/
	/*All Filters are disabled now*/
	Local_u32Value =((Filter27_Enable<<Filter27)| (Filter26_Enable<<Filter26)| (Filter25_Enable<<Filter25)|
					 (Filter24_Enable<<Filter24)| (Filter23_Enable<<Filter23)| (Filter23_Enable<<Filter23)|
					 (Filter22_Enable<<Filter22)| (Filter21_Enable<<Filter21)| (Filter20_Enable<<Filter20)|
					 (Filter19_Enable<<Filter19)| (Filter18_Enable<<Filter18)| (Filter17_Enable<<Filter17)|
					 (Filter16_Enable<<Filter16)| (Filter15_Enable<<Filter15)| (Filter14_Enable<<Filter14)|
					 (Filter13_Enable<<Filter13)| (Filter12_Enable<<Filter12)| (Filter11_Enable<<Filter11)|
					 (Filter10_Enable<<Filter10)| (Filter9_Enable<<Filter9  )| (Filter8_Enable<<Filter8  )|
					 (Filter7_Enable<<Filter7  )| (Filter6_Enable<<Filter6  )| (Filter5_Enable<<Filter5  )|
					 (Filter4_Enable<<Filter4  )| (Filter3_Enable<<Filter3  )| (Filter2_Enable<<Filter2  )|
					 (Filter1_Enable<<Filter1  )| (Filter0_Enable<<Filter0  ));
	return Local_u32Value;  // Returning the control to the caller function
}
/********************************************************************************/
/*Function: MCAN_u32FiltersMode     					                           	*/
/*I/P Parameters: void															*/
/*Returns:it returns u32 Variable                  							    */
/*Desc:This Function returns the value to Filters modes list or mask            */
/********************************************************************************/
static u32 MCAN_u32FiltersMode(void)
{
	u32 Local_u32Value=0;  //Local Variable For Data Read
	/*Assemble Filters Values*/
	/*Two 32-bit registers of filter bank x are in Identifier List mode. when x is 0-->27 */
	Local_u32Value =((Filter27_Mode<<Filter27)| (Filter26_Mode<<Filter26)| (Filter25_Mode<<Filter25)|
					 (Filter24_Mode<<Filter24)| (Filter23_Mode<<Filter23)| (Filter23_Mode<<Filter23)|
					 (Filter22_Mode<<Filter22)| (Filter21_Mode<<Filter21)| (Filter20_Mode<<Filter20)|
					 (Filter19_Mode<<Filter19)| (Filter18_Mode<<Filter18)| (Filter17_Mode<<Filter17)|
					 (Filter16_Mode<<Filter16)| (Filter15_Mode<<Filter15)| (Filter14_Mode<<Filter14)|
					 (Filter13_Mode<<Filter13)| (Filter12_Mode<<Filter12)| (Filter11_Mode<<Filter11)|
					 (Filter10_Mode<<Filter10)| (Filter9_Mode<<Filter9  )| (Filter8_Mode<<Filter8  )|
					 (Filter7_Mode<<Filter7  )| (Filter6_Mode<<Filter6  )| (Filter5_Mode<<Filter5  )|
					 (Filter4_Mode<<Filter4  )| (Filter3_Mode<<Filter3  )| (Filter2_Mode<<Filter2  )|
					 (Filter1_Mode<<Filter1  )| (Filter0_Mode<<Filter0  ));
	return Local_u32Value;  // Returning the control to the caller function
}
/************************************************************************************/
/*Function: MCAN_u32FiltersScale     					                            */
/*I/P Parameters: void															    */
/*Returns:it returns u32 Variable                  							        */
/*Desc:This Function returns the value to Filters Scale Dual 16-bit or single 32-bit*/
/************************************************************************************/
static u32 MCAN_u32FiltersScale(void)
{
	u32 Local_u32Value=0;   //Local Variable For Data Read
	/*Assemble Filters Values*/
	/*Two 32-bit registers of filter bank x are in Identifier List mode. when x is 0-->27 */
	Local_u32Value =((Filter27_Scale<<Filter27)| (Filter26_Scale<<Filter26)| (Filter25_Scale<<Filter25)|
					 (Filter24_Scale<<Filter24)| (Filter23_Scale<<Filter23)| (Filter23_Scale<<Filter23)|
					 (Filter22_Scale<<Filter22)| (Filter21_Scale<<Filter21)| (Filter20_Scale<<Filter20)|
					 (Filter19_Scale<<Filter19)| (Filter18_Scale<<Filter18)| (Filter17_Scale<<Filter17)|
					 (Filter16_Scale<<Filter16)| (Filter15_Scale<<Filter15)| (Filter14_Scale<<Filter14)|
					 (Filter13_Scale<<Filter13)| (Filter12_Scale<<Filter12)| (Filter11_Scale<<Filter11)|
					 (Filter10_Scale<<Filter10)| (Filter9_Scale<<Filter9  )| (Filter8_Scale<<Filter8  )|
					 (Filter7_Scale<<Filter7  )| (Filter6_Scale<<Filter6  )| (Filter5_Scale<<Filter5  )|
					 (Filter4_Scale<<Filter4  )| (Filter3_Scale<<Filter3  )| (Filter2_Scale<<Filter2  )|
					 (Filter1_Scale<<Filter1  )| (Filter0_Scale<<Filter0  ));
	return Local_u32Value;  // Returning the control to the caller function
}
/********************************************************************************/
/*Function: MCAN_u32FiltersAssign   					                           	*/
/*I/P Parameters: void															*/
/*Returns:it returns u32 Variable                  							    */
/*Desc:This Function returns the value to Filters assigned to FIFO 0 or 1       */
/********************************************************************************/
static u32 MCAN_u32FiltersAssign(void)
{
	u32 Local_u32Value=0;   //Local Variable For Data Read
	/*Assemble Filters Values*/
	/*Set the assignments of filter x to FIFO(0) when x is 0-->27*/
	Local_u32Value =((Filter27_Assign<<Filter27)| (Filter26_Assign<<Filter26)| (Filter25_Assign<<Filter25)|
					 (Filter24_Assign<<Filter24)| (Filter23_Assign<<Filter23)| (Filter23_Assign<<Filter23)|
					 (Filter22_Assign<<Filter22)| (Filter21_Assign<<Filter21)| (Filter20_Assign<<Filter20)|
					 (Filter19_Assign<<Filter19)| (Filter18_Assign<<Filter18)| (Filter17_Assign<<Filter17)|
					 (Filter16_Assign<<Filter16)| (Filter15_Assign<<Filter15)| (Filter14_Assign<<Filter14)|
					 (Filter13_Assign<<Filter13)| (Filter12_Assign<<Filter12)| (Filter11_Assign<<Filter11)|
					 (Filter10_Assign<<Filter10)| (Filter9_Assign<<Filter9  )| (Filter8_Assign<<Filter8  )|
					 (Filter7_Assign<<Filter7  )| (Filter6_Assign<<Filter6  )| (Filter5_Assign<<Filter5  )|
					 (Filter4_Assign<<Filter4  )| (Filter3_Assign<<Filter3  )| (Filter2_Assign<<Filter2  )|
					 (Filter1_Assign<<Filter1  )| (Filter0_Assign<<Filter0  ));
	return Local_u32Value;  // Returning the control to the caller function
}
/********************************************************************************/
/*Function: MCAN_voidSetIDs							                           	*/
/*I/P Parameters: void															*/
/*Returns:it returns nothing                       							    */
/*Desc:This Function set the IDs For Each Filter in the CAN  		            */
/********************************************************************************/
static void MCAN_voidSetIDs(void)
{
   #if (Filter0_Enable==Enable)
   {
	 CAN->Filter[Filter0].FR1=Filter0_ID1;  // Assign ID 1 For Filter 0
	 CAN->Filter[Filter0].FR2=Filter0_ID2;  // Assign ID 2 For Filter 0
   }
   #endif
   #if (Filter1_Enable==Enable)
   {
	 CAN->Filter[Filter1].FR1=Filter1_ID1;  // Assign ID 1 For Filter 1
	 CAN->Filter[Filter1].FR2=Filter1_ID2;  // Assign ID 2 For Filter 1
   }
   #endif
      #if (Filter2_Enable==Enable)
   {
	 CAN->Filter[Filter2].FR1=Filter2_ID1;  // Assign ID 1 For Filter 2
	 CAN->Filter[Filter2].FR2=Filter2_ID2;  // Assign ID 2 For Filter 2
   }
   #endif
      #if (Filter3_Enable==Enable)
   {
	 CAN->Filter[Filter3].FR1=Filter3_ID1;  // Assign ID 1 For Filter 3
	 CAN->Filter[Filter3].FR2=Filter3_ID2;  // Assign ID 2 For Filter 3
   }
   #endif
      #if (Filter4_Enable==Enable)
   {
	 CAN->Filter[Filter4].FR1=Filter4_ID1;  // Assign ID 1 For Filter 4
	 CAN->Filter[Filter4].FR2=Filter4_ID2;  // Assign ID 2 For Filter 4
   }
   #endif
      #if (Filter5_Enable==Enable)
   {
	 CAN->Filter[Filter5].FR1=Filter5_ID1;   // Assign ID 1 For Filter 5
	 CAN->Filter[Filter5].FR2=Filter5_ID2;   // Assign ID 2 For Filter 5
   }
   #endif
      #if (Filter6_Enable==Enable)
   {
	 CAN->Filter[Filter6].FR1=Filter6_ID1;   // Assign ID 1 For Filter 6
	 CAN->Filter[Filter6].FR2=Filter6_ID2;   // Assign ID 2 For Filter 6
   }
   #endif
      #if (Filter7_Enable==Enable)
   {
	 CAN->Filter[Filter7].FR1=Filter7_ID1;   // Assign ID 1 For Filter 7
	 CAN->Filter[Filter7].FR2=Filter7_ID2;   // Assign ID 2 For Filter 7
   }
   #endif
      #if (Filter8_Enable==Enable)
   {
	 CAN->Filter[Filter8].FR1=Filter8_ID1;   // Assign ID 1 For Filter 8
	 CAN->Filter[Filter8].FR2=Filter8_ID2;   // Assign ID 2 For Filter 8
   }
   #endif
      #if (Filter9_Enable==Enable)
   {
	 CAN->Filter[Filter9].FR1=Filter9_ID1;   // Assign ID 1 For Filter 9
	 CAN->Filter[Filter9].FR2=Filter9_ID2;   // Assign ID 2 For Filter 9
   }
   #endif
      #if (Filter10_Enable==Enable)
   {
	 CAN->Filter[Filter10].FR1=Filter10_ID1;  // Assign ID 1 For Filter 10
	 CAN->Filter[Filter10].FR2=Filter10_ID2;  // Assign ID 2 For Filter 10
   }
   #endif
      #if (Filter11_Enable==Enable)
   {
	 CAN->Filter[Filter11].FR1=Filter11_ID1;  // Assign ID 1 For Filter 11
	 CAN->Filter[Filter11].FR2=Filter11_ID2;  // Assign ID 2 For Filter 11
   }
   #endif
      #if (Filter12_Enable==Enable)
   {
	 CAN->Filter[Filter12].FR1=Filter12_ID1;  // Assign ID 1 For Filter 12
	 CAN->Filter[Filter12].FR2=Filter12_ID2;  // Assign ID 2 For Filter 12
   }
   #endif
      #if (Filter13_Enable==Enable)
   {
	 CAN->Filter[Filter13].FR1=Filter13_ID1;  // Assign ID 1 For Filter 13
	 CAN->Filter[Filter13].FR2=Filter13_ID2;  // Assign ID 2 For Filter 13
   }
   #endif
      #if (Filter14_Enable==Enable)
   {
	 CAN->Filter[Filter14].FR1=Filter14_ID1;  // Assign ID 1 For Filter 14
	 CAN->Filter[Filter14].FR2=Filter14_ID2;  // Assign ID 2 For Filter 14
   }
   #endif
      #if (Filter15_Enable==Enable)
   {
	 CAN->Filter[Filter15].FR1=Filter15_ID1;  // Assign ID 1 For Filter 15
	 CAN->Filter[Filter15].FR2=Filter15_ID2;  // Assign ID 2 For Filter 15
   }
   #endif
      #if (Filter16_Enable==Enable)
   {
	 CAN->Filter[Filter16].FR1=Filter16_ID1;  // Assign ID 1 For Filter 16
	 CAN->Filter[Filter16].FR2=Filter16_ID2;  // Assign ID 2 For Filter 16
   }
   #endif
      #if (Filter17_Enable==Enable)
   {
	 CAN->Filter[Filter17].FR1=Filter17_ID1; // Assign ID 1 For Filter 17
	 CAN->Filter[Filter17].FR2=Filter17_ID2; // Assign ID 2 For Filter 17
   }
   #endif
      #if (Filter18_Enable==Enable)
   {
	 CAN->Filter[Filter18].FR1=Filter18_ID1; // Assign ID 1 For Filter 18
	 CAN->Filter[Filter18].FR2=Filter18_ID2; // Assign ID 2 For Filter 18
   }
   #endif
      #if (Filter19_Enable==Enable)
   {
	 CAN->Filter[Filter19].FR1=Filter19_ID1;  // Assign ID 1 For Filter 19
	 CAN->Filter[Filter19].FR2=Filter19_ID2;  // Assign ID 2 For Filter 19
   }
   #endif
       #if (Filter20_Enable==Enable)
   {
	 CAN->Filter[Filter20].FR1=Filter20_ID1; // Assign ID 1 For Filter 20
	 CAN->Filter[Filter20].FR2=Filter20_ID2; // Assign ID 2 For Filter 20
   }
   #endif
       #if (Filter21_Enable==Enable)
   {
	 CAN->Filter[Filter21].FR1=Filter21_ID1;  // Assign ID 1 For Filter 21
	 CAN->Filter[Filter21].FR2=Filter21_ID2;  // Assign ID 2 For Filter 21
   }
   #endif
       #if (Filter22_Enable==Enable)
   {
	 CAN->Filter[Filter22].FR1=Filter22_ID1;  // Assign ID 1 For Filter 22
	 CAN->Filter[Filter22].FR2=Filter22_ID2;  // Assign ID 2 For Filter 22
   }
   #endif
       #if (Filter23_Enable==Enable)
   {
	 CAN->Filter[Filter23].FR1=Filter23_ID1;  // Assign ID 1 For Filter 23
	 CAN->Filter[Filter23].FR2=Filter23_ID2;  // Assign ID 2 For Filter 23
   }
   #endif
       #if (Filter24_Enable==Enable)
   {
	 CAN->Filter[Filter24].FR1=Filter24_ID1;   // Assign ID 1 For Filter 24
	 CAN->Filter[Filter24].FR2=Filter24_ID2;   // Assign ID 2 For Filter 24
   }
   #endif
       #if (Filter25_Enable==Enable)
   {
	 CAN->Filter[Filter25].FR1=Filter25_ID1;  // Assign ID 1 For Filter 25
	 CAN->Filter[Filter25].FR2=Filter25_ID2;  // Assign ID 2 For Filter 25
   }
   #endif
       #if (Filter26_Enable==Enable)
   {
	 CAN->Filter[Filter26].FR1=Filter26_ID1;  // Assign ID 1 For Filter 26
	 CAN->Filter[Filter26].FR2=Filter26_ID2;  // Assign ID 2 For Filter 26
   }
   #endif
       #if (Filter27_Enable==Enable)
   {
	 CAN->Filter[Filter27].FR1=Filter27_ID1;  // Assign ID 1 For Filter 27
	 CAN->Filter[Filter27].FR2=Filter27_ID2;  // Assign ID 2 For Filter 27
   }
   #endif
}

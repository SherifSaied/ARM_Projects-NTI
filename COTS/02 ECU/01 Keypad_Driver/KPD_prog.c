/*
 * KPD_prog.c
 *
 *  Created on: May 4, 2023
 *      Author: Sherif Ahmed
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "KPD_priv.h"
#include "KPD_config.h"

#include "RCC_interface.h"
#include "DIO_interface.h"


u8 KPD_u8GetPressedKey(void)
{
	/* set direction for 4 rows pins as INPUT */
		DIO_voidSetPinDirection(KPD_PORT, KPD_ROW0_PIN, GPIO_INPUT_PULL_UP_DOWN);
		//GPIOA_ODR |= (1<<0);    /*to get pull-up only put on GPIOx_ODR=1 */ //already made in set pin
		DIO_voidSetPinDirection(KPD_PORT, KPD_ROW1_PIN, GPIO_INPUT_PULL_UP_DOWN);
		//GPIOA_ODR |= (1<<1);    /*to get pull-up only put on GPIOx_ODR=1 */ //already made in set pin
		DIO_voidSetPinDirection(KPD_PORT, KPD_ROW2_PIN, GPIO_INPUT_PULL_UP_DOWN);
		//GPIOA_ODR |= (1<<2);    /*to get pull-up only put on GPIOx_ODR=1 */ //already made in set pin
		DIO_voidSetPinDirection(KPD_PORT, KPD_ROW3_PIN, GPIO_INPUT_PULL_UP_DOWN);
		//GPIOA_ODR |= (1<<3);    /*to get pull-up only put on GPIOx_ODR=1 */ //already made in set pin
	/* set direction for 4 columns pins as OUTPUT */
		DIO_voidSetPinDirection(KPD_PORT, KPD_COLUMN0_PIN, GPIO_OUTPUT_10MHZ_PP);
		DIO_voidSetPinDirection(KPD_PORT, KPD_COLUMN1_PIN, GPIO_OUTPUT_10MHZ_PP);
		DIO_voidSetPinDirection(KPD_PORT, KPD_COLUMN2_PIN, GPIO_OUTPUT_10MHZ_PP);
		DIO_voidSetPinDirection(KPD_PORT, KPD_COLUMN3_PIN, GPIO_OUTPUT_10MHZ_PP);
	/* set Value for 4 rows pins as PULL-UP for input and High as output for 4 columns*/
		DIO_voidSetPinValue(KPD_PORT, KPD_COLUMN0_PIN, KPD_COLUMN_HIGH);
		DIO_voidSetPinValue(KPD_PORT, KPD_COLUMN1_PIN, KPD_COLUMN_HIGH);
		DIO_voidSetPinValue(KPD_PORT, KPD_COLUMN2_PIN, KPD_COLUMN_HIGH);
		DIO_voidSetPinValue(KPD_PORT, KPD_COLUMN3_PIN, KPD_COLUMN_HIGH);



	u8 local_u8PressedKey=KPD_NO_PRESSED_KEY;
	static u8 local_u8KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARR_VAL ;   /* we put static keyword to avoid doing many pushing in stack  */

	static u8 local_u8KPDColumnArr[COLUMN_NUM]={KPD_COLUMN0_PIN,
										 KPD_COLUMN1_PIN,
										 KPD_COLUMN2_PIN,
										 KPD_COLUMN3_PIN};
	static u8 local_u8KPDRowArr[ROW_NUM]={KPD_ROW0_PIN,
										 KPD_ROW1_PIN,
										 KPD_ROW2_PIN,
										 KPD_ROW3_PIN};


	u8 local_u8RowIdx,local_u8ColumnIdx;
	u8 local_u8PinState;
	for (local_u8ColumnIdx=0;local_u8ColumnIdx<COLUMN_NUM;local_u8ColumnIdx++)
	{
		/*Activate current column*/
		DIO_voidSetPinValue(KPD_PORT, local_u8KPDColumnArr[local_u8ColumnIdx], KPD_COLUMN_LOW); //wasl column 3la gnd

		for (local_u8RowIdx=0;local_u8RowIdx<ROW_NUM;local_u8RowIdx++)
		{
			/*read current row*/
			DIO_u8GetPinValue(KPD_PORT,local_u8KPDRowArr[local_u8RowIdx], &local_u8PinState);
			if (local_u8PinState == DIO_LOW)
			{
				local_u8PressedKey = local_u8KPDArr[local_u8RowIdx][local_u8ColumnIdx];
				return local_u8PressedKey; //for avoid bouncing return 3la tool f wa2taha w kaman lo 7ad das 3la 2 keys ma3 ba3d
			}
		}
		/*De-Activate current column*/
		DIO_voidSetPinValue(KPD_PORT, local_u8KPDColumnArr[local_u8ColumnIdx], KPD_COLUMN_HIGH);
	}

	return local_u8PressedKey;

}

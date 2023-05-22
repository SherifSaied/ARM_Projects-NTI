/*
 * ADC_interface.h
 *
 *  Created on: May 10, 2023
 *      Author: Sherif Ahmed
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*typedef enum
{
	channel_0,
	channel_1,
	channel_2,
	channel_3,
	channel_4,
	channel_5,
	channel_6,
	channel_7,
	channel_8,
	channel_9,
	channel_10,
	channel_11,
	channel_12,
	channel_13,
	channel_14,
	channel_15,
	channel_16,
	channel_17

}channel;

typedef enum
{
	cycles_1_5,
	cycles_7_5,
	cycles_13_5,
	cycles_28_5,
	cycles_41_5,
	cycles_55_5,
	cycles_71_5,
	cycles_239_5

}sampleTime;*/

void ADC_voidInit(void);
void ADC_voidStart(void);
u16  ADC_Read(void);





#endif /* ADC_INTERFACE_H_ */

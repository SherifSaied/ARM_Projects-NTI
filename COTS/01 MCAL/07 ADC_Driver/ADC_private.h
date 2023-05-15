/*
 * ADC_private.h
 *
 *  Created on: May 10, 2023
 *      Author: Sherif Ahmed
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#define	Disable 0
#define	Enable  1

/*external event select for regular group*/
#define Timer_1_CC1  0
#define Timer_1_CC2  1
#define Timer_1_CC3  2
#define Timer_2_CC2  3
#define Timer_3_TRGO 4
#define Timer_4_CC4  5
#define	EXTI_line_11 6
#define SWSTART      7





#define ADC1_BASE_ADD           0x40012400

typedef struct
{
	volatile u32 SR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 JOFR1;
	volatile u32 JOFR2;
	volatile u32 JOFR3;
	volatile u32 JOFR3;
	volatile u32 HTR;
	volatile u32 LTR;
	volatile u32 SQR1;
	volatile u32 SQR2;
	volatile u32 SQR3;
	volatile u32 JSQR;
	volatile u32 JDR1;
	volatile u32 JDR2;
	volatile u32 JDR3;
	volatile u32 JDR4;
	volatile u32 DR;

}ADC1_type;
#define ADC1     ((ADC1_type*)ADC1_BASE_ADD)









#endif /* ADC_PRIVATE_H_ */

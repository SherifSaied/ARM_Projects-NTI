/*
 * ADC_private.h
 *
 *  Created on: May 10, 2023
 *      Author: Sherif Ahmed
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

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
	volatile u32 JOFR4;
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
#define ADC1     ((volatile ADC1_type*)ADC1_BASE_ADD)


#define				ADCPRE0					14
#define 			ADCPRE1					15


#define				ENABLED					1
#define				DISABLED				0



#define				SINGLE					2
#define				CONTINUOUS				3

#define				RIGHT					7
#define				LEFT					8

#define				TIMER_1_CC1				9
#define				TIMER_1_CC2				10
#define				TIMER_1_CC3				11
#define				TIMER_2_CC2				12
#define				TIMER_3_TRGO			13
#define				TIMER_4_CC4				14
#define				EXTI_LINE_11			15
#define				TIMER_8_TRGO			155
#define				SWSTART					16

#define				SMP_1_5					17
#define				SMP_7_5					18
#define				SMP_13_5				19
#define				SMP_28_5				20
#define				SMP_41_5				21
#define				SMP_55_5				22
#define				SMP_71_5				23
#define				SMP_239_5				24

#define				TIMER_1_TRGO			25
#define				TIMER_1_CC4				26
#define				TIMER_2_TRGO			27
#define				TIMER_2_CC1				28
#define				TIMER_3_CC4				29
#define				TIMER_4_TRGO			30
#define				EXTI_LINE_15			31
#define				TIMER_8_CC4				32
#define				JSWSTART				33

#define				AW_SINGLE_CH			34
#define				AW_ALL_CH				35



/*#define	Disable 0
#define	Enable  1*/

/*external event select for regular group*/
/*#define Timer_1_CC1  0
#define Timer_1_CC2  1
#define Timer_1_CC3  2
#define Timer_2_CC2  3
#define Timer_3_TRGO 4
#define Timer_4_CC4  5
#define	EXTI_line_11 6
#define SWSTART      7





*/









#endif /* ADC_PRIVATE_H_ */

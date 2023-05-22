/*
 * DMA_config.h
 *
 *  Created on: May 13, 2023
 *      Author: Sherif Ahmed
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

//enable or disable channels
#define		ADC1_CH0			           DISABLED
#define		ADC1_CH1					   DISABLED
#define		ADC1_CH2					   DISABLED
#define		ADC1_CH3			           DISABLED
#define		ADC1_CH4			           DISABLED
#define		ADC1_CH5			           DISABLED
#define		ADC1_CH6			           DISABLED
#define		ADC1_CH7			           DISABLED
#define		ADC1_CH8			           DISABLED
#define		ADC1_CH9			           DISABLED
//temp sensor
#define		ADC1_CH16					   ENABLED
/*choose ADC  PRESCALER
/  options are {2, 4, 6, 8} **/
#define		RCC_ADC_PRE						6
//enable or disable analog watchdog on regular and injected channels
//options : { ENCABLED, DISABLED }
#define 	ADC1_AW_REGULAR					DISABLED
#define 	ADC1_AW_INJECTED				DISABLED
//number of channels to be converted in discontinuous mode
//options: { 0 : 8 }
#define 	ADC1_DISC_CH_COUNT				0
//enable or disable discontinuous mode on regular and injected channels
//options : { ENCABLED, DISABLED }
#define 	ADC1_DISC_MODE					DISABLED
#define 	ADC1_INJECTED_DISC_MODE			DISABLED

//enable or disable Automatic Injected Group conversion
//options : { ENCABLED, DISABLED }
#define 	ADC1_INJECTED_AUTO				DISABLED

//choose if analog watchdog is enabled on all or a single channel
//options : { AW_SINGLE_CH, AW_ALL_CH }
#define 	ADC1_AW_MODE					AW_SINGLE_CH

//enable or disable scan mode
//options : { ENCABLED, DISABLED }
#define 	ADC1_SCAN_MODE					DISABLED

//enable or disable EOC Interrupts for injected channels
//options : { ENCABLED, DISABLED }
#define		ADC1_INJ_INTERRUPT_GEN			DISABLED
//enable or disable Interrupts for analog watchdog
//options : { ENCABLED, DISABLED }
#define 	ADC1_AW_INTERRUPT				DISABLED

//enable or disable EOC Interrupts for regular channels
//options : { ENCABLED, DISABLED }
#define		ADC1_INTERRUPT_GEN				DISABLED

//select the input channel to be guarded by the Analog watchdog.
//options: { 0 : 17 }
#define 	ADC1_AW_CH						0

//enable or disable Temperature sensor and VREFINT
//options : { ENCABLED, DISABLED }
#define 	TEMP_SENSOR_VREF				ENABLED

//enable or disable External trigger conversion mode for regular channels
//options : { ENCABLED, DISABLED }
#define		ADC1_EXT_TRIGGER				ENABLED
//select the external event used to trigger the start of conversion of a regular group.
//options: { TIMER_1_CC1, TIMER_1_CC2,
//			 TIMER_1_CC3, TIMER_2_CC2,
//			 TIMER_3_TRGO, TIMER_4_CC4,
//			 EXTI_LINE_11, TIMER_8_TRGO,
//			 SWSTART }
#define		ADC1_TRIGGER					SWSTART

//enable or disable External trigger conversion mode for Injected channels
//options : { ENCABLED, DISABLED }
#define		ADC1_INJECTED_EXT_TRIGGER		ENABLED

//select the external event used to trigger the start of conversion of a Injected group.
//options: { TIMER_1_TRGO, TIMER_1_CC4,
//			 TIMER_2_TRGO, TIMER_2_CC1,
//			 TIMER_3_CC4, TIMER_4_TRGO,
//			 EXTI_LINE_15, TIMER_8_CC4,
//			 JSWSTART }
#define		ADC1_INJECTED_TRIGGER			JSWSTART
//select Data alignment
//options: { RIGHT : LEFT }
#define		DATA_ALIGNMENT					RIGHT
//enable or disable Direct memory access mode
//options : { ENCABLED, DISABLED }
#define		ADC1_DMA_REQ					DISABLED
//enable or disable Calibration of adc(at the start)
//options : { ENCABLED, DISABLED }
#define		ADC1_CALIBRATIN					ENABLED
//select Conversion mode
//options: { CONTINUOUS : SINGLE }
#define 	ADC1_CONVERSION_MODE			CONTINUOUS
//select  Channel Sample time in cycles(x_y = x.y, ex: 1_5 = 1.5 cycles)
//options: { SMP_1_5, SMP_7_5,
//			 SMP_13_5, SMP_28_5,
//			 SMP_41_5, SMP_55_5,
//			 SMP_71_5, SMP_239_5 }
#define		ADC1_CH0_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH1_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH2_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH3_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH4_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH5_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH6_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH7_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH8_SAMPLING_TIME			SMP_1_5
#define		ADC1_CH9_SAMPLING_TIME			SMP_1_5
//sampling time for temp sensor
#define		ADC1_CH16_SAMPLING_TIME			SMP_71_5

//enter the offset to be subtracted from the raw converted data when converting injected channels
//options: { 0 : 4095 }
#define		ADC1_INJECTED1_OFFSET			0
#define		ADC1_INJECTED2_OFFSET			0
#define		ADC1_INJECTED3_OFFSET			0
#define		ADC1_INJECTED4_OFFSET			0
//enter the  Analog watchdog high threshold
//options: { 0 : 4095 }
#define		ADC1_AW_HTR						0
//enter the  Analog watchdog high threshold
//options: { 0 : 4095 }
#define		ADC1_AW_LTR						0

//enter the number of regular conversions.
//options: { 1 : 16 }
#define		SEQ_LENGTH						1
//select  Channel sequences
//options: { 1 : 16 }
#define		ADC1_CH0_SQ						1
#define		ADC1_CH1_SQ						1
#define		ADC1_CH2_SQ						1
#define		ADC1_CH3_SQ						1
#define		ADC1_CH4_SQ						1
#define		ADC1_CH5_SQ						1
#define		ADC1_CH6_SQ						1
#define		ADC1_CH7_SQ						1
#define		ADC1_CH8_SQ						1
#define		ADC1_CH9_SQ						1
//sequences for temp sensor
#define		ADC1_CH16_SQ					1

//enter the number of injected conversions.
//options: { 1 : 4 }
#define		INJECTED_SEQ_LENGTH				1
//select  injected Channel sequences
//options: { 1 : 16 }
#define		ADC1_CH0_INJ_SQ					1
#define		ADC1_CH1_INJ_SQ					1
#define		ADC1_CH2__INJ_SQ				1
#define		ADC1_CH3__INJ_SQ				1
#define		ADC1_CH4__INJ_SQ				1
#define		ADC1_CH5__INJ_SQ				1
#define		ADC1_CH6__INJ_SQ				1
#define		ADC1_CH7__INJ_SQ				1
#define		ADC1_CH8__INJ_SQ				1
#define		ADC1_CH9__INJ_SQ				1
#define		ADC1_CH16_INJ_SQ				1






#endif /* ADC_CONFIG_H_ */

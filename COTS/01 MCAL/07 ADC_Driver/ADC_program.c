/*
 * ADC_program.c
 *
 *  Created on: May 13, 2023
 *      Author: Sherif Ahmed
 */
#include "stdTypes.h"
#include "BITMATH.h"
#include "errorStates.h"
#include "delay.h"

#include "RCC_interface.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"


void ADC_Init(void) {

#ifndef		RCC_CFGR
#define		RCC_BASE_ADD			(0x40021000)
#define		RCC_CFGR				*((u32 *)(RCC_BASE_ADD+0x04))
#endif
	/* 		setting ADC prescaler bits according to desired value		*/
	switch (RCC_ADC_PRE) {
	case 2:
		break;
	case 4:
		SET_BIT(RCC_CFGR, ADCPRE0);
		break;
	case 6:
		SET_BIT(RCC_CFGR, ADCPRE1);
		break;
	case 8:
		SET_BIT(RCC_CFGR, ADCPRE1);
		SET_BIT(RCC_CFGR, ADCPRE0);
		break;
	default:
		break;
	}
	
	/* 		setting conversion mode		*/
	switch (ADC1_CONVERSION_MODE) {
	case CONTINUOUS:
		SET_BIT(ADC1->CR2, 1);
		break;
	case SINGLE:
		CLR_BIT(ADC1->CR2, 1);
		break;
	}
	
	/* 		setting trigger source		*/
	switch (ADC1_TRIGGER) {
	case TIMER_1_CC1:
		ADC1->CR2 |= (0 << 17);
		break;
	case TIMER_1_CC2:
		ADC1->CR2 |= (1 << 17);
		break;
	case TIMER_1_CC3:
		ADC1->CR2 |= (2 << 17);
		break;
	case TIMER_2_CC2:
		ADC1->CR2 |= (3 << 17);
		break;
	case TIMER_3_TRGO:
		ADC1->CR2 |= (4 << 17);
		break;
	case TIMER_4_CC4:
		ADC1->CR2 |= (5 << 17);
		break;
	case EXTI_LINE_11:
		ADC1->CR2 |= (6 << 17);
		break;
	case TIMER_8_TRGO:
		ADC1->CR2 |= (6 << 17);
		break;
	case SWSTART:
		ADC1->CR2 |= (7 << 17);
		break;
	default:
		break;
	}
	/* 		setting data alignmemt		*/
	switch (DATA_ALIGNMENT) {
	case RIGHT:
		CLR_BIT(ADC1->CR2, 11);
		break;
	case LEFT:
		SET_BIT(ADC1->CR2, 11);
		break;
	}
	/* 		setting channel config		*/
#if	(ADC1_CH0 == ENABLED)
	switch(ADC1_CH0_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<0);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<0);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<0);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<0);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<0);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<0);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<0);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<0);break;
		default: break;
	}
	switch(ADC1_CH0_SQ){
		case 1:  			ADC1->SQR3 |= (0<<0);break;
		case 2:  			ADC1->SQR3 |= (0<<5);break;
		case 3: 			ADC1->SQR3 |= (0<<10);break;
		case 4: 			ADC1->SQR3 |= (0<<15);break;
		case 5: 			ADC1->SQR3 |= (0<<20);break;
		case 6: 			ADC1->SQR3 |= (0<<25);break;
		case 7:				ADC1->SQR2 |= (0<<0);break;
		case 8:				ADC1->SQR2 |= (0<<5);break;
		case 9:				ADC1->SQR2 |= (0<<10);break;
		case 10:			ADC1->SQR2 |= (0<<15);break;
		case 11:			ADC1->SQR2 |= (0<<20);break;
		case 12:			ADC1->SQR2 |= (0<<25);break;
		case 13:			ADC1->SQR1 |= (0<<0);break;
		case 14:			ADC1->SQR1 |= (0<<5);break;
		case 15:			ADC1->SQR1 |= (0<<10);break;
		case 16:			ADC1->SQR1 |= (0<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH1 == ENABLED)
	switch(ADC1_CH1_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<3);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<3);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<3);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<3);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<3);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<3);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<3);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<3);break;
		default: break;
	}
	switch(ADC1_CH1_SQ){
		case 1:  			ADC1->SQR3 |= (1<<0);break;
		case 2:  			ADC1->SQR3 |= (1<<5);break;
		case 3: 			ADC1->SQR3 |= (1<<10);break;
		case 4: 			ADC1->SQR3 |= (1<<15);break;
		case 5: 			ADC1->SQR3 |= (1<<20);break;
		case 6: 			ADC1->SQR3 |= (1<<25);break;
		case 7:				ADC1->SQR2 |= (1<<0);break;
		case 8:				ADC1->SQR2 |= (1<<5);break;
		case 9:				ADC1->SQR2 |= (1<<10);break;
		case 10:			ADC1->SQR2 |= (1<<15);break;
		case 11:			ADC1->SQR2 |= (1<<20);break;
		case 12:			ADC1->SQR2 |= (1<<25);break;
		case 13:			ADC1->SQR1 |= (1<<0);break;
		case 14:			ADC1->SQR1 |= (1<<5);break;
		case 15:			ADC1->SQR1 |= (1<<10);break;
		case 16:			ADC1->SQR1 |= (1<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH2 == ENABLED)
	switch(ADC1_CH2_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<6);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<6);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<6);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<6);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<6);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<6);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<6);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<6);break;
		default: break;
	}
	switch(ADC1_CH2_SQ){
		case 1:  			ADC1->SQR3 |= (2<<0);break;
		case 2:  			ADC1->SQR3 |= (2<<5);break;
		case 3: 			ADC1->SQR3 |= (2<<10);break;
		case 4: 			ADC1->SQR3 |= (2<<15);break;
		case 5: 			ADC1->SQR3 |= (2<<20);break;
		case 6: 			ADC1->SQR3 |= (2<<25);break;
		case 7:				ADC1->SQR2 |= (2<<0);break;
		case 8:				ADC1->SQR2 |= (2<<5);break;
		case 9:				ADC1->SQR2 |= (2<<10);break;
		case 10:			ADC1->SQR2 |= (2<<15);break;
		case 11:			ADC1->SQR2 |= (2<<20);break;
		case 12:			ADC1->SQR2 |= (2<<25);break;
		case 13:			ADC1->SQR1 |= (2<<0);break;
		case 14:			ADC1->SQR1 |= (2<<5);break;
		case 15:			ADC1->SQR1 |= (2<<10);break;
		case 16:			ADC1->SQR1 |= (2<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH3 == ENABLED)
	switch(ADC1_CH3_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<9);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<9);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<9);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<9);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<9);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<9);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<9);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<9);break;
		default: break;
	}
	switch(ADC1_CH3_SQ){
		case 1:  			ADC1->SQR3 |= (3<<0);break;
		case 2:  			ADC1->SQR3 |= (3<<5);break;
		case 3: 			ADC1->SQR3 |= (3<<10);break;
		case 4: 			ADC1->SQR3 |= (3<<15);break;
		case 5: 			ADC1->SQR3 |= (3<<20);break;
		case 6: 			ADC1->SQR3 |= (3<<25);break;
		case 7:				ADC1->SQR2 |= (3<<0);break;
		case 8:				ADC1->SQR2 |= (3<<5);break;
		case 9:				ADC1->SQR2 |= (3<<10);break;
		case 10:			ADC1->SQR2 |= (3<<15);break;
		case 11:			ADC1->SQR2 |= (3<<20);break;
		case 12:			ADC1->SQR2 |= (3<<25);break;
		case 13:			ADC1->SQR1 |= (3<<0);break;
		case 14:			ADC1->SQR1 |= (3<<5);break;
		case 15:			ADC1->SQR1 |= (3<<10);break;
		case 16:			ADC1->SQR1 |= (3<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH4 == ENABLED)
	switch(ADC1_CH4_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<12);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<12);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<12);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<12);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<12);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<12);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<12);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<12);break;
		default: break;
	}
	switch(ADC1_CH4_SQ){
		case 1:  			ADC1->SQR3 |= (4<<0);break;
		case 2:  			ADC1->SQR3 |= (4<<5);break;
		case 3: 			ADC1->SQR3 |= (4<<10);break;
		case 4: 			ADC1->SQR3 |= (4<<15);break;
		case 5: 			ADC1->SQR3 |= (4<<20);break;
		case 6: 			ADC1->SQR3 |= (4<<25);break;
		case 7:				ADC1->SQR2 |= (4<<0);break;
		case 8:				ADC1->SQR2 |= (4<<5);break;
		case 9:				ADC1->SQR2 |= (4<<10);break;
		case 10:			ADC1->SQR2 |= (4<<15);break;
		case 11:			ADC1->SQR2 |= (4<<20);break;
		case 12:			ADC1->SQR2 |= (4<<25);break;
		case 13:			ADC1->SQR1 |= (4<<0);break;
		case 14:			ADC1->SQR1 |= (4<<5);break;
		case 15:			ADC1->SQR1 |= (4<<10);break;
		case 16:			ADC1->SQR1 |= (4<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH5 == ENABLED)
	switch(ADC1_CH5_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<15);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<15);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<15);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<15);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<15);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<15);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<15);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<15);break;
		default: break;
	}
	switch(ADC1_CH5_SQ){
		case 1:  			ADC1->SQR3 |= (5<<0);break;
		case 2:  			ADC1->SQR3 |= (5<<5);break;
		case 3: 			ADC1->SQR3 |= (5<<10);break;
		case 4: 			ADC1->SQR3 |= (5<<15);break;
		case 5: 			ADC1->SQR3 |= (5<<20);break;
		case 6: 			ADC1->SQR3 |= (5<<25);break;
		case 7:				ADC1->SQR2 |= (5<<0);break;
		case 8:				ADC1->SQR2 |= (5<<5);break;
		case 9:				ADC1->SQR2 |= (5<<10);break;
		case 10:			ADC1->SQR2 |= (5<<15);break;
		case 11:			ADC1->SQR2 |= (5<<20);break;
		case 12:			ADC1->SQR2 |= (5<<25);break;
		case 13:			ADC1->SQR1 |= (5<<0);break;
		case 14:			ADC1->SQR1 |= (5<<5);break;
		case 15:			ADC1->SQR1 |= (5<<10);break;
		case 16:			ADC1->SQR1 |= (5<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH6 == ENABLED)
	switch(ADC1_CH6_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<18);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<18);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<18);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<18);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<18);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<18);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<18);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<18);break;
		default: break;
	}
	switch(ADC1_CH6_SQ){
		case 1:  			ADC1->SQR3 |= (6<<0);break;
		case 2:  			ADC1->SQR3 |= (6<<5);break;
		case 3: 			ADC1->SQR3 |= (6<<10);break;
		case 4: 			ADC1->SQR3 |= (6<<15);break;
		case 5: 			ADC1->SQR3 |= (6<<20);break;
		case 6: 			ADC1->SQR3 |= (6<<25);break;
		case 7:				ADC1->SQR2 |= (6<<0);break;
		case 8:				ADC1->SQR2 |= (6<<5);break;
		case 9:				ADC1->SQR2 |= (6<<10);break;
		case 10:			ADC1->SQR2 |= (6<<15);break;
		case 11:			ADC1->SQR2 |= (6<<20);break;
		case 12:			ADC1->SQR2 |= (6<<25);break;
		case 13:			ADC1->SQR1 |= (6<<0);break;
		case 14:			ADC1->SQR1 |= (6<<5);break;
		case 15:			ADC1->SQR1 |= (6<<10);break;
		case 16:			ADC1->SQR1 |= (6<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH7 == ENABLED)
	switch(ADC1_CH7_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<21);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<21);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<21);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<21);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<21);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<21);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<21);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<21);break;
		default: break;
	}
	switch(ADC1_CH7_SQ){
		case 1:  			ADC1->SQR3 |= (7<<0);break;
		case 2:  			ADC1->SQR3 |= (7<<5);break;
		case 3: 			ADC1->SQR3 |= (7<<10);break;
		case 4: 			ADC1->SQR3 |= (7<<15);break;
		case 5: 			ADC1->SQR3 |= (7<<20);break;
		case 6: 			ADC1->SQR3 |= (7<<25);break;
		case 7:				ADC1->SQR2 |= (7<<0);break;
		case 8:				ADC1->SQR2 |= (7<<5);break;
		case 9:				ADC1->SQR2 |= (7<<10);break;
		case 10:			ADC1->SQR2 |= (7<<15);break;
		case 11:			ADC1->SQR2 |= (7<<20);break;
		case 12:			ADC1->SQR2 |= (7<<25);break;
		case 13:			ADC1->SQR1 |= (7<<0);break;
		case 14:			ADC1->SQR1 |= (7<<5);break;
		case 15:			ADC1->SQR1 |= (7<<10);break;
		case 16:			ADC1->SQR1 |= (7<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH8 == ENABLED)
	switch(ADC1_CH8_SAMPLING_TIME){
		case SMP_1_5:  		ADC1->SMPR2 |= (0<<24);break;
		case SMP_7_5:  		ADC1->SMPR2 |= (1<<24);break;
		case SMP_13_5: 		ADC1->SMPR2 |= (2<<24);break;
		case SMP_28_5: 		ADC1->SMPR2 |= (3<<24);break;
		case SMP_41_5: 		ADC1->SMPR2 |= (4<<24);break;
		case SMP_55_5: 		ADC1->SMPR2 |= (5<<24);break;
		case SMP_71_5:		ADC1->SMPR2 |= (6<<24);break;
		case SMP_239_5:		ADC1->SMPR2 |= (7<<24);break;
		default: break;
	}
	switch(ADC1_CH8_SQ){
		case 1:  			ADC1->SQR3 |= (8<<0);break;
		case 2:  			ADC1->SQR3 |= (8<<5);break;
		case 3: 			ADC1->SQR3 |= (8<<10);break;
		case 4: 			ADC1->SQR3 |= (8<<15);break;
		case 5: 			ADC1->SQR3 |= (8<<20);break;
		case 6: 			ADC1->SQR3 |= (8<<25);break;
		case 7:				ADC1->SQR2 |= (8<<0);break;
		case 8:				ADC1->SQR2 |= (8<<5);break;
		case 9:				ADC1->SQR2 |= (8<<10);break;
		case 10:			ADC1->SQR2 |= (8<<15);break;
		case 11:			ADC1->SQR2 |= (8<<20);break;
		case 12:			ADC1->SQR2 |= (8<<25);break;
		case 13:			ADC1->SQR1 |= (8<<0);break;
		case 14:			ADC1->SQR1 |= (8<<5);break;
		case 15:			ADC1->SQR1 |= (8<<10);break;
		case 16:			ADC1->SQR1 |= (8<<15);break;
		default: break;
	}
#endif

#if	(ADC1_CH9 == ENABLED)
	switch (ADC1_CH9_SAMPLING_TIME) {
	case SMP_1_5:
		ADC1->SMPR2 |= (0 << 27);
		break;
	case SMP_7_5:
		ADC1->SMPR2 |= (1 << 27);
		break;
	case SMP_13_5:
		ADC1->SMPR2 |= (2 << 27);
		break;
	case SMP_28_5:
		ADC1->SMPR2 |= (3 << 27);
		break;
	case SMP_41_5:
		ADC1->SMPR2 |= (4 << 27);
		break;
	case SMP_55_5:
		ADC1->SMPR2 |= (5 << 27);
		break;
	case SMP_71_5:
		ADC1->SMPR2 |= (6 << 27);
		break;
	case SMP_239_5:
		ADC1->SMPR2 |= (7 << 27);
		break;
	default:
		break;
	}
	switch (ADC1_CH9_SQ) {
	case 1:
		ADC1->SQR3 |= (9 << 0);
		break;
	case 2:
		ADC1->SQR3 |= (9 << 5);
		break;
	case 3:
		ADC1->SQR3 |= (9 << 10);
		break;
	case 4:
		ADC1->SQR3 |= (9 << 15);
		break;
	case 5:
		ADC1->SQR3 |= (9 << 20);
		break;
	case 6:
		ADC1->SQR3 |= (9 << 25);
		break;
	case 7:
		ADC1->SQR2 |= (9 << 0);
		break;
	case 8:
		ADC1->SQR2 |= (9 << 5);
		break;
	case 9:
		ADC1->SQR2 |= (9 << 10);
		break;
	case 10:
		ADC1->SQR2 |= (9 << 15);
		break;
	case 11:
		ADC1->SQR2 |= (9 << 20);
		break;
	case 12:
		ADC1->SQR2 |= (9 << 25);
		break;
	case 13:
		ADC1->SQR1 |= (9 << 0);
		break;
	case 14:
		ADC1->SQR1 |= (9 << 5);
		break;
	case 15:
		ADC1->SQR1 |= (9 << 10);
		break;
	case 16:
		ADC1->SQR1 |= (9 << 15);
		break;
	default:
		break;
	}
#endif

#if	(ADC1_CH16 == ENABLED)
	switch(ADC1_CH16_SAMPLING_TIME) {
		case SMP_1_5: ADC1->SMPR1 |= (0<<18);break;
		case SMP_7_5: ADC1->SMPR1 |= (1<<18);break;
		case SMP_13_5: ADC1->SMPR1 |= (2<<18);break;
		case SMP_28_5: ADC1->SMPR1 |= (3<<18);break;
		case SMP_41_5: ADC1->SMPR1 |= (4<<18);break;
		case SMP_55_5: ADC1->SMPR1 |= (5<<18);break;
		case SMP_71_5: ADC1->SMPR1 |= (6<<18);break;
		case SMP_239_5: ADC1->SMPR1 |= (7<<18);break;
		default: break;
	}
	switch(ADC1_CH16_SQ) {
		case 1: ADC1->SQR3 |= (16<<0);break;
		case 2: ADC1->SQR3 |= (16<<5);break;
		case 3: ADC1->SQR3 |= (16<<10);break;
		case 4: ADC1->SQR3 |= (16<<15);break;
		case 5: ADC1->SQR3 |= (16<<20);break;
		case 6: ADC1->SQR3 |= (16<<25);break;
		case 7: ADC1->SQR2 |= (16<<0);break;
		case 8: ADC1->SQR2 |= (16<<5);break;
		case 9: ADC1->SQR2 |= (16<<10);break;
		case 10: ADC1->SQR2 |= (16<<15);break;
		case 11: ADC1->SQR2 |= (16<<20);break;
		case 12: ADC1->SQR2 |= (16<<25);break;
		case 13: ADC1->SQR1 |= (16<<0);break;
		case 14: ADC1->SQR1 |= (16<<5);break;
		case 15: ADC1->SQR1 |= (16<<10);break;
		case 16: ADC1->SQR1 |= (16<<15);break;
		default: break;
	}
#endif
	if(TEMP_SENSOR_VREF == ENABLED) SET_BIT(ADC1->CR2, 23);

	ADC1->CR2 |= 1 << 0;
	_delay_ms(50);
	if(ADC1_CALIBRATIN  == ENABLED){
		SET_BIT(ADC1->CR2, 2);
		while(GET_BIT(ADC1->CR2, 2));
	}
}

void ADC_Start(void) 
{
	ADC1->SR = 0;                      	 // Clear Status register
	ADC1->CR2 |= (1 << 20);              // Conversion on external event enabled
	ADC1->CR2 |= 1 << 22;                // Start conversion
}

u16 ADC_Read(void) 
{
	return (u16) ADC1->DR;
}


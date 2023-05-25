/*
 * ADC_private.h
 *
 *  Created on: May 10, 2023
 *      Author: Sherif Ahmed
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#define ADC1_BASE_ADD           0x40012400
#define ADC1_SR                  *((u32 *)(ADC1_BASE_ADD+0x00))
#define ADC1_CR1                  *((u32 *)(ADC1_BASE_ADD+0x04))


#define ADC1_CR2                    *((u32 *)(ADC1_BASE_ADD+0x08))
#define ADC1_SMPR1                  *((u32 *)(ADC1_BASE_ADD+0x0C))
#define ADC1_SMPR2                  *((u32 *)(ADC1_BASE_ADD+0x10))
#define ADC1_JOFR1                  *((u32 *)(ADC1_BASE_ADD+0x14))
#define ADC1_JOFR2                  *((u32 *)(ADC1_BASE_ADD+0x18))
#define ADC1_JOFR3                  *((u32 *)(ADC1_BASE_ADD+0x1C))
#define ADC1_JOFR4                  *((u32 *)(ADC1_BASE_ADD+0x20))
#define ADC1_HTR                    *((u32 *)(ADC1_BASE_ADD+0x24))
#define ADC1_LTR                    *((u32 *)(ADC1_BASE_ADD+0x28))
#define ADC1_SQR1                   *((u32 *)(ADC1_BASE_ADD+0x2C))
#define ADC1_SQR2                   *((u32 *)(ADC1_BASE_ADD+0x30))
#define ADC1_SQR3                   *((u32 *)(ADC1_BASE_ADD+0x34))
//#define ADC_JSQR                  *((u32 *)(ADC1_BASE_ADD+))
//#define ADC_SQR3                  *((u32 *)(ADC1_BASE_ADD+))
//#define ADC_SQR3                  *((u32 *)(ADC1_BASE_ADD+))
//#define ADC_SQR3                  *((u32 *)(ADC1_BASE_ADD+))
//#define ADC_SQR3                  *((u32 *)(ADC1_BASE_ADD+))

//#define ADC_SQR3                  *((u32 *)(ADC1_BASE_ADD+))




#endif /* ADC_PRIVATE_H_ */

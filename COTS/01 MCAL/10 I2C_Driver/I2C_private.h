/*
 * I2C_private.h
 *
 *  Created on: May 18, 2023
 *      Author: Sherif Ahmed
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#include "stdTypes.h"
#include "errorStates.h"




#define READ     0
#define WRITE    1

//
//#define	F_PCLK_2      0
//#define	F_PCLK_4      1
//#define	F_PCLK_8      2
//#define	F_PCLK_16     3
//#define	F_PCLK_32     4
//#define	F_PCLK_64     5
//#define	F_PCLK_128    6
//#define	F_PCLK_256    7


#define  I2C1_BASE_ADD   0x40005400

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 OAR1;
	volatile u32 OAR2;
	volatile u32 DR;
	volatile u32 SR1;
	volatile u32 SR2;
	volatile u32 CCR;
	volatile u32 TRISE ;



}I2C_type;

#define    I2C1     ((I2C_type*)I2C1_BASE_ADD)


#endif /* I2C_PRIVATE_H_ */

/*
 * SPI_private.h
 *
 *  Created on: May 15, 2023
 *      Author: Sherif Ahmed
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#include "stdTypes.h"
#include "errorStates.h"

#define BIT_8   0
#define BIT_16  1

#define Full_Duplex		0
#define Recieve_Only	1

#define Disabled 0
#define Enabled  1


#define MSB		0
#define LSB     1

#define	F_PCLK_2      0
#define	F_PCLK_4      1
#define	F_PCLK_8      2
#define	F_PCLK_16     3
#define	F_PCLK_32     4
#define	F_PCLK_64     5
#define	F_PCLK_128    6
#define	F_PCLK_256    7


#define  SPI1_BASE_ADD   0x40013000

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR ;



}SPI_type;

#define   SPI1     ((SPI_type*)SPI1_BASE_ADD)

#endif /* SPI_PRIVATE_H_ */

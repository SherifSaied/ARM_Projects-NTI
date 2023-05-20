/*
 * USART_private.h
 *
 *  Created on: May 14, 2023
 *      Author: Sherif Ahmed
 */

#ifndef USART1_PRIVATE_H_
#define USART1_PRIVATE_H_

#define  USART1_BASE_ADD     0x40013800

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;

}USART_type;

#define  USART1     ((USART_type*)USART1_BASE_ADD )


#endif /* USART1_PRIVATE_H_ */

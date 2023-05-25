/*
 * delay.h
 *
 *  Created on: May 11, 2023
 *      Author: Sherif Ahmed
 */

#ifndef DELAY_H_
#define DELAY_H_

void _delay_ms(u32 ticks)
{
	u32 i;
	for( i = 0; i < (ticks*500) ; i++)
			{
				asm("NOP");
			}
}

#endif /* DELAY_H_ */

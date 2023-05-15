/*
 * LCD_priv.h
 *
 *  Created on: May 6, 2023
 *      Author: Sherif Ahmed
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

// delay function
void _delay_ms(u32 ticks)
{
	u32 i;
	for( i = 0; i < (ticks * 500) ; i++)
		{
			asm("NOP");
		}
}


#endif /* LCD_PRIV_H_ */

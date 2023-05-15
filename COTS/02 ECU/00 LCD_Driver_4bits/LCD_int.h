/*
 * LCD_int.h
 *
 *  Created on: May 6, 2023
 *      Author: Sherif Ahmed
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

#include "stdTypes.h"
#include "errorStates.h"

#include "LCD_priv.h"
#include "LCD_config.h"




void _delay_ms(u32 ticks); //delay function


ES_t LCD_enuInit(void);
ES_t LCD_enuDisplayChar(u8 copy_u8Data);
ES_t LCD_enuSendCommand(u8 copy_u8Command);



#endif /* LCD_INT_H_ */

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




ES_t LCD_enuInit(void);
ES_t LCD_enuSendCommand(u8 copy_u8Command);

ES_t LCD_enuSendChar(u8 copy_u8Char);
ES_t LCD_enuSendString(char * copy_u8Data);

ES_t LCD_enuGoToCursor(u8 lineNumber, u8 Column);

ES_t LCD_enuCreateCustomChar(u8 *pattern, u8 location);
ES_t LCD_enuClear(void);

void LCD_voidWriteNumber(u32 number);




#endif /* LCD_INT_H_ */

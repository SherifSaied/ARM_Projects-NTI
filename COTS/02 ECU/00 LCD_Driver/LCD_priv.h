/*
 * LCD_priv.h
 *
 *  Created on: May 6, 2023
 *      Author: Sherif Ahmed
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

/*
#define  LCD_CURSOR_RETURN        0x02  // return cursor to first position on first line
#define  SHIFT_CURSOR_RIGHT       0x06  // make you write from left to right
#define  LCD_CLEAR_CMD  		  0x01
#define  SHIFT_CURSOR_TO_1_LINE   0x80  // to write in first line
#define  SHIFT_CURSOR_TO_2_LINE   0xC0  // to write in second line
////////////////////////////////////////////////////////////////////
#define  LCD_FONT_BOLD            0x04         // 5 x 10 font
#define  LCD_FONT_NOT_BOLD        0x00         // 5 x 8 font
#define  LCD_2_LINE               0x08         // 2-line display
#define  LCD_1_LINE               0x00         // 1-line display
#define  FOUR_BIT_MODE            0x20    // 1 line, 4-bit mode
#define  EIGHT_BIT_MODE           0x30    // 1 line, 4-bit mode
#define  CONTROL_MODE   (LCD_FONT_NOT_BOLD | LCD_2_LINE | FOUR_BIT_MODE) // 2 lines, 5x8 matrix,4-bit mode (you can make your own mode)
/////////////////////////////////////////////////////////////////////
#define  DISPLAY_ON_CURSOR_OFF    0x0C
#define  DISPLAY_ON_CURSOR_ON     0x0E
////////////////////////////////////////////////////////////////////////
#define  CGRAM_ADDRESS     0x40
*/




#define CGRAM_ADDRESS        0x40

#define FUNC_SET_BIT_8       0x38
#define FUNC_SET_BIT_4       0x28                      /*(0x20 + 0x20)*/


#define NEXT_LINE    0b11000000
#define BIT_4      0
#define BIT_8      1





#endif /* LCD_PRIV_H_ */

/*
 * LCD_config.h
 *
 *  Created on: May 6, 2023
 *      Author: Sherif Ahmed
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_




/*CONTROL PINS*/

#define  RS_PORT     DIO_PORTC
#define  RS_PIN      DIO_PIN13

#define  RW_PORT     DIO_PORTC
#define  RW_PIN      DIO_PIN14

#define  EN_PORT     DIO_PORTC
#define  EN_PIN      DIO_PIN15

/*Data PORT and PINS*/
#define LCD_Data_PORT    DIO_PORTA

#define LCD_D0       DIO_PIN0
#define LCD_D1       DIO_PIN1
#define LCD_D2       DIO_PIN2
#define LCD_D3       DIO_PIN3
#define LCD_D4       DIO_PIN4
#define LCD_D5       DIO_PIN5
#define LCD_D6       DIO_PIN6
#define LCD_D7       DIO_PIN7









#define LCD_MODE    BIT_4    /*BIT_4 or BIT_8*/

#endif /* LCD_CONFIG_H_ */

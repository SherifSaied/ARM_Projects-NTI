/*
 * KPD_config.h
 *
 *  Created on: May 4, 2023
 *      Author: Sherif Ahmed
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_


#define KPD_PORT   DIO_PORTA

#define   KPD_COLUMN0_PIN         DIO_PIN0
#define   KPD_COLUMN1_PIN         DIO_PIN1
#define   KPD_COLUMN2_PIN         DIO_PIN2
#define   KPD_COLUMN3_PIN         DIO_PIN3

#define   KPD_ROW0_PIN            DIO_PIN4
#define   KPD_ROW1_PIN            DIO_PIN5
#define   KPD_ROW2_PIN            DIO_PIN6
#define   KPD_ROW3_PIN            DIO_PIN7


#define KPD_ARR_VAL                  {{1,2,3,4},{5,2,3,4},{6,2,3,4},{13,2,3,4}}





#define KPD_NO_PRESSED_KEY       0xff




#endif /* KPD_CONFIG_H_ */

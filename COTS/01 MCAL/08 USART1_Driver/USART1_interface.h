/*
 * USART_interface.h
 *
 *  Created on: May 14, 2023
 *      Author: Sherif Ahmed
 */

#ifndef USART1_INTERFACE_H_
#define USART1_INTERFACE_H_

#include "stdTypes.h"
#include "errorStates.h"

void UART_init();

void UART_enableTX(void);
void UART_enableRX(void);

void UART_voidSendchar(u8 data);
void UART_voidRecieveChar (u8 *data );

void UART1_voidSendString(u8 * str);
void UART1_StrReceiveString(u8 *str);





#endif /* USART1_INTERFACE_H_ */

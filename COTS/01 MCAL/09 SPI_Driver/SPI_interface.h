/*
 * SPI_interface.h
 *
 *  Created on: May 15, 2023
 *      Author: Sherif Ahmed
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "stdTypes.h"
#include "errorStates.h"


void SPI1_voidInit(void);
void SPI_voidMasterEnable();
void SPI_voidSlaveEnable();
u8 SPI1_u8SendRecievedChar(u8 byte);
void SPI1_voidSendString(u8 * str);
void SPI1_voidReceiveString(u8 *str);

#endif /* SPI_INTERFACE_H_ */

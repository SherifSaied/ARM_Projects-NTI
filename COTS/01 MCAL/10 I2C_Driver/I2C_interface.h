/*
 * I2C_interface.h
 *
 *  Created on: May 18, 2023
 *      Author: Sherif Ahmed
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_


void I2C_voidInit();
void I2C_voidStart();
void I2C_voidAddressSelect(u8 address);
void I2C_voidWriteByte(u8 byte);
void I2C_voidReadByte(u8 *byte);
void I2C_voidStop();

#endif /* I2C_INTERFACE_H_ */

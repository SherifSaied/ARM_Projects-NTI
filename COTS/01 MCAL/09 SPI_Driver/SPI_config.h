/*
 * SPI_config.h
 *
 *  Created on: May 15, 2023
 *      Author: Sherif Ahmed
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define  SPI1_BAUD_RATE_CONTROL      F_PCLK_2    /*you can choose from F_PCLK_2 up to F_PCLK_256*/

#define  SPI1_FRAME_FORMAT           MSB         /*LSB OR MSB*/

#define SPI1_SOFTWARE_SLAVE_MANAGEMENT  Enabled    /*Disabled or Enabled*/

#define SPI1_RECIEVE_ONLY    Full_Duplex    /*Full_Duplex "transmit and recieve" or Recieve_Only */

#define SPI1_DATA_FRAME_FORMAT    BIT_8         /*BIT_8 or BIT_16*/

#endif /* SPI_CONFIG_H_ */

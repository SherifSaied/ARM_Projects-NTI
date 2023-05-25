/*
 * bitMath.h
 *
 *  Created on: May 02, 2023
 *      Author: Sherif Ahmed
 */
 
#ifndef bitMath_H_
#define bitMath_H_

#define		SET_BIT(REG,BIT)		(REG |=  (1<<BIT))
#define		CLEAR_BIT(REG,BIT)		(REG &= ~(1<<BIT))
#define		TOG_BIT(REG,BIT)		(REG ^=  (1<<BIT))
#define		GET_BIT(REG,BIT)		((REG>>BIT)& 0x01)



#endif 

#ifndef		EXTI_interface_H
#define		EXTI_interface_H

#include "stdTypes.h"




void		EXTI_voidInit(u8 EXTI_line ,u8 line_PORT);

void		EXTI_voidEnableInt(u8 line_num);
void		EXTI_voidDisableInt(u8 line_num);

void		EXTI_voidEnableSWI(u8 line_num);
void		EXTI_voidChangeSenseMode(u8 line_num, u8 Sense_Mode);

void		EXTI_voidSetCallBack(void (*Fptr)(void), u8 ID_EXTI);


void	EXTI0_IRQHandler(void);
#endif

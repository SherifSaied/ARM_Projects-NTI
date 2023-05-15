/*



 * LCD_prog.c
 *
 *  Created on: May 6, 2023
 *      Author: Sherif Ahmed
*/
/*#include mn ta7t titititittiti l fooo2*/
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_interface.h"


#include "LCD_priv.h"
#include "LCD_config.h"













ES_t LCD_enuInit(void)
{
	ES_t local_u8ErrorState = ES_NOK;


	_delay_ms(35);  /*!comment: Delay more than 30ms*/








	return local_u8ErrorState;


}

ES_t LCD_enuDisplayChar(u8 copy_u8Data);
ES_t LCD_enuSendCommand(u8 copy_u8Command)
{
	ES_t local_u8ErrorState = ES_NOK;

	DIO_voidSetPinValue(RS_PORT, RS_PIN, DIO_LOW);









	return local_u8ErrorState;

}





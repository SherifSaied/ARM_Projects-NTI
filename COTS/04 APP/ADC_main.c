
#include "stdTypes.h"
#include "BITMATH.h"
#include "errorStates.h"


#include "RCC_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LCD_int.h"


#include "ADC_config.h"
#include "ADC_private.h"



int main(void) {
	u16 val;
	char c[6];
	//System Clock Init
	RCC_enuSysClkInit();
	//Enable RCC for GPIOs
	RCC_enuEnablePerClk(RCC_APB2, 2);
	RCC_enuEnablePerClk(RCC_APB2, 3);
	RCC_enuEnablePerClk(RCC_APB2, 4);
	RCC_enuEnablePerClk(RCC_APB2, 9);
	//DIO_voidSetPinDirection(PORTB, PIN1, GPIO_INPUT_ANALOG);
	LCD_enuInit();
	ADC_Init();
	ADC_Start();
	LCD_enuSendString("Temp = ");
	LCD_enuGoToCursor(1, 9);
	LCD_enuSendChar(223);
	LCD_enuSendChar('C');
	u16 temp;
	while (1) {
		val = ADC_Read();
		temp = ((1.43 - ((float)(3.3*val/(float)4095))) / 0.0043) + 25;
		temp+=2;
		sprintf(c, "%d", (int) temp);
		LCD_enuGoToCursor(1, 7);
		LCD_enuSendString("  ");
		LCD_enuGoToCursor(1, 7);
		LCD_enuSendString(c);
		_delay_ms(2000);
	}

}

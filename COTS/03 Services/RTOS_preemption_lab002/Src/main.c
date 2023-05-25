


#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#include "DIO_interface.h"

#ifndef NULL
#define NULL (void *)0
#endif

/* Define Tasks Priorities */
#define  LedOn_PRIORITY (2)

#define  LedOFF_PRIORITY (3)

/*tasks codes prototypes */
 void LedOn_code( void* pvParamter);

 void LedOFF_code( void* pvParamter);


 /*Create Task Handles Create */
 xTaskHandle Task1Hand = NULL;

 xTaskHandle Task2Hand = NULL;

 int main(void)
{
	/*initialize DIO*/
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN0,GPIO_OUTPUT_10MHZ_PP);
	/*Create tasks*/
	xTaskCreate(LedOn_code,(const signed char *)"Task1",85,NULL,LedOn_PRIORITY,&Task1Hand);

	/*Create tasks*/
	xTaskCreate(LedOFF_code,(const signed char *)"Task2",85,NULL,LedOFF_PRIORITY,&Task2Hand);


	/*start Scheduler */
	vTaskStartScheduler();

	/*Never Enter Here */
	return 0;
}

/*Task1 Code */


 void LedOn_code( void* pvParamter){

	for (;;)
	{
		/*Turn On  Led */
		LED_on(DIO_PORTB, DIO_PIN0);

	}
 }
 void LedOFF_code( void* pvParamter){

		vTaskDelay(2000);
		for (;;)
		{
			/*Turn Off Led */
			LED_off(DIO_PORTB, DIO_PIN0);

		}
 }


 /*
  * if You Turn On Preemption Led will Be Off Always
  * if You Turn Off Preemtion "0" will Be On Always
  *
  * **/

















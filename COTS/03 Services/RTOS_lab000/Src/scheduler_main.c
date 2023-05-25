#include "stdTypes.h"
#include "delay.h"
#include "DIO_interface.h"
#include "RCC_interface.h"
#include "STK_interface.h"
#include "scheduler_private.h"

#define NoOfTask    3
task_t arrTask[NoOfTask];
u32 taskCounter= 0;
void create_task(u32 copy_priority, u32 copy_priodicity,u32 copy_firstDelay,void *copy_fptr)
{
	//index based on prio here
	arrTask[copy_priority].priority=copy_priority;
	arrTask[copy_priority].priodicity=copy_priodicity;
	arrTask[copy_priority].firstDelay=copy_firstDelay;
	arrTask[copy_priority].fptr=copy_fptr;

}
void task_1(void)
{
_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0, GPIO_HIGH);

	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2, GPIO_LOW);

}
void task_2(void)
{
	_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1, GPIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2, GPIO_LOW);
}
void task_3(void)
{
	_delay_ms(200);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2, GPIO_HIGH);
}
static void schedulerStart(void)
{
	/* for loop to check on every TCB */
	u8 counter;
	for(counter = 0; counter < NoOfTask ; counter++)
	{
		if(arrTask[counter].firstDelay == 0)
		{
			//Call function
			arrTask[counter].fptr();
			//Periodicity => firstdelay
			arrTask[counter].firstDelay = arrTask[counter].priodicity - 1;
		}
		else
		{
			arrTask[counter].firstDelay--;
		}
	}

}

void start(void)
{
	//time set to start scheduler again
	STK_voidSetIntervalPeriodic(1, TIME_MS, schedulerStart);

}



int main(void)
{
	RCC_enuSysClkInit();
	RCC_enuEnablePerClk(RCC_APB2, 2) ;

	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN2, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN1, GPIO_OUTPUT_10MHZ_PP);

	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1, GPIO_LOW);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2, GPIO_LOW);
	STK_voidInit() ;



	//schedulerStart();

	create_task(0, 1000, 0, task_1);
	create_task(1, 2000, 1, task_2);
	create_task(2, 3000, 2, task_3);


		start();
	while (1)
	{


	}
	return 0 ;
}







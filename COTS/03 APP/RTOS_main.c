typedef  struct {
	u8 period ;
	void (*PTR)(void) ;
}TASK_t;
void creat_task (u8 pariortynum , u8 per,void (*ptr)(void));
void start(void) ;
void scheduler(void) ;
TASK_t arroftask[3] ;
void LED0(void){
	DIO_voidSetPinValue(PORTA, PIN0, GPIO_HIGH) ;
	_delay_ms(10);

}
void LED1(void){
	DIO_voidSetPinValue(PORTA, PIN1, GPIO_HIGH) ;
	_delay_ms(10);
}





int main(void)
{
	RCC_voidSysClkInt() ;
	RCC_voidEnablePerClk(RCC_APB2, 2) ;
	STK_voidInit() ;


	DIO_voidSetPinDirection(PORTA, PIN0 ,GPIO_OUTPUT_2MHZ_PP ) ;
	DIO_voidSetPinDirection(PORTA, PIN1 ,GPIO_OUTPUT_2MHZ_PP ) ;

	/* Loop forever */
	creat_task(0, 100, LED0);
	creat_task(1, 200, LED1);
	start() ;
	while (1){

	}
	return 0 ;
}

void scheduler(void){
	for(u8 i = 0 ; i < 3 ; i ++){
		arroftask[i].PTR() ;
	}

}

void creat_task (u8 pariortynum ,u8 per , void (*ptr)(void) ){
	arroftask[pariortynum].period = per ;
	arroftask[pariortynum].PTR = ptr ;
}

void start (void ) {
	STK_voidSetIntervalSingle(10000 , scheduler) ;

}

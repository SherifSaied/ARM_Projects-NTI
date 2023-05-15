




/*vector table for IntNum for EXTI 16 line */

#define EXTI_0     0
#define EXTI_1     1
#define EXTI_2     2
#define EXTI_3     3
#define EXTI_4     4

#define EXTI_5     5
#define EXTI_6     6
#define EXTI_7     7
#define EXTI_8     8
#define EXTI_9     9

#define EXTI_10     10
#define EXTI_11     11
#define EXTI_12     12
#define EXTI_13     13
#define EXTI_14     14
#define EXTI_15     15


#define NONE          3
#define FALLING_EDGE  0
#define RISING_EDGE   1
#define IOC           2

//#define   AFIO_BASE_ADD       0x40010000
//typedef struct
//{
//	volatile u32  EVCR;
//	volatile u32  MAPR;
//	volatile u32  EXTICR1;
//	volatile u32  EXTICR2;
//	volatile u32  EXTICR3;
//	volatile u32  EXTICR4;
//	volatile u32  MAPR2;
//
//}AFIO_Type;
//
//#define    AFIO            ((AFIO_Type*)(AFIO_BASE_ADD))



/*making registers addresses in struct instead of #define*/
typedef struct
{
	volatile	u32		IMR;     /*Int Mask Register*/
	volatile	u32		EMR;     /*Event Mask Register //have no any goal*/
	volatile	u32		RTSR;    /*Rising trigger selection Register*/ //if choose 1 then rising and if 0 will disable
	volatile	u32		FTSR;    /*Falling trigger selection Register*/
	volatile	u32		SWIER;   /*software Int event register*/ //for test SW only
	volatile	u32		PR;      /*Pending register*/ //very important   //write 1 then clr and read 1 then there is an Int
	
}EXTI_Type;

#define			EXTI				((EXTI_Type *)(EXTI_BASE_ADD))
#define		EXTI_BASE_ADD			   0x40010400





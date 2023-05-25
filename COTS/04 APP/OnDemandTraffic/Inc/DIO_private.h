#ifndef		DIO_PRIVATE_H
#define		DIO_PRIVATE_H

#define		DIO_PORTA			0
#define		DIO_PORTB			1
#define		DIO_PORTC			2

#define		DIO_PIN0			0
#define		DIO_PIN1			1
#define		DIO_PIN2			2
#define		DIO_PIN3			3
#define		DIO_PIN4			4
#define		DIO_PIN5			5
#define		DIO_PIN6			6
#define		DIO_PIN7			7
#define		DIO_PIN8			8
#define		DIO_PIN9			9
#define		DIO_PIN10			10
#define		DIO_PIN11			11
#define		DIO_PIN12			12
#define		DIO_PIN13			13
#define		DIO_PIN14			14
#define		DIO_PIN15			15

#define		GPIOA_BASE_ADD		(0x40010800)
#define		GPIOA_CRL			*((u32 *)(GPIOA_BASE_ADD+0x00))
#define		GPIOA_CRH			*((u32 *)(GPIOA_BASE_ADD+0x04))
#define		GPIOA_IDR			*((u32 *)(GPIOA_BASE_ADD+0x08))
#define		GPIOA_ODR			*((u32 *)(GPIOA_BASE_ADD+0x0C))
#define		GPIOA_BSRR			*((u32 *)(GPIOA_BASE_ADD+0x10))
#define		GPIOA_BRR			*((u32 *)(GPIOA_BASE_ADD+0x14))
#define		GPIOA_LCKR			*((u32 *)(GPIOA_BASE_ADD+0x18))


#define		GPIOB_BASE_ADD		(0x40010C00)
#define		GPIOB_CRL			*((u32 *)(GPIOB_BASE_ADD+0x00))
#define		GPIOB_CRH			*((u32 *)(GPIOB_BASE_ADD+0x04))
#define		GPIOB_IDR			*((u32 *)(GPIOB_BASE_ADD+0x08))
#define		GPIOB_ODR			*((u32 *)(GPIOB_BASE_ADD+0x0C))
#define		GPIOB_BSRR			*((u32 *)(GPIOB_BASE_ADD+0x10))
#define		GPIOB_BRR			*((u32 *)(GPIOB_BASE_ADD+0x14))
#define		GPIOB_LCKR			*((u32 *)(GPIOB_BASE_ADD+0x18))

#define		GPIOC_BASE_ADD		(0x40011000)
#define		GPIOC_CRL			*((u32 *)(GPIOC_BASE_ADD+0x00))
#define		GPIOC_CRH			*((u32 *)(GPIOC_BASE_ADD+0x04))
#define		GPIOC_IDR			*((u32 *)(GPIOC_BASE_ADD+0x08))
#define		GPIOC_ODR			*((u32 *)(GPIOC_BASE_ADD+0x0C))
#define		GPIOC_BSRR			*((u32 *)(GPIOC_BASE_ADD+0x10))
#define		GPIOC_BRR			*((u32 *)(GPIOC_BASE_ADD+0x14))
#define		GPIOC_LCKR			*((u32 *)(GPIOC_BASE_ADD+0x18))




#endif

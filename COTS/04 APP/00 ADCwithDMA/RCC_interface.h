#ifndef		RCC_INTERFACE_H_
#define		RCC_INTERFACE_H_

#include "errorStates.h"
#include "RCC_config.h"
#include "RCC_private.h"




#define RCC_AHB    0
#define RCC_APB1   1
#define RCC_APB2   2

/*peripheral id bits in  "RCC_AHBENR" Register*/
#define DMA1_PERIPHERAL     0
#define DMA2_PERIPHERAL     1
#define SRAM_PERIPHERAL     2
#define FLITF_PERIPHERAL    4
#define CRCE_PERIPHERAL     6
#define FSMC_PERIPHERAL     8
#define SDIO_PERIPHERAL     10

/*peripheral id bits in  "RCC_APB2RSTR" Register*/
#define AFIO_PERIPHERAL     0
#define IOPA_PERIPHERAL     2
#define IOPB_PERIPHERAL     3
#define IOPC_PERIPHERAL     4
#define IOPD_PERIPHERAL     5
#define IOPE_PERIPHERAL     6
#define IOPF_PERIPHERAL     7
#define IOPG_PERIPHERAL     8
#define ADC1_PERIPHERAL     9
#define ADC2_PERIPHERAL     10
#define TIM1_PERIPHERAL     11
#define SPI1_PERIPHERAL     12
#define TIM8_PERIPHERAL     13
#define USART1_PERIPHERAL   14
#define ADC3_PERIPHERAL     15
#define TIM9_PERIPHERAL     19
#define TIM10_PERIPHERAL    20
#define TIM11_PERIPHERAL    21
/*peripheral id bits in  "RCC_APB1RSTR" Register*/
#define TIM2_PERIPHERAL     0
#define TIM3_PERIPHERAL     1
#define TIM4_PERIPHERAL     2
#define TIM5_PERIPHERAL     3
#define TIM6_PERIPHERAL     4
#define TIM7_PERIPHERAL     5
#define TIM12_PERIPHERAL    6
#define TIM13_PERIPHERAL    7
#define TIM14_PERIPHERAL    8
#define WWD_PERIPHERAL      11
#define SPI2_PERIPHERAL     14
#define SPI3_PERIPHERAL     15
#define USART2_PERIPHERAL   17
#define USART3_PERIPHERAL   18
#define USART4_PERIPHERAL   19
#define USART5_PERIPHERAL   20
#define I2C1_PERIPHERAL     21
#define I2C2_PERIPHERAL     22
#define USB_PERIPHERAL      23
#define CAN_PERIPHERAL      25
#define BKP_PERIPHERAL      27
#define PWR_PERIPHERAL      28
#define DAC_PERIPHERAL      29
/*
  * RCC_enuSysClkInit - > Intialize the clock for the system
*/
ES_t		RCC_enuSysClkInit(void);

/*
  * RCC_enuEnablePerClk - > Enable a periheral clock
  * i/p : Bus id (AHB - APB1 - APB2) / Peripheral id 0:31
*/
ES_t		RCC_enuEnablePerClk(u8 BusId , u8 copy_u8PerID);

/*
  * RCC_enuDisablePerClk - > Disable a periheral clock
  * i/p : Bus id (AHB - APB1 - APB2) / Peripheral id 0:31
*/
ES_t		RCC_enuDisablePerClk(u8 BusId , u8 copy_u8PerID);

#endif

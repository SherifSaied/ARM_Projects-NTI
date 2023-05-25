#ifndef		RCC_PRIVATE_H_
#define		RCC_PRIVATE_H_



#define		RCC_BASE_ADD		(0x40021000)
/*from page 121*/
#define		RCC_CR				*((u32 *)(RCC_BASE_ADD+0x00))
#define		RCC_CFGR			*((u32 *)(RCC_BASE_ADD+0x04))
#define		RCC_CIR				*((u32 *)(RCC_BASE_ADD+0x08))
#define		RCC_APB2RSTR		*((u32 *)(RCC_BASE_ADD+0x0C))
#define		RCC_APB1RSTR		*((u32 *)(RCC_BASE_ADD+0x10))
#define		RCC_AHBENR			*((u32 *)(RCC_BASE_ADD+0x14))
#define		RCC_APB2ENR			*((u32 *)(RCC_BASE_ADD+0x18))
#define		RCC_APB1ENR			*((u32 *)(RCC_BASE_ADD+0x1C))
#define		RCC_BDCR			*((u32 *)(RCC_BASE_ADD+0x20))
#define		RCC_CSR				*((u32 *)(RCC_BASE_ADD+0x24))





/* RCC_CFGR register BITS */
#define RCC_SW0          0
#define RCC_SW1          1
#define RCC_SWS_0        2
#define RCC_SWS_1        3
#define RCC_HPRE0        4
#define RCC_HPRE1        5
#define RCC_HPRE2        6
#define RCC_HPRE3        7
#define RCC_PPRE1_0      8
#define RCC_PPRE1_1      9
#define RCC_PPRE1_2      10
#define RCC_PPRE2_0      11
#define RCC_PPRE2_1      12
#define RCC_PPRE2_2      13
#define RCC_ADCPRE0      14
#define RCC_ADCPRE2      15
#define RCC_PLL_SRC      16
#define RCC_PLL_XTPRE    17
#define RCC_PLL_MUL0     18
#define RCC_PLL_MUL_1    19
#define RCC_PLL_MUL_2    20
#define RCC_PLL_MUL_3    21
#define RCC_USB_PRE      22
#define RCC_MCO_0        24
#define RCC_MCO_1        25
#define RCC_MCO_2        26

/* RCC_CR Register BITS  */
#define RCC_HSI_ON            0
#define RCC_HSI_RDY           1
#define RCC_HSI_TRIM0         3
#define RCC_HSI_TRIM_1        4
#define RCC_HSI_TRIM_2        5
#define RCC_HSI_TRIM_3        6
#define RCC_HSI_TRIM_4        7
#define RCC_HSI_CAL_0         8
#define RCC_HSI_CAL_1         9
#define RCC_HSI_CAL_2         10
#define RCC_HSI_CAL_3         11
#define RCC_HSI_CAL_4         12
#define RCC_HSI_CAL_5         13
#define RCC_HSI_CAL_6         14
#define RCC_HSI_CAL_7         15
#define RCC_HSE_ON            16
#define RCC_HSE_RDY           17
#define RCC_HSE_BYP           18
#define RCC_CSS_ON            19
#define RCC_PLL_ON            24
#define RCC_PLL_RDY           25


/* Prescaller options */
#define RCC_PRESCALLER_0 	 0
#define RCC_PRESCALLER_2     2
#define RCC_PRESCALLER_4     3
#define RCC_PRESCALLER_6     4
#define RCC_PRESCALLER_16    5
#define RCC_PRESCALLER_64    6
#define RCC_PRESCALLER_128   7
#define RCC_PRESCALLER_256   8
#define RCC_PRESCALLER_512   9

/*  MCO pin options "RCC_MCO_PIN"   */
#define NO_CLOCK      0
#define HSI_CLOCK     1
#define HSE_CLOCK     2
#define PLL_CLOCK     3
#define SYSTEM_CLOCK  4

/* PLL options */
#define RCC_PLL_HSI_BY2   0
#define RCC_PLL_HSE       1
#define RCC_PLL_HSE_BY2   2

/*            Configuratuin parameters                     */
#define ENABLE   1
#define DISABLE  0


/*  Clock system options  "SYS_CLOCK" */
#define RCC_HSI 		  0
#define RCC_HSE_CRYSTAL   1
#define RCC_HSE_RC        2
#define RCC_PLL           3


/******************itt_1********************/
//#define OFF  0
//#define ON	 1
//
//#define  RCC_AHB         0
//#define  RCC_APB1        1
//#define  RCC_APB2        2
//
//
//
//
//#define NoClk_S        		0b000
//#define SYSCLK_S       		0b100
//#define HSI_Clk_S           0b101
//#define HSE_Clk_S           0b110
//#define PLLdiv2_Clk_S       0b111
//
//
//#define PLL_ClkDiv       0
//#define PLL_ClkNotDiv    1
//
//
//#define         PLL_inputClk2         0b0000
//#define         PLL_inputClk3         0b0001
//#define         PLL_inputClk4         0b0010
//#define         PLL_inputClk5         0b0011
//#define         PLL_inputClk6         0b0100
//#define         PLL_inputClk7         0b0101
//#define         PLL_inputClk8         0b0110
//#define         PLL_inputClk9         0b0111
//#define         PLL_inputClk10        0b1000
//#define         PLL_inputClk11        0b1001
//#define         PLL_inputClk12        0b1010
//#define         PLL_inputClk13        0b1011
//#define         PLL_inputClk14        0b1100
//#define         PLL_inputClk15        0b1101
//#define         PLL_inputClk16        0b1110
//
//
//
//
//
//
//#define HSE_NotDiv       0
//#define HSE_NotDiv2      1
//
//#define RCC_HSI_2        0
//
///*ADC prescaler*/
//
//#define              PCLK2_2             0b00
//#define              PCLK2_4             0b01
//#define              PCLK2_6             0b10
//#define              PCLK2_8             0b11
//
//  /**/
//#define              HCLK_notD           0b000
//#define              HCLK_2              0b100
//#define              HCLK_4              0b101
//#define              HCLK_8              0b110
//#define              HCLK_16             0b111
//
//#define		 		 SYSCLK_notD        0b0000
//#define		 		 SYSCLK_2			0b1000
//#define				 SYSCLK_4			0b1001
//#define				 SYSCLK_8			0b1010
//#define				 SYSCLK_16			0b1011
//#define				 SYSCLK_64 			0b1100
//#define				 SYSCLK_128
//#define				 SYSCLK_256
//#define				 SYSCLK_512
//
//
//#define	  		RCC_HSI       0b00
//#define	  		RCC_HSE       0b01
//#define	  		RCC_PLL       0b10
//
///*for bits of Clock control register RCC_CR register*/
//#define HSION        		0
//#define HSIRDY		  		1
///*#define HSION       0*/
//#define HSITRIM_0         	3
//#define HSITRIM_1         	4
//#define HSITRIM_2         	5
//#define HSITRIM_3         	6
//#define HSITRIM_4         	7
//#define HSICAL_0            8
//#define HSICAL_1            9
//#define HSICAL_2            10
//#define HSICAL_3            11
//#define HSICAL_4            12
//#define HSICAL_5            13
//#define HSICAL_6       		14
//#define HSICAL_7       		15
//#define HSEON         		16
//#define HSERDY				17
//#define HSEBYP         		18
//#define CSSON         		19
//#define PLLON         		24
//#define PLLRDY         		25
//
//
//
///*for bits of RCC_CFGR register*/
//#define SW0           0
//#define SW1           1
//#define SWS0          2
//#define SWS1          3
//#define HPRE0         4
//#define HPRE1         5
//#define HPRE2         6
//#define HPRE3         7
//#define PPRE1_0       8
//#define PPRE1_1       9
//#define PPRE1_2       10
//#define PPRE2_0       11
//#define PPRE2_1       12
//#define PPRE2_2       13
//#define ADCPRE_0      14
//#define ADCPRE_1      15
//#define PLLSRC        16
//#define PLLXTPRE      17
//#define PLLMUL0       18
//#define PLLMUL1       19
//#define PLLMUL2       20
//#define PLLMUL3       21
//#define USBPRE        22
///*  RESERVED bits
// * #define ADCPRE_1   23*/
//#define MCO0          24
//#define MCO1          25
//#define MCO2          26
///*      RESERVED bits
// *	#define ADCPRE_1      27
// *	#define ADCPRE_1      28
// *	#define ADCPRE_1      29
// *	#define ADCPRE_1      30
// *	#define ADCPRE_1      31*/
//
//
//
//#define		RCC_BASE_ADD		(0x40021000)
///*from page 121*/
//#define		RCC_CR				*((u32 *)(RCC_BASE_ADD+0x00))
//#define		RCC_CFGR			*((u32 *)(RCC_BASE_ADD+0x04))
//#define		RCC_CIR				*((u32 *)(RCC_BASE_ADD+0x08))
//#define		RCC_APB2RSTR		*((u32 *)(RCC_BASE_ADD+0x0C))
//#define		RCC_APB1RSTR		*((u32 *)(RCC_BASE_ADD+0x10))
//#define		RCC_AHBENR			*((u32 *)(RCC_BASE_ADD+0x14))
//#define		RCC_APB2ENR			*((u32 *)(RCC_BASE_ADD+0x18))
//#define		RCC_APB1ENR			*((u32 *)(RCC_BASE_ADD+0x1C))
//#define		RCC_BDCR			*((u32 *)(RCC_BASE_ADD+0x20))
//#define		RCC_CSR				*((u32 *)(RCC_BASE_ADD+0x24))
//


#endif

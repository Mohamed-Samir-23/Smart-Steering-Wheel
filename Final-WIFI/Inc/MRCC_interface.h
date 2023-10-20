/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: RCC					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.0					*/
/*  Date		: October 09, 2023		*/
/*  Last Edit	: N/A					*/
/****************************************/


#ifndef _MRCC_INTERFACE_H_
#define _MRCC_INTERFACE_H_

typedef enum
{
	AHB1=0,
	APB1,
	APB2,
	
}RCC_Bus_t;

typedef enum
{
	HSE_Crystal=0,
	HSE_RC,
	HSI,
	PLL_HSE,
	PLL_HSE_DIVIDED_BY_2,
	PLL_HSI_DIVIDED_BY_2,
	
}RCC_ClkSrc_t;

typedef enum
{
	APB_PreScaler1=0,
	APB_PreScaler2=4,
	APB_PreScaler4,
	APB_PreScaler8,
	APB_PreScaler16,

}RCC_APBPreScaler_t;



typedef enum
{
	Wait_States_0=0,/*if  0 < clk < 24 MHZ*/
	Wait_States_1=1,/*if 24 < clk < 48 MHZ*/
	Wait_States_2=2,/*if 48 < clk < 72 MHZ*/


}RCC_FLASH_LATENCY_t;

typedef enum
{
	AHB_PreScaler1=0,
	AHB_PreScaler2=8,
	AHB_PreScaler4,
	AHB_PreScaler8,
	AHB_PreScaler16,
	AHB_PreScaler64,
	AHB_PreScaler128,
	AHB_PreScaler256,
	AHB_PreScaler512
	
}RCC_AHBPreScaler_t;



typedef enum
{
	PLL_PreScaler2=0,
	PLL_PreScaler3,
	PLL_PreScaler4,
	PLL_PreScaler5,
	PLL_PreScaler6,
	PLL_PreScaler7,
	PLL_PreScaler8,
	PLL_PreScaler9,
	PLL_PreScaler10,
	PLL_PreScaler11,
	PLL_PreScaler12,
	PLL_PreScaler13,
	PLL_PreScaler14,
	PLL_PreScaler15,
	PLL_PreScaler16,

}RCC_PLLPreScaler_t;

typedef enum
{
	/*AHB Peripheral*/
	DMA1EN_PER		=	0,
	DMA2EN_PER		=	1,
	SRAMEN_PER		=	2,
	FLITFEN_PER		=	4,
	CRCEN_PER		=	6,
	OTGFSEN_PER		=	12,
	ETHMACEN_PER	=	14,
	ETHMACTXEN_PER	=	15,
	ETHMACRXEN_PER	=	16,
	
	/*APB2 peripheral*/
	AFIOEN_PER		=	0,
	GPIOA_PER		=	2,
	GPIOB_PER		=	3,
	GPIOC_PER		=	4,
	GPIOD_PER		=	5,
	GPIOE_PER		=	6,
	ADC1EN_PER		=	9,
	ADC2EN_PER		=	10,
	TIM1EN_PER		=	11,
	SPI1EN_PER		=	12,
	USART1EN_PER	=	14,
	
	/*APB1 peripheral*/
	TIM2EN_PER		=	0,
	TIM3EN_PER		=	1,
	TIM4EN_PER		=	2,
	TIM5EN_PER		=	3,
	TIM6EN_PER		=	4,
	TIM7EN_PER		=	5,
	WWDGEN_PER		=	11,
	SPI2E_PER		=	14,
	SPI3EN_PER		=	15,
	USART2EN_PER	=	17,
	USART3EN_PER	=	18,
	UART4EN_PER		=	19,
	UART5EN_PER		=	20,
	I2C1EN_PER		=	21,
	I2C2EN_PER		=	22,
	CAN1EN_PER		=	25,
	CAN2EN_PER		=	26,
	BKPEN_PER		=	27,
	PWREN_PER		=	28,
	DACEN_PER		=	29,
	
}RCC_PeripheraName_t;


STD_error_t MRCC_stderrorInit 
(
	RCC_ClkSrc_t 		ARG_udtClkSrc ,
	RCC_AHBPreScaler_t 	ARG_udtAHBPreScaler,
	RCC_APBPreScaler_t 	ARG_udtAPB1PreScaler,
	RCC_APBPreScaler_t 	ARG_udtAPB2PreScaler
);

STD_error_t MRCC_stderrorSetPllClockFreq
(
	RCC_PLLPreScaler_t 	ARG_udtPLLPreScaler,
	RCC_FLASH_LATENCY_t ARG_udtLatency
);

STD_error_t RCC_EnablePeripheralClk
(
	RCC_Bus_t 			ARG_udtBus,
	RCC_PeripheraName_t ARG_udtPeripheraName
);

STD_error_t RCC_DisablePeripheralClk
(
	RCC_Bus_t 			ARG_udtBus,
	RCC_PeripheraName_t ARG_udtPeripheraName
);

#endif

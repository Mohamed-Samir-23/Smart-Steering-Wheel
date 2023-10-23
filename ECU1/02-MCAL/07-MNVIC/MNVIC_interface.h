/*****************************************/
/*   Author      : Mohamed Samir         */
/*   SWC         : NVIC                  */
/*   Layer       : MCAL                  */
/*   Version     : 1.1                   */
/*   Date        : October 2 , 2023	     */
/*   Last Edit   : October 23, 2023      */
/*****************************************/


#ifndef _MNVIC_INTERFACE_H_
#define _MNVIC_INTERFACE_H_

typedef enum 
{
	WWDG=0,
	PVD,
	TAMPER,
	RTC,
	FLASH,
	RCC,
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	DMA1_Channel1,
	DMA1_Channel2,
	DMA1_Channel3,
	DMA1_Channel4,
	DMA1_Channel5,
	DMA1_Channel6,
	DMA1_Channel7,
	ADC1_2,
	USB_HP_CAN_TX,
	USB_HP_CAN_RX0,
	CAN_RX1,
	CAN_SCE,
	EXTI9_5,
	TIM1_BRK,
	TIM1_UP,
	TIM1_TRG_COM,
	TIM1_CC,
	TIM2,
	TIM3,
	TIM4,
	I2C1_EV,
	I2C1_ER,
	I2C2_EV,
	I2C2_ER,
	SPI1,
	SPI2,
	USART1,
	USART2,
	USART3,
	EXTI15_10,
	RTCAlarm,
	USBWakeup,
	TIM8_BRK,
	TIM8_UP,
	TIM8_TRG_COM,
	TIM8_CC,
	ADC3,
	FSMC,
	SDIO,
	TIM5,
	SPI3,
	UART4,
	UART5,
	TIM6,
	TIM7,
	DMA2_Channel1,
	DMA2_Channel2,
	DMA2_Channel3,
	DMA2_Channel4_5,
	
}IRQ_t;

typedef enum 
{
	PRIGROUP_16GRU_0SUB=3,
	PRIGROUP_8GRU_2SUB,
	PRIGROUP_4GRU_4SUB,
	PRIGROUP_2GRU_8SUB,
	PRIGROUP_0GRU_16SUB,
	
} SCB_PriorityGroup_t;


#define MNVIC_VECTKEY							0x5FA

#define MNVIC_GIE(void) __ASM volatile ("cpsie i");
#define MNVIC_GID(void) __ASM volatile ("cpsid i");


STD_error_t MNVIC_stderrorEnableIRQ
(
	IRQ_t ARG_udtIRQn
);

STD_error_t MNVIC_stderrorDisableIRQ
(
	IRQ_t ARG_udtIRQn
);

STD_error_t MNVIC_stderrorSetPendingIRQ
(
	IRQ_t ARG_udtIRQn
);

STD_error_t MNVIC_stderrorClearPendingIRQ
(
	IRQ_t ARG_udtIRQn
);

STD_error_t MNVIC_stderrorGetPendingIRQ
(
	IRQ_t ARG_udtIRQn,
	u8* ARG_u8PendingState
);

STD_error_t MNVIC_stderrorSetPriorityConfig 
(
	SCB_PriorityGroup_t ARG_udtPrioriyConfig
);

STD_error_t MNVIC_stderrorSetPriorityIRQ
(
	IRQ_t ARG_udtIRQn,
	u8 ARG_u8GroupId,
	u8 ARG_u8SubGroupId
);



#endif

/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : ESP_Wifi_module       */
/*   Layer       : HAL                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef _HESP_CONFIG_H_
#define _HESP_CONFIG_H_

#define TICK_FOR_MSEC 				72000
#define ESP_BAUDRATE					115200
#define ESP_UART_NUMBER				MUART1
#define ESP_UART_PARITY				MUART_PARITY_OFF
#define	ESP_UART_STOPBIT			MUART_STOP_1
#define ESP_UART_WORDSIZE			MUART_WORD8

#define ESP_UART_EN_PER				USART1EN_PER
#define	ESP_UART_BUS					APB2

#define ESP_PORT							GPIOA
#define ESP_TX_PIN						PIN9
#define ESP_RX_PIN						PIN10
#define ESP_GPIO_BUS_PER			APB2,GPIOA_PER
#define USE_OF_RESET_PIN 1


#if USE_OF_RESET_PIN == 1

	#define ESP_RESET_PIN			PIN1
	
#endif


#endif

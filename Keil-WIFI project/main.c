
/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : Wifi_module       		 */
/*   Layer       : -	                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#define F_CPU 8000000

/*********inclusion section********/
/*****LIB*****/
#include "LBIT_math.h"
#include "LSTD_types.h"

/****RCC******/
#include "MRCC_interface.h"

/****GPIO*****/
#include "MGPIO_config.h"
#include "MGPIO_interface.h"

/****STK******/
#include "MSYSTICK_interface.h"

/***UART*****/
#include "MUART_interface.h"

/*********API********/
void app_init(void);
void UART_INIT(void);

int main()
{
	u8 DATA = 0 ;
	app_init();
	while(1)
	{
		MGPIO_stderrorSetPinValue(GPIOA,PIN0,HIGH);
		MSYSTICK_stderrorSetBusyWait(8000000);
		MGPIO_stderrorSetPinValue(GPIOA,PIN0,LOW);
		MSYSTICK_stderrorSetBusyWait(8000000);
		DATA = MUART_u8ReceivePolling(MUART1);
		MUART_voidTransimit(MUART1,++DATA);
		
	}
	

}


void app_init(void)
{
	MRCC_stderrorInit(HSI,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
	
	RCC_EnablePeripheralClk(APB2,GPIOA_PER);
	MGPIO_stderrorPinModeSelect(GPIOA,PIN0,OUTPUT_PUSH_PULL_SPEED_50MHZ);
	 UART_INIT();

	
	MSYSTICK_stderrorInit(AHB);
	MSYSTICK_stderrorSetBusyWait(8000000);

}
void UART_INIT(void)
{
	RCC_EnablePeripheralClk(APB2,GPIOA_PER);
	MGPIO_stderrorPinModeSelect(GPIOA,PIN9,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	MGPIO_stderrorPinModeSelect(GPIOA,PIN10,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	
	RCC_EnablePeripheralClk(APB2,USART1EN_PER);
	MUART_voidInit(MUART1,9600,MUART_PARITY_OFF,MUART_STOP_1,MUART_WORD8);
	
	
}	

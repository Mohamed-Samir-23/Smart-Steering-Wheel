
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

/*****ESP****/
#include "HESP_config.h"
#include "HESP_interface.h"

#include "SWIFI_interface.h"

u8 Response_Buffer[50] = {0};

/*********API********/
void app_init(void);

WIFI_ERROR_T DATA = WIFI_OK ;

int main()
{
	app_init();
	MRCC_stderrorInit(HSI,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
	
	DATA	=	SWIFI_errTurnOn(SWIFI_MODE_STATION_AND_SOFTAP);
	DATA	= SWIFI_errConfigSoftAP("MyESP","12345678",SWIFI_CNANNEL_10,SWIFI_ENCRYPTION_WPA_WPA2_PSK);
	DATA 	=	SWIFI_errConnectSSID("N9","m123m456");
	
	MSYSTICK_stderrorSetBusyWait(8000000*10);
	DATA 	=	SWIFI_errDisconnectSSID();
	
	while(1)
	{
		/*MGPIO_stderrorSetPinValue(GPIOA,PIN0,HIGH);
		MSYSTICK_stderrorSetBusyWait(8000000);
		MGPIO_stderrorSetPinValue(GPIOA,PIN0,LOW);
		
		*/
		/*DATA = HESP_SEND_COMMAND((const u8 *)"AT\r\n",Response_Buffer,10);
		ESP_errEchoEnable();
		if ( ESP_OK ==   DATA)
		{
				MSYSTICK_stderrorSetBusyWait(8000000*10);
		}
		else
		{
				MSYSTICK_stderrorSetBusyWait(8000000*15);
				ESP_errEchoEnable();
		}
	}
	*/
	//SWIFI_
	}

}
void app_init(void)
{
	MRCC_stderrorInit(HSI,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
	
	RCC_EnablePeripheralClk(APB2,GPIOA_PER);
	MGPIO_stderrorPinModeSelect(GPIOA,PIN0,OUTPUT_PUSH_PULL_SPEED_50MHZ);
	
	/*****ESP initialization********/
	HESP_INIT();

	//MSYSTICK_stderrorInit(AHB_);

}
/*void UART_INIT(void)
{
	RCC_EnablePeripheralClk(APB2,GPIOA_PER);
	MGPIO_stderrorPinModeSelect(GPIOA,PIN9,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	MGPIO_stderrorPinModeSelect(GPIOA,PIN10,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	
	RCC_EnablePeripheralClk(APB2,USART1EN_PER);
	MUART_voidInit(MUART1,9600,MUART_PARITY_OFF,MUART_STOP_1,MUART_WORD8);
	
	
}	*/

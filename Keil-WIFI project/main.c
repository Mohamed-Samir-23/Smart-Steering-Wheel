
/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : Wifi_module       		 */
/*   Layer       : -	                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/



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
#include <stdlib.h>

#define F_CPU 72000000
u8 Response_Buffer[50] = {0};

/*********API********/
void app_init(void);

WIFI_ERROR_T DATA = WIFI_OK ;
void test(SWIFI_MSG_T *MSG );


//CAN
//Jetson
//ARM
//Encoder

/*

	void 				(*pDest_Function)(SWIFI_MSG_T *);
	const u8* 	Dest_Name;
	const u8		Dest_Name_size;			

*/

void CAN(SWIFI_MSG_T *msg)
{
	//SWIFI_errSendDataTCP(0,"OK","2");
	DeleteMsg(msg);
}
void Jetson(SWIFI_MSG_T *msg)
{
	//SWIFI_errSendDataTCP(0,"OK","2");
	DeleteMsg(msg);
}
SWIFI_COMM_Handler_T Mykeys[2] = 
{
	{
	CAN,
	"CAN",
	3
	},
	{
	Jetson,
	"JETSON",
	6
	}
	
};



int main()
{

	app_init();
	SWIFI_errSetCaptureKeys(Mykeys,2);
	SWIFI_errTurnOn(SWIFI_MODE_STATION_AND_SOFTAP);
	SWIFI_errConnectSSID("Hello World2","H*#*#10#*#*");
	SWIFI_errCreateTCPServer("8080");
	SWIFI_errStartCommunicationHandler();

	
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
	//MRCC_stderrorSetPllClockFreq(7);
//	MRCC_stderrorInit(PLL_HSE,AHB_PreScaler1,APB_PreScaler1,APB_PreScaler1);
	
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

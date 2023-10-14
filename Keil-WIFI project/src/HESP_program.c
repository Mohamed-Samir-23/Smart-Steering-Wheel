/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : ESP_Wifi_module       */
/*   Layer       : HAL                   */
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

/****ESP***/
#include "HESP_config.h"
#include "HESP_private.h"
#include "HESP_interface.h"


/****String*****/
#include <string.h>

ESP_ERR_T ISTimeOut = ESP_OK;
u32 L_u32TimeOutCounter =0;



void HESP_INIT(void)
{
	MSYSTICK_stderrorInit(AHB_DIV_8);
	RCC_EnablePeripheralClk(ESP_GPIO_BUS_PER);
	MGPIO_stderrorPinModeSelect(ESP_PORT,ESP_TX_PIN,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	MGPIO_stderrorPinModeSelect(ESP_PORT,ESP_RX_PIN,ALTFUN_PUSH_PULL_SPEED_50MHZ);
	
	#if USE_OF_RESET_PIN == 1
			MGPIO_stderrorPinModeSelect(ESP_PORT,ESP_RESET_PIN,OUTPUT_PUSH_PULL_SPEED_50MHZ);
	#endif
	
	RCC_EnablePeripheralClk(ESP_UART_BUS,ESP_UART_EN_PER);
	HESP_voidInterruptDisable();
	HESP_RESET();
	MUART_voidInit(ESP_UART_NUMBER,ESP_BAUDRATE,ESP_UART_PARITY,ESP_UART_STOPBIT,ESP_UART_WORDSIZE);
	
}

void HESP_RESET(void)
{
	#if USE_OF_RESET_PIN == 1
	/******Hardware Reset*******/
	
	MGPIO_stderrorSetPinValue(ESP_PORT,ESP_RESET_PIN,LOW);
	ESP_Delay_ms(100);
	MGPIO_stderrorSetPinValue(ESP_PORT,ESP_RESET_PIN,HIGH);
	ESP_Delay_ms(1200);
	#else
	/******Software Reset*******/
	HESP_SEND_COMMAND("AT+RST",NULL_POINTER,20000);
	
	#endif

}

ESP_ERR_T HESP_SEND_COMMAND(const u8 * Copy_pu8Command, u8 * Copy_pu8Response, u32 timeout )
{
	u32 L_u32Count = 0;
	ESP_ERR_T L_errStatus = ESP_OK; 
	ISTimeOut = ESP_OK;
	L_u32TimeOutCounter = timeout;
	MUART_u16GetData(ESP_UART_NUMBER);
	/*******Sending Command********/
	while('\0' != Copy_pu8Command[L_u32Count] )
	{
		MUART_voidTransimit(ESP_UART_NUMBER,Copy_pu8Command[L_u32Count++]);
	}
	
	L_u32Count = 0;
	MSYSTICK_stderrorSetPeriodiceInterval(TICK_FOR_MSEC,ESP_TimeOutAlarm);
	if(NULL_POINTER != Copy_pu8Response)
	{
		/******Recieving Response*******/
	
		while(1)
		{
			if(ISTimeOut== ESP_TIMEOUT)
			{
				Copy_pu8Response[L_u32Count]	='\0';	
				L_errStatus =  ESP_TIMEOUT;
				
				break;
			}
			else if( 1 == MUART_u8RXNEFlag(ESP_UART_NUMBER) )
			{
				Copy_pu8Response[L_u32Count] = (u8) MUART_u16GetData(ESP_UART_NUMBER);
				if(  Copy_pu8Response[L_u32Count] == '\n' && (0 != ISEndStream ) )
				{
					L_errStatus = ISEndStream;
					break;
				}
				L_u32Count++;
			}
		}
	}
	
	return L_errStatus;
}



ESP_ERR_T ESP_errEchoEnable(void)
{
	
	return HESP_SEND_COMMAND((const u8 *)"ATE1\r\n",NULL_POINTER,10);
}	

ESP_ERR_T ESP_errEchoDisable(void)
{
	
	return HESP_SEND_COMMAND((const u8 *)"ATE0\r\n",NULL_POINTER,10);
}	

void HESP_CALLBACK_INIT(FUNC_T FUNC)
{
	if(NULL_POINTER != FUNC)
	{
		MUART_voidSetCallBack(ESP_UART_NUMBER,FUNC);
	}
}
void HESP_voidInterruptEnable(void)
{
	MUART_voidInterruptEnable(ESP_UART_NUMBER,MUART_INTERRUPT_RXNE);
}

void HESP_voidInterruptDisable(void)
{
	MUART_voidInterruptDisable(ESP_UART_NUMBER,MUART_INTERRUPT_DS);
}

ESP_ERR_T HESP_errCheckESP(void)
{
	u8 temp[20];
	return HESP_SEND_COMMAND((const u8 *)"AT\r\n",temp,10);
}

static void ESP_TimeOutAlarm(void)
{
	while( 0 !=  L_u32TimeOutCounter  )
	{
		L_u32TimeOutCounter--;
		return;
	}
		MSYSTICK_voidStopTICK();
	ISTimeOut = ESP_TIMEOUT;
}

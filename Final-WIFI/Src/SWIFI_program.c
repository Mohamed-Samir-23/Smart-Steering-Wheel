/*   Author      : Mahmoud Ahmed         */
/*   SWC         : Wifi_module       		 */
/*   Layer       : Service               */
/*   Version     : 1.0                   */
/*   Date        : October 14, 2023      */
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
#include "HESP_interface.h"

/*****SWIFI*****/
#include "SWIFI_interface.h"
#include "SWIFI_private.h"
#include "SWIFI_config.h"

#include <string.h>
#include <stdlib.h>

char WIFI_Buffer[WIFI_Buffer_Size] = {0};
Buffer_Count_UT L_Buffer_Count = 0;

static void Systemhandel_voidConnectedNotify(void);
static void Systemhandel_voidClosedNotify(void);
static void Systemhandel_voidConnectionFail(void);
static void Systemhandel_voidBusyNotify(void);
static void SWIFI_voidKeysCapture(void);
static void SWIFI_voidMessageCapture(void);
static void SWIFI_voidCommunicationHandler(SWIFI_MSG_T* Copy_pMSG);
static void SWIFI_voidIPDHandler(void);

/*	FUNC_T 			pDest_Function;
		const u8* 	Dest_Name;
		const u8		Dest_Name_size;		*/
#define SYSCALL_SIZE 6
SWIFI_COMM_SYS_T SystemCalls[SYSCALL_SIZE] = 
{
		{
				NULL_POINTER,
				"ready\r\n",
				7
		},

		{
				Systemhandel_voidConnectedNotify,
				",CONNECT\r",
				9
		},
		{
				Systemhandel_voidClosedNotify,
				",CLOSED",
				7
		},
		{
				SWIFI_voidIPDHandler,
				"IPD,",
				4
		},
		{
				Systemhandel_voidConnectionFail,
				"CONNECT FAIL",
				12
		},
		{
				Systemhandel_voidBusyNotify,
				"Systemhandel_voidBusyNotify s",
				6
		}

};
u8 						 UserDefinedKeysNumber = 0;
SWIFI_COMM_Handler_T *  UserDefinedKeys = NULL_POINTER;
FUNC_T   ConnectFailHandler = NULL_POINTER;
Connection_Status SWIFI_Connections_status[5] = {Connection_Closed,Connection_Closed,Connection_Closed,Connection_Closed,Connection_Closed};
/*	u8									 ID;
	u16									 Connection_Number;
	Connection_Status*	 Status	;					*/
SWIFI_Connection_T Connections_Info[5] = 
{
		{
				SWIFI_TCP_ID_0,
				0,
				&SWIFI_Connections_status[0]
		},
		{
				SWIFI_TCP_ID_1,
				0,
				&SWIFI_Connections_status[1]
		},
		{
				SWIFI_TCP_ID_2,
				0,
				&SWIFI_Connections_status[2]
		},
		{
				SWIFI_TCP_ID_3,
				0,
				&SWIFI_Connections_status[3]
		},
		{
				SWIFI_TCP_ID_4,
				0,
				&SWIFI_Connections_status[4]
		},
};

WIFI_ERROR_T	SWIFI_errTurnOn(u8 Copy_u8WIFIMode)
{

	ESP_ERR_T L_errESP_Status = HESP_errCheckESP();
	if( ESP_OK == L_errESP_Status )
	{
		if( SWIFI_MODE_STATION == Copy_u8WIFIMode)
		{
			L_errESP_Status = HESP_SEND_COMMAND("AT+CWMODE=1\r\n",WIFI_Buffer,100);
		}
		else if( SWIFI_MODE_SOFTAP== Copy_u8WIFIMode)
		{
			L_errESP_Status = HESP_SEND_COMMAND("AT+CWMODE=2\r\n",WIFI_Buffer,100);
		}
		else if( SWIFI_MODE_STATION_AND_SOFTAP == Copy_u8WIFIMode)
		{
			L_errESP_Status = HESP_SEND_COMMAND("AT+CWMODE=3\r\n",WIFI_Buffer,100);
		}
		else
		{
			L_errESP_Status = ESP_ERROR;
		}
	}

	return (WIFI_ERROR_T) L_errESP_Status;
}


WIFI_ERROR_T	SWIFI_errConnectSSID(const char * Copy_pu8SSID ,const char * Copy_puPassword)
{
	ESP_ERR_T L_errESP_Status = HESP_errCheckESP();

	if( ESP_OK == L_errESP_Status )
	{
		HESP_SEND_COMMAND("AT+CWJAP=",NULL_POINTER,0);
		HESP_SEND_COMMAND("\"",NULL_POINTER,0);
		HESP_SEND_COMMAND(Copy_pu8SSID,NULL_POINTER,0);
		HESP_SEND_COMMAND("\",",NULL_POINTER,0);
		HESP_SEND_COMMAND("\"",NULL_POINTER,0);
		HESP_SEND_COMMAND(Copy_puPassword,NULL_POINTER,0);
		L_errESP_Status =  HESP_SEND_COMMAND("\"\r\n",WIFI_Buffer,30000);
	}

	return (WIFI_ERROR_T)L_errESP_Status;
}

WIFI_ERROR_T	SWIFI_errGetConnectedSSID(char * Copy_pu8SSID)
{
	ESP_ERR_T L_errESP_Status = HESP_errCheckESP();
	if( ESP_OK == L_errESP_Status )
	{
		L_errESP_Status = HESP_SEND_COMMAND("AT+CWJAP?\r\n",Copy_pu8SSID,100);
	}

	return (WIFI_ERROR_T)L_errESP_Status;
}

WIFI_ERROR_T	SWIFI_errDisconnectSSID(void)
{
	ESP_ERR_T L_errWIFI_Status = HESP_errCheckESP();

	if( ESP_OK == L_errWIFI_Status )
	{
		L_errWIFI_Status = HESP_SEND_COMMAND("AT+CWQAP\r\n",WIFI_Buffer,100);
	}
	return (WIFI_ERROR_T)L_errWIFI_Status;
}

WIFI_ERROR_T	SWIFI_errConfigSoftAP(const char * Copy_pu8SSID, const char * Copy_puPassword , const char * Copy_u8Channel, const char * Copy_u8Encryption)
{
	ESP_ERR_T L_errWIFI_Status = HESP_errCheckESP();

	if( ESP_OK == L_errWIFI_Status )
	{
		HESP_SEND_COMMAND("AT+CWSAP=",NULL_POINTER,0);
		HESP_SEND_COMMAND("\"",NULL_POINTER,0);
		HESP_SEND_COMMAND(Copy_pu8SSID,NULL_POINTER,0);
		HESP_SEND_COMMAND("\",",NULL_POINTER,0);
		HESP_SEND_COMMAND("\"",NULL_POINTER,0);
		HESP_SEND_COMMAND(Copy_puPassword,NULL_POINTER,0);
		HESP_SEND_COMMAND("\",",NULL_POINTER,0);
		HESP_SEND_COMMAND(Copy_u8Channel,NULL_POINTER,0);
		HESP_SEND_COMMAND(",",NULL_POINTER,0);
		HESP_SEND_COMMAND(Copy_u8Encryption,NULL_POINTER,0);
		L_errWIFI_Status = HESP_SEND_COMMAND("\r\n",WIFI_Buffer,3000);
	}

	return (WIFI_ERROR_T)L_errWIFI_Status;
}

WIFI_ERROR_T	SWIFI_errCreateTCPServer(const char * Copy_u16PortNumber)
{
	ESP_ERR_T L_errWIFI_Status = HESP_errCheckESP();

	if( ESP_OK == L_errWIFI_Status )
	{
		HESP_SEND_COMMAND("AT+CIPMUX=1\r\n",WIFI_Buffer,100);
		HESP_SEND_COMMAND("AT+CIPSERVER=1,",NULL_POINTER,100);
		HESP_SEND_COMMAND(Copy_u16PortNumber,NULL_POINTER,100);
		L_errWIFI_Status = HESP_SEND_COMMAND("\r\n",WIFI_Buffer,3000);
	}

	return (WIFI_ERROR_T)L_errWIFI_Status;
}
WIFI_ERROR_T	SWIFI_errConnectTCP(const char *Copy_u16ID, const char * Copy_pu8ServerIP, const char * Copy_pu8ServerPort)
{
	ESP_ERR_T L_errWIFI_Status = HESP_errCheckESP();

	if( ESP_OK == L_errWIFI_Status )
	{
		HESP_SEND_COMMAND("AT+CIPSTART=",NULL_POINTER,100);
		HESP_SEND_COMMAND(Copy_u16ID,NULL_POINTER,100);
		HESP_SEND_COMMAND(",\"TCP\",\"",NULL_POINTER,100);
		HESP_SEND_COMMAND(Copy_pu8ServerIP,NULL_POINTER,100);
		HESP_SEND_COMMAND("\",",NULL_POINTER,100);
		HESP_SEND_COMMAND(Copy_pu8ServerPort,NULL_POINTER,100);
		L_errWIFI_Status = HESP_SEND_COMMAND("\r\n",WIFI_Buffer,300);
		if(L_errWIFI_Status == ESP_OK)
		{
			SWIFI_Connections_status[Copy_u16ID[0] - '0'] = Connection_Open;
		}
	}

	return (WIFI_ERROR_T)L_errWIFI_Status;
}
WIFI_ERROR_T	SWIFI_errDisconnectTCP(const char * Copy_u16ID)
{
	ESP_ERR_T L_errWIFI_Status = HESP_errCheckESP();
	if( ESP_OK == L_errWIFI_Status )
	{
		HESP_SEND_COMMAND("AT+CIPCLOSE=",NULL_POINTER,100);
		HESP_SEND_COMMAND(Copy_u16ID,NULL_POINTER,100);
		L_errWIFI_Status = HESP_SEND_COMMAND("\r\n",WIFI_Buffer,1);
		if(L_errWIFI_Status == ESP_OK)
		{
			SWIFI_Connections_status[Copy_u16ID[0] - '0'] = Connection_Closed;
		}
	}

	return (WIFI_ERROR_T)L_errWIFI_Status;
}

WIFI_ERROR_T	SWIFI_errSendDataTCP(const char * Copy_u16ID, const char * Data)
{
	static char Temp[5];
	ESP_ERR_T L_errWIFI_Status = HESP_errCheckESP();

	itoa(strlen(Data),Temp,10);
	if(Temp[0] == '0' &&  Temp[1] == '\0')
	{
		L_errWIFI_Status = HESP_errCheckESP();
	}
	if( ESP_OK == L_errWIFI_Status )
	{
		HESP_SEND_COMMAND("AT+CIPSEND=",NULL_POINTER,100);
		HESP_SEND_COMMAND(Copy_u16ID,NULL_POINTER,100);
		HESP_SEND_COMMAND(",",NULL_POINTER,100);
		HESP_SEND_COMMAND(Temp,NULL_POINTER,30);
		L_errWIFI_Status = HESP_SEND_COMMAND("\r\n",WIFI_Buffer,300);
		if(ESP_OK ==  L_errWIFI_Status)
		{
			L_errWIFI_Status = HESP_SEND_COMMAND(Data,WIFI_Buffer,3000);
		}
	}

	return (WIFI_ERROR_T)L_errWIFI_Status;
}


void	SWIFI_errStartCommunicationHandler(void)
{
	HESP_CALLBACK_INIT(SWIFI_voidKeysCapture);
	HESP_voidInterruptEnable();
}
WIFI_ERROR_T	SWIFI_errSetCaptureKeys(SWIFI_COMM_Handler_T * Copy_pUserKeys , u8 Copy_u8KeysNumbers)
{
	ESP_ERR_T L_errWIFIStatus =WIFI_ERROR;
	if(NULL_POINTER != Copy_pUserKeys)
	{
		UserDefinedKeys = Copy_pUserKeys;
		UserDefinedKeysNumber =Copy_u8KeysNumbers;
		L_errWIFIStatus =  WIFI_OK;
	}
	return L_errWIFIStatus;
}
void SWIFI_voidSetConnectionFailHandler(FUNC_T UserFunc)
{
	if(NULL_POINTER != UserFunc)
	{
		ConnectFailHandler = UserFunc;
	}
}

static void SWIFI_voidKeysCapture(void)
{
	u32 L_intCounter = 0;
	WIFI_Buffer[L_Buffer_Count] = MUART_u16GetData(ESP_UART_NUMBER);

	//Capturing the systems keywords
	for(L_intCounter = 0 ; L_intCounter < SYSCALL_SIZE ; L_intCounter++ )
	{
		if ( 1 == SysCaptureKey )
		{
			if(NULL_POINTER != SystemCalls[L_intCounter].pDest_Function)
			{
				SystemCalls[L_intCounter].pDest_Function();
				L_Buffer_Count=0;
				break;
			}
		}
	}

	L_Buffer_Count++;
	//Buffer Overflow
	if(L_Buffer_Count == WIFI_Buffer_Size )
	{
		L_Buffer_Count=0;
		//Handle by func if it needed
	}
	return;

}

static void SWIFI_voidIPDHandler(void)
{
	HESP_CALLBACK_INIT(SWIFI_voidMessageCapture);
}

/*IPD,ID,length:Data*/
static void SWIFI_voidMessageCapture(void)
{
	static u8 	L_u8Entry_Counter 					= 0;
	static u16 	L_u8IsRecLength_And_Counter 	= 0;
	static u8 	L_u8IsRecData 					= 0;
	static u16 	L_16Data_size 					= 0;
	static SWIFI_MSG_T * MSG;
	static u8 L_u8ID;

	u8 Temp = MUART_u16GetData(ESP_UART_NUMBER);


	//Capturing the user keywords
	if(L_u8IsRecData == 1 )
	{
		MSG->Data[L_u8IsRecLength_And_Counter] = Temp ;
		L_u8IsRecLength_And_Counter++;
		if(L_u8IsRecLength_And_Counter == L_16Data_size )
		{
			HESP_CALLBACK_INIT(SWIFI_voidKeysCapture);
			MSG->Data[L_u8IsRecLength_And_Counter] = '\0';
			//Reset everything
			L_u8Entry_Counter = 0;
			L_u8IsRecLength_And_Counter = 0;
			L_u8IsRecData = 0;
			L_16Data_size = 0;
			SWIFI_voidCommunicationHandler(MSG);
			return;
		}
	}
	else
	{

		if(L_u8Entry_Counter == 0)
		{
			L_u8ID = Temp - '0';
			L_u8IsRecLength_And_Counter = 1;
		}
		else if(L_u8Entry_Counter >= 2 && L_u8IsRecLength_And_Counter == 1)
		{
			if(Temp  != ':')
			{
				L_16Data_size = L_16Data_size * 10 + (Temp - '0');

			}
			else
			{
				MSG = CreateMsg(L_16Data_size);
				if(NULL_POINTER == MSG )
				{
					L_u8Entry_Counter = 0;
					L_u8IsRecLength_And_Counter = 0;
					L_u8IsRecData = 0;
					L_16Data_size = 0;
					HESP_CALLBACK_INIT(SWIFI_voidKeysCapture);
					return;
				}
				MSG->Connection_info = Connections_Info[L_u8ID];
				L_u8IsRecData = 1;
				L_u8IsRecLength_And_Counter=0;
			}	
		}

	}
	L_u8Entry_Counter++;
}

static void SWIFI_voidCommunicationHandler(SWIFI_MSG_T* Copy_pMSG)
{
	u32 L_intCounter = 0;
	for(L_intCounter = 0 ; L_intCounter < UserDefinedKeysNumber ; L_intCounter++ )
	{
		if( 1 == UserCaptureKey)
		{
			if(NULL_POINTER != UserDefinedKeys[L_intCounter].pDest_Function)
			{
				UserDefinedKeys[L_intCounter].pDest_Function(Copy_pMSG);
			}
			break;
		}
	}

}

SWIFI_MSG_T * CreateMsg(u16 Copy_u8MSG_Size)
{
	SWIFI_MSG_T * L_pMSG = malloc(sizeof(SWIFI_MSG_T));
	if(L_pMSG != NULL_POINTER)
	{
		L_pMSG->Data = malloc(Copy_u8MSG_Size+1);
		if(NULL_POINTER !=  L_pMSG->Data)
		{
			L_pMSG->Data_size = Copy_u8MSG_Size;

		}
	}
	return L_pMSG;

}

void DeleteMsg(SWIFI_MSG_T * Copy_pMSG)
{
	if(Copy_pMSG != NULL_POINTER)
	{
		free(Copy_pMSG->Data);
		free(Copy_pMSG);
	}
}
static void Systemhandel_voidConnectedNotify(void)
{
	Buffer_Count_ST L_Start = L_Buffer_Count - 8 ;
	u8 ID = 0;
	if(L_Start < 0)
	{
		ID = WIFI_Buffer[(WIFI_Buffer_Size - L_Start)] - '0';
		SWIFI_Connections_status[ID] = Connection_Open;
		Connections_Info[ID].Connection_Number ++;
	}
	else
	{
		ID = WIFI_Buffer[L_Start] - '0';
		SWIFI_Connections_status[ID] = Connection_Open;
		Connections_Info[ID].Connection_Number ++;
	}

}
static void Systemhandel_voidClosedNotify(void)
{
	Buffer_Count_ST L_Start = L_Buffer_Count - 8 ;
	u8 ID = 0;
	if(L_Start < 0)
	{
		ID = WIFI_Buffer[(WIFI_Buffer_Size - L_Start)] - '0';
		SWIFI_Connections_status[ID] = Connection_Closed;
	}
	else
	{
		ID = WIFI_Buffer[L_Start] - '0';
		SWIFI_Connections_status[ID] = Connection_Closed;
	}
}
static void Systemhandel_voidConnectionFail(void)
{

	//Must reinit everything ->to be in APP layer
	if(NULL_POINTER != ConnectFailHandler)
	{
		ConnectFailHandler();
	}
}
void Systemhandel_voidBusyNotify(void)
{
	u32 L_u32counter = 0;
	for(L_u32counter = 0; L_u32counter <3000; L_u32counter++)
		MSYSTICK_stderrorSetBusyWait(TICK_FOR_MSEC);
}

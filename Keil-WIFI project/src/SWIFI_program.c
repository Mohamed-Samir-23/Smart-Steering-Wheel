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

u8 WIFI_Buffer[WIFI_Buffer_Size] = {0};


/*	FUNC_T 			pDest_Function;
		const u8* 	Dest_Name;
		const u8		Dest_Name_size;		*/
#define SYSCALL_SIZE 5
SWIFI_COMM_SYS_T SystemCalls[SYSCALL_SIZE] = 
{
	{	
		NULL_POINTER,
		"ready\r\n",
		7
	},
	
	{	
		Connected,
		",CONNECT",
		8
	},
	{	
		Connected,
		",CLOSED",
		7
	},
	{	
		SWIFI_voidIPDHandler,
		"IPD,",
		4
	},
	{	
		NULL_POINTER,
		"CONNECT FAIL",
		12
	}
	
};
SWIFI_COMM_Handler_T * UserDefinedKeys = NULL_POINTER;
u8 						 UserDefinedKeysNumber = 0;

WIFI_ERROR_T	SWIFI_errTurnOn(u8 Copy_u8WIFIMode)
{
		
		ESP_ERR_T L_errESP_Status = HESP_errCheckESP();
		WIFI_ERROR_T L_errWIFI_Status = WIFI_OK;
	 if( ESP_OK == L_errESP_Status )
	 {
		 if( SWIFI_MODE_STATION == Copy_u8WIFIMode)
		 {
				L_errESP_Status = HESP_SEND_COMMAND((const u8 *)"AT+CWMODE=1\r\n",WIFI_Buffer,100);
		 }
		 else if( SWIFI_MODE_SOFTAP== Copy_u8WIFIMode)
		 {
				L_errESP_Status = HESP_SEND_COMMAND((const u8 *)"AT+CWMODE=2\r\n",WIFI_Buffer,100);
		 }
		 else if( SWIFI_MODE_STATION_AND_SOFTAP == Copy_u8WIFIMode)
		 {
				L_errESP_Status = HESP_SEND_COMMAND((const u8 *)"AT+CWMODE=3\r\n",WIFI_Buffer,100);
		 }
		 else
		 {
			 L_errWIFI_Status = WIFI_ERROR;
		 }
	 }
	 else if( ESP_BUSY == L_errESP_Status )
	 {
			L_errWIFI_Status = WIFI_BUSY;
	 }
	return L_errWIFI_Status;
}


WIFI_ERROR_T	SWIFI_errConnectSSID(u8 * Copy_pu8SSID , u8 * Copy_puPassword)
{
	 ESP_ERR_T L_errESP_Status = HESP_errCheckESP();
	 WIFI_ERROR_T L_errWIFI_Status = WIFI_OK; 
	
	 if( ESP_OK == L_errESP_Status )
	 {
			HESP_SEND_COMMAND((const u8 *)"AT+CWJAP=",NULL_POINTER,0);
			HESP_SEND_COMMAND((const u8 *)"\"",NULL_POINTER,0);
			HESP_SEND_COMMAND(Copy_pu8SSID,NULL_POINTER,0);
		  HESP_SEND_COMMAND((const u8 *)"\",",NULL_POINTER,0);
		  HESP_SEND_COMMAND((const u8 *)"\"",NULL_POINTER,0);
		  HESP_SEND_COMMAND(Copy_puPassword,NULL_POINTER,0);
		  L_errWIFI_Status = (WIFI_ERROR_T) HESP_SEND_COMMAND((const u8 *)"\"\r\n",WIFI_Buffer,30000);
	 }
	 else if( ESP_BUSY == L_errESP_Status )
	 {
			L_errWIFI_Status = WIFI_BUSY;
	 }
	return L_errWIFI_Status;
}

WIFI_ERROR_T	SWIFI_errGetConnectedSSID(u8 * Copy_pu8SSID)
{
	ESP_ERR_T L_errESP_Status = HESP_errCheckESP();
	WIFI_ERROR_T L_errWIFI_Status = WIFI_OK; 

	if( ESP_OK == L_errESP_Status )
	{
		L_errESP_Status = HESP_SEND_COMMAND((const u8 *)"AT+CWJAP?\r\n",Copy_pu8SSID,100);
		if(ESP_OK == L_errESP_Status)
		{
			L_errWIFI_Status = WIFI_OK;
		}
	}
	else if( ESP_BUSY == L_errESP_Status )
	{
		L_errWIFI_Status = WIFI_BUSY;
	}
	return L_errWIFI_Status;
}

WIFI_ERROR_T	SWIFI_errDisconnectSSID(void)
{
	WIFI_ERROR_T L_errWIFI_Status = (WIFI_ERROR_T)HESP_errCheckESP(); 

	if( ESP_OK == L_errWIFI_Status )
	{
		L_errWIFI_Status = (WIFI_ERROR_T)HESP_SEND_COMMAND((const u8 *)"AT+CWQAP\r\n",WIFI_Buffer,100);
	}
	else if( ESP_BUSY == L_errWIFI_Status )
	{
		L_errWIFI_Status = WIFI_BUSY;
	}
	return L_errWIFI_Status;
}

WIFI_ERROR_T	SWIFI_errConfigSoftAP(u8 * Copy_pu8SSID, u8 * Copy_puPassword , u8 * Copy_u8Channel, u8 * Copy_u8Encryption)
{
	WIFI_ERROR_T L_errWIFI_Status = (WIFI_ERROR_T)HESP_errCheckESP(); 

	if( ESP_OK == L_errWIFI_Status )
	{
			HESP_SEND_COMMAND((const u8 *)"AT+CWSAP=",NULL_POINTER,0);
			HESP_SEND_COMMAND((const u8 *)"\"",NULL_POINTER,0);
			HESP_SEND_COMMAND(Copy_pu8SSID,NULL_POINTER,0);
		  HESP_SEND_COMMAND((const u8 *)"\",",NULL_POINTER,0);
		  HESP_SEND_COMMAND((const u8 *)"\"",NULL_POINTER,0);
		  HESP_SEND_COMMAND(Copy_puPassword,NULL_POINTER,0);
			HESP_SEND_COMMAND((const u8 *)"\",",NULL_POINTER,0);
			HESP_SEND_COMMAND((const u8 *)Copy_u8Channel,NULL_POINTER,0);
			HESP_SEND_COMMAND((const u8 *)",",NULL_POINTER,0);
			HESP_SEND_COMMAND((const u8 *)Copy_u8Encryption,NULL_POINTER,0);
			L_errWIFI_Status = (WIFI_ERROR_T)HESP_SEND_COMMAND((const u8 *)"\r\n",WIFI_Buffer,3000);
	}
	else if( ESP_BUSY == L_errWIFI_Status )
	{
		L_errWIFI_Status = WIFI_BUSY;
	}
	return L_errWIFI_Status;
}

WIFI_ERROR_T	SWIFI_errCreateTCPServer(const u8 * Copy_u16PortNumber)
{
	WIFI_ERROR_T L_errWIFI_Status = (WIFI_ERROR_T)HESP_errCheckESP(); 

	if( ESP_OK == L_errWIFI_Status )
	{
			HESP_SEND_COMMAND((const u8 *)"AT+CIPMUX=1\r\n",WIFI_Buffer,100);
			HESP_SEND_COMMAND((const u8 *)"AT+CIPSERVER=1,",NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)Copy_u16PortNumber,NULL_POINTER,100);
			L_errWIFI_Status = (WIFI_ERROR_T)HESP_SEND_COMMAND((const u8 *)"\r\n",WIFI_Buffer,3000);
	}
	else if( ESP_BUSY == L_errWIFI_Status )
	{
		L_errWIFI_Status = WIFI_BUSY;
	}
	return L_errWIFI_Status;
}
WIFI_ERROR_T	SWIFI_errConnectTCP(u8 Copy_u16ID, const u8 * Copy_pu8ServerIP, const u8 * Copy_pu8ServerPort)
{
	WIFI_ERROR_T L_errWIFI_Status = (WIFI_ERROR_T)HESP_errCheckESP(); 
	Copy_u16ID += '0';
	if( ESP_OK == L_errWIFI_Status )
	{
			HESP_SEND_COMMAND((const u8 *)"AT+CIPSTART=",NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)&Copy_u16ID,NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)",\"TCP\",",NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)Copy_pu8ServerIP,NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)",",NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)Copy_pu8ServerPort,NULL_POINTER,100);
			L_errWIFI_Status = (WIFI_ERROR_T)HESP_SEND_COMMAND((const u8 *)"\r\n",WIFI_Buffer,300);
	}
	else if( ESP_BUSY == L_errWIFI_Status )
	{
		L_errWIFI_Status = WIFI_BUSY;
	}
	return L_errWIFI_Status;
}
WIFI_ERROR_T	SWIFI_errSendDataTCP(u8 Copy_u16ID, const u8 * Data,const u8 * Data_size )
{
	WIFI_ERROR_T L_errWIFI_Status = (WIFI_ERROR_T)HESP_errCheckESP(); 
	Copy_u16ID += '0';
	if( ESP_OK == L_errWIFI_Status )
	{
			HESP_SEND_COMMAND((const u8 *)"AT+CIPSEND=",NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)&Copy_u16ID,NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)",",NULL_POINTER,100);
			HESP_SEND_COMMAND((const u8 *)Data_size,NULL_POINTER,100);
			L_errWIFI_Status = (WIFI_ERROR_T)HESP_SEND_COMMAND((const u8 *)"\r\n",WIFI_Buffer,30);
			if(WIFI_OK ==  L_errWIFI_Status)
			{
				HESP_SEND_COMMAND((const u8 *)Data,NULL_POINTER,30);
				L_errWIFI_Status = (WIFI_ERROR_T)HESP_SEND_COMMAND((const u8 *)"\r\n",WIFI_Buffer,30);
			}
	}
	else if( ESP_BUSY == L_errWIFI_Status )
	{
		L_errWIFI_Status = WIFI_BUSY;
	}
	return L_errWIFI_Status;
}


void	SWIFI_errStartCommunicationHandler(void)
{
	HESP_CALLBACK_INIT(SWIFI_voidKeysCapture);
	HESP_voidInterruptEnable();
}
WIFI_ERROR_T	SWIFI_errSetCaptureKeys(SWIFI_COMM_Handler_T * Copy_pUserKeys , u8 Copy_u8KeysNumbers)
{
	if(NULL_POINTER != Copy_pUserKeys)
	{
		UserDefinedKeys = Copy_pUserKeys;
		UserDefinedKeysNumber =Copy_u8KeysNumbers;
		return WIFI_OK;
	}
	return WIFI_ERROR;
}


static void SWIFI_voidKeysCapture(void)
{
	static u8 L_u8Buffer_Count = 0;
	int L_intCounter = 0;
	WIFI_Buffer[L_u8Buffer_Count] = MUART_u16GetData(ESP_UART_NUMBER);
	
	//Capturing the systems keywords
	for(L_intCounter = 0 ; L_intCounter < SYSCALL_SIZE ; L_intCounter++ )
	{
		if ( 1 == SysCaptureKey )
		{
			if(NULL_POINTER != SystemCalls[L_intCounter].pDest_Function)
			{
				L_u8Buffer_Count=0;
				SystemCalls[L_intCounter].pDest_Function();
				break;
			}
		}
	}

	L_u8Buffer_Count++;
	//Buffer Overflow
	if(L_u8Buffer_Count == WIFI_Buffer_Size )
	{
		L_u8Buffer_Count=0;
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
	static u8 L_u8Buffer_Count = 0;
	static u8 L_u8IsRecLength = 0;
	static u8 L_u8IsRecData = 0;
	static u8 L_u8Data_size = 0;
	static SWIFI_MSG_T * MSG;
	static u8 L_u8MSG_Counter = 0;
	WIFI_Buffer[L_u8Buffer_Count] = MUART_u16GetData(ESP_UART_NUMBER);

	//Capturing the user keywords
	if(L_u8IsRecData == 1 )
	{
		MSG->Data[L_u8IsRecLength] = WIFI_Buffer[L_u8Buffer_Count] ;
		L_u8IsRecLength++;
		if(L_u8IsRecLength == L_u8Data_size )
		{
			HESP_CALLBACK_INIT(SWIFI_voidKeysCapture);
			MSG->Data[L_u8IsRecLength] = '\0';
			//Reset everything
			L_u8Buffer_Count = 0;
			L_u8IsRecLength = 0;
			L_u8IsRecData = 0;
			L_u8Data_size = 0;
			L_u8MSG_Counter = 0;
			SWIFI_voidCommunicationHandler(MSG);

			return;
		}
	}
	else
	{
		
		if(L_u8Buffer_Count == 0)
		{
			L_u8IsRecLength = 1;
		}
		else if(L_u8Buffer_Count >= 2 && L_u8IsRecLength == 1)
		{
			if(WIFI_Buffer[L_u8Buffer_Count]  != ':')
			{
				L_u8Data_size = L_u8Data_size * 10 + (WIFI_Buffer[L_u8Buffer_Count] - '0');
			}
			else
			{
				MSG = CreateMsg(L_u8Data_size);
				L_u8IsRecData = 1;
				L_u8IsRecLength=0;
			}	
		}
		
	}
	L_u8Buffer_Count++;
}

static void SWIFI_voidCommunicationHandler(SWIFI_MSG_T* Copy_pMSG)
{
	int L_intCounter = 0;
	
	for(L_intCounter = 0 ; L_intCounter < UserDefinedKeysNumber ; L_intCounter++ )
	{
		if( 1 == UserCaptureKey )
		{
			if(NULL_POINTER != UserDefinedKeys[L_intCounter].pDest_Function)
			{
				UserDefinedKeys[L_intCounter].pDest_Function(Copy_pMSG);
			}
			break;
		}
	}
	
}

SWIFI_MSG_T * CreateMsg(u8 Copy_u8MSG_Size)
{
	SWIFI_MSG_T * temp = malloc(sizeof(u8) + sizeof(u8 *));
	if(temp != NULL_POINTER)
	{
	temp->Data = malloc(Copy_u8MSG_Size+1);
	temp->Data_size = Copy_u8MSG_Size;
	return temp;
	}
	else
	{
		return NULL_POINTER;
	}
}

void DeleteMsg(SWIFI_MSG_T * Copy_pMSG)
{
	if(Copy_pMSG != NULL_POINTER)
	{
		free(Copy_pMSG->Data);
		free(Copy_pMSG);
	}
}
void Connected(void)
{
}


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
#include "SWIFI_private.h"
#include "SWIFI_interface.h"

u8 WIFI_Buffer[50] = {0};


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


WIFI_ERROR_T	SWIFI_errConnectSSID(const u8 * Copy_pu8SSID , const u8 * Copy_puPassword)
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
		L_errESP_Status = HESP_SEND_COMMAND((const u8 *)"AT+ CWJAP?",Copy_pu8SSID,100);
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

WIFI_ERROR_T	SWIFI_errConfigSoftAP(const u8 * Copy_pu8SSID, const u8 * Copy_puPassword , const u8 * Copy_u8Channel, const u8 * Copy_u8Encryption)
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


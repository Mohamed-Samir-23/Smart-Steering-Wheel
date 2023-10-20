/*   Author      : Mahmoud Ahmed         */
/*   SWC         : Wifi_module       		 */
/*   Layer       : Service               */
/*   Version     : 1.0                   */
/*   Date        : October 14, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/


#ifndef _SWIFI_INTERFACE_H_
#define _SWIFI_INTERFACE_H_


typedef enum
{
    WIFI_OK = 1,
    WIFI_ERROR,
    WIFI_BUSY,
    WIFI_FAIL,
	WIFI_RESETED,
	WIFI_TCP_ALREADY_CONNECTED,
	WIFI_TIMEOUT
}WIFI_ERROR_T;

typedef enum
{
	Connection_Closed,
	Connection_Open
}Connection_Status;

typedef struct
{
	char*					ID;
	u16						Connection_Number;
	Connection_Status*	 	Status	;
}SWIFI_Connection_T;

typedef struct
{
	char* 								Data;
	u8									Data_size;
	SWIFI_Connection_T					Connection_info;
}SWIFI_MSG_T;

typedef struct
{
	void 				(*pDest_Function)(SWIFI_MSG_T *);
	const char*			Dest_Name;
	const u8			Dest_Name_size;
}SWIFI_COMM_Handler_T;

#define SWIFI_MODE_STATION					1
#define SWIFI_MODE_SOFTAP					2
#define SWIFI_MODE_STATION_AND_SOFTAP 		3

#define SWIFI_ENCRYPTION_OPEN 					"0"
#define SWIFI_ENCRYPTION_WPA_PSK 				"2"
#define SWIFI_ENCRYPTION_WPA2_PSK 				"3"
#define SWIFI_ENCRYPTION_WPA_WPA2_PSK 			"4"

#define SWIFI_CNANNEL_1			"1"
#define SWIFI_CNANNEL_2			"2"
#define SWIFI_CNANNEL_3			"3"
#define SWIFI_CNANNEL_4			"4"
#define SWIFI_CNANNEL_5			"5"
#define SWIFI_CNANNEL_6			"6"
#define SWIFI_CNANNEL_7			"7"
#define SWIFI_CNANNEL_8			"8"
#define SWIFI_CNANNEL_9			"9"
#define SWIFI_CNANNEL_10		"10"
#define SWIFI_CNANNEL_11		"10"

#define SWIFI_TCP_ID_0 			"0"
#define SWIFI_TCP_ID_1 			"1"
#define SWIFI_TCP_ID_2 			"2"
#define SWIFI_TCP_ID_3 			"3"
#define SWIFI_TCP_ID_4 			"4"

/***********WIFI handle***********/
WIFI_ERROR_T	SWIFI_errTurnOn(u8 Copy_u8WIFIMode);
WIFI_ERROR_T	SWIFI_errConnectSSID(const char * Copy_pu8SSID ,const char * Copy_puPassword);
WIFI_ERROR_T	SWIFI_errGetConnectedSSID(char * Copy_pu8SSID);
WIFI_ERROR_T	SWIFI_errDisconnectSSID(void);
WIFI_ERROR_T	SWIFI_errConfigSoftAP(const char * Copy_pu8SSID, const char * Copy_puPassword , const char * Copy_u8Channel, const char * Copy_u8Encryption);
/*******TCP**********/
WIFI_ERROR_T	SWIFI_errCreateTCPServer(const char * Copy_u16PortNumber);
WIFI_ERROR_T	SWIFI_errSendDataTCP(const char * Copy_u16ID, const char * Data);

WIFI_ERROR_T	SWIFI_errConnectTCP(const char *Copy_u16ID, const char * Copy_pu8ServerIP, const char * Copy_pu8ServerPort);
WIFI_ERROR_T	SWIFI_errDisconnectTCP(const char * Copy_u16ID);

WIFI_ERROR_T	SWIFI_errSetCaptureKeys(SWIFI_COMM_Handler_T * Copy_pUserKeys , u8 Copy_u8KeysNumbers);
void SWIFI_voidSetConnectionFailHandler(FUNC_T UserFunc);
void	SWIFI_errStartCommunicationHandler(void);

SWIFI_MSG_T * CreateMsg(u16 Copy_u8MSG_Size);
void DeleteMsg(SWIFI_MSG_T * Copy_pMSG);



/*

WIFI_ERROR_T	SWIFI_errConfigSoftAP()
WIFI_ERROR_T	SWIFI_errSetMAC()
WIFI_ERROR_T	SWIFI_errSetIP()
WIFI_ERROR_T	SWIFI_errEnableAutoConnect()
WIFI_ERROR_T	SWIFI_errDisconnectSSID()*/

/*********TCP/UDP Handle***********/
//WIFI_ERROR_T	SWIFI_errEnableDHCP()

#endif

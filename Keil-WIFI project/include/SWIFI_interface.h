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
    WIFI_TIMEOUT,
    WIFI_ERROR,
    WIFI_FAIL,
    WIFI_BUSY,
    WIFI_RESETED
}WIFI_ERROR_T;


typedef struct
{
	FUNC_T 			pDest_Function;
	const u8* 	Dest_Name;
	const u8		Dest_Name_size;			
}SWIFI_COMM_T;

#define SWIFI_MODE_STATION							1
#define SWIFI_MODE_SOFTAP								2
#define SWIFI_MODE_STATION_AND_SOFTAP 	3

#define SWIFI_ENCRYPTION_OPEN 					"0"
#define SWIFI_ENCRYPTION_WPA_PSK 				"2"
#define SWIFI_ENCRYPTION_WPA2_PSK 			"3"
#define SWIFI_ENCRYPTION_WPA_WPA2_PSK 	"4"

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

/***********WIFI handle***********/
WIFI_ERROR_T	SWIFI_errTurnOn(u8 Copy_u8WIFIMode);
WIFI_ERROR_T	SWIFI_errConnectSSID(u8 * Copy_pu8SSID , u8 * Copy_puPassword);
WIFI_ERROR_T	SWIFI_errGetConnectedSSID(u8 * Copy_pu8SSID);
WIFI_ERROR_T	SWIFI_errDisconnectSSID(void);
WIFI_ERROR_T	SWIFI_errConfigSoftAP(u8 * Copy_pu8SSID, u8 * Copy_puPassword , u8 * Copy_u8Channel, u8 * Copy_u8Encryption);

/*******TCP**********/
WIFI_ERROR_T	SWIFI_errCreateTCPServer(const u8 * Copy_u16PortNumber);

WIFI_ERROR_T	SWIFI_errStartCommunicationHandler(void);
static void SWIFI_voidCommunicationCapture(void);


/*

WIFI_ERROR_T	SWIFI_errConfigSoftAP()
WIFI_ERROR_T	SWIFI_errSetMAC()
WIFI_ERROR_T	SWIFI_errSetIP()
WIFI_ERROR_T	SWIFI_errEnableAutoConnect()
WIFI_ERROR_T	SWIFI_errDisconnectSSID()*/

/*********TCP/UDP Handle***********/
//WIFI_ERROR_T	SWIFI_errEnableDHCP()

#endif

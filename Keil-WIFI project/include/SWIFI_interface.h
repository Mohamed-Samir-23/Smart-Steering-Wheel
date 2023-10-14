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

#define SWIFI_MODE_STATION							1
#define SWIFI_MODE_SOFTAP								2
#define SWIFI_MODE_STATION_AND_SOFTAP 	3

#define SWIFI_CHANNEL_OPEN "0"
#define SWIFI_CHANNEL_WPA_PSK "2"
#define SWIFI_CHANNEL_WPA2_PSK "3"
#define SWIFI_CHANNEL_WPA_WPA2_PSK "4"
/***********WIFI handle***********/
WIFI_ERROR_T	SWIFI_errTurnOn(u8 Copy_u8WIFIMode);
WIFI_ERROR_T	SWIFI_errConnectSSID(const u8 * Copy_pu8SSID , const u8 * Copy_puPassword);
WIFI_ERROR_T	SWIFI_errGetConnectedSSID(u8 * Copy_pu8SSID);
WIFI_ERROR_T	SWIFI_errDisconnectSSID(void);
WIFI_ERROR_T	SWIFI_errConfigSoftAP(const u8 * Copy_pu8SSID, const u8 * Copy_puPassword , const u8 * Copy_u8Channel, const u8 * Copy_u8Encryption);


/*

WIFI_ERROR_T	SWIFI_errConfigSoftAP()
WIFI_ERROR_T	SWIFI_errSetMAC()
WIFI_ERROR_T	SWIFI_errSetIP()
WIFI_ERROR_T	SWIFI_errEnableAutoConnect()
WIFI_ERROR_T	SWIFI_errDisconnectSSID()*/

/*********TCP/UDP Handle***********/
//WIFI_ERROR_T	SWIFI_errEnableDHCP()

#endif

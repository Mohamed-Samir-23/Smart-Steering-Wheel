/*   Author      : Mahmoud Ahmed         */
/*   SWC         : Wifi_module       		 */
/*   Layer       : Service               */
/*   Version     : 1.0                   */
/*   Date        : October 14, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/


#ifndef _SWIFI_PRIVATE_H_
#define _SWIFI_PRIVATE_H_

#define SysCaptureKey (!strncmp( (const char *) &WIFI_Buffer[L_u8Buffer_Count-SystemCalls[L_intCounter].Dest_Name_size - 1] ,(const char *) SystemCalls[L_intCounter].Dest_Name,SystemCalls[L_intCounter].Dest_Name_size))

#define UserCaptureKey (!strncmp( (const char *) &WIFI_Buffer[L_u8Buffer_Count-UserDefinedKeys[L_intCounter].Dest_Name_size - 1] ,(const char *) UserDefinedKeys[L_intCounter].Dest_Name,UserDefinedKeys[L_intCounter].Dest_Name_size))

#endif

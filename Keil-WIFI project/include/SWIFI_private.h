/*   Author      : Mahmoud Ahmed         */
/*   SWC         : Wifi_module       		 */
/*   Layer       : Service               */
/*   Version     : 1.0                   */
/*   Date        : October 14, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/


#ifndef _SWIFI_PRIVATE_H_
#define _SWIFI_PRIVATE_H_

typedef struct
{
	FUNC_T 			pDest_Function;
	const u8* 	Dest_Name;
	const u8		Dest_Name_size;			
}SWIFI_COMM_SYS_T;

#define SysCaptureKey (!strncmp( (const char *) &WIFI_Buffer[L_u8Buffer_Count+ 1 -SystemCalls[L_intCounter].Dest_Name_size ] ,(const char *) SystemCalls[L_intCounter].Dest_Name,SystemCalls[L_intCounter].Dest_Name_size))

#define UserCaptureKey (!strncmp(( char *)(Copy_pMSG->Data),( char *)(UserDefinedKeys[L_intCounter].Dest_Name),UserDefinedKeys[L_intCounter].Dest_Name_size ) )
#endif

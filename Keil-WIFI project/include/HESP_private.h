/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : ESP_Wifi_module       */
/*   Layer       : HAL                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef _HESP_PRIVATE_H_
#define _HESP_PRIVATE_H_


#define 	ESP_Delay_ms(x); MSYSTICK_stderrorSetBusyWait(x*TICK_FOR_MSEC)

#define ISEndStream (ESP_ERR_T)(ESP_OK * (strncmp((const char *)&Copy_pu8Response[L_u32Count-3],"OK\r\n",4) ==0) \
				+ ESP_ERROR *(strncmp((const char *)&Copy_pu8Response[L_u32Count-6],"ERROR\r\n",7)==0) \
				+ ESP_BUSY*(strncmp((const char *)&Copy_pu8Response[L_u32Count-5],"busy",4) ==0) \
				+ ESP_FAIL *(strncmp((const char *)&Copy_pu8Response[L_u32Count-4],"FAIL\r",5) ==0) \
				+ ESP_RESETED *(strncmp((const char *)&Copy_pu8Response[L_u32Count-3],"ready",4) ==0)) 
					
#endif

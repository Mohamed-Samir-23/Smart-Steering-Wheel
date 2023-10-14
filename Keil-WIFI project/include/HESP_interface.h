/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : ESP_Wifi_module       */
/*   Layer       : HAL                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef _HESP_INTERFACE_H_
#define _HESP_INTERFACE_H_


typedef enum 
{
    ESP_OK = 1,
    ESP_TIMEOUT,
    ESP_ERROR,
    ESP_FAIL,
    ESP_BUSY,
    ESP_RESETED
}ESP_ERR_T;


void HESP_INIT(void);
void HESP_RESET(void);
ESP_ERR_T HESP_SEND_COMMAND(const u8 * Copy_pu8Command, u8 * Copy_pu8Response, u32 timeout );


void HESP_CALLBACK_INIT(FUNC_T FUNC);
void HESP_voidInterruptEnable(void);
void HESP_voidInterruptDisable(void);


ESP_ERR_T ESP_errEchoDisable(void);
ESP_ERR_T ESP_errEchoEnable(void);

static void ESP_TimeOutAlarm(void);





#endif


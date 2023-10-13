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



#define ON 1
#define OFF 0
void HESP_INIT(void);
void HESP_RESET(void);
void HESP_CALLBACK_INIT(FUNC_T FUNC);
ESP_ERR_T HESP_SEND_COMMAND(const u8 * command,u8 * response,u16 timeout );
void HESP_voidInterruptEnable(void);
void HESP_voidInterruptDisable(void);


/*void ESP_SEND_DATA(char * DATA);

ESP_ERR_T  ESP_ECHO(uint16_t State, unsigned char * response);
uint16_t ESP_SENDCOMMAND_CONFIRM(char * command,unsigned char * response,uint16_t timeout , uint16_t TIME_UNIT);
int String_LENGTH(char * DATA);

void EMPTY_ARR(unsigned char * response);*/





#endif


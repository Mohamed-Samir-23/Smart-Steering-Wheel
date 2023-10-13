/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : ESP_Wifi_module       */
/*   Layer       : HAL                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#include "../../01-LIB\LSTD_types.h"
#include "../../01-LIB\LBIT_math.h"

#include "../../02-MCAL\01-MRCC\MRCC_interface.h"
#include "../../02-MCAL\02-MGPIO\MGPIO_interface.h"

#include "03-HAL\ESP\HESP_interface.h"
#include "03-HAL\ESP\HESP_private.h"

void HESP_INIT(void);
void HESP_RESET(void);
void HESP_CALLBACK_INIT(FUNC_T FUNC);
ESP_ERR_T HESP_SEND_COMMAND(const u8 * command,u8 * response,u16 timeout );
void HESP_voidInterruptEnable(void);
void HESP_voidInterruptDisable(void);
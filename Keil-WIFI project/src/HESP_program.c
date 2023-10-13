/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : ESP_Wifi_module       */
/*   Layer       : HAL                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#include "LSTD_types.h"
#include "LBIT_math.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"

#include "HESP_interface.h"
#include "HESP_private.h"

void HESP_INIT(void);
void HESP_RESET(void);
void HESP_CALLBACK_INIT(FUNC_T FUNC);
ESP_ERR_T HESP_SEND_COMMAND(const u8 * command,u8 * response,u16 timeout );
void HESP_voidInterruptEnable(void);
void HESP_voidInterruptDisable(void);

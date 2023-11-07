/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : SPI                   */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : September 26, 2023    */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

#define MSP1_STATUS          MSPI_ENABLE

#define MSPI1_CLOCK_MODE     MSPI_CPOL_1_CPHA_1

#define MSPI1_MASTER_SLAVE   MSPI_MASTER

#define MSPI1_PRESCALLER     MSPI_FPCLK_DIVIDED_32

#define MSPI1_DATA_ORDER     MSPI_MSB_FIRST

#define MSPI1_SS_MANAGE      HW_SLAVE_MANAGEMENT

#define MSPI1_DATA_SIZE      MSPI_DATA_8BITS

#define MSPI1_INT_STATUS     MSPI_INT_DISABLE

#endif /* SPI_CONFIG_H_ */

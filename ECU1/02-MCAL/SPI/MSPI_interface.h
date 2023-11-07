/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : SPI                   */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : September 26, 2023    */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#define MSPI_DISABLE                 0
#define MSPI_ENABLE                  1

#define MSPI_CPOL_0_CPHA_0                   0
#define MSPI_CPOL_0_CPHA_1                   1
#define MSPI_CPOL_1_CPHA_0                   2
#define MSPI_CPOL_1_CPHA_1                   3

#define MSPI_MASTER                  0
#define MSPI_SLAVE                   1

#define MSPI_FPCLK_DIVIDED_2      0
#define MSPI_FPCLK_DIVIDED_4      1
#define MSPI_FPCLK_DIVIDED_8      2
#define MSPI_FPCLK_DIVIDED_16     3
#define MSPI_FPCLK_DIVIDED_32     4
#define MSPI_FPCLK_DIVIDED_64     5
#define MSPI_FPCLK_DIVIDED_128    6
#define MSPI_FPCLK_DIVIDED_256    7

#define MSPI_MSB_FIRST               0
#define MSPI_LSB_FIRST 				 1

#define HW_SLAVE_MANAGEMENT          0
#define SW_SLAVE_MANAGEMENT          1

#define MSPI_DATA_8BITS               0
#define MSPI_DATA_16BITS              1

#define MSPI_INT_DISABLE             0
#define MSPI_TXE_INT_ENABLE          1
#define MSPI_RXNE_INT_ENABLE         2


void MSPI_vInit (void) ;
u8   MSPI1_vSendData( u8 Copy_u8Data) ;
void MSPI1_vSetCallBack ( void (*ptr) (void) ) ;


#endif 

/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : SPI                   */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : September 26, 2023    */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

typedef struct {

	volatile u32 CR1     ;
	volatile u32 CR2     ;
	volatile u32 SR      ;
	volatile u32 DR      ;
	volatile u32 CRCPR   ;
	volatile u32 RXCRCR  ;
	volatile u32 TXCRCR  ;
	volatile u32 I2SCFGR ;
	volatile u32 I2SPR   ;

}SPI;

#define MSPI1 ( ( volatile SPI* ) 0x40013000 )

#endif /* SPI_REG_H_ */

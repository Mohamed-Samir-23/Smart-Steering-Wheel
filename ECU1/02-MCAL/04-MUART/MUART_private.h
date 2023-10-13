/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : UART						       */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef _UART_PRIVATE_H_
#define _UART_PRIVATE_H_

#define USART1_BASE_ADDRESS 0x40013800


typedef struct
{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
	
}USART_T;
	
#define USART1 ((volatile USART_T * ) 0x40013800)
#define USART2 ((volatile USART_T * ) 0x40004400)
#define USART3 ((volatile USART_T * ) 0x40004800)


// Bit Numbers
#define UE_BIT      13
#define M_BIT       12
#define WAKE_BIT    11
#define PCE_BIT     10
#define PS_BIT       9
#define PEIE_BIT     8
#define TXEIE_BIT    7
#define TCIE_BIT     6
#define RXNEIE_BIT   5
#define IDLEIE_BIT   4
#define TE_BIT       3
#define RE_BIT       2
#define RWU_BIT      1
#define SBK_BIT      0

// Macros to set/clear the bits
#define UE_SET      (1 << UE_BIT)
#define M_SET       (1 << M_BIT)
#define WAKE_SET    (1 << WAKE_BIT)
#define PCE_SET     (1 << PCE_BIT)
#define PS_SET      (1 << PS_BIT)
#define PEIE_SET    (1 << PEIE_BIT)
#define TXEIE_SET   (1 << TXEIE_BIT)
#define TCIE_SET    (1 << TCIE_BIT)
#define RXNEIE_SET  (1 << RXNEIE_BIT)
#define IDLEIE_SET  (1 << IDLEIE_BIT)
#define TE_SET      (1 << TE_BIT)
#define RE_SET      (1 << RE_BIT)
#define RWU_SET     (1 << RWU_BIT)
#define SBK_SET     (1 << SBK_BIT)

// Macros to clear the bits
#define UE_CLEAR      ~(UE_SET)
#define M_CLEAR       ~(M_SET)
#define WAKE_CLEAR    ~(WAKE_SET)
#define PCE_CLEAR     ~(PCE_SET)
#define PS_CLEAR      ~(PS_SET)
#define PEIE_CLEAR    ~(PEIE_SET)
#define TXEIE_CLEAR   ~(TXEIE_SET)
#define TCIE_CLEAR    ~(TCIE_SET)
#define RXNEIE_CLEAR  ~(RXNEIE_SET)
#define IDLEIE_CLEAR  ~(IDLEIE_SET)
#define TE_CLEAR      ~(TE_SET)
#define RE_CLEAR      ~(RE_SET)
#define RWU_CLEAR     ~(RWU_SET)
#define SBK_CLEAR     ~(SBK_SET)

#define STOP_BITS 12
#define STOP_MASK 3000

// Bit Numbers
#define CTS_BIT     9
#define LBD_BIT     8
#define TXE_BIT     7
#define TC_BIT      6
#define RXNE_BIT    5
#define IDLE_BIT    4
#define ORE_BIT     3
#define NE_BIT      2
#define FE_BIT      1
#define PE_BIT      0
#endif

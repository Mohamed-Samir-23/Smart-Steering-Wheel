/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : UART						       */
/*   Layer       : MCAL                  */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/

#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

#define MUART1 	1
#define MUART2	2
#define MUART3	3

#define MUART_WORD8	0
#define MUART_WORD9	1

#define MUART_PARITY_EVEN	0
#define MUART_PARITY_ODD		1
#define MUART_PARITY_OFF		2

#define MUART_STOP_1		0
#define MUART_STOP__5		1
#define MUART_STOP_2		2
#define MUART_STOP_1_5	3

#define MUART_INTERRUPT_RXNE	5
#define MUART_INTERRUPT_TC		6	
#define MUART_INTERRUPT_TXE		7
#define MUART_INTERRUPT_DS		8




#ifndef F_CPU 
#define F_CPU 72000000
#warning F_CPU is not define so the default is 8MHz
#endif

void MUART_voidInit( u8 Copy_u8UART_Number,u32 Copy_u32BaudRate,u8 Copy_u8Parity, u8 Copy_u8StopBit,u8 Copy_u8WordSize);

void MUART_voidTransimit( u8 Copy_u8UART_Number,  u16 Copy_u8Data);
u16 MUART_u8ReceivePolling( u8 Copy_u8UART_Number);


void MUART_voidSetCallBack( u8 Copy_u8UART_Number,FUNC_T  Copy_pvUserFunc);

void MUART_voidInterruptEnable(u8 Copy_u8UART_Number, u8 Copy_u8InterruptType);
void MUART_voidInterruptDisable(u8 Copy_u8UART_Number, u8 Copy_u8InterruptType);

u8 MUART_u8TCFlag(u8 Copy_u8UART_Number);
u8 MUART_u8RXNEFlag(u8 Copy_u8UART_Number);
u16 MUART_u16GetData(u8 Copy_u8UART_Number);

volatile void * GetUsartPointer(u8 Copy_u8UART_Number);



#endif

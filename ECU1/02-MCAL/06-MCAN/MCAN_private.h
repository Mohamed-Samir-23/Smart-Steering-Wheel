/****************************************/
/*  Author		: Mohamed Samir			*/
/*  SWC			: CAN					*/
/*  Layer		: MCAL					*/
/*  Version		: 1.2					*/
/*  Date		: October 13, 2023		*/
/*  Last Edit	: October 25, 2023		*/
/****************************************/

#ifndef _MCAN_PRIVATE_H_
#define _MCAN_PRIVATE_H_



#define CAN_BASE  			0x40006400 

#define CAN_MCR				*((uv32 *)(0x00 + CAN_BASE))
#define	DBF					16
#define	RESET				15
#define	TTCM				7
#define	ABOM				6
#define	AWUM				5
#define	NART				4
#define	RFLM				3
#define	TXFP				2
#define	SLEEP				1
#define	INRQ				0

#define CAN_MSR				*((uv32 *)(0x04 + CAN_BASE))
#define RX					11
#define SAMP				10
#define RXM					9
#define TXM					8
#define SLAKI				4
#define WKUI				3
#define ERRI				2
#define SLAK				1
#define INAK				0

#define CAN_TSR				*((uv32 *)(0x08 + CAN_BASE))
#define LOW2                31
#define LOW1                30
#define LOW0                29
#define TME2				28
#define TME1				27
#define TME0				26
#define MAILBOX_CODE		24
#define ABRQ2               23
#define TERR2               19
#define ALST2               18
#define TXOK2               17
#define RQCP2               16
#define ABRQ1               15
#define TERR1               11
#define ALST1               10
#define TXOK1               9
#define RQCP1               8
#define ABRQ0               7
#define TERR0               3
#define ALST0               2
#define TXOK0               1
#define RQCP0               0





#define CAN_RF0R			*((uv32 *)(0x0C + CAN_BASE))
#define CAN_RF1R			*((uv32 *)(0x10 + CAN_BASE))
#define RFOM0				5
#define FULL				3
#define FOVR				4
#define FMP					0

#define CAN_IER				*((uv32 *)(0x14 + CAN_BASE))
#define SLKIE				17
#define WKUIE				16
#define ERRIE				15
#define LECIE				11
#define BOFIE				10
#define EPVIE				9
#define EWGIE				8
#define FOVIE1				6
#define FFIE1				5
#define FMPIE1				4
#define FOVIE0				3
#define FFIE0				2
#define FMPIE0				1
#define TMEIE				0


#define CAN_ESR				*((uv32 *)(0x18 + CAN_BASE))
#define LEC					4

#define CAN_BTR				*((uv32 *)(0x1C + CAN_BASE))
#define SILM				31
#define LBKM				30
#define SJW					24
#define TS2					20
#define TS1					16
#define BRP					0

typedef struct
{

	u32 TIR;
	u32 TDTR;
	u32 TDLR;
	u32 TDHR;
	
} MCAN_MailBox_s;


#define CAN_MailBox			((volatile MCAN_MailBox_s *)(0x180 + CAN_BASE))

#define TXRQ				1


typedef struct
{
  u32 RIR;
  u32 RDTR;
  u32 RDLR;
  u32 RDHR;
  
} MCAN_FIFO_MailBox_s;

#define CAN_FIFO_MailBox			((volatile MCAN_FIFO_MailBox_s *)(0x1B0 + CAN_BASE))


#define CAN_FMR				*((uv32 *)(0x200 + CAN_BASE))
#define FINIT				0

#define CAN_FM1R			*((uv32 *)(0x204 + CAN_BASE))

#define CAN_FS1R			*((uv32 *)(0x20C + CAN_BASE))

#define CAN_FFA1R			*((uv32 *)(0x214 + CAN_BASE))

#define CAN_FA1R			*((uv32 *)(0x21C + CAN_BASE))


typedef struct
{
  u32 FR1;
  u32 FR2;
} MCAN_Filter_s;

#define CAN_FILTER			((volatile MCAN_Filter_s *)(0x240 + CAN_BASE))


#define STIDMSG_FLAG 0x7FFU

#define EXIDMSG_FLAG 0xFFFFFFF8U


static u8 MCAN_u8EmptyMailboxNumber
(
	void
);

static u8 MCAN_u8ReadyMailBox
(
	void
);


static u8 MCAN_u8FIFOMailboxNumber
(
	u8 ARG_u8FIFOINDEX
);

#endif


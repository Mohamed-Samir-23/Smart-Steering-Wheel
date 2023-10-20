
/*****************************************/
/*   Author      : Mahmoud Ahmed         */
/*   SWC         : Wifi_module       		 */
/*   Layer       : -	                   */
/*   Version     : 1.0                   */
/*   Date        : October 13, 2023      */
/*   Last Edit   : N/A                   */
/*****************************************/



/*********inclusion section********/

/*****LIB*****/
#include "LBIT_math.h"
#include "LSTD_types.h"

/****RCC******/
#include "MRCC_interface.h"

/****GPIO*****/
#include "MGPIO_config.h"
#include "MGPIO_interface.h"

/****STK******/
#include "MSYSTICK_interface.h"

/***UART*****/
#include "MUART_interface.h"

/*****ESP****/
#include "HESP_config.h"
#include "HESP_interface.h"

#include "SWIFI_interface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



typedef struct
{
	char * LineOfCode;
	char * Target;
	u32	   LineNo;

}CodeLine_T;

/*********API********/
void App_init(void);
void WIFI_init(void);

void MCU1_Update(void);
void MCU1ToMailBox(SWIFI_MSG_T * msg);
void MCU2_Update(void);
void MCU2ToMailBox(SWIFI_MSG_T * msg);
void JETSON_Update(void);
void JETSONToMailBox(SWIFI_MSG_T * msg);
void CheckForUpdates(void);
void CheckToMailBox(SWIFI_MSG_T * msg);
void simpleXOREncrypt(char *message, char key);
WIFI_ERROR_T RequestCodeLine(char * TCP_ID,char * Copy_pTarget , u32 Copy_u32Line_no);
WIFI_ERROR_T RequestHexSize(char * TCP_ID,char * Copy_pTarget );
void Delay_ms(u32 time);
char * GetCell(const char * Cell , u32 Copy_u32Cellno);

extern Connection_Status SWIFI_Connections_status[5];

SWIFI_MSG_T * MCU1_MailBox= NULL_POINTER;
u8 IsMessageRecMCU1 = 0;

SWIFI_MSG_T * MCU2_MailBox= NULL_POINTER;
u8 IsMessageRecMCU2 = 0;

SWIFI_MSG_T * JETSON_MailBox= NULL_POINTER;
u8 IsMessageRecJETSON = 0;

SWIFI_MSG_T * Check_MailBox= NULL_POINTER;
u8 IsMessageRecCheck = 0;

SWIFI_COMM_Handler_T Mykeys[4] =
{
		{
				MCU1ToMailBox,
				"MCU1",
				4
		},
		{
				MCU2ToMailBox,
				"MCU2",
				4
		},
		{
				JETSONToMailBox,
				"JETSON",
				6
		},
		{
				CheckToMailBox,
				"Check",
				5
		}


};



/***To DO:This values must be saved and loaded from flash***/

u8 IsUpdateRequest= 0;


#define Ver_MCU1  0
#define Ver_MCU2  1
#define Ver_MCU3  0

#define Server_IP 		"63.63.63.6"
#define Server_Port 	"8080"
u8 Server_MCU1_ver ,Server_MCU2_ver , Server_JETSON_ver;
WIFI_ERROR_T Status ;
char Copy_pu8Response[50];
int main()
{

	App_init();
	WIFI_init();
	SWIFI_voidSetConnectionFailHandler(WIFI_init);

	while(1)
	{

		 CheckForUpdates();

		if(Server_MCU1_ver > Ver_MCU1)
			MCU1_Update();
		if(Server_MCU2_ver > Ver_MCU2)
			MCU2_Update();
		if(Server_JETSON_ver > Ver_MCU3)
			JETSON_Update();

		//Wait For a  day then get updates again or wait for update request
		while(IsUpdateRequest == 0);

		//reset these values
		WIFI_init();

	}

}

void App_init(void)
{
	MRCC_stderrorInit(PLL_HSE,AHB_PreScaler1,APB_PreScaler2,APB_PreScaler1);
	MRCC_stderrorSetPllClockFreq(PLL_PreScaler9,Wait_States_2);
	RCC_EnablePeripheralClk(APB2,GPIOA_PER);
	MGPIO_stderrorPinModeSelect(GPIOA,PIN0,OUTPUT_PUSH_PULL_SPEED_50MHZ);

	/*****ESP initialization********/
	HESP_INIT();

}
void WIFI_init(void)
{
	SWIFI_errSetCaptureKeys(Mykeys,4);
	SWIFI_errTurnOn(SWIFI_MODE_STATION_AND_SOFTAP);
	while (SWIFI_errTurnOn(SWIFI_MODE_STATION_AND_SOFTAP) != WIFI_OK);
	while (SWIFI_errConnectSSID("Hello World","Helloworld*#*#10#*#*") != WIFI_OK);
	SWIFI_errCreateTCPServer(Server_Port); //I don't need but for test purposes
	SWIFI_errStartCommunicationHandler();
}
void MCU1ToMailBox(SWIFI_MSG_T * msg)
{
	MCU1_MailBox = msg;
	IsMessageRecMCU1 = 1;
}
void MCU2ToMailBox(SWIFI_MSG_T * msg)
{
	MCU2_MailBox = msg;
	IsMessageRecMCU2 = 1;
}
void JETSONToMailBox(SWIFI_MSG_T * msg)
{
	JETSON_MailBox= msg;
	IsMessageRecJETSON = 1;
}
void CheckToMailBox(SWIFI_MSG_T * msg)
{
	Check_MailBox= msg;
	IsMessageRecCheck = 1;
}
void CheckForUpdates(void)
{
	WIFI_ERROR_T Status =WIFI_ERROR;
	while(Status != WIFI_OK)
	{
		Status = SWIFI_errSendDataTCP(SWIFI_TCP_ID_0,"CheckForUpdates");
		if( WIFI_OK == Status )
		{
			Status = WIFI_OK;
		}
		else
		{
			SWIFI_errConnectTCP(SWIFI_TCP_ID_0,Server_IP,Server_Port);
		}
	}

	while(IsMessageRecCheck == 0);
	Server_MCU1_ver = atoi( GetCell(Check_MailBox->Data, 2) );
	Server_MCU2_ver = atoi( GetCell(Check_MailBox->Data, 4) );
	Server_JETSON_ver= atoi( GetCell(Check_MailBox->Data, 6) );
}
void MCU1_Update(void)
{
	u32 Hexsize = 0;
	u32 L_u32LineCounter =0;

	RequestHexSize(SWIFI_TCP_ID_0, "MCU1");
	while( IsMessageRecMCU1 == 0); //Waiting to get Hex size from the server
	Hexsize = atoi(GetCell( (MCU1_MailBox->Data),1)); //Getting hex size in int

	//Replying OK to server
	SWIFI_errSendDataTCP(MCU1_MailBox->Connection_info.ID, "OK");

	DeleteMsg(MCU1_MailBox);
	IsMessageRecMCU1 = 0; //this means that i finished reading the mail box

	for(L_u32LineCounter = 0 ; L_u32LineCounter < Hexsize ; L_u32LineCounter++)
	{
		RequestCodeLine(SWIFI_TCP_ID_0, "MCU1", L_u32LineCounter);
		while( IsMessageRecMCU1 == 0);
		if(L_u32LineCounter == atoi(GetCell( (MCU1_MailBox->Data),1)) )
		{
			//Replying OK to server
			SWIFI_errSendDataTCP(MCU1_MailBox->Connection_info.ID, "OK");
			/*****************************************************************
			 *
			 *
			 * Doing Some operations
			 * send it by CAN or whatever
			 * to be implemented by CAN team
			 *
			 */
			DeleteMsg(MCU1_MailBox);
			IsMessageRecMCU1 = 0; //this means that i finished reading the mail box

		}
		else
		{
			L_u32LineCounter--;
		}
	}
	SWIFI_errDisconnectTCP(SWIFI_TCP_ID_0);
}


void MCU2_Update(void)
{
	u32 Hexsize = 0;
	u32 L_u32LineCounter =0;

	RequestHexSize(SWIFI_TCP_ID_0, "MCU2");
	while( IsMessageRecMCU2 == 0); //Waiting to get Hex size from the server
	Hexsize = atoi(GetCell( (MCU2_MailBox->Data),1)); //Getting hex size in int

	//Replying OK to server
	SWIFI_errSendDataTCP(MCU2_MailBox->Connection_info.ID, "OK");

	DeleteMsg(MCU2_MailBox);
	IsMessageRecMCU2 = 0; //this means that i finished reading the mail box

	for(L_u32LineCounter = 0 ; L_u32LineCounter < Hexsize ; L_u32LineCounter++)
	{
		RequestCodeLine(SWIFI_TCP_ID_0, "MCU2", L_u32LineCounter);
		while( IsMessageRecMCU2 == 0);
		if(L_u32LineCounter == atoi(GetCell( (MCU2_MailBox->Data),1)) )
		{
			//Replying OK to server
			SWIFI_errSendDataTCP(MCU2_MailBox->Connection_info.ID, "OK");
			/*****************************************************************
			 *
			 *
			 * Doing Some operations
			 * send it by CAN or whatever
			 * to be implemented by CAN team
			 *
			 */
			DeleteMsg(MCU2_MailBox);
			IsMessageRecMCU2 = 0; //this means that i finished reading the mail box

		}
		else
		{
			L_u32LineCounter--;
		}
	}
	SWIFI_errDisconnectTCP(SWIFI_TCP_ID_0);

}
void JETSON_Update(void)
{
	u32 Hexsize = 0;
	u32 L_u32LineCounter =0;

	RequestHexSize(SWIFI_TCP_ID_0, "JETSON");
	while( IsMessageRecJETSON == 0); //Waiting to get Hex size from the server
	Hexsize = atoi(GetCell( (JETSON_MailBox->Data),1)); //Getting hex size in int

	//Replying OK to server
	SWIFI_errSendDataTCP(JETSON_MailBox->Connection_info.ID, "OK");

	DeleteMsg(JETSON_MailBox);
	IsMessageRecJETSON = 0; //this means that i finished reading the mail box

	for(L_u32LineCounter = 0 ; L_u32LineCounter < Hexsize ; L_u32LineCounter++)
	{
		RequestCodeLine(SWIFI_TCP_ID_0, "JETSON", L_u32LineCounter);
		while( IsMessageRecJETSON == 0);
		if(L_u32LineCounter == atoi(GetCell( (JETSON_MailBox->Data),1)) )
		{
			//Replying OK to server
			SWIFI_errSendDataTCP(JETSON_MailBox->Connection_info.ID, "OK");
			/*****************************************************************
			 *
			 *
			 * Doing Some operations
			 * send it by CAN or whatever
			 * to be implemented by CAN team
			 *
			 */
			DeleteMsg(JETSON_MailBox);
			IsMessageRecJETSON = 0; //this means that i finished reading the mail box

		}
		else
		{
			L_u32LineCounter--;
		}
	}
	SWIFI_errDisconnectTCP(SWIFI_TCP_ID_0);

}
void simpleXOREncrypt(char *message, char key) {
	int len = strlen(message);
	for (int i = 0; i < len; i++) {
		message[i] = message[i] ^ key;
	}
}
WIFI_ERROR_T RequestCodeLine(char * TCP_ID,char * Copy_pTarget , u32 Copy_u32Line_no)
{
	char StrLine_no[10];
	WIFI_ERROR_T Status= WIFI_ERROR;
	u8 RetryMax = 5;
	itoa(Copy_u32Line_no,StrLine_no,10);
	char *StringToSend = malloc(strlen(Copy_pTarget) + sizeof("Update,"",GetLine")) ;
	sprintf( StringToSend ,"%s,%s,%s,%s","Update",Copy_pTarget,"GetLine",StrLine_no);
	while (Status != WIFI_OK)
	{

		if(RetryMax == 0)
		{
			break;
		}
		RetryMax--;
		//Status is suffecient for the last one only but i made it for all for debug purpose

		Status = SWIFI_errSendDataTCP(TCP_ID,StringToSend);
		if( WIFI_OK == Status )
		{
			Status = WIFI_OK;
		}
		else
		{
			SWIFI_errConnectTCP(TCP_ID,Server_IP,Server_Port);
		}

		if(Status == WIFI_BUSY)
		{
			Delay_ms(20);
		}

	}
	free(StringToSend);
	return Status;

}
WIFI_ERROR_T RequestHexSize(char * TCP_ID,char * Copy_pTarget )
{
	WIFI_ERROR_T Status= WIFI_ERROR;
	u8 RetryMax = 20;
	char *StringToSend = malloc(strlen(Copy_pTarget) + sizeof("Update,"",GetHexSize")) ;
	sprintf(StringToSend,"%s,%s,%s","Update",Copy_pTarget,"GetHexSize");

	while (Status != WIFI_OK)
	{

		if(RetryMax == 0)
		{
			break;
		}
		RetryMax--;
		//Status is suffecient for the last one only but i made it for all for debug purpose
		Status = SWIFI_errConnectTCP(TCP_ID,Server_IP,Server_Port);
		if( (Status == WIFI_OK) || (Status == WIFI_TCP_ALREADY_CONNECTED) )
		{
			if( WIFI_OK == SWIFI_errSendDataTCP(TCP_ID,StringToSend) )
			{
				Status = WIFI_OK;
			}
			else if(Status == WIFI_BUSY)
			{
				Delay_ms(1000);
			}
		}
		else if(Status == WIFI_BUSY)
		{
			Delay_ms(1000);
		}

	}
	free(StringToSend);
	return Status;
}
char * GetCell(const char * Cell , u32 Copy_u32Cellno)
{
	int L_intCounter = 0;
	int L_intValue   = 0;
	char *  ReturnValue =NULL_POINTER;
	for(L_intCounter = 0 ; L_intCounter < Copy_u32Cellno ;L_intCounter++)
	{
		while(Cell[L_intValue] != ',')
		{
			L_intValue++;
		}
		L_intValue++;
	}


	if(Cell[L_intValue-1] != ',')
	{
		ReturnValue = NULL_POINTER;
	}
	else
	{
		ReturnValue =(char *) &Cell[L_intValue];
	}

	return ReturnValue;
}
void Delay_ms(u32 time)
{
	int i = 0;
	for(i = 0 ; i < time ; i++)
	{
		MSYSTICK_stderrorSetBusyWait(TICK_FOR_MSEC);
	}
}

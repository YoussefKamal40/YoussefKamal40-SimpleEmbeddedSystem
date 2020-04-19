/*
 * counter_App.c
 *
 *  Created on: Apr 2, 2020
 *      Author: LENOVO.SXM1
 */
#include "LIB/STD_TYPES_H.h"
#include "Counter_app_interface.h"
#include "stdint.h"
#include "HAL/HSYSTEM/systemClockHandler_interface.h"
#include "MCAL/RCC/RCC_interface.h"
#include "HAL/HLCD/LCD_interface.h"
#include "HAL/HSWITCH/SwitchHandler_interface.h"
#include "HAL/HLED/LEDHandler_interface.h"
#include "SERVICE/SCHED/Schedular_interface.h"
#include "HAL/HUSART/ChipUSARTHandler_interface.h"
#include "LIB/HamadaProtocol.h"

typedef u8 Status_type;

#define STATUS_OK	0
#define STATUS_NOK	0

#define WORD_BYTE_SIZE	4
#define SWITCH1_ID	0
#define LED0_ID		0
#define	COUNTER_ID	0X2311
#define TOGGLE	1
#define FIRST_DATA_WORD	0
#define FOUR_CHARACTERS		4
volatile u8 sendFlag;
volatile u8 recieveFlag;

//static u32 ProcessQueue[MAX_PROCESS_QUEUE_SIZE];
static Hamada_parserObjectType parserObject;

static void SendNotify(void);
static void RecieveNotify(void);
static void updateRecieveMailboxProcess(void);
static void UpdateHardwareProcess(void);
static void updateSendMaileboxProcess(void);
static void SendDataMAilboxProcess(void);
static void SendStateMailboxProcess(void);


void counterApp_sysinit(void){
	SYS_HAN_setSystemClock(SYS_HAN_CLOCK_72MHz);
	SYS_HAN_setAHBClock(SYS_HAN_CLOCK_72MHz);
	SYS_HAN_setAPB1Clock(SYS_HAN_CLOCK_36MHz);
	SYS_HAN_setAPB2Clock(SYS_HAN_CLOCK_72MHz);
	RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_IOPAEN,RCC_u8_ENABLE);
	RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_IOPCEN,RCC_u8_ENABLE);
	RCC_u8_ControlPrephiral(RCC_u32_CONTROL_PERIP_IOPBEN,RCC_u8_ENABLE);
	LCD_init();
	HSWITCH_init();
	LED_init();
	ChipUSARTHandler_Init();
	Hamada_parserObjectInit(&parserObject);
	Sched_init();
	Sched_start();
}



static Hamada_stateMailBoxType LEDMailbox={NOT_PRESSED_STATE,LED0_ID,0};
static Hamada_dataMailBoxType LCD_dataMailbox={{0},0,1};

static Hamada_stateMailBoxType ReciveStateMailbox;
static Hamada_dataMailBoxType  ReciveDataMailbox;

static u8 sendbuffer[MAX_FRAME_BYTE_SIZE];
static u8 recievebuffer[MAX_FRAME_BYTE_SIZE];
static u32 LED_State, LCD_string;
static Hamada_parserStateType parser_doneFlag;
static u8 doneframeFlag;


void counterApp_runnable(void)
{
	static u8 sendSateDataFlag,instFlag;

	updateSendMaileboxProcess();

	if(parser_doneFlag ==DONE)
	{
	UpdateHardwareProcess();
	}
	if(!doneframeFlag){
		updateRecieveMailboxProcess();
	}



	if(instFlag)
	{
		lcd_applyCommand(CMD_CLEAR_SCREEN);
		instFlag=0;
	}
	else
	{
		if(sendSateDataFlag)
		{
			SendDataMAilboxProcess();
			sendSateDataFlag =0;
		}
		else
		{
			SendStateMailboxProcess();
			sendSateDataFlag =1;
		}
		lcdnumberprinting(LCD_string);
		instFlag=1;
	}
}
static void SendStateMailboxProcess(void)
{
	u8 sentDataSize;

	sentDataSize= Hamada_frameConstructor(sendbuffer,FRAME_CONSTRUCTOR_STATE,&LEDMailbox);
	ChipUSARTHandler_sendBacket(0,sendbuffer,sentDataSize,SendNotify);
	sendFlag=0;
}

static void SendDataMAilboxProcess(void)
{
	u8 sentDataSize;

	sentDataSize= Hamada_frameConstructor(sendbuffer,FRAME_CONSTRUCTOR_DATA,&LCD_dataMailbox);
	ChipUSARTHandler_sendBacket(0,sendbuffer,sentDataSize,SendNotify);
	sendFlag=0;
}

static void updateSendMaileboxProcess(void)
{
	static u32 SwitchCounter;
	static u8 PressedFlag;

	if(HSWITCH_getState(SWITCH1_ID) == PRESSED_STATE &&(!PressedFlag))
	{
		PressedFlag=1;
	}
	else if(HSWITCH_getState(SWITCH1_ID) == NOT_PRESSED_STATE &&(PressedFlag))
	{
		SwitchCounter ++;
		*(LCD_dataMailbox.data)=SwitchCounter;
		LEDMailbox.state^=TOGGLE;
		PressedFlag =0;
	}
}


static void UpdateHardwareProcess(void)
{
		 LED_State =ReciveStateMailbox.state;
		 LCD_string=ReciveDataMailbox.data[FIRST_DATA_WORD];
}

static void updateRecieveMailboxProcess(void)
{
	if(recieveFlag){
	parser_doneFlag = Hamada_frameParse(recievebuffer,&ReciveStateMailbox,&ReciveDataMailbox,&parserObject);
	}
	if(parser_doneFlag == DONE)
	{
	ChipUSARTHandler_receiveBacket(0,recievebuffer,WORD_BYTE_SIZE,RecieveNotify);
	}
	recieveFlag =0;
}


static void SendNotify(void)
{
	sendFlag =1;
}


static void RecieveNotify(void)
{
	 recieveFlag =1;
	parser_doneFlag = Hamada_frameParse(recievebuffer,&ReciveStateMailbox,&ReciveDataMailbox,&parserObject);
	if(parser_doneFlag == IDLE)
	{
		ChipUSARTHandler_receiveBacket(0,recievebuffer,WORD_BYTE_SIZE,RecieveNotify);
	}
	else
	{
		doneframeFlag =0;
	}
}

/*
 * counter_App.c
 *
 *  Created on: Apr 2, 2020
 *      Author: LENOVO.SXM1
 */
#include "STD_TYPES_H.h"
#include "Counter_app_interface.h"
#include "stdint.h"
#include "systemClockHandler_interface.h"
#include "RCC_interface.h"
#include "LCD_interface.h"
#include "SwitchHandler_interface.h"
#include "LEDHandler_interface.h"
#include "ChipUSARTHandler_interface.h"
#include "HamadaProtocol.h"

#define SWITCH1_ID	0
#define LED0_ID		0
#define	COUNTER_ID	0X2311

#define TOGGLE	1
volatile u8 sendFlag;
volatile u8 recieveFlag;

static Hamada_parserObjectType parserObject;

static void SendNotify(void);
static void RecieveNotify(void);


static void SendNotify(void)
{
	sendFlag =1;
}

static void RecieveNotify(void)
{


}


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

void counterApp_runnable(void)
{
	static u8 instFlag, PressedFlag;
	static u32 counter;
	static Hamada_stateMailBoxType LEDMailbox={NOT_PRESSED_STATE,LED0_ID,0};
	static Hamada_dataMailBoxType LCD_dataMailbox={{0},0,1};
	static u8 sendbuffer[MAX_FRAME_BYTE_SIZE];
	static u8 recievebuffer[MAX_FRAME_BYTE_SIZE];
	static Hamada_stateMailBoxType ReciveStateMailbox;
	static Hamada_dataMailBoxType  ReciveDataMailbox;
		u8 sentDataSize;

	if(HSWITCH_getState(SWITCH1_ID) == PRESSED_STATE &&(!PressedFlag))
	{

		PressedFlag=1;
	}
	else if(HSWITCH_getState(SWITCH1_ID) == NOT_PRESSED_STATE &&(PressedFlag))
	{
		counter ++;
		*(LCD_dataMailbox.data)=counter;
		PressedFlag =0;
		LEDMailbox.state^=TOGGLE;

	}

	if(recieveFlag)
	{
		 LED_setState(LED0_ID, ((u8)ReciveStateMailbox.state));
		 lcd_applyCommand(CMD_CLEAR_SCREEN);
		// LCD_writeString();


		 Hamada_frameParse(recievebuffer,&ReciveStateMailbox,&ReciveDataMailbox,&parserObject);
		 ChipUSARTHandler_receiveBacket(0,recievebuffer,sentDataSize,RecieveNotify);
	}

	if(instFlag)
	{
		if(sendFlag)
		{
			sentDataSize= Hamada_frameConstructor(sendbuffer,FRAME_CONSTRUCTOR_DATA,&LCD_dataMailbox);
			instFlag = ChipUSARTHandler_sendBacket(0,sendbuffer,sentDataSize,SendNotify);
		}
	}
	else
	{
		if(sendFlag)
		{
			sentDataSize= Hamada_frameConstructor(sendbuffer,FRAME_CONSTRUCTOR_STATE,&LEDMailbox);
			instFlag = ChipUSARTHandler_sendBacket(0,sendbuffer,sentDataSize,SendNotify);
			instFlag ^=TOGGLE;
		}
	}
}



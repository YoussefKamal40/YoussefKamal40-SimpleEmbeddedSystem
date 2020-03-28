/*
 * LCD.c
 *
 *  Created on: Mar 28, 2020
 *      Author: LENOVO.SXM1
 */


#include "STD_TYPES_H.h"
#include "GPIO_Interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"


static void LCD_8bitInitProcess(void);
static void LCD_8bitCMDProcess(void);
static void LCD_8bitWriteProcess(void);

#define NO_CONTROL_PINS		3
#define NO_DATA_PINS		8

#define RS 0
#define RW 1
#define E  2
#define ZERO_VALUE	((u8)0)
#define ONE_VALUE	((u8)1)

#define INIT_COMPLETED	1
#define	INIT_NOT_COMPLETED 0

#define GETBIT	1


#define MOVE_CURSER_CMD		14
#define DELAY_tick	6

#define DB7	7
#define DB6	6
#define DB5	5
#define DB4	4
#define DB3	3
#define DB2	2
#define DB1	1
#define DB0	0


typedef enum {
		s1 ,
		s2 ,
		s3 ,
		s4,
		s5
	}initState_t;


typedef enum {
		idle_proc ,
		write_proc ,
		cmd_proc,
	}process_t;

	static u8 userWord[255] ;
	static u8 userWordLen;
	static u8 userCommand;
	//static u8 isWriteReq;
	static u8 userXposition;
	static u8 userYposition;
	static u8 initCompleteFlag = INIT_NOT_COMPLETED;


static process_t currentProcess ;
static initState_t currentInitState;
	GPIO_pinType lcd_control_pins[NO_CONTROL_PINS]={
			{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_RS_PORT,LCD_RS_PIN,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_RW_PORT,LCD_RW_PIN,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_E_PORT,LCD_E_PIN,ZERO_VALUE}
	};

	GPIO_pinType lcd_data_pins[NO_DATA_PINS]={
			{GPIO_GPOUT_PP_MODE,PINS_SPEED, LCD_D0_PIN,LCD_D0_PORT,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_D1_PIN,LCD_D1_PORT,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_D2_PIN,LCD_D2_PORT,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_D3_PIN,LCD_D3_PORT,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_D4_PIN,LCD_D4_PORT,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_D5_PIN,LCD_D5_PORT,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_D6_PIN,LCD_D6_PORT,ZERO_VALUE}
			,{GPIO_GPOUT_PP_MODE,PINS_SPEED,LCD_D7_PIN,LCD_D7_PORT,ZERO_VALUE}
	};




void LCD_init(void)
{
	u8 index;
	for(index=0; index<NO_DATA_PINS; index++)
	{
		GPIO_configPins(&lcd_data_pins[index]);
	}
	for(index=0; index<NO_CONTROL_PINS; index++)
	{
		GPIO_configPins(&lcd_control_pins[index]);
	}
	currentProcess = idle_proc;
	currentInitState =s1;
}

Status_t lcd_applyCommand(u8 cmd)
{
	Status_t status;
	if(currentProcess == idle_proc){
		userCommand = cmd;
		currentProcess = cmd_proc;
		status = STATUS_OK;
	}else{
		status = STATUS_BUSY;
	}

	return status;
}

Status_t LCD_writeString(const u8 * word, u8 length)
{
	Status_t status;
	u8 index;
	if(currentProcess == idle_proc){
		for(index =0; index<length; index++){
			userWord[index]=word[index];
		}
		userWordLen=length;
		currentProcess = write_proc;
		status = STATUS_OK;
	}else{
		status = STATUS_BUSY;
	}
	return status;
}
/*
Status_t LCD_moveXY(u8 x, u8 y)
{
	Status_t status;
	if(currentProcess == idle_proc){
		userXposition = x;
		userYposition = y;

		userCommand =	MOVE_CURSER_CMD;
		currentProcess = cmd_proc;
		status = STATUS_OK;
	}else{
		status = STATUS_BUSY;
	}
	return status;
}
*/

void LCD_runnable(void)
{
	if(initCompleteFlag)
	{
		switch(currentProcess)
		{
		case idle_proc:
		break;
		case write_proc:
			LCD_8bitWriteProcess();
		break;
		case cmd_proc:
			LCD_8bitCMDProcess();
		break;

		}
	}
	else{
		LCD_8bitInitProcess();
	}
}


static void LCD_8bitInitProcess(void)
{
	static u8 counter =0;
	switch(currentInitState)
	{
	case s1:
		counter ++;

		if(counter >= DELAY_tick)
		{
			counter =0;
			currentInitState= s2;
		}
		break;
	case s2:
		lcd_control_pins[RS].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RS]);
		lcd_control_pins[RW].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RW]);
		lcd_control_pins[DB7].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB7]);
		lcd_control_pins[DB6].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB6]);
		lcd_control_pins[DB5].value=ONE_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB5]);
		lcd_control_pins[DB4].value=ONE_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB4]);
		lcd_control_pins[DB3].value=NUMBER_OF_LINES;
		GPIO_setPinValue(&lcd_control_pins[DB3]);
		lcd_control_pins[DB2].value=FONT;
		GPIO_setPinValue(&lcd_control_pins[DB2]);
		lcd_control_pins[DB1].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB1]);
		lcd_control_pins[DB0].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB0]);

		currentInitState= s3;
		break;
	case s3:
		lcd_control_pins[RS].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RS]);
		lcd_control_pins[RW].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RW]);
		lcd_control_pins[DB7].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB7]);
		lcd_control_pins[DB6].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB6]);
		lcd_control_pins[DB5].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB5]);
		lcd_control_pins[DB4].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB4]);
		lcd_control_pins[DB3].value=ONE_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB3]);
		lcd_control_pins[DB2].value=DISPLAY;
		GPIO_setPinValue(&lcd_control_pins[DB2]);
		lcd_control_pins[DB1].value=CURSER;
		GPIO_setPinValue(&lcd_control_pins[DB1]);
		lcd_control_pins[DB0].value=BLINKING;
		GPIO_setPinValue(&lcd_control_pins[DB0]);

		currentInitState= s4;
		break;
	case s4:
		lcd_control_pins[RS].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RS]);
		lcd_control_pins[RW].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RW]);
		lcd_control_pins[DB7].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB7]);
		lcd_control_pins[DB6].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB6]);
		lcd_control_pins[DB5].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB5]);
		lcd_control_pins[DB4].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB4]);
		lcd_control_pins[DB3].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB3]);
		lcd_control_pins[DB2].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB2]);
		lcd_control_pins[DB1].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB1]);
		lcd_control_pins[DB0].value=ONE_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB0]);

		currentInitState= s5;
		break;
	case s5:
		lcd_control_pins[RS].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RS]);
		lcd_control_pins[RW].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RW]);
		lcd_control_pins[DB7].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB7]);
		lcd_control_pins[DB6].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB6]);
		lcd_control_pins[DB5].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB5]);
		lcd_control_pins[DB4].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB4]);
		lcd_control_pins[DB3].value=ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB3]);
		lcd_control_pins[DB2].value=ONE_VALUE;
		GPIO_setPinValue(&lcd_control_pins[DB2]);
		lcd_control_pins[DB1].value=INC_MODE;
		GPIO_setPinValue(&lcd_control_pins[DB1]);
		lcd_control_pins[DB0].value=DISPLAY_SHIFT_OPERATION;
		GPIO_setPinValue(&lcd_control_pins[DB0]);

		initCompleteFlag = INIT_COMPLETED;
	}
}


static void LCD_8bitCMDProcess(void)
{

	if(lcd_control_pins[E].value)
	{
		lcd_control_pins[E].value =ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[E]);
		currentProcess = idle_proc;
	}
	else
	{
		lcd_control_pins[RS].value =ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RS]);
		lcd_control_pins[RW].value =ZERO_VALUE;
		GPIO_setPinValue(&lcd_control_pins[RW]);

		lcd_control_pins[DB7].value =(GETBIT&(userCommand>>DB7));
		GPIO_setPinValue(&lcd_control_pins[DB7]);

		lcd_control_pins[DB6].value =(GETBIT&(userCommand>>DB6));
		GPIO_setPinValue(&lcd_control_pins[DB6]);

		lcd_control_pins[DB5].value =(GETBIT&(userCommand>>DB5));
		GPIO_setPinValue(&lcd_control_pins[DB5]);

		lcd_control_pins[DB4].value =(GETBIT&(userCommand>>DB4));
		GPIO_setPinValue(&lcd_control_pins[DB4]);

		lcd_control_pins[DB3].value =(GETBIT&(userCommand>>DB3));
		GPIO_setPinValue(&lcd_control_pins[DB3]);

		lcd_control_pins[DB2].value =(GETBIT&(userCommand>>DB2));
		GPIO_setPinValue(&lcd_control_pins[DB2]);

		lcd_control_pins[DB1].value =(GETBIT&(userCommand>>DB1));
		GPIO_setPinValue(&lcd_control_pins[DB1]);

		lcd_control_pins[DB0].value =(GETBIT&(userCommand>>DB0));
		GPIO_setPinValue(&lcd_control_pins[DB0]);

		lcd_control_pins[E].value =ONE_VALUE;
		GPIO_setPinValue(&lcd_control_pins[E]);
	}
}


static void LCD_8bitWriteProcess(void){

	static u8 currentChar=0;

		if(lcd_control_pins[E].value)
		{
			lcd_control_pins[E].value =ZERO_VALUE;
			GPIO_setPinValue(&lcd_control_pins[E]);

			if(userWordLen ==currentChar)
						{
							currentProcess =idle_proc;
							currentChar =0;
						}
		}
		else
		{

			lcd_control_pins[RS].value =ONE_VALUE;
			GPIO_setPinValue(&lcd_control_pins[RS]);
			lcd_control_pins[RW].value =ZERO_VALUE;
			GPIO_setPinValue(&lcd_control_pins[RW]);

			lcd_control_pins[DB7].value =(GETBIT&(userWord[currentChar]>>DB7));
			GPIO_setPinValue(&lcd_control_pins[DB7]);

			lcd_control_pins[DB6].value =(GETBIT&(userWord[currentChar]>>DB6));
			GPIO_setPinValue(&lcd_control_pins[DB6]);

			lcd_control_pins[DB5].value =(GETBIT&(userWord[currentChar]>>DB5));
			GPIO_setPinValue(&lcd_control_pins[DB5]);

			lcd_control_pins[DB4].value =(GETBIT&(userWord[currentChar]>>DB4));
			GPIO_setPinValue(&lcd_control_pins[DB4]);

			lcd_control_pins[DB3].value =(GETBIT&(userWord[currentChar]>>DB3));
			GPIO_setPinValue(&lcd_control_pins[DB3]);

			lcd_control_pins[DB2].value =(GETBIT&(userWord[currentChar]>>DB2));
			GPIO_setPinValue(&lcd_control_pins[DB2]);

			lcd_control_pins[DB1].value =(GETBIT&(userWord[currentChar]>>DB1));
			GPIO_setPinValue(&lcd_control_pins[DB1]);

			lcd_control_pins[DB0].value =(GETBIT&(userWord[currentChar]>>DB0));
			GPIO_setPinValue(&lcd_control_pins[DB0]);


			lcd_control_pins[E].value =ONE_VALUE;
			GPIO_setPinValue(&lcd_control_pins[E]);

			currentChar ++;

			}
		}

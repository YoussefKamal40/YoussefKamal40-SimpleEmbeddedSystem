/*
 * App2.c
 *
 *  Created on: Apr 9, 2020
 *      Author: Sarah
 */

#include "STD_TYPES_H.h"
#include "LCD_interface.h"

#define MAX_OF_SEC	59
#define MAX_OF_MIN	59
#define MAX_OF_HR	23
#define MAX_CLOCKCOUNT	86399
#define HOURS_SECONDS_ADJUST	3600
#define MINUTE_SECOND_ADJUST	60
#define JAN			 31
#define	FEB          30
#define	MAR        31
#define	APR        30
#define	MAY          31
#define	JUN         30
#define	JUL         31
#define	AGU        31
#define	SEP         30
#define OCT          31
#define NOV          30
#define DEC          31
//jan,mar,may,july,oct,dec,ogust
#define NO_MONTH		12
#define ARRAY_OFFSET	1
#define SECOND_BYTE		8
static u32 seconds,minutes,hours;

const u8 max_month_days[NO_MONTH]={  JAN
									,FEB
									,MAR
									,APR
									,MAY
									,JUN
									,JUL
									,AGU
									,SEP
									,OCT
									,NOV
									,DEC};


const u8* month_str[NO_MONTH]={   "JAN"
								,"FEB"
								,"MAR"
								,"APR"
								,"MAY"
								,"JUNE"
								,"JULY"
								,"AGU"
								,"SEP"
								,"OCT"
								,"NOV"
								,"DEC" };

static void * rowDataPtr;

void App2_runnable(void)
{
	clockupdate();
}
void DateUpdate(void)
{
		days++;
		if(days >max_month_days[months-ARRAY_OFFSET])
		{
			days=1;
		}
}

static void ClockUpdate1(void)
{
	static u8 sFlag;
	u32 clockCount;
	u32 temp;
		if(sFlag)
		{
			clockCount++;
			if(clockCount>MAX_CLOCKCOUNT)
			{
				clockCount=0;
				DateUpdate();
			}
			sFlag =0;
		}
		else
		{
			sFlag=1;
		}
	hours=(u8)(clockCount/HOURS_SECONDS_ADJUST);
	temp=clockCount-(HOURS_SECONDS_ADJUST*hours);
	minutes=temp/MINUTE_SECOND_ADJUST;
	temp=temp/MINUTE_SECOND_ADJUST;
	seconds=temp -(MINUTE_SECOND_ADJUST*minutes);
}

void clockupdate(void)

{
	static u8 sFlag;
		if(sFlag)
		{
			seconds++;
			if(seconds>MAX_OF_SEC)
			{	seconds=0;
				minutes++;
				if(minutes>MAX_OF_MIN)
				{	minutes=0;
					hours++;
					if(hours>MAX_OF_HR)
					{
						hours=0;
					}
				}
			}
			sFlag=0;
		}
		else{
			sFlag =1;
		}
}

/*
void cb_clock(void)
{
	u8 sec=((u16*)rowDataPtr)[0];
	u8 min=(((u16*)rowDataPtr)[0])>>8;
	u8 hour=((u16*)rowDataPtr)[1];

	Queue(lcdnumberprinting,hour);
	Queue(LCD_writeString,colon);
	Queue(lcdnumberprinting,min);
	Queue(LCD_writeString,colon);
	Queue(lcdnumberprinting,sec);
}
*/




/**************************LCD_Qwarping********************************************************/
Status_t LCD_QmoveXY(u32 coord )
{
	u8 x=(u8)coord;
	u8 y=(u8)(coord>>SECOND_BYTE);
	return LCD_moveXY(x,y);
}

Status_t LCD_writeString(u32 word)
{

}
Status_t LCD_applyCommand(u8 cmd);
Status_t LCD_curserConterol(u8 cursermode);
Status_t LCD_numberprinting(u32 num);
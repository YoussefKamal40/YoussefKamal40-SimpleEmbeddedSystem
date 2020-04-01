/*
 * Schedular_program.c
 *
 *  Created on: Mar 30, 2020
 *      Author: Esraa
 */
#include "stdint.h"
#include "systemClockHandler_interface.h"
#include"Schedular_config.h"
#include "Schedular_interface.h"
#include "SysTick.h"

#define STATE_RUNNING     1
#define STATE_SUSPENDED   0

extern  taskConfig_t sysTaskConfig[NUMBER_OF_TASKS];

typedef struct
{
	const taskConfig_t *taskConfig;
	uint32_t periodicityinTicks;
	uint32_t ticksToExecute;
	uint32_t state;
}sysTask_t;

sysTask_t sysTask[NUMBER_OF_TASKS];

static uint32_t iterator;
static uint8_t OS_Flag;

static void Sched_setOsFlag (void);

void Sched_setOsFlag (void)
{
	OS_Flag=1;
}

void Sched_init(void)
{
    uint32_t input_clock;
	for(iterator=0; iterator< NUMBER_OF_TASKS ; iterator++)
	{
		sysTask[iterator].taskConfig = &sysTaskConfig[iterator];
		sysTask[iterator].periodicityinTicks = sysTaskConfig[iterator].periodicity_us /TICK_TIME_US;
		sysTask[iterator].ticksToExecute = sysTaskConfig[iterator].firstDelayInTick;
		sysTask[iterator].state = STATE_RUNNING;
	}
	SysTick_init();
	SysTick_setCallBack(Sched_setOsFlag);
	input_clock = SYS_HAN_getAHBClock();
	SysTick_setTime(TICK_TIME_US,input_clock);
}

void Sched(void)
{
	for(iterator=0 ;iterator< NUMBER_OF_TASKS ; iterator++)
	{
		if(sysTask[iterator].ticksToExecute== 0 && sysTask[iterator].state==STATE_RUNNING)
		{
			sysTask[iterator].taskConfig->taskRunnable() ;
			sysTask[iterator].ticksToExecute = sysTask[iterator].periodicityinTicks;
		}
		sysTask[iterator].ticksToExecute --;
	}
}

void Sched_start(void)
{
	SysTick_start();
	while(1)
	{
		if(OS_Flag)
		{
			OS_Flag =0;
			Sched();
		}
	}
}

void Sched_suspend(void)
{
	sysTask[iterator].state = STATE_SUSPENDED;
}

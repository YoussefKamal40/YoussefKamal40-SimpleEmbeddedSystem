/*
 * Schedular_program.c
 *
 *  Created on: Mar 30, 2020
 *      Author: Esraa
 */
#include "stdint.h"
#include "STD_TYPES_H.h"
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

static uint32_t CurrentTaskIndex;
static uint8_t OS_Flag;

static void Sched_setOsFlag (void);
static void Sched(void);

void Sched_setOsFlag (void)
{
	OS_Flag=1;
}

void Sched_init(void)
{
    uint32_t input_clock;
	for(CurrentTaskIndex=0; CurrentTaskIndex< NUMBER_OF_TASKS ; CurrentTaskIndex++)
	{
		sysTask[CurrentTaskIndex].taskConfig = &sysTaskConfig[CurrentTaskIndex];
		sysTask[CurrentTaskIndex].periodicityinTicks = sysTaskConfig[CurrentTaskIndex].periodicity_us /TICK_TIME_US;
		sysTask[CurrentTaskIndex].ticksToExecute = sysTaskConfig[CurrentTaskIndex].firstDelayInTick;
		sysTask[CurrentTaskIndex].state = STATE_RUNNING;
	}
	SysTick_init();
	SysTick_setCallBack(Sched_setOsFlag);
	input_clock = SYS_HAN_getSystemClock();
	SysTick_setTime(TICK_TIME_US,input_clock);
}

void Sched(void)
{
	for(CurrentTaskIndex=0 ;CurrentTaskIndex< NUMBER_OF_TASKS ; CurrentTaskIndex++)
	{
		if(sysTask[CurrentTaskIndex].ticksToExecute== 0 && sysTask[CurrentTaskIndex].state==STATE_RUNNING)
		{
			sysTask[CurrentTaskIndex].taskConfig->taskRunnable() ;
			sysTask[CurrentTaskIndex].ticksToExecute = sysTask[CurrentTaskIndex].periodicityinTicks;
		}
		sysTask[CurrentTaskIndex].ticksToExecute --;
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
	sysTask[CurrentTaskIndex].state = STATE_SUSPENDED;
}

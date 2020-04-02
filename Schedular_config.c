/*
 * Schedular_config.c
 *
 *  Created on: Mar 30, 2020
 *      Author: Esraa
 */
#include "stdint.h"
#include "Schedular_interface.h"
#include "Schedular_config.h"

extern void LCD_runnable(void);
void HSWITCH_debounce_runnable(void);
void counterApp_runnable(void);

const taskConfig_t sysTaskConfig[NUMBER_OF_TASKS]=
{
	{.taskRunnable=&HSWITCH_debounce_runnable,.periodicity_us=5000,.firstDelayInTick=0},
	{.taskRunnable=&LCD_runnable,.periodicity_us=5000,.firstDelayInTick=0},
	{.taskRunnable=&counterApp_runnable,.periodicity_us=5000,.firstDelayInTick=0}
};




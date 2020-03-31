/*
 * HSWITCH.C
 *
 *  Created on: Mar 25, 2020
 *      Author: Sarah
 */

#include "STD_TYPES_H.h"
#include "SwitchHandler_interface.h"
#include "SwitchHandler_config.h"
#include "GPIO_Interface.h"

u8 state_global[NO_SWITCHES];
GPIO_pinType GPIOs[NO_SWITCHES];

extern switch_type switches[NO_SWITCHES];

u8 HSWITCH_getState(u8 switch_index)
{	u8 state;
	if((switches[switch_index].active_state == ACTIVE_LOW))
	{
		 state = 1^state_global[switch_index];
	}
	else
	{
		 state = state_global[switch_index];
	}
	return state;
}

void HSWITCH_init(void)
{
	u8 index;
	for(index=0 ; index<NO_SWITCHES ;index++ )
	{
		GPIOs[index].pin = switches[index].pin;
		GPIOs[index].port = switches[index].port;
		GPIOs[index].mode = switches[index].mode;
		GPIOs[index].speed=GPIO_10M_SPEED;
		GPIO_configPins(&GPIOs[index]);
	}
}


void HSWITCH_debounce_runnable(void)
{
	static u8 prev_state[NO_SWITCHES];
	static u8 counter[NO_SWITCHES];
	u8 current_state;
	u8 index;
	for(index=0 ;index<NO_SWITCHES ;index ++)
	{
		GPIO_getPinValue(&GPIOs[index]);
		current_state = GPIOs[index].value;

		if(current_state == prev_state[index])
		{
			(counter[index])++;
		}
		else
		{
			counter[index]=0;
		}

		if(counter[index] == DEBOUNCE_TIMEOUT)
		{
		state_global[index] = current_state;
		counter[index] = 0;
		prev_state[index] =current_state;
		}

	}
}

/*
 * HSWITCH_config.c
 *
 *  Created on: Mar 25, 2020
 *      Author: LENOVO.SXM1
 */

#include "STD_TYPES_H.h"
#include "GPIO_Interface.h"
#include "HSWITCH_interface.h"
#include "HSWITCH_config.h"

switch_type switches[NO_SWITCHES]={
		{
				MODE_OUTPUT_PULL_UP,
				ACTIVE_LOW,
				PORTA,PIN0
		},
		{
				MODE_OUTPUT_PULL_UP,
				ACTIVE_HIGH,
				PORTA,
				PIN0
		},
		{
				MODE_OUTPUT_PULL_UP,

				32,
				PORTA,
				PIN0
		}
	};

/*
 * HSWITCH_config.c
 *
 *  Created on: Mar 25, 2020
 *      Author: LENOVO.SXM1
 */

#include "STD_TYPES_H.h"
#include "GPIO_Interface.h"
#include "HSWITCH_config.h"
#include "HSWITCH_interface.h"


switch_type switches[NO_SWITCHES]={
		{
				MODE_PULL_UP_ACTIVE_LOW,
				PIN0,
				PORTA
		},
		{
				MODE_PULL_UP_ACTIVE_LOW,
				PIN0,
				PORTA
		},
		{
				MODE_PULL_UP_ACTIVE_LOW,
				PIN0,
				PORTA
		}
	};

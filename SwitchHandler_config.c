/*
 * SwitchHandler_config.c
 *
 *  Created on: Mar 30, 2020
 *      Author: LENOVO.SXM1
 */

#include "STD_TYPES_H.h"
#include "GPIO_Interface.h"
#include "SwitchHandler_interface.h"
#include "SwitchHandler_config.h"

switch_type switches[NO_SWITCHES]={
		{
				MODE_INPUT_PULL_UP,
				ACTIVE_HIGH,
				PORTA,
				PIN11
		}

	};





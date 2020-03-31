/*
 * Schedular_config.c
 *
 *  Created on: Mar 30, 2020
 *      Author: Esraa
 */
#include "stdint.h"
#include "Schedular_interface.h"
#include "Schedular_config.h"




extern taskConfig_t Esraa_task;
extern taskConfig_t soso_task;

const taskConfig_t *sysTaskConfig[NUMBER_OF_TASKS]={&Esraa_task,&soso_task};




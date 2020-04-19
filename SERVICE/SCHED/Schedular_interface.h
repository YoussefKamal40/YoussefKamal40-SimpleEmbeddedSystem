/*
 * Schedular_interface.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Esraa
 */

#ifndef SCHEDULAR_INTERFACE_H_
#define SCHEDULAR_INTERFACE_H_

typedef void (*taskRunable_t)(void);

typedef struct
{
	taskRunable_t taskRunnable;
	uint32_t periodicity_us;
	uint32_t firstDelayInTick;
}taskConfig_t;


extern void Sched_init(void);
extern void Sched_start(void);
extern void Sched_suspend(void);


#endif /* SCHEDULAR_INTERFACE_H_ */

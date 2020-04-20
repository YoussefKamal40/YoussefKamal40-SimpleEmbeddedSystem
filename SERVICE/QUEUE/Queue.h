/*
 * Queue.h
 *
 *  Created on: Apr 15, 2020
 *      Author: LENOVO.SXM1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "Queue_config.h"


void queue_init(void);
u8 queue( element_t element);
u8 dequeue(element_t * element);
u8 peak(element_t * element);
u8 dequeue_func(void);

#endif /* QUEUE_H_ */

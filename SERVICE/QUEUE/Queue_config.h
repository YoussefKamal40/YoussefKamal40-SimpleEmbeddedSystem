/*
 * Queue_config.h
 *
 *  Created on: Apr 17, 2020
 *      Author: LENOVO.SXM1
 */

#ifndef QUEUE_CONFIG_H_
#define QUEUE_CONFIG_H_

typedef struct{
		u8 (*func)(u32);
		u32 arg;
}element_t;

#define SIZE_OF_QUEUE	3

#endif /* QUEUE_CONFIG_H_ */

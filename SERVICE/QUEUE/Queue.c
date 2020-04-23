/*
 * Queue.c
 *
 *  Created on: Apr 15, 2020
 *      Author: LENOVO.SXM1
 */

#include "../../LIB/STD_TYPES_H.h"
#include "Queue.h"
#include "Queue_config.h"

#define EMPTY_QUEUE 0

struct {
	element_t *queue;
	u8 Q_head;
	u8 Q_tail;
	u8 Q_size;
	u8 Q_numberOfElements;
}Q;

element_t elements[SIZE_OF_QUEUE];

void queue_init(void)
{
	Q.Q_head=0;
	Q.Q_tail =0;
	Q.Q_numberOfElements=0;
	Q.Q_size=SIZE_OF_QUEUE;
}

u8 queue( element_t element)
{
	u8 local_error=OK;
	if(Q.Q_numberOfElements == SIZE_OF_QUEUE)
	{
		local_error= NOK;
	}
	else if(Q.Q_head == (SIZE_OF_QUEUE-1))
	{
		Q.queue[Q.Q_head]=element;
		Q.Q_head=0;

	}
	else
	{
		Q.queue[Q.Q_head]=element;
		Q.Q_head++;
	}

	return local_error;

}

u8 dequeue(element_t * element)
{
	u8 local_error=OK;
	if(Q.Q_numberOfElements == EMPTY_QUEUE)
	{
		local_error= NOK;
	}
	else
	{
		*element =Q.queue[Q.Q_tail];
		if(Q.Q_tail == (SIZE_OF_QUEUE-1))
		{
			Q.Q_tail=0;
		}
		else
		{
			Q.Q_tail++;
		}
	}
	return local_error;
}

u8 peak(element_t * element)
{
	u8 local_error=OK;
	if(Q.Q_numberOfElements == EMPTY_QUEUE)
	{
		local_error= NOK;
	}
	else
	{
		*element =Q.queue[Q.Q_tail];
	}
	return local_error;
}


u8 dequeue_func(void)
{
	u8 local_error=OK;
	element_t element;
	if(peak(&element))
	{
		local_error = NOK;
	}
	else
	{

		if(( element.func(element.arg)))
		{
			 dequeue(&element);
		}
		else
		{
			local_error = NOK;
		}

	}
	return local_error;
}

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
	elemt_t *queue;
	u8 Q_top;
	u8 Q_buttom;
	u8 Q_size;
	u8 Q_numberOfElements;
}Q;

elemt_t elements[SIZE_OF_QUEUE];

void queue_init(void)
{
	Q.Q_top=0;
	Q.Q_buttom =0;
	Q.Q_numberOfElements=0;
	Q.Q_size=SIZE_OF_QUEUE;
}

u8 queue( elemt_t element)
{
	u8 local_error=OK;
	if(Q.Q_numberOfElements == SIZE_OF_QUEUE)
	{
		local_error= NOK;
	}
	else if(Q.Q_top == (SIZE_OF_QUEUE-1))
	{
		Q.queue[Q.Q_top]=element;
		Q.Q_top=0;

	}
	else
	{
		Q.queue[Q.Q_top]=element;
		Q.Q_top++;
	}

	return local_error;

}

u8 dequeue(elemt_t * element)
{
	u8 local_error=OK;
	if(Q.Q_numberOfElements == EMPTY_QUEUE)
	{
		local_error= NOK;
	}
	else
	{
		*element =Q.queue[Q.Q_buttom];
		if(Q.Q_buttom == (SIZE_OF_QUEUE-1))
		{
			Q.Q_buttom=0;
		}
		else
		{
			Q.Q_buttom++;
		}
	}
	return local_error;
}

u8 peak(elemt_t * element)
{
	u8 local_error=OK;
	if(Q.Q_numberOfElements == EMPTY_QUEUE)
	{
		local_error= NOK;
	}
	else
	{
		*element =Q.queue[Q.Q_buttom];
	}
	return local_error;
}


u8 dequeue_func(void)
{
	u8 local_error=OK,status;
	elemt_t element;
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

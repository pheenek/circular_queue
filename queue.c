/**
 * @file 		queue.h 
 * 
 * @author 		Stephen Muriithi (stevek.muriithi@gmail.com) 
 * 
 * @brief	 	This module defines a circular queue buffer. The circular buffer eases
 * 				reading and writing data to and from the peripherals.
 * 				This header provides the definitions for the queue.
 * 
 * @version 	0.1 
 * 
 * @date 		2022-02-19
 * 
 * ***************************************************************************
 * @copyright Copyright (c) 2022 by Stephen Muriithi
 * This software is copyrighted by and is the sole property of Stephen Muriithi
 * All rights, title, ownership, or other interests
 * in the software remain the property of Stephen Muriithi
 * 
 * This software may only be used in accordance with the corresponding
 * license agreement.  Any unauthorized use, duplication, transmission,
 * distribution, or disclosure of this software is expressly forbidden.
 * 
 * This Copyright notice may not be removed or modified without prior
 * written consent of Stephen Muriithi.
 * 
 * Stephen Muriithi reserves the right to modify this software
 * without notice
 * 
 * Stephen Muriithi
 * ***************************************************************************
 * 
 */

#include "queue.h"

/**
 * @brief   This function is used to initialize the queue with the specified size.
 * 
 * @param   q -> The queue to be initialised
 */
// #define Q_INIT(q) q.head = q.tail = 0
void q_init(Q *q)
{
	q->head = 0;
	q->tail = 0;
	q->len = 0;
	q->elements = malloc(DEFAULT_QUEUE_SIZE);

	if (q->elements) q->size = DEFAULT_QUEUE_SIZE;
}

/**
 * @brief   Defines the queue length.
 * 
 * @param   q -> The queue to be examined
 */
// #define Q_LEN(q) ((q.tail) - (q.head))
uint16_t q_len(Q *q)
{
	return (q->len);
}

/**
 * @brief   This function is used to check if the queue specified is empty
 * 
 * @param   q   -> The queue to be checked
 * @return  
 *      true The queue is empty
 *      false The queue is not empty
 */
// #define Q_IS_EMPTY(q) (Q_LEN(q) == 0)
uint8_t q_is_empty(Q *q)
{
	return (q->len == 0);
}

/**
 * @brief   This function is used to check if the queue specified is full
 * 
 * @param   q -> The queue to be checked
 * @return  true The queue is full
 * @return  false The queue is not full
 */
// #define Q_IS_FULL(q) (Q_LEN(q) == DEFAULT_QUEUE_SIZE)
uint8_t q_is_full(Q *q)
{
	return (q->len == q->size);
}

/**
 * @brief	 Defines the remaining capacity in the queue
 * 
 * @param	q -> The queue to be examined
 */
// #define Q_REMAINING_CAPACITY(q) ((DEFAULT_QUEUE_SIZE) - Q_LEN(q))
uint16_t q_remaining_capacity(Q *q)
{
	return (q->size - q->len);
}

/**
 * @brief	 Doubles the size of the queue.
 * 			Called when the queue is full, and more data is to be pushed to it
 * 
 * @param q 
 * 
 * @return none
 */
void q_resize(Q *q)
{
	uint8_t *newArray = malloc(q->size * 2);
	uint16_t len = q->len;
	for (uint16_t i = 0; i < len; i++)
	{
		newArray[i] = q->elements[(q->head + i) % q->size];
	}

	free(q->elements);

	q->elements = newArray;
	q->head = 0;
	q->tail = len;
	q->len = len;
	q->size = q->size * 2;
	
}

/**
 * @brief   This function is used to push an element onto the queue
 *          An element can be pushed if the queue is not full
 * 
 * @param   q -> The queue to which an element should be pushed
 * @param   e -> The element to be pushed onto the queue
 */
// #define Q_PUSH(q, e) (q.elements)[q.tail++ & (DEFAULT_QUEUE_SIZE)] = e
void q_push(Q *q, uint8_t e)
{
	if (q_is_full(q))
	{
		q_resize(q);
	}
	
	q->elements[q->tail] = e;
	q->tail = ((q->tail + 1) % q->size);
	q->len++;
}

/**
 * @brief   This function is used to pop an element from a queue.
 *          An element can be popped if the queue is not empty
 * 
 * @param   q -> The queue from which an element should be popped
 * @return  uint8_t -> The element popped from the queue 
 */
// #define Q_POP(q) (q.elements)[q.head++ & (DEFAULT_QUEUE_SIZE)]
uint8_t q_pop(Q *q)
{
	uint8_t element = q->elements[q->head];
	q->head = ((q->head + 1) % q->size);
	q->len--;
	
	if (q_is_empty(q) && (q->size > DEFAULT_QUEUE_SIZE))
	{
		q->elements = realloc(q->elements, DEFAULT_QUEUE_SIZE);
		q->size = DEFAULT_QUEUE_SIZE;
	}

	return element;
}

/**
 * @brief	This function is used to clear the queue contents.
 * 			All elements currently in the queue are discarded
 * 
 * @param q -> The queue to be modified.
 * 
 * @return none
 */
void q_delete(Q *q)
{
	free(q->elements);
	q_init(q);
}

/**
 * @brief	 This function is used to check for the contents of the queue
 * 			at the specified index without modifying the queue
 * 
 * @param q 
 * @param index
 * 
 * @return none
 */
uint8_t q_peek(Q *q, uint16_t index)
{
	return q->elements[((q->head + index) & (q->size - 1))];
}

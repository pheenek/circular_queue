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

#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

/**
 * Possible values: 64, 128, 256, 512, etc.
 */
#define DEFAULT_QUEUE_SIZE    128 /*< Defines the size of a uart rx/tx buffer */

/**
 * @brief   Defines the structure of the queue (circular buffer) to be used in storing
 *          data when reading/writing to/from the uart peripheral.
 * 
 */
typedef struct {
    uint16_t head;
    uint16_t tail;
	uint16_t len;
    uint8_t *elements;
	uint16_t size;
} Q;

/**
 * @brief   This function is used to initialize the queue with the specified size.
 * 
 * @param   q -> The queue to be initialised
 */
void q_init(Q *q);

/**
 * @brief   Defines the queue length.
 * 
 * @param   q -> The queue to be examined
 */
uint16_t q_len(Q *q);

/**
 * @brief   This function is used to check if the queue specified is empty
 * 
 * @param   q   -> The queue to be checked
 * @return  
 *      true The queue is empty
 *      false The queue is not empty
 */
uint8_t q_is_empty(Q *q);

/**
 * @brief   This function is used to check if the queue specified is full
 * 
 * @param   q -> The queue to be checked
 * @return  true The queue is full
 * @return  false The queue is not full
 */
uint8_t q_is_full(Q *q);

/**
 * @brief	 Defines the remaining capacity in the queue
 * 
 * @param	q -> The queue to be examined
 */
uint16_t q_remaining_capacity(Q *q);

/**
 * @brief   This function is used to push an element onto the queue
 *          An element can be pushed if the queue is not full
 * 
 * @param   q -> The queue to which an element should be pushed
 * @param   elememnt -> The element to be pushed onto the queue
 */
void q_push(Q *q, uint8_t e);

/**
 * @brief   This function is used to pop an element from a queue.
 *          An element can be popped if the queue is not empty
 * 
 * @param   q -> The queue from which an element should be popped
 * @return  uint8_t -> The element popped from the queue 
 */
uint8_t q_pop(Q *q);

/**
 * @brief	This function is used to clear the queue contents.
 * 			All elements currently in the queue are discarded
 * 
 * @param q -> The queue to be modified.
 * 
 * @return none
 */
void q_delete(Q *q);

/**
 * @brief	 This function is used to check for the contents of the queue
 * 			at the specified index without modifying the queue
 * 
 * @param q 
 * @param index
 * 
 * @return none
 */
uint8_t q_peek(Q *q, uint16_t index);

#ifdef __cplusplus
}
#endif

#endif

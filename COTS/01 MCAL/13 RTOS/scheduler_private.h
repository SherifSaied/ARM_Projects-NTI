/*
 * scheduler_private.h
 *
 *  Created on: May 22, 2023
 *      Author: Sherif Ahmed
 */

#ifndef SCHEDULER_PRIVATE_H_
#define SCHEDULER_PRIVATE_H_

typedef struct
{
	u32 priority;
	u32 priodicity;
	void (*fptr)(void);
}Task;

Task *ptr;


#endif /* SCHEDULER_PRIVATE_H_ */

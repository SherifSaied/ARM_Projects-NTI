/*
 * scheduler_private.h
 *
 *  Created on: May 22, 2023
 *      Author: Sherif Ahmed
 */

#ifndef SCHEDULER_PRIVATE_H_
#define SCHEDULER_PRIVATE_H_

#include "stdTypes.h"
typedef struct
{
	u32 priority;
	u32 priodicity;
	u32 firstDelay;
	void (*fptr)(void);
}task_t;




#endif /* SCHEDULER_PRIVATE_H_ */

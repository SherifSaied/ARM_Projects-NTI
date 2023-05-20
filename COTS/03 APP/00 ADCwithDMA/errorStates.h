/*
 * errorStates.h
 *
 *  Created on: Apr 25, 2023
 *      Author: Sherif Ahmed
 */

#ifndef ERRORSTATES_H_
#define ERRORSTATES_H_
//itt1
/*#define OK 0
#define NOT 1
etc.. so we will use enum as it increases by one and text replacement by num*/

typedef enum
{
	ES_NOK,
	ES_OK,
	ES_NULL_POINTER,
	ES_OUT_OF_RANGE

}ES_t ;       //ErrorState_typedef


#endif /* ERRORSTATES_H_ */

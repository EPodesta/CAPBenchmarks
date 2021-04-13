/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * fh.h - Friendly Numbers kernel library.
 */

#ifndef _FN_H_
#define _FN_H_

#include <stdio.h>

/*
 * Computes friendly numbers.
 */
extern void friendly_numbers();

/*============================================================================*
 * Parameters                                                                 *
 *============================================================================*/

#define PROBLEM_SIZE                                 16383
#define PROBLEM_START_NUM                            	 1
#define PROBLEM_END_NUM      (PROBLEM_START + PROBLEM_SIZE)

/*============================================================================*
 * Kernel                                                                     *
 *============================================================================*/

struct item
{
	int number;
	int num;
	int den;
};


#endif /* _FN_H_ */

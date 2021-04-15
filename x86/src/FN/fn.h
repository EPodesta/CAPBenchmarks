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

#ifdef PAGES32
#define PROBLEM_SIZE                                 10582
#define PROBLEM_START_NUM                            	 1
#endif
#ifdef PAGES42
#define PROBLEM_SIZE                                 13995
#define PROBLEM_START_NUM                            	 1
#endif
#ifdef PAGES48
#define PROBLEM_SIZE                                 16383
#define PROBLEM_START_NUM                            	 1
#endif
#ifdef PAGES64
#define PROBLEM_SIZE                                 21504
#define PROBLEM_START_NUM                            	 1
#endif
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

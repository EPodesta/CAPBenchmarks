/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * gf.h - Gaussian Filter kernel library.
 */

#ifndef _GF_H_
#define _GF_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <util.h>

/*============================================================================*
 * Parameters                                                                 *
 *============================================================================*/

	#define PROBLEM_SEED 0

	#define PROBLEM_MASKSIZE                           7
	#define PROBLEM_IMGSIZE     (399 + PROBLEM_MASKSIZE - 1)
	#define HALF                    (PROBLEM_MASKSIZE / 2)

	#define PROBLEM_IMGSIZE2    (PROBLEM_IMGSIZE*PROBLEM_IMGSIZE)
	#define PROBLEM_MASKSIZE2 (PROBLEM_MASKSIZE*PROBLEM_MASKSIZE)


/*============================================================================*
 * Math                                                                       *
 *============================================================================*/

	/**
	 * @brief Math Constants
	 */
	/**@{*/
	#define PI 3.14159265359    /* pi */
	#define E 2.71828182845904  /* e */
	/**@}*/
	#define __fdiv(a, b) ((a)/(b))

/*============================================================================*
 * Kernel                                                                     *
 *============================================================================*/

	/**
	 * @brief Standard Deviation for Mask
	 */
	#define SD 0.8

	#define MASK(i, j) \
		mask[(i)*PROBLEM_MASKSIZE + (j)]

	#define IMAGE(i, j) \
		img[(i)*PROBLEM_IMGSIZE + (j)]

	#define NEWIMAGE(i, j) \
		newimg[(i)*PROBLEM_IMGSIZE + (j)]
	/*
	 * Gaussian filter.
	 */
	extern void do_kernel(void);

#endif /* _GF_H_ */

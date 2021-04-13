#ifndef _KM_H_
#define _KM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <util.h>

/*============================================================================*
 * Parameters                                                                 *
 *============================================================================*/

	#define PROBLEM_SEED                           0
	#define PROBLEM_LNPOINTS                   (2304)
	#define PROBLEM_NUM_CENTROIDS                512
	#define DIMENSION_MAX                         16
	#define PROBLEM_NUM_POINTS     (PROBLEM_LNPOINTS)

/*============================================================================*
 * Vector                                                                     *
 *============================================================================*/

	extern float vector_distance(float *a, float *b);
	extern float *vector_add(float *v1, const float *v2);
	extern float *vector_mult(float *v, float scalar);
	extern float *vector_assign(float *v1, const float *v2);
	extern int vector_equal(const float *v1, const float *v2);

/*============================================================================*
 * Kernel                                                                     *
 *============================================================================*/

	#define CENTROID(i) \
		(&centroids[(i)*DIMENSION_MAX])

	#define POINT(i) \
		(&points[(i)*DIMENSION_MAX])

	#define POPULATION(i, j) \
		(&population[(i)*PROBLEM_NUM_CENTROIDS + (j)])

	extern void do_kernel();

#endif

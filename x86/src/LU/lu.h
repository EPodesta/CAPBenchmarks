/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * LU.h - Lower Upper kernel library.
 */

#ifndef _LU_H_
#define _LU_H_

/*============================================================================*
 * Parameters                                                                 *
 *============================================================================*/

#ifdef PAGES32
#define PROBLEM_HEIGHT	180
#define PROBLEM_WIDTH   180
#endif
#ifdef PAGES42
#define PROBLEM_HEIGHT	206
#define PROBLEM_WIDTH   206
#endif
#ifdef PAGES48
#define PROBLEM_HEIGHT	220
#define PROBLEM_WIDTH   220
#endif
#ifdef PAGES64
#define PROBLEM_HEIGHT	254
#define PROBLEM_WIDTH   254
#endif

/*
 * Matrix.
 */
struct matrix
{
	int height;      /* Height.   */
	int width;       /* Width.    */
	float *elements; /* Elements. */
};

/*
 * Caster to a matrix pointer.
 */
#define MATRIXP(m) \
	((struct matrix *)(m))

/*
 * Returns the element [i][j] in a matrix.
 */
#define MATRIX(m, i, j)                                 \
	(MATRIXP(m)->elements[(i)*MATRIXP(m)->width + (j)]) \

/*
 * Performs LU factorization in a matrix.
 */
extern int lower_upper(struct matrix *,struct matrix *, struct matrix *);

/*
 * Creates a matrix.
 */
extern struct matrix* matrix_create(int height, int width);

/*
 * Destroys a matrix.
 */
extern void matrix_destroy(struct matrix *);

/*
 * Performs LU factorization.
 */
extern int matrix_lu(struct matrix *, struct matrix *, struct matrix *);

/*
 * Fills up a matrix with random numbers.
 */
extern void matrix_random(struct matrix *);

extern void do_kernel(void);

#endif /* _KM_H_ */

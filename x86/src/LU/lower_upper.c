/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * lu.c - Lower Upper Benchmark Kerkernl.
 */

#include <assert.h>
#include <stdio.h>
#include <global.h>
#include <math.h>
#include <omp.h>
#include <util.h>
#include "lu.h"

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(m != NULL); \
	assert(l != NULL); \
	assert(u != NULL); \

static struct matrix *m;
static struct matrix *l;
static struct matrix *u;

void init_task()
{
	m = matrix_create(PROBLEM_HEIGHT, PROBLEM_WIDTH);
	l = matrix_create(PROBLEM_HEIGHT, PROBLEM_WIDTH);
	u = matrix_create(PROBLEM_HEIGHT, PROBLEM_WIDTH);
	matrix_random(m);
}

/*
 * Swaps two rows of a matrix.
 */
static void _swap_rows(struct matrix *m, int i1, int i2)
{
	int j;     /* Loop index.      */
	float tmp; /* Temporary value. */

	/* Swap columns. */
	for (j = 0; j < m->width; j++)
	{
		tmp = MATRIX(m, i1, j);
		MATRIX(m, i1, j) = MATRIX(m, i2, j);
		MATRIX(m, i2, j) = tmp;
	}
}

/*
 * Swaps two columns in a matrix.
 */
static void _swap_columns(struct matrix *m, int j1, int j2)
{
	int i;     /* Loop index.      */
	float tmp; /* Temporary value. */

	/* Swap columns. */
	for (i = 0; i < m->height; i++)
	{
		tmp = MATRIX(m, i, j1);
		MATRIX(m, i, j1) = MATRIX(m, i, j2);
		MATRIX(m, i, j2) = tmp;
	}
}

/*
 * Finds the pivot element.
 */
static float _find_pivot(struct matrix *m, int i0, int j0)
{
	int i, j;         /* Loop indexes.          */
	int ipvt, jpvt;   /* Pivot indexes.         */
	int pipvt, pjpvt; /* Private pivot indexes. */

	ipvt = i0;
	jpvt = j0;

	pipvt = i0;
	pjpvt = j0;

	/* Find pivot element. */
	for (i = i0; i < m->height; i++)
	{
		for (j = j0; j < m->width; j++)
		{
			/* Found. */
			if (fabs(MATRIX(m, i, j)) < fabs(MATRIX(m,pipvt,pjpvt)))
			{
				pipvt = i;
				pjpvt = j;
			}
		}
	}

	/* Reduct. */
	if (fabs(MATRIX(m, pipvt, pjpvt)) > fabs(MATRIX(m, ipvt, jpvt)))
	{
		ipvt = pipvt;
		jpvt = pjpvt;
	}

	_swap_rows(m, i0, ipvt);
	_swap_columns(m, j0, jpvt);

	return (MATRIX(m, ipvt, jpvt));
}

/*
 * Applies the row reduction algorithm in a matrix.
 */
static void _row_reduction(struct matrix *m, int i0, float pivot)
{
	int j0;      /* Starting column. */
	int i, j;    /* Loop indexes.    */
	float mult;  /* Row multiplier.  */

	j0 = i0;

	/* Apply row redution in some lines. */
	for (i = i0 + 1; i < m->height; i++)
	{
		mult = MATRIX(m, i, j0)/pivot;

		/* Store multiplier. */
		MATRIX(m, i, j0) = mult;

		/* Iterate over columns. */
		for (j = j0 + 1; j < m->width; j++)
			MATRIX(m, i, j) = MATRIX(m, i, j) - mult*MATRIX(m, i0, j);
	}
}

/*
 * Performs LU factorization in a matrix.
 */
int lower_upper(struct matrix *m, struct matrix *l, struct matrix *u)
{
	int i, j;    /* Loop indexes. */
	float pivot; /* Pivot.        */

	/* Apply elimination on all rows. */
	for (i = 0; i < m->height - 1; i++)
	{
		pivot = _find_pivot(m, i, i);

		/* Impossible to solve. */
		if (pivot == 0.0)
		{
			warning("cannot factorize matrix");
			return (-1);
		}

		_row_reduction(m, i, pivot);
	}

	/* Build upper and lower matrixes.  */
	for (i = 0; i < m->height; i++)
	{
		for (j = 0; j < m->width; j++)
		{
			if (i > j)
			{
				MATRIX(u, i, j) = 0.0;
				MATRIX(l, i, j) = MATRIX(m, i, j);
			}

			else if (i < j)
			{
				MATRIX(u, i, j) = MATRIX(m, i, j);
				MATRIX(l, i, j) = 0.0;
			}

			else
			{
				MATRIX(l, i, j) = 1.0;
				MATRIX(u, i, j) = MATRIX(m, i, j);
			}
		}
	}

	return (0);
}

void do_kernel()
{
	init_task();

	lower_upper(m, l, u);

	/* House keeping. */
	matrix_destroy(u);
	matrix_destroy(l);
	matrix_destroy(m);
}

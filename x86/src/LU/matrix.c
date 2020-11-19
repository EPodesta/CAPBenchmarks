/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * matrix.c - Matrix library.
 */

#include <assert.h>
#include <global.h>
#include <util.h>
#include "lu.h"

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK()  \
	assert(height > 0); \
	assert(width > 0);  \

/*
 * Creates a matrix.
 */
struct matrix *matrix_create(int height, int width)
{
	struct matrix *m; /* Matrix.     */

	SANITY_CHECK();

	m = smalloc(sizeof(struct matrix));

	/* Initialize matrix. */
	m->height = height;
	m->width = width;
	m->elements = scalloc(height*width, sizeof(float));

	return (m);
}

#undef SANITY_CHECK

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(m != NULL); \

/*
 * Destroys a matrix.
 */
void matrix_destroy(struct matrix *m)
{
	SANITY_CHECK();

	free(m->elements);

	free(m);
}

#undef SANITY_CHECK

/*
 * Arguments sanity check.
 */
#define SANITY_CHECK() \
	assert(m != NULL); \

/*
 * Fills up a matrix with random numbers.
 */
void matrix_random(struct matrix *m)
{
	int i, j;

	SANITY_CHECK();

	/* Fill matrix. */
	for (i = 0; i < m->height; i++)
	{
		for (j = 0; j < m->width; j++)
			MATRIX(m, i, j) = randnum();
	}
	/* MATRIX(m, 0, 0) = 10; */
	/* MATRIX(m, 0, 1) = 12; */
	/* MATRIX(m, 0, 2) = 15; */
	/* MATRIX(m, 0, 3) = 16; */
	/* MATRIX(m, 0, 4) = 18; */
	/* MATRIX(m, 1, 0) = 8; */
	/* MATRIX(m, 1, 1) = 9; */
	/* MATRIX(m, 1, 2) = 13; */
	/* MATRIX(m, 1, 3) = 23; */
	/* MATRIX(m, 1, 4) = 12; */
	/* MATRIX(m, 2, 0) = 7; */
	/* MATRIX(m, 2, 1) = 3; */
	/* MATRIX(m, 2, 2) = 2; */
	/* MATRIX(m, 2, 3) = 1; */
	/* MATRIX(m, 2, 4) = 0; */
	/* MATRIX(m, 3, 0) = 56; */
	/* MATRIX(m, 3, 1) = 18; */
	/* MATRIX(m, 3, 2) = 34; */
	/* MATRIX(m, 3, 3) = 23; */
	/* MATRIX(m, 3, 4) = 11; */
	/* MATRIX(m, 4, 0) = 45; */
	/* MATRIX(m, 4, 1) = 13; */
	/* MATRIX(m, 4, 2) = 11; */
	/* MATRIX(m, 4, 3) = 10; */
	/* MATRIX(m, 4, 4) = 10; */
}

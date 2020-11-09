/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 */

#include <global.h>
#include <limits.h>
#include <omp.h>
#include <util.h>
#include "is.h"
#include <stdio.h>

static int *task;

void init_task(void)
{
	double num;

	for (int i = 0; i < PROBLEM_SIZE; i++)
	{
		num = normalnum(0, (PROBLEM_MAX >> 4));
		task[i] = (int)((num < 0) ? -num : num) + 1;
	}
}

/*
 * Bucket sort algorithm.
 */
void integer_sort(int *array, int n)
{
	int max, _max;           /* Max number in array. */
	int range;               /* Bucket range.        */
	int i, j, k;             /* Loop indexes.        */
	int *indexes;            /* Index for buckets.   */
	struct darray **buckets; /* Buckets.            */

	indexes = smalloc(NUM_BUCKETS*sizeof(int));

	/* Create buckets. */
	buckets = smalloc(NUM_BUCKETS*sizeof(struct darray *));
	for (i = 0; i < NUM_BUCKETS; i++)
		buckets[i] = darray_create(n/NUM_BUCKETS);

	max = INT_MIN;
	_max = INT_MIN;

	/* Find max number in the array. */
	for (i = 0; i < n; i++)
	{
		/* Found. */
		if (array[i] > _max)
			_max = array[i];
	}

	if (_max > max) {
		max = _max;
	}

	range = max/NUM_BUCKETS;

	/* Distribute numbers into buckets. */
	for (i = 0; i < n; i++)
	{
		j = array[i]/range;
		if (j >= NUM_BUCKETS)
			j = NUM_BUCKETS - 1;

		darray_append(buckets[j], array[i]);
	}

	/* Sort Each bucket. */
	for (i = 0; i < NUM_BUCKETS; i++)
	{
		if (darray_size(buckets[i]) > 0)
			sort(buckets[i]);
	}

	/* Build indexes. */
	indexes[0] = 0;
	for (i = 1; i < NUM_BUCKETS; i++)
		indexes[i] = indexes[i - 1] + darray_size(buckets[i]);

	/* Rebuild array. */
	for (i = 0; i < NUM_BUCKETS; i++)
	{
		k = indexes[i];

		for (j = 0; j < darray_size(buckets[i]); j++)
			array[k + j] = darray_get(buckets[i], j);
	}

	/* House keeping. */
	for (i = 0; i < NUM_BUCKETS; i++)
		darray_destroy(buckets[i]);
	free(buckets);
	free(indexes);
}

void do_kernel(void)
{
	task = malloc(PROBLEM_SIZE*sizeof(int));

	init_task();

	integer_sort(task, PROBLEM_SIZE);

	for ( int i = 0; i < PROBLEM_SIZE; i++)
		printf("%d ", task[i]);

	free(task);
}

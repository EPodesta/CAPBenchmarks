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
	for (int i = 0; i < PROBLEM_SIZE; i++)
		task[i] = randnum() & 0xfffff;
}
/* Rebuilds array. */
static void rebuild_array(struct bucket **done, int *array) {
	int j = 0; 		/* array[] offset. */
	int i;  		/* Loop index.     */

	j = bucket_size(done[0]);
	bucket_merge(done[0], &array[j-1]);

	for (i = 1; i < NUM_BUCKETS; i++) {
		j += bucket_size(done[i]);
		bucket_merge(done[i], &array[j-1]);
	}
}

static void bucketsort(int *array, int n) {
	int max;                  /* Maximum number.      */
	int i, j;                 /* Loop indexes.        */
	int range;                /* Bucket range.        */
	struct minibucket *minib; /* Working mini-bucket. */
	struct bucket **todo;     /* Todo buckets.        */
	struct bucket **done;     /* Done buckets.        */

	todo = smalloc(NUM_BUCKETS*sizeof(struct bucket *));
	done = smalloc(NUM_BUCKETS*sizeof(struct bucket *));

	for (i = 0; i < NUM_BUCKETS; i++) {
		done[i] = bucket_create();
		todo[i] = bucket_create();
	}

	/* Find max number in the array. */
	max = INT_MIN;
	for (i = 0; i < n; i++) {
		/* Found. */
		if (array[i] > max)
			max = array[i];
	}

	/* Distribute numbers. */
	range = max/NUM_BUCKETS;
	for (i = 0; i < n; i++) {
		j = array[i]/range;
		if (j >= NUM_BUCKETS)
			j = NUM_BUCKETS - 1;

		bucket_insert(&todo[j], array[i]);
	}

	/* Sort buckets. */
	for (i = 0; i < NUM_BUCKETS; i++) {
			minib = bucket_pop(todo[i]);
			sort(minib->elements, minib->size);
			bucket_push(done[i], minib);
	}

	rebuild_array(done, array);

	/* House keeping. */
	for (i = 0; i < NUM_BUCKETS; i++) {
		bucket_destroy(todo[i]);
		bucket_destroy(done[i]);
	}
	free(done);
	free(todo);
}

void do_kernel(void)
{
	task = malloc(PROBLEM_SIZE*sizeof(int));

	init_task();

	bucketsort(task, PROBLEM_SIZE);

	free(task);
}

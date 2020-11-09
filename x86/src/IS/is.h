/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * is.h - Integer Sort kernel library.
 */

#ifndef _IS_H_
#define _IS_H_

/*============================================================================*
 * Parameters                                                                 *
 *============================================================================*/

#define PROBLEM_SIZE                               8388608
#define PROBLEM_MAX		                           1 << 20
#define NUM_BUCKETS								   8192

/*=========================================================*
 * Dynamic Array										   *
 *=========================================================*/

struct darray
{
	int size;      /* Current size. */
	int maxsize;   /* Maximum size. */
	int *elements; /* Elements.     */
};

extern void darray_append(struct darray *da, int value);
extern struct darray *darray_create(int size);
extern void darray_destroy(struct darray *da);
extern int darray_get(struct darray *da, int idx);
extern void darray_set(struct darray *da, int idx, int value);
#define darray_size(da) \
	((da)->size)

/*=========================================================*
 * Functions     										   *
 *=========================================================*/
extern void integer_sort(int *array, int n);
extern void sort(struct darray *da);
extern void do_kernel(void);

#endif /* _IS_H_ */

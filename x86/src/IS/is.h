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

#define PROBLEM_SIZE                              8388608
#define NUM_BUCKETS								  256

/*=========================================================*
 * Functions     										   *
 *=========================================================*/

extern void sort(int *a, int n);
extern void do_kernel(void);

/*============================================================================*
 * Mini-Buckets Library														  *
 *============================================================================*/

/*
 * Size of mini-bucket.
 */
#define MINIBUCKET_SIZE 262144

/*
 * Mini-bucket.
 */
struct minibucket
{
	int size;                      /* Current size.               */
	int elements[MINIBUCKET_SIZE]; /* Elements.                   */
	struct minibucket *next;       /* Next mini-bucket in a list. */
};

/*
 * Creates a mini-bucket.
 */
extern struct minibucket *minibucket_create(void);

/*
 * Destroys a mini bucket.
 */
extern void minibucket_destroy(struct minibucket *minib);

/*
 * Asserts if a mini-bucket is empty.
 */
#define minibucket_empty(minib) \
	((minib)->size == 0)

/*
 * Asserts if a bucket is full.
 */
#define minibucket_full(minib) \
	((minib)->size == MINIBUCKET_SIZE)

/*
 * Pushes an item onto a mini-bucket.
 */
#define minibucket_push(minib, x) \
	((minib)->elements[(minib)->size++] = (x))

/*
 * Pops an item from a mini-bucket.
 */
#define minibucket_pop(minib, x) \
	((x) = (minib)->elements[--(minib)->size])

/*
 * Pops an item from a mini-bucket and attributes it inversally.
 */
#define minibucket_pop_inv(minib, x, i) \
	((x) = (minib)->elements[(i)])


/*
 * Returns the top element in a bucket.
 */
#define minibucket_top(minib) \
	((minib)->elements[(minib)->size - 1])

/*
 * Returns the bottom element in a bucket.
 */
#define minibucket_bottom(minib) \
	((minib)->elements[0])

/*============================================================================*
 * Buckets Library															  *
 *============================================================================*/

/*
 * Bucket.
 */
struct bucket
{
	int size;                /* Number of elements.  */
	struct minibucket *head; /* List of mini-buckets.*/
};

/*
 * Creates a bucket.
 */
extern struct bucket *bucket_create(void);

/*
 * Destroys a bucket.
 */
extern void bucket_destroy(struct bucket *b);

/*
 * Merges a bucket.
 */
extern void bucket_merge(struct bucket *b, int *array);

/*
 * Pops a mini-bucket from a bucket.
 */
extern struct minibucket *bucket_pop(struct bucket *b);

/*
 * Pushes a mini-bucket onto a bucket.
 */
extern void bucket_push(struct bucket *b, struct minibucket *minib);

/*
 * Insert an item into a bucket.
 */
extern void bucket_insert(struct bucket **b, int x);

/*
 * Returns the size of a bucket.
 */
#define bucket_size(b) \
	((b)->size)


#endif /* _IS_H_ */

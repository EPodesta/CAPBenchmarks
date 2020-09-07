/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * friendly-numbers.c - Friendly numbers kernel.
 */

#include <stdlib.h>
#include "fn.h"

static int _friendly_numbers = 0; /* Number of friendly numbers. */

static struct item *task;         /* Array of items (task).      */

/*============================================================================*
 * Division                                                                   *
 *============================================================================*/

struct division
{
	int quotient;
	int remainder;
};

struct division divide(int a, int b)
{
	struct division result;

	result.quotient = 0;
	result.remainder = a;

	while (result.remainder >= b)
	{
		result.remainder -= b;
		result.quotient++;
	}

	return (result);
}

/*============================================================================*
 * Functions                                                                  *
 *============================================================================*/

/**
 * @brief Initializes the task array.
 */
static void init_task()
{
	int aux = PROBLEM_START_NUM;

	for (int i = 0; i < PROBLEM_SIZE; ++i)
		task[i].number = aux++;
}

/**
 * Computes the Greatest Common Divisor of two numbers.
 */
static int gcd(int a, int b)
{
	struct division result;
	int mod;

	while (b != 0)
	{
		result = divide(a, b);
		mod = result.remainder;
		a = b;
		b = mod;
	}

	return (a);
}

static int sumdiv(int n)
{
	int sum;    /* Sum of divisors.     */
	int factor; /* Working factor.      */
	int maxD; 	/* Max divisor before n */
	struct division result;

	maxD = (int)n/2;

	sum = (n == 1) ? 1 : 1 + n;

	/* Compute sum of divisors. */
	for (factor = 2; factor <= maxD; factor++)
	{
		result = divide(n, factor);
		if (result.remainder == 0)
			sum += factor;
	}

	return (sum);
}

/**
 * @brief Compute abundances for task array.
 */
static void compute_abundances()
{
	int n;

	for (int i = 0; i < PROBLEM_SIZE; ++i)
	{
		task[i].num = sumdiv(task[i].number);
		task[i].den = task[i].number;

		n = gcd(task[i].num, task[i].den);

		if (n != 0)
		{
			struct division result1 = divide(task[i].num, n);
			struct division result2 = divide(task[i].den, n);
			task[i].num = result1.quotient;
			task[i].den = result2.quotient;
		}
	}
}

/**
 * @brief Counts the friendly numbers.
 *
 * @returns Returns the number of friendly numbers in @p task.
 */
static void sum_friendly_numbers()
{
	for (int i = 0; i < PROBLEM_SIZE; i++)
	{
		for (int j = (i + 1); j < PROBLEM_SIZE; j++)
		{
			if ((task[i].num == task[j].num) && (task[i].den == task[j].den))
				_friendly_numbers++;
		}
	}
}

/**
 * @brief Friendly Numbers sequential solution.
 */
void friendly_numbers(void)
{
	/* Allocates task array. */
	task = (struct item *) malloc(sizeof(struct item) * PROBLEM_SIZE);

	/* Initializes task array. */
	init_task();

	/* Compute abundances. */
	compute_abundances();

	/* Gets the number of friendly numbers. */
	sum_friendly_numbers();

	/* Frees the allocated memory. */
	free((void *) task);

	/* Prints the result. */
	printf("result: %d\n", _friendly_numbers);
}

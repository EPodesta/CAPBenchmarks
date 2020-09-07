/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * Friendly Numbers Benchmark Kernel.
 */

#include "fn.h"

/*
 * Computes friendly numbers.
 */
extern void friendly_numbers();

/*
 * Runs benchmark.
 */
int main()
{
	printf("computing friendly numbers...\n");

	friendly_numbers();

	printf("done!\n");

	return (0);
}

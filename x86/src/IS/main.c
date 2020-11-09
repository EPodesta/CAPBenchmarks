/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * Integer-Sort Benchmark Kernel.
 */

#include <math.h>
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <timer.h>
#include <util.h>
#include "is.h"

/*
 * Runs benchmark.
 */
int main(int argc, char **argv)
{
	((void) argc);
	((void) argv);

	printf("Computing integer sort\n");

	do_kernel();

	return (0);
}

/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * Gaussian Filter Benchmark Kernel.
 */

#include "gf.h"

/*
 * Runs benchmark.
 */
int main(int argc, char **argv)
{
	((void) argc);
	((void) argv);

	printf("computing gaussian filter...");

	do_kernel();

	printf("done!");

	return (0);
}

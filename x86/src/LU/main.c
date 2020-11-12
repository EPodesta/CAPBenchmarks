/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * LU Factorization Benchmark Kernel.
 */

#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <util.h>
#include <timer.h>
#include "lu.h"

int main(int argc, char **argv)
{
	((void) argc);
	((void) argv);

	do_kernel();

	return (0);
}

/* Kernel Include */
#include "km.h"

/* Runs benchmark. */
int main(int argc, char **argv) {

	((void) (argc));
	((void) (argv));

	printf("computing k-means...\n");

	do_kernel();

	printf("done!\n");

	return (0);
}

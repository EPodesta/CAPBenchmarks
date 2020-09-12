/*
 * Copyright(C) 2014 Matheus M. Queiroz <matheus.miranda.queiroz@gmail.com>,
 *                   Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * gaussian-filter.c - Gaussian filter kernel.
 */

#include "gf.h"

/**
 * @brief Kernel Data
 */
/**@{*/
static unsigned char *img;    /* Input Image.  */
static unsigned char *newimg; /* Output Image. */
static double *mask;           /* Mask.         */

/**@}*/
/**
 * @brief Generates the special mask.
 */
static void generate_mask(void)
{
    double sec;
    double first;
    double total_aux;

    total_aux = 0;
    first     = 1.0/(2.0 * PI * SD * SD);

    for (int i = -(HALF); i <= (HALF); i++)
    {
        for (int j = -(HALF); j <= (HALF); j++)
        {
            sec = -((i * i + j * j)/2.0 * SD * SD);
            sec = pow(E,sec);

            MASK(i + (HALF), j + (HALF)) = first * sec;
            total_aux += MASK(i + (HALF), j + (HALF));
        }
    }

    for (int i = 0; i < PROBLEM_MASKSIZE; i++)
    {
        for (int j = 0; j < PROBLEM_MASKSIZE; j++)
            MASK(i, j) /= total_aux;
    }
}

/**
 * @brief Initializes the image matrix.
 */
static void init(void)
{
	srandnum(PROBLEM_SEED);
    for (int i = 0; i < PROBLEM_IMGSIZE2; i++)
        img[i] = randnum() & 0xff;

    generate_mask();
}

/*
 * Gaussian filter.
 */
static void gauss_filter(void)
{
    double pixel;

    for (int imgI = HALF; imgI < (PROBLEM_IMGSIZE - HALF); imgI++)
    {
        for (int imgJ = HALF; imgJ < (PROBLEM_IMGSIZE - HALF); imgJ++)
        {
            pixel = 0.0;

            for (int maskI = 0; maskI < PROBLEM_MASKSIZE; maskI++)
            {
                for (int maskJ = 0; maskJ < PROBLEM_MASKSIZE; maskJ++)
                    pixel += IMAGE(imgI + maskI - HALF, imgJ + maskJ - HALF) *
                             MASK(maskI, maskJ);
            }

            NEWIMAGE(imgI, imgJ) = (pixel > 255) ? 255 : (int)pixel;
        }
    }
}

/*============================================================================*
 * Kernel                                                                     *
 *============================================================================*/

void do_kernel(void)
{
    /* Allocates memory for original image. */
    img = (unsigned char *)malloc(sizeof(unsigned char) * PROBLEM_IMGSIZE2);

    /* Allocates memory to the gaussian mask. */
    mask = (double *)malloc(sizeof(double) * PROBLEM_MASKSIZE2);

    /* Allocates memory for the new image. */
    newimg = (unsigned char *)malloc(sizeof(unsigned char) * PROBLEM_IMGSIZE2);

    printf("initializing...\n");

    init();

    /* Apply filter. */
    printf("applying filter...\n");

    gauss_filter();

    /* Prints the resultant image. */
    printf("Result:\n");
    for (int imgI = 0; imgI < PROBLEM_IMGSIZE; imgI++)
    {
        for (int imgJ = 0; imgJ < PROBLEM_IMGSIZE; imgJ++)
            printf("%d ", NEWIMAGE(imgI, imgJ));

        printf("\n");
    }

    /* Frees the allocated memory. */
    free((void *)newimg);
    free((void *)mask);
    free((void *)img);
}

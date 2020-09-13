/* Kernel Include */
#include "km.h"

/* K-means Data */
static float *points;    /* Data points.              */
static float *centroids; /* Data centroids.           */
static int *map;         /* Map of clusters.          */
static int *population;  /* Population of centroids.  */
static int has_changed;  /* Has any centroid changed? */

const int _dimension = DIMENSION_MAX;

uint64_t total_time = 0;

/*============================================================================*
 * initialize_variables()                                                     *
 *============================================================================*/

static void initialize_variables()
{
	srandnum(PROBLEM_SEED);
	for (int i = 0; i < PROBLEM_NUM_POINTS*DIMENSION_MAX; i++)
		points[i] = randnum() & 0xffff;

	/* Initialize mapping. */
	for (int i = 0; i < PROBLEM_NUM_POINTS; i++)
		map[i] = -1;

	/* Initialize centroids. */
	for (int i = 0; i < PROBLEM_NUM_CENTROIDS; i++)
	{
		int j = randnum()%PROBLEM_NUM_POINTS;
		memcpy(CENTROID(i), POINT(j), DIMENSION_MAX*sizeof(float));
		map[j] = i;
	}

	/* Map unmapped data points. */
	for (int i = 0; i < PROBLEM_NUM_POINTS; i++)
	{
		if (map[i] < 0)
			map[i] = randnum()%PROBLEM_NUM_CENTROIDS;
	}
}

/*============================================================================*
 * populate()                                                                 *
 *============================================================================*/

static void populate(void )
{
	int init_map;   /* Point initial mapping. */
	float tmp_dist; /* Temporary distance.    */
	float distance; /* Distance.              */

	/* Reset variables for new calculation. */
	for (int i = 0; i < PROBLEM_NUM_CENTROIDS; ++i)
		population[i] = 0;

	/* Iterate over data points. */
	for (int i = 0; i < PROBLEM_NUM_POINTS; i++)
	{
		distance = vector_distance(CENTROID(map[i]), POINT(i));
		init_map = map[i];

		/* Looking for closest cluster. */
		for (int j = 0; j < PROBLEM_NUM_CENTROIDS; j++) {
			/* Point is in this cluster. */
			if (j == map[i])
				continue;

			tmp_dist = vector_distance(CENTROID(j), POINT(i));

			/* Found. */
			if (tmp_dist < distance) {
				map[i] = j;
				distance = tmp_dist;
			}
		}

		population[map[i]]++;

		if (map[i] != init_map)
			has_changed = 1;
	}
}

/*============================================================================*
 * compute_centroids()                                                        *
 *============================================================================*/

static void compute_centroids(void)
{
	/* Compute means. */
	memset(CENTROID(0), 0, PROBLEM_NUM_CENTROIDS*DIMENSION_MAX*sizeof(float));
	for (int i = 0; i < PROBLEM_NUM_POINTS; i++)
		vector_add(CENTROID(map[i]), POINT(i));

	for (int i = 0; i < PROBLEM_NUM_CENTROIDS; i++)
		vector_mult(CENTROID(i), 1.0f/population[i]);
}

/*============================================================================*
 * do_kmeans()                                                                *
 *============================================================================*/

void do_kernel(void)
{
	int iterations;

	/* Allocates memory for points. */
	points = (float *) malloc(sizeof(float) * PROBLEM_NUM_POINTS*DIMENSION_MAX);

	/* Allocates memory for centroids. */
	centroids = (float *) malloc(sizeof(float) * PROBLEM_NUM_CENTROIDS*DIMENSION_MAX);

	/* Allocates memory for map. */
	map = (int *) malloc(sizeof(int) * PROBLEM_NUM_POINTS);

	/* Allocates memory for population array. */
	population = (int *) malloc(sizeof(int) * PROBLEM_NUM_CENTROIDS);

	/* Benchmark initialization. */
	initialize_variables();

	iterations = 0;

	/* Cluster data. */
	do
	{
		has_changed = 0;

		populate();
		compute_centroids();

		iterations++;
	} while (has_changed);

	for (int i = 0; i < PROBLEM_NUM_POINTS; i++)
		printf("%d ", map[i]);
	printf("\n");

	/* Frees the allocated memory. */
	free((void *) population);
	free((void *) map);
	free((void *) centroids);
	free((void *) points);
}


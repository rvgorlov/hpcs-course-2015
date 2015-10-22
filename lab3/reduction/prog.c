/*
 * prog.c:
 *
 */

#include <immintrin.h> /* SSE3 */
#include <stdio.h>

#include "hpctimer.h"

enum { N = 16 * 1024 * 1024, NREPS = 10 };

float reduction_sum(float *v, int n)
{
    int i;
    float sum = 0.0;
    
    for (i = 0; i < n; i++) {
        sum += v[i];
    }
    return sum;
}

float reduction_sum_sse(float *v, int n)
{
    /* TODO */
    return 0.0;
}

int main()
{
	int i;
	float *a;
    double t, sum;
    		
    a = (float *)_mm_malloc(sizeof(*a) * N, 16);
	for (i = 0; i < N; i++)
		a[i] = 1.0;

    t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
        sum = reduction_sum(a, N);
    }
    t = (hpctimer_getwtime() - t) / NREPS;
    printf("Reduction sum: %.4f (real %.4f)\n", sum, (float)N);
    printf("Elapsed time: %.6f sec.\n", t);

	_mm_free(a);
    return 0;
}

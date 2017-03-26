/*
 * prog.c:
 *
 */

#include <pmmintrin.h> /* SSE3 */
#include <stdio.h>

#include "hpctimer.h"

enum { N = 16 * 1024 * 1024, NREPS = 1 };

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
	int i;
	float sum;
	__m128 x;
    __m128 *vv = (__m128 *)v;
	x = *vv;
	vv++;
	
	for (i = 0; i < (n / 4) - 1; i++) {
		x = _mm_add_ps(x, *vv);
        vv++;	
	}
	x = _mm_hadd_ps(x, x);
	x = _mm_hadd_ps(x, x);
	_mm_store_ss(&sum, x);
	
    return sum;
}

int main()
{
	int i;
	float *a;
    double t = 0.0, sum;
    		
    a = (float *)_mm_malloc(sizeof(*a) * N, 16);
	for (i = 0; i < N; i++)
		a[i] = 1.0;

   // t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
        sum = reduction_sum(a, N);
    }
    //t = (hpctimer_getwtime() - t) / NREPS;
    printf("Reduction sum: %.4f (real %.4f)\n", sum, (float)N);
    printf("Elapsed time: %.6f sec.\n", t);

	for (i = 0; i < NREPS; i++) {
        sum = reduction_sum_sse(a, N);
    }
    printf("Reduction sum: %.4f (real %.4f)\n", sum, (float)N);
    printf("Elapsed time: %.6f sec.\n", t);
	
	_mm_free(a);
    return 0;
}

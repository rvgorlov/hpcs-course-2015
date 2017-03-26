/*
 * prog.c:
 *
 */
#include <immintrin.h>  /* SSE3 */
#include <stdio.h>
#include <float.h>      /* for FLT_MAX */

#include "hpctimer.h"

enum { N = 16 * 1024 * 1024, NREPS = 1 };

float vmin(float *v, int n)
{
    int i;
    float minval = FLT_MAX;
    
    for (i = 0; i < n; i++) {
        if (v[i] < minval)
            minval = v[i];
    }
    return minval;
}

float vmin_sse(float *v, int n)
{
    /* TODO */
	int i;
	float min;
	__m128 x;
    __m128 *vv = (__m128 *)v;
	
	x = *vv;
	vv++;
	
	for (i = 0; i < (n / 4) - 1; i++) {
		x = _mm_min_ps(x, *vv);
        vv++;	
	}
	
	x = _mm_min_ps(x, _mm_shuffle_ps(x, x, 0x93));
	x = _mm_min_ps(x, _mm_shuffle_ps(x, x, 0x93));
	x = _mm_min_ps(x, _mm_shuffle_ps(x, x, 0x93));
	_mm_store_ss(&min, x);
	
	
    return min;
}

int main()
{
	int i;
	float *a, val;
    double t = 0.0;
    		
    a = (float *)_mm_malloc(sizeof(*a) * N, 16);
	for (i = 0; i < N; i++)
		a[i] = (float)(N - i);

    //t = hpctimer_getwtime();
    for (i = 0; i < NREPS; i++) {
        val = vmin(a, N);
    }
    //t = (hpctimer_getwtime() - t) / NREPS;
    printf("Min value: %.4f (real %.4f)\n", val, a[N - 1]);
    printf("Elapsed time: %.6f sec.\n", t);
	
    for (i = 0; i < NREPS; i++) {
        val = vmin_sse(a, N);
    }
    printf("Min value: %.4f (real %.4f)\n", val, a[N - 1]);
    printf("Elapsed time: %.6f sec.\n", t);

	_mm_free(a);
    return 0;
}


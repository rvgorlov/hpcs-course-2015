/*
 * loop.c:
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hpctimer.h"

enum { n = 64 * 1024 * 1024 };

int main()
{
    long sum = 0; 
    int *v, i;
    int s1, s2, s3, s4, s5, s6, s7, s8;
    int s9, s10, s11, s12, s13, s14, s15, s16;
    double t;
    
    if ( (v = malloc(sizeof(*v) * n)) == NULL) {
        fprintf(stderr, "No enough memory\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++)
        v[i] = 1;
   
    s1 = s2 = s3 = s4 = s5 = s6 =s7 = s8 = 0;
    s9 = s10 = s11 = s12 = s13 = s14 =s15 = s16 = 0; 
    t = hpctimer_wtime();
    /* TODO: Unroll this loop */
    for (i = 0; i < n; i += 16) {
    /*    s1 += v[i];
        s2 += v[i + 1];
        s3 += v[i + 2];
        s4 += v[i + 3];
        s5 += v[i + 4];
        s6 += v[i + 5];
        s7 += v[i + 6];
        s8 += v[i + 7];
        s9 += v[i + 8];
        s10 += v[i + 9];
        s11 += v[i + 10];
        s12 += v[i + 11];
        s13 += v[i + 12];
        s14 += v[i + 13];
        s15 += v[i + 14];
        s16 += v[i + 15];*/
        sum += v[i]; 
    }
    t = hpctimer_wtime() - t;
    //sum = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10 + s11 + s12 + s13 + s15 + s16; 

    printf("Sum = %ld\n", sum);
    printf("Elapsed time (sec.): %.6f\n", t);

    free(v);
    return 0;
}

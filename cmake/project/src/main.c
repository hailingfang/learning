#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_sf_bessel.h>
#include "add.h"
#include <multi.h>
#include "sub.h"

int
main(int argc, char * argv[])
{
    if (argc != 3) {
        printf("argument error.\n");
        return 0;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    double c = (double)(a + b);
    double d = gsl_sf_bessel_J0(c);
    printf("1. the sum is: %d\n", add(a, b));
    printf("2. gls d is %lf\n", d);
    printf("3. multi d is %ld\n", multi(a, b));
    printf("4. sub is: %d\n", sub(a, b));
    return 0;
}

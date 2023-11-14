#include <stdio.h>
#include <gsl/gsl_fit.h>


int
main(int argc, char *argv[])
{
    double x[] = {1.0l, 2.0l, 3.0l, 4.0f, 5.0l};
    double y[] = {1.9l, 4.1l, 6.1l, 7.8l, 10.1l};
    size_t n = 5;
    double c0, c1, cov00, cov01, cov11, sumsq;
    gsl_fit_linear(x, 1, y, 1, n, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);
    printf("%lf %lf %lf %lf %lf %lf\n", c0, c1, cov00, cov01, cov11, sumsq);
    return 0;
}

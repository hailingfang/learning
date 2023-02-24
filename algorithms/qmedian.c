#include <stdio.h>
#include <stdbool.h>


int
qmedian(double *array, int p, int r, int pos)
{
    double x = array[r];
    int i = p - 1;
    double tmp;
    for (int j = p; j < r; j++) {
        if (array[j] <= x) {
            i++;
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }
    array[r] = array[i + 1];
    array[i + 1] = x;

    if (pos > i + 1) {
        return qmedian(array, i + 2, r, pos);
    } else if (pos < i + 1) {
        return qmedian(array, p, i, pos);
    } else {
        return array[i + 1];
    }   
}


int
main(void)
{

    double array[] = {2, 9, 8, 1, 6, 3, 4, 10, 5, 7, 8, 6};

    double n = qmedian(array, 0, 11, 7);

    printf(">>>%lf\n", n);

    for (int i = 0; i < 12; i++) {
        printf("%lf\n", array[i]);
    }


    return 0;
}

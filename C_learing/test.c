#include <stdio.h>

int pp(int *);

int
main(void)
{
    int a[] = {1, 2, 3};
    printf("%u\n", sizeof(a));
    printf("%d\n", *a);
    pp(a);
    return 0;

}

int
pp(int * n)
{
    printf("%u\n", sizeof(n));
}

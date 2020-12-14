#include <stdio.h>
#include <string.h>

int
main(void)
{
    
    char * x = "abc";
    printf(x);
    char * y = "def";
    char z[7];
    strcpy(z, x);
    strcpy(z, y);
    printf("%s|\n", z);
}


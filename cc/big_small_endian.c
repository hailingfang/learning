#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
    
    uint32_t ii = 16975631;

    printf("1. write %08x\n", ii);
    FILE * fout = fopen("intout", "w");
    if (fwrite(&ii, sizeof(uint32_t), 1, fout) != 1) {
        printf("error.\n");
        exit(0);
    }
    fclose(fout);


    uint32_t jj = 0;
    FILE * fin = fopen("intout", "r");
    if (fread(&jj, sizeof(uint32_t), 1, fin) != 1) {
        printf("error.\n");
        exit(0);
    }
    printf("2. read  %08x\n", jj);
    fclose(fin);
   

    fin = fopen("intout", "r");
    unsigned char kk[4];
    if (fread(kk, sizeof(unsigned char), 4, fin) != 4) {
        printf("error.\n");
        exit(0);
    }
    printf("3. bytes ");
    for (int i = 0; i < 4; i++) {
        printf("%02x|", kk[i]);
    }
    printf("\b \b\n");

    fclose(fin);

    return 0;
}

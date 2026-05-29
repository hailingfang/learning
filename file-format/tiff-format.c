#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int
main(int argc, char *argv[])
{
    unsigned char readbuf[32];
    char *fname = argv[1];
    FILE *fin = fopen(fname, "rb");

    if (!fin)
        exit(1);


    if (fread(readbuf, 1, 2, fin) == 2) {
        readbuf[2] = '\0';
        printf("%s\n", readbuf);
    }

    if (fread(readbuf, 1, 2, fin) == 2) {
        printf("%d\n", ((int *)readbuf)[0]);
    }

    if (fread(readbuf, 1, 4, fin) == 4) {
        printf("%u\n", ((uint32_t *)readbuf)[0]);
    }

    uint32_t offset = ((uint32_t *)readbuf)[0];
    offset -= 8;
    for(uint32_t i = 0; i < offset; i++) {
        getc(fin);
        //printf("%d", getc(fin));
    }

    uint32_t read_len = 0;
    while ((read_len = fread(readbuf, sizeof(char), 32, fin)) > 0){
        for (int i = 0; i < read_len; i++) {
            if (readbuf[i] >= 'A' && readbuf[i] <= 'z') {
                printf("%c\n", readbuf[i]);
            } else {
                printf("%02u\n", readbuf[i]);
            }
        }
    }

    fclose(fin);
    return 0;
}
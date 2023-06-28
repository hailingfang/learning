#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <zlib.h>

#define READ_BUF_LEN 10240

int
main(int argc, char *argv[])
{
    const char * zver = zlibVersion();
    printf("The zlib version is %s\n", zver);

    if (argc != 2) {
        fprintf(stderr, "Usage: cmd filename\n");
    }

    char read_buf[READ_BUF_LEN];


    const char *filename = argv[1];
    FILE *fin = fopen(filename, "r");
    uint32_t deflate_bound = compressBound(READ_BUF_LEN);
    char deflate_buf[deflate_bound];
    uint64_t read_len = 0;
    while((read_len = fread(read_buf, sizeof(char), READ_BUF_LEN - 1, fin)) > 0) {
        read_buf[read_len] = '\0';
        //printf("%s", read_buf);
        printf("read len: %lu\n", read_len);

        uint64_t deflate_len = deflate_bound;
        compress(deflate_buf, &deflate_len, read_buf, read_len);
        printf("deflate len: %lu\n", deflate_len);
        read_len = READ_BUF_LEN;
        uncompress(read_buf, &read_len, deflate_buf, deflate_len);
        printf("read_len uncompressed: %lu\n", read_len);
        read_buf[read_len] = '\0';
        //printf("%s", read_buf);
    }

    return 0;
}

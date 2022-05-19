#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

int
main(int argc, char *argv[])
{
    FILE * fin = fopen(argv[1], "rb");

    SHA256_CTX c;
    unsigned char md[SHA256_DIGEST_LENGTH];
    char buffer[1024];
    long readlen = 0;

    SHA256_Init(&c);
    while((readlen = fread(buffer, 1, 1024, fin)) > 0) {
        SHA256_Update(&c, buffer, readlen);
    }
    SHA256_Final(md, &c);

    fclose(fin);

    printf("%d\n", SHA256_DIGEST_LENGTH);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        printf("%02x", (unsigned char)md[i]);
    }
    printf("\n");
    
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int
main(void)
{
    char dirname[] = "oscatmp";
    char fname[512];
    int status = 0;
    if (!access(dirname, F_OK)) {
        printf("dir already exist\n");
        DIR *dirp = opendir(dirname);
        struct dirent *dp;
        while ((dp = readdir(dirp)) != NULL) {
            printf("%s\n", dp->d_name);
            if (strcmp(".", dp->d_name) != 0 && strcmp("..", dp->d_name) != 0) {
                strcpy(fname, dirname);
                strcat(fname, "/");
                strcat(fname, dp->d_name);
                unlink(fname);  
            }
        }

        status = rmdir(dirname);
        if (status == -1) {
            printf("rm dir failed.\n");
        }
        
        mkdir(dirname, S_IRWXU);
    } else {
        printf("mk new dir.\n");
        mkdir(dirname, S_IRWXU);
    }

    strcpy(fname, dirname);
    strcat(fname, "/tfile");
    FILE *fout = fopen(fname, "w");
    fprintf(fout, "hello world.\n");
    return 0;
}

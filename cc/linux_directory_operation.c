#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Error, a paration and a directory name must given.\n");
    }

    char fname[512];
    const char *opr = argv[1];
    const char *dirname = argv[2];

    if (strcmp(opr, "c") == 0) {
        if (access(dirname, F_OK)) {
            mkdir(dirname, S_IRWXU);
        } else {
            printf("%s alread exist, clean files within it.\n", dirname);
            DIR *dirp = opendir(dirname);
            struct dirent *dp;
            while ((dp = readdir(dirp)) != NULL) {
                if (strcmp(".", dp->d_name) != 0 && strcmp("..", dp->d_name) != 0) {
                    strcpy(fname, dirname);
                    strcat(fname, "/");
                    strcat(fname, dp->d_name);
                    if (unlink(fname)) {
                        fprintf(stderr, "%s remove failed.\n", fname);
                    } else {
                        printf("%s removed.\n", fname);
                    }
                }
            }
            closedir(dirp);
        }
    } else if (strcmp(opr, "d") == 0) {
        if (access(dirname, F_OK)) {
            fprintf(stderr, "%s not exists.\n", dirname);
        } else {
            DIR *dirp = opendir(dirname);
            struct dirent *dp;
            while ((dp = readdir(dirp)) != NULL) {
                if (strcmp(".", dp->d_name) != 0 && strcmp("..", dp->d_name) != 0) {
                    strcpy(fname, dirname);
                    strcat(fname, "/");
                    strcat(fname, dp->d_name);
                    if (unlink(fname)) {
                        fprintf(stderr, "%s ii remove failed.\n", fname);
                    } else {
                        printf("%s removed.\n", fname);
                    }
                }
            }
            closedir(dirp);
            rmdir(dirname);
            printf("%s was removed.\n", dirname);
        }
    } else {
        fprintf(stderr, "opr not recognized.\n");
    }
    return 0;
}

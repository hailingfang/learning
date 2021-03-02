#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Line {
    char * name;
    char * age;
    char *  score;
    struct Line * next;
};

struct Line * solver(char *);


int
main(int argc, char * argv[])
{
    struct Line * data;
    struct Line * pt;
    if (argc != 2){
        printf("table file name was needed.\n");
        exit(1);
    }
    data = solver(argv[1]);
    pt = data;
    while(pt->next){
        printf("%s|%s|%s\n", pt->name, pt->age, pt->score);
        pt = pt->next;
    }
    printf("%s|%s|%s\n", pt->name, pt->age, pt->score);
    while(data->next){
        pt = data->next;
        free(data);
        data=pt;
    }
    printf("%s\n", data->name);
    return 0;
}

struct Line *
solver(char * filename)
{
    struct Line * line;
    struct Line * root;
    struct Line * priv;
    char c;
    char * tmp;
    unsigned short i = 0, j = 0, k=0, l=0;
    char conti[10];
    FILE * f_in;
    f_in = fopen(filename, "r");
    while ((c = getc(f_in)) != EOF ){
        if (i == j) {
            line = (struct Line *)malloc(sizeof(struct Line));
            printf("%p\n", line);
            line->next = NULL;
            if (i == 0){
                root = line;
                priv = line;
            }else{
                priv->next = line;
                priv = line;
            }
            j++;
        }
        if (c == ' '){
            conti[k] = '\0';
            k = 0;
            printf("%s\n", conti);
            if (l==0){
                tmp = (char *)malloc(strlen(conti) + 1);
                strcpy(tmp, conti);
                line->name = tmp;
                printf("%s\n", line->name);
            }else if(l==1){
                tmp = (char *)malloc(strlen(conti) + 1);
                strcpy(tmp, conti);
                line->age = tmp;
                printf("%s\n", line->age);
            }
            else{
                printf("error.");
                exit(1);
            }
            l++;
        }else if (c == '\n'){
            conti[k] = '\0';
            k = 0;
            printf("%s\n",conti); 
            tmp = (char *)malloc(strlen(conti) + 1);
            strcpy(tmp, conti);
            line->score = tmp;
            printf("%s\n", line->score);
            k = 0;
            l = 0;
            i++;
        }else{
            conti[k] = c;
            k++;
        }
    }
    fclose(f_in);
    return root;
}


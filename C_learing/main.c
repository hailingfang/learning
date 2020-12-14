#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_LEN 50
#define DEBUG

struct Line_part {
    char line_p[BLOCK_LEN];
    struct Line_part * next;
};

struct Lines{
    char * line;
    struct Lines * next;
};

static char * integrate_line_part(struct Line_part *);
static struct Lines * structure_file_line(char *);


int
main(int argc, char * argv[])
{
    if (argc != 2){
        printf("Need file name as onle pramater.\n");
        exit(1);
    }
    struct Lines * file_line = structure_file_line(argv[1]);
#ifdef DEBUG
    while(1){
        printf("%s", file_line->line);
        if (file_line->next == NULL)
            break;
        file_line = file_line->next;
    }
#endif
}


static struct Lines *
structure_file_line(char * file_name)
{
    struct Lines * res_ref = (struct Lines *) malloc(sizeof(struct Lines));
    struct Lines * res_head = res_ref;

    FILE * f_in;
    f_in = fopen(file_name, "r");
    struct Line_part * line_ele = (struct Line_part *) malloc(sizeof(struct Line_part));
    struct Line_part * head = line_ele;
    struct Line_part * head_tmp = line_ele;
    head->next = NULL;
    while(fgets(head->line_p, BLOCK_LEN, f_in)){
        if(strlen(head->line_p) < BLOCK_LEN - 1 || head->line_p[BLOCK_LEN - 2] == '\n'){
            char * line = integrate_line_part(line_ele);
            res_head->next = (struct Lines *) malloc(sizeof(struct Lines));
            res_head = res_head->next;
            res_head->line = line;
            head = line_ele->next;
            while(1){
                if(head->next){
                    head_tmp = head->next;
                    free(head);
                    head = head_tmp;
                }
                else{
                    free(head);
                    break;
                }
            }
            head = line_ele;
            continue;
        }
        head->next = (struct Line_part *) malloc(sizeof(struct Line_part));
        head = head->next;
        head->next = NULL;
    }
    if (res_ref->next){
        res_head = res_ref->next;
        free(res_ref);
        res_ref = res_head;
    }
    return res_ref;
}


static char *
integrate_line_part(struct Line_part * Line_first_ele)
{
    struct Line_part * head = Line_first_ele;
    long int line_len = 0;
    int k = 1;
    long i = 0;
    while(head->next){
        line_len += strlen(head->line_p);
        head = head->next;
    } 
    line_len += strlen(head->line_p);
    char * res = (char *) malloc(line_len + 1);
    head = Line_first_ele;
    while(1){
        for(long j = 0; j < strlen(head->line_p); j ++){
            res[i] = head->line_p[j];
            i++;
        }
        if (!head->next)
            break;
        head = head->next;
    }
    return res;
}


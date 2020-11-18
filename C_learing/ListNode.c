#include <stdio.h>
#include <stdlib.h>

struct ListNode {
int val;
struct ListNode * next;
};

int
main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    struct ListNode  * aa;
    struct ListNode * aa_r;
    aa = (struct ListNode *)malloc(sizeof(struct ListNode));
    aa_r = aa;
    for (int i = 0; i < sizeof(a)/sizeof(int); i++){
        printf("i = %d\n", i);
        aa->val = a[i];
        if (i < sizeof(a)/sizeof(int) - 1){
            aa->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            aa = aa->next;
        }
        else
            aa->next =NULL;
    }
    aa = aa_r;
    struct ListNode * next;
    do{
    printf("%d\n", aa->val);
    next = aa->next;
    free(aa);
    aa = next;
    }while(aa);

    return 0;
}


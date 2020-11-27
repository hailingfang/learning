#include <stdio.h>
#include <stdlib.h>
#define arraylen(array) (sizeof(array))/(sizeof(*array))
typedef struct ListNode {int val; struct ListNode * next;} LIST;
LIST * creat_list(int *, int);


int
main(void)
{
    int a1[] = {1, 2, 3, 4};
    int a2[] = {5, 6, 7, 8};
    LIST * a1r;
    a1r = creat_list(a1, arraylen(a1));
    while(a1r->next){
        printf("%d\n", a1r->val);
        a1r = a1r->next;
    }
    printf("%d\n", a1r->val);
   
    return 0;
}


LIST *
creat_list(int * arr, int n)
{
    LIST * dt_out;
    LIST * curr;
    dt_out = (LIST *)malloc(sizeof(LIST));
    curr = dt_out;
    for(int i = 0; i < n; i++){
       curr->val = arr[i];
       if(i < n - 1){
            curr->next = (LIST *)malloc(sizeof(LIST));
            curr = curr->next;
       }
    }
    return dt_out;
}



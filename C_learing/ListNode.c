#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* when compile with lib math, using -lm paramter within gcc commander line.*/
#define arraylen(array) (sizeof(array))/(sizeof(*array))
#define print(x) printf("%d\n", (x))
#define Debug
#undef Debug
typedef struct ListNode {int val; struct ListNode * next;} LIST;
static LIST * creat_list(int *, int);
static LIST * addTwoNum(LIST *, LIST *);


int
main(void)
{
    int a1[] = {1, 2, 3, 4, 9, 9, 9};
    int a2[] = {5, 6, 7, 8, 9};
    long int addsum = 0;
    int i = 0;
    LIST * a1r;
    LIST * a2r;
    a1r = creat_list(a1, arraylen(a1));
    a2r = creat_list(a2, arraylen(a2));
    LIST * summ;

    summ = addTwoNum(a1r, a2r);
    do {
        addsum += summ->val * pow(10, i);
        i++;
    } while((summ->next) && (summ = summ->next));
    printf("the result is: %ld\n", addsum);
    return 0;
}


static LIST *
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


static LIST *
addTwoNum(LIST * l1, LIST * l2)
{
    unsigned int lenl1 = 0, lenl2 = 0, lenless = 0;
    unsigned int tnew = 0, up = 0;
    LIST * res;
    LIST * head;
    LIST * tmp1 = l1;
    LIST * tmp2 = l2;
    res = (LIST *)malloc(sizeof(LIST));
    res->next = NULL;
    head = res;

    do{
        lenl1 ++;

    }while((tmp1->next) && (tmp1 = tmp1->next));
    do{
        lenl2 ++;
    }while((tmp2->next) && (tmp2 = tmp2->next));
    lenless = (lenl1 < lenl2 ? lenl1: lenl2);
    //print(lenless);
    for(unsigned int i = 0; i < lenless; i ++){
        tnew = (l1->val + l2->val + up)%10;
        //print(new);
        up = (l1->val + l2->val + up)/10;
        head->val = tnew;
        if(i < lenless - 1){
            head->next = (LIST *)malloc(sizeof(LIST));
            head->next->next = NULL;
            head = head->next;
        }
        l1 = l1->next;
        l2 = l2->next;
    }


    if (lenl1 > lenl2) {
        for (unsigned int i = 0; i < lenl1 - lenl2; i++) {
            tnew = (l1->val + up)%10;
            up = (l1->val + up)/10;
            LIST * tmp = (LIST *)malloc(sizeof(LIST));
            tmp->val = tnew;
            tmp->next =NULL;
            head->next = tmp;
            head = head->next;
            l1 = l1->next;
        }
    }
    else if (lenl1 < lenl2) {
        for (unsigned int i = 0; i < lenl2 - lenl1; i++) {
            tnew = (l2->val + up)%10;
            up = (l2->val + up)/10;
            LIST * tmp = (LIST *)malloc(sizeof(LIST));
            tmp->val = tnew;
            tmp->next = NULL;
            head->next = tmp;
            head = head->next;
            l2 = l2->next;
        }
    }

    if (up > 0){
        LIST * tmp = (LIST *)malloc(sizeof(LIST));
        tmp->val = up;
        tmp->next = NULL;
        head->next = tmp;
    }

#ifdef Debug
    printf("len of l1 %d\n", lenl1);
    printf("len of l2 %d\n", lenl1);
#endif

    return res;
}



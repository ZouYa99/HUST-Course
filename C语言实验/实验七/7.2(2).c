//
//  main.c
//  7.2(2)
//
//  Created by 雅 on 2019/12/13.
//  Copyright © 2019 雅. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
struct s_list{
    int data;
    struct s_list *next;
};
void create_list (struct s_list **headp,int *p);
int main(void){
    struct s_list *head=NULL,*p,*pp;
    int s[] = {1,2,3,4,5,6,7,8,0};
    int i;
    create_list(&head, s);
    p = head;
    while (p) {
        printf("%d\t",p->data);
        p = p->next;
    }
    printf("\n");
    p = head;
    for (i=0; i<8; i++) {
        pp=p->next;
        free(p);
        p=pp;
    }
    return 0;
}
void create_list (struct s_list **headp,int *p)
{
    struct s_list *loc_head=NULL,*current;
    if (p[0]==0);
    else {
        loc_head = (struct s_list *)malloc(sizeof(struct s_list));
        loc_head->data = *p++;
        loc_head->next = NULL;
        current = loc_head;
        while (*p) {
            loc_head = (struct s_list *)malloc(sizeof(struct s_list));
            loc_head->data = *p++;
            loc_head->next=current;
            current=loc_head;
        }
    }
    *headp=loc_head;
}

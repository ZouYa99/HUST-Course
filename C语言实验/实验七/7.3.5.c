//
//  main.c
//  7.3.5
//
//  Created by 雅 on 2019/12/16.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
struct number{
    int num;
    struct number *next;
};
int main(void){
    char c;
    struct number *head1,*head2,*sumhead;
    struct number *p,*pp,*sump;
    int carry=0;
    //输入部分
    head1=(struct number*)malloc(sizeof(struct number));
    head2=(struct number*)malloc(sizeof(struct number));
    c=getchar();
    head1->num=c-'0';head1->next=NULL;
    for (p=head1,c=getchar(); isdigit(c); p=head1,c=getchar()) {
        head1=(struct number*)malloc(sizeof(struct number));
        head1->num=c-'0';
        head1->next=p;
    }
    c=getchar();
    head2->num=c-'0';head2->next=NULL;
    for (p=head2,c=getchar(); isdigit(c); p=head2,c=getchar()) {
        head2=(struct number*)malloc(sizeof(struct number));
        head2->num=c-'0';
        head2->next=p;
    }
    
    //求和部分
    p=head1;pp=head2;
    sumhead=(struct number*)malloc(sizeof(struct number));
    sumhead->num=p->num+pp->num+carry;
    carry=(sumhead->num-(sumhead->num%10))/10;
    sumhead->num%=10;
    sumhead->next=NULL;
    p=p->next;pp=pp->next;
    for (sump=sumhead;p!=NULL&&pp!=NULL; ) {
        sumhead=(struct number*)malloc(sizeof(struct number));
        sumhead->num=p->num+pp->num+carry;
        carry=(sumhead->num-(sumhead->num%10))/10;
        sumhead->num%=10;
        sumhead->next=sump;
        p=p->next;pp=pp->next;sump=sumhead;
    }
    if (p==NULL&&pp!=NULL) {
        while (pp) {
            sumhead=(struct number*)malloc(sizeof(struct number));
            sumhead->num=pp->num+carry;
            carry=(sumhead->num-(sumhead->num%10))/10;
            sumhead->num%=10;
            sumhead->next=sump;
            pp=pp->next;sump=sumhead;
        }
    }
    if (p!=NULL&&pp==NULL) {
        while (p) {
            sumhead=(struct number*)malloc(sizeof(struct number));
            sumhead->num=p->num+carry;
            carry=(sumhead->num-(sumhead->num%10))/10;
            sumhead->num%=10;
            sumhead->next=sump;
            p=p->next;sump=sumhead;
        }
    }
    if (carry) {
        sumhead=(struct number*)malloc(sizeof(struct number));
        sumhead->num=carry;
        sumhead->next=sump;
    }
    //print sum
    p=sumhead;
    while (p) {
        printf("%d",p->num);
        p=p->next;
    }
    printf("\n");
    //free部分
    p=head1;
    while (p) {
        pp=p->next;
        free(p);
        p=pp;
    }
   p=head2;
    while (p) {
        pp=p->next;
        free(p);
        p=pp;
    }
    p=sumhead;
    while (p) {
        pp=p->next;
        free(p);
        p=pp;
    }
    return 0;
}

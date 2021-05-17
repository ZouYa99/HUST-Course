//
//  main.c
//  7.3.7
//
//  Created by 雅 on 2019/12/14.
//  Copyright © 2019 雅. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct infomation{
    int number;
    char name[9];
    int es,ms,ps,cs;
    struct infomation *next;
};
#define students 4 //此处修改学生人数
float averages[students];
void input(struct infomation **headp,int n);
void output(struct infomation *headp,int n);
void change(struct infomation *headp,int n);
void average(struct infomation *headp,int n);
void outputagain(struct infomation *headp,int n);
void sort(struct infomation **headp);
int main(void) {
    struct infomation *head,*p,*pp;
    int alternative;
void (*p_fun[4])(struct infomation *headp,int n)={output,change,average,outputagain};
    printf("Please input students' information\n");
    input(&head, students);
    printf("0:output students'information\n");
    printf("1:change information\n");
    printf("2:average scores\n");
    printf("3:output again\n");
    printf("4:sort\n");
    printf("5:exit\n");
    scanf("%d",&alternative);
    while (alternative==0||alternative==1|| alternative==2||alternative==3||alternative==4) {
        if (alternative==4) {
            sort(&head);
        }
        else{
        p_fun[alternative](head,students);
        }
        printf("input your choice again\n");
        scanf("%d",&alternative);
    }
    p=head;
    for (int i=0; i<students;i++) {
        pp=p->next;
        free(p);
        p=pp;
    }
    printf("Already free!\n");
    return 0;
}
void input(struct infomation **headp,int n){
    struct infomation *loc_head,*tail;
    int i;
    loc_head = (struct infomation *)malloc(sizeof(struct infomation));
    scanf("%d",&loc_head->number);
    scanf("%s",loc_head->name);
    scanf("%d%d%d%d",&loc_head->es,&loc_head->ms,&loc_head->ps,&loc_head->cs);
    tail=loc_head;
    for (i=1; i<n; i++) {
        tail->next=(struct infomation *)malloc(sizeof(struct infomation));
        tail=tail->next;
        scanf("%d",&tail->number);
        scanf("%s",tail->name);
        scanf("%d%d%d%d",&tail->es,&tail->ms,&tail->ps,&tail->cs);
    }
    tail->next=NULL;
    *headp=loc_head;
}
void output(struct infomation *headp,int n){
    struct infomation *p=headp;
    while (p) {
        printf("%d\t",p->number);
        printf("%s\t",p->name);
        printf("%d\t%d\t%d\t%d\n",p->es,p->ms,p->ps,p->cs);
        p=p->next;
    }
}
void change(struct infomation *headp,int n){
    printf("change number input 1\nchange name input 2\n");
    printf("change English score input 3\n");
    printf("change math score input 4\n");
    printf("change physics score input 5\n");
    printf("change Clanguage score input 6\n");
    int choice,num;
    printf("input the number of student you want to change");
    scanf("%d",&num);
    struct infomation *p=headp;
    while (p->number!=num) {
        p=p->next;
    }
    scanf("%d",&choice);
    printf("Please input information");
    switch (choice) {
        case 1:
            scanf("%d",&p->number);break;
       case 2:
            scanf("%s",p->name);break;
        case 3:
            scanf("%d",&p->es);break;
        case 4:
            scanf("%d",&p->ms);break;
        case 5:
            scanf("%d",&p->ps);break;
        case 6:
            scanf("%d",&p->cs);break;
    }
}
void average(struct infomation *headp,int n){
    struct infomation *p=headp;
    int i;
    for (i=0; i<n; i++) {
        averages[i]=(p->es+p->ms+p->ps+p->cs)*1.0/4.0;
        p=p->next;
    }
    for (i=0; i<n; i++) {
        printf("%.2f\t",averages[i]);
    }
    printf("\n");
}
void outputagain(struct infomation *headp,int n){
    int sum[n],k;
    struct infomation *p=headp;
    for (k=0; k<n; k++) {
        sum[k]=p->es+p->ms+p->ps+p->cs;
        p=p->next;
    }
    p=headp;
    for (k=0; k<n; k++) {
        printf("%d\t%s\t%d\t%.2f\n",p->number,p->name,sum[k],averages[k]);
        p=p->next;
    }
}
void sort(struct infomation **headp){
    struct infomation *prior1,*prior2,*p1,*p2,*t;
    int i,j;
    float temp;
    p1=*headp;
    for (p2=p1->next,prior2=p1,i=1; p2!=NULL&&i<students; prior2=p2,p2=p2->next,i++) {
        if (averages[0]>averages[i]) {
            prior2->next=p1;t=p1->next;
            p1->next=p2->next;(*headp)=p2;
            p2->next=t;p1=p2;
            temp=averages[0];averages[0]=averages[i];averages[i]=temp;
        }
    }
    for (prior1=*headp,p1=prior1->next,i=1; p1->next!=NULL; prior1=p1,p1=p1->next,i++) {
        for (p2=p1->next,prior2=p1,j=i+1; p2!=NULL&&j<students; prior2=p2,p2=p2->next,j++) {
            if (averages[i]>averages[j]) {
                t=p2->next;prior1->next=p2;
                prior2->next=p1;p2->next=p1->next;
                p1->next=t;p1=p2;
                temp=averages[i];averages[i]=averages[j];averages[j]=temp;
            }
        }
    }
    printf("Already sort!\n");
}

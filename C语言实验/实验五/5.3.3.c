//
//  main.c
//  5.3.3
//
//  Created by 雅 on 2019/11/20.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
int flag1=0,flag2=0;
char name[100][10];
int score[100];
int number;
void input(void);
void sort(char name[100][10],int score[]);
void output(void);
void found(void);
int main(void)
{
    int x;
start:
        printf("---menu---\n");
        printf("1:Input the information\n");
        printf("2:Sort\n");
        printf("3:Output\n");
        printf("4:found\n");
        printf("----------\n");
        printf("Input a number: ");
        scanf("%d",&x);
        printf("\n");
    if(x==1&&flag1==0) {input();flag1=1;goto start;}
    else if(x==2&&flag1==1) {
        sort(name, score);flag2=1;
        printf("sort is finished\n");
        goto start;
    }
    else if(x==3&&flag1==1&&flag2==1) {output();goto start;}
    else if(x==4&&flag1==1&&flag2==1) {found();goto start;}
    else {printf("error\n");goto start;}
    return 1;
}
 void input()
{
    int i,k;
    printf("Input the number of students:");
    scanf("%d",&number);
    for(i=0;i<number;i++){
         scanf("%s",name[i]);
        }
    for(k=0;k<number;k++){
        scanf("%d",&score[k]);
    }
}
void sort(char name[100][10],int score[100])
{
    int i,j,t;
    char tem[100][10];
    for(i=0;i<number-1;i++){
        for(j=0;j<number-i-1;j++){
            if(score[j]>score[j+1])
            {t=score[j];score[j]=score[j+1];score[j+1]=t;
                *tem[j]=*name[j];*name[j]=*name[j+1];*name[j+1]=*tem[j];
            }
        }
    }
}
void output(void)
{
    int i;
    for(i=number-1;i>=0;i--)
    {
        printf("%s  ",name[i]);
        printf("%d\n",score[i]);
    }
}
void found(void)
{
    int s,result=-1,flag=0;
    int front=0,back=number-1,middle;
    printf("Input a score you want to find:");
    scanf("%d",&s);
    while(front<=back&&flag==0){
        middle=(front+back)/2;
        if(s<score[middle]) back=middle-1;
        else if(s>score[middle]) front=middle+1;
        else {result=middle;flag=1;}
    }
    if(result==-1) printf("not found!");
    else {printf("%s   ",name[result]);
    printf("%d\n",score[result]);
    }
}


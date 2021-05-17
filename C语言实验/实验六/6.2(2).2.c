//
//  main.c
//  6.2(2).2
//
//  Created by 雅 on 2019/12/3.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <string.h>
int main(void){
    char* (*p[])(char *,const char *)={strcpy,strcat,strtok};
    char a[80],b[80],*result;
    int choice;
    while (1) {
        do
        {
            printf("\t\t1 copy string.\n");
            printf("\t\t2 connect string.\n");
            printf("\t\t3 parse string.\n");
            printf("\t\t4 exit.\n");
            scanf("%d",&choice);
        }while (choice<1||choice>4);
        getchar();
        printf("input the first string please!\n");
        gets(a);
        printf("input the second string please!\n");
        gets(b);
        result= p[choice-1](a,b);
        printf("the result is %s\n",result);
    }
down:
    return 0;
}


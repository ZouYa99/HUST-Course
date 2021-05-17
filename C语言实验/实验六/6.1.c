//
//  main.c
//  6.1
//
//  Created by 雅 on 2019/12/3.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
char *strcopy(char *,const char *);
int main(void) {
    char *s1,*s2,*s3;
    char s[20],t[20];
    s1=s;s2=t;
    printf("Input a string:\n");
    scanf("%s",s2);
    strcopy(s1, s2);
    printf("%s\n",s1);
    printf("Input a string again:\n");
    scanf("%s",s2);
    s3=strcopy(s1, s2);
    printf("%s\n",s3);
    return 0;
}
char *strcopy(char *t,const char *s){
    char *temp=t;
    while ((*t++ = *s++)) ;
    return (temp);
}

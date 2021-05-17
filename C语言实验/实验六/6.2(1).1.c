//
//  main.c
//  6.2（1）.1
//
//  Created by 雅 on 2019/12/3.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
void strsort(char *s[],int size){
    char *temp;
    int i,j;
    for (i=0; i<size-1; i++) {
        for (j=0; j<size-i-1; j++) {
            if(*s[j]>*s[j+1]){
                temp=s[j];
                s[j]=s[j+1];
                s[j+1]=temp;
            }
        }
    }
}
int main(void) {
    int i;
    char *s[N],t[50];
    for (i=0; i<N; i++) {
        scanf("%s",t);
        s[i]=(char *)malloc(strlen(t)+1);
        strcpy(s[i], t);
    }
    strsort(s,N);
    for (i=0; i<N; i++) {
        puts(s[i]);
        free(s[i]);
    }
    return 0;
}

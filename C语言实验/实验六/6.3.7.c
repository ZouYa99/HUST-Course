//
//  main.c
//  6.3.7
//
//  Created by 雅 on 2019/12/4.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *find(int n,char *s[],int *p){
    int j;
    char *result;
    result=s[0];
    for (j=0; j<n; j++) {
        if (strlen(s[j-1])<strlen(s[j])) {
            result=s[j];
            *p=strlen(s[j]);
        }
    }
    return result;
}
int main(void) {
    int n,i,len;
    scanf("%d",&n);
    char *s[n];int *u;
    char t[50];
    char *ps;
    u=&len;
    for (i=0; i<n ; i++) {
        scanf("%s",t);
        s[i]=(char *)malloc(strlen(t)+1);
        strcpy(s[i], t);
    }
    ps=find(n, s,u);
    printf("%s\n",ps);
    printf("%d\n",*u);
    for (i=0; i<n; i++) {
        free(s[i]);
    }
    return 0;
}

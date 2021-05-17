//
//  main.c
//  5.3.5
//
//  Created by 雅 on 2019/11/20.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <string.h>
void strnins(char [],char [],int );
int main(void){
    char t[100],s[100];
    int n;
    scanf("%d",&n);
    scanf("%s",t);
    scanf("%s",s);
    strnins(t,s,n);
}
void strnins(char t[],char s[],int n){
    unsigned long i,u;
    int k,j,a,b,c,d;
    i=strlen(s);
    u=strlen(t);
    char tem[u-n];
    for(k=n,j=0;k<u;k++,j++){
        tem[j]=t[k];
    }
    for(a=n,b=0;b<i;a++,b++){
        t[a]=s[b];
    }
    for (c=0,d=n+i; c<j; c++,d++) {
        t[d]=tem[c];
    }
    printf("%s\n",t);
}

//
//  main.c
//  6.3.10
//
//  Created by 雅 on 2019/12/4.
//  Copyright © 2019 雅. All rights reserved.
//
#include <stdio.h>
#include "ctype.h"
#define N 200
int len;
void shift(int *a,int n){
    int k,sft;
    len=N-1-n;
    sft=N-len;
    for (k=0; k<len; k++) {
        *(a+k)=*(a+k+sft);
    }
    for (k=len; k<N; k++) {
        *(a+k)=0;
    }
}
int main(void) {
    int s1[N],s2[N],result[3*N],i,j,carry=0,m=0,w;
    int *longer,*shorter;
    int len1,len2;
    int lens,lenss;
    for (i=0; i<3*N; i++) {
        *(result+i)=0;
    }
    i=N-1;
    while (i>=0&&isdigit(*(s1+i)=getchar())) {
        *(s1+i--)-='0';
    }
    if (i>=0) {
        shift(s1, i);
        len1=len;
    }
    i=N-1;
    while (i>=0&&isdigit(*(s2+i)=getchar())) {
        *(s2+i--)-='0';
    }
    if (i>=0) {
        shift(s2, i);
        len2=len;
    }
    if (len1>len2) {
        lens=len1;
        longer=s1;shorter=s2;lenss=len2;
    }
    else {
        lens=len2;
        longer=s2;shorter=s1;lenss=len1;
    }
    for (i=0; i<lenss; i++) {
        for(j=0,w=i;j<lens;j++,w++){
        result[w]+=*(longer+j) * *(shorter+i);
        carry=(result[w]-result[w]%10)/10;
        result[w]%=10;
        m=w;
        while (carry) {
               result[++m]+=carry%10;
               carry/=10;
        }
      }
    }
    for (i=m; i>=0; i--) {
        printf("%d",result[i]);
    }
    printf("\n");
    return 0;
}

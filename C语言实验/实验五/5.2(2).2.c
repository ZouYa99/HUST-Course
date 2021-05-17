//
//  main.c
//  5.2(2).2
//
//  Created by 雅 on 2019/11/18.
//  Copyright © 2019 雅. All rights reserved.
//
#include <stdio.h>
#define M 10
#define N 3
int main(void)
{
    int a[M],b[M];
    int i,j,k;
    for(i=0;i<M;i++)
        a[i]=i+1;
    for(i=M,j=0;i>1;i--){
        for(k=1;k<=N;k++)
        {
            while (!a[j]) {
                j++;
            }
            if(++j>M-1) j=0;
        }
        if(j){
            b[M-i]=a[j-1];
            a[j-1]=0;
        }
        else {
            b[M-i]=a[M-1];
            a[M-1]=0;
        }
    }
    for(i=0;i<M-1;i++)
        printf("%6d",b[i]);
    for(i=0;i<M;i++)
        if (a[i]!=0) {
            printf("%6d",a[i]);
        }
    return 0;
}

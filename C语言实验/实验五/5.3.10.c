//
//  main.c
//  5.3.10
//
//  Created by 雅 on 2019/11/21.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#define M 6
int s[M][M];
int main(void)
{
    int i=0,j=0,k=1;
    s[0][0]=1;
    while (k<M*M) {
        while (j<M-1&&!s[i][j+1]) {
            s[i][++j]=++k;
        }
        while (i<M-1&&!s[i+1][j]) {
            s[++i][j]=++k;
        }
        while (j>0&&!s[i][j-1]) {
            s[i][--j]=++k;
        }
        while (i>0&&!s[i-1][j]) {
            s[--i][j]=++k;
        }
    }
    for (i=0; i<M; i++) {
        for (j=0; j<M; j++) {
            printf("%6d",s[i][j]);
        }
        printf("\n");
    }
    return 0;
}

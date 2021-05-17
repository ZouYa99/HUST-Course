//
//  main.c
//  6.3.4
//
//  Created by 雅 on 2019/12/4.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
void revolve(int *p,int n,int m);
int main(void) {
    int n,m;
    int i,j;
    printf("Input n and m:\n");
    scanf("%d%d",&n,&m);
    int s[n][m];
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            scanf("%d",&s[i][j]);
        }
    }
    revolve(&s[0][0],n,m);
    return 0;
}
void revolve(int *p,int n,int m){
    int u[m][n];
    int k,t;
    for (k=0; k<n; k++) {   //k为列
        for (t=m-1; t>=0; t--) { //t为倒序的行
            u[t][k]=*p++;
        }
    }
    for (k=0; k<m; k++) {
        for (t=0; t<n; t++) {
            printf("%d\t",u[k][t]);
        }
        printf("\n");
    }
}

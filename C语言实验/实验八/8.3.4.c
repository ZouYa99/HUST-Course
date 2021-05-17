//
//  main.c
//  8.3.4
//
//  Created by 雅 on 2019/12/25.
//  Copyright © 2019 雅. All rights reserved.
//
#include <stdio.h>
void revolve(int *p,int n,int m);
int main(void) {
    FILE *fp;
    fp=fopen("/Users/zouya/Desktop/C语言实验8/8.3.4/matrix.in", "w");
    int n,m;
    int i,j;
    char change='\n';
    printf("Input n and m:\n");
    scanf("%d%d",&n,&m);
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(&m, sizeof(int), 1, fp);
    fwrite(&change, sizeof(char), 1, fp);
    int s[n][m];
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            scanf("%d",&s[i][j]);
            fwrite(&s[i][j], sizeof(int), 1, fp);
        }
        fwrite(&change, sizeof(char), 1, fp);
    }
    revolve(&s[0][0],n,m);
    fclose(fp);
    return 0;
}
void revolve(int *p,int n,int m){
    char change='\n';
    FILE *fp;
    fp=fopen("/Users/zouya/Desktop/C语言实验8/8.3.4/matrix.out", "wb");
    fwrite(&m, sizeof(int), 1, fp);
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(&change, sizeof(char), 1, fp);
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
            fwrite(&u[k][t], sizeof(int), 1, fp);
        }
        fwrite(&change, sizeof(char), 1, fp);
        printf("\n");
    }
    fclose(fp);
}

//
//  main.c
//  5.3.6
//
//  Created by 雅 on 2019/11/21.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
int main(void)
{
    int n,m,i,j;
    printf("Input n and m:");
    scanf("%d%d",&n,&m);
    int ori[n][m],sed[n][m],result[n][m];
    int first=0,end=0,a,b,flag=0;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&ori[i][j]);
        sed[i][j]=ori[i][j];
    }
    }
    for(i=0;i<n;i++){
        for(j=0;j<m-2;j++,flag=0)
        {
        if(sed[i][j]==sed[i][j+1]&&sed[i][j+1]==sed[i][j+2])
        {
            first=j;end=j+2;
            for(a=3;a+j<m;a++){
                if(sed[i][j+a]==sed[i][j]) end=j+a;
                else break;
            }
            flag=1;
        }
            if(flag==1){
                for(b=first;b<=end;b++)
                    sed[i][b]=0;
            }
    }
    }
    for(j=0;j<m;j++){
        for(i=0;i<n-2;i++,flag=0)
        {
        if(ori[i][j]==ori[i+1][j]&&ori[i+1][j]==ori[i+2][j])
        {
            first=i;end=i+2;
            for(a=3;a+j<m;a++){
                if(ori[i+a][j]==ori[i][j]) end=j+a;
                else break;
            }
            flag=1;
        }
        if(flag==1){
            for(b=first;b<=end;b++)
                ori[b][j]=0;
        }
    }
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
        result[i][j]=ori[i][j]&sed[i][j];
    }
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
        printf("%d  ",result[i][j]);
    }
        printf("\n");
    }
    return 1;
}


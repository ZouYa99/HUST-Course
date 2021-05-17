//
//  main.c
//  5.3.9
//
//  Created by 雅 on 2019/11/21.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void  breaks(char s[],int op ,int rest);
int main()
{
    int n,i;
    char s[20];
    printf("Input an interger:\n");
    scanf("%d",&n);
    for(i=n;i>=1;i--)
    {
        if(i==n) printf("%d\n",n);
        else{
        s[0]=i+'0';
        breaks(s,i,n-i);
        printf("\n");
        }
    }
    return 0;
}
void  breaks(char s[],int op ,int rest)
{
    int k;
    static char t[20]={0};
    char res[20]={0},str[3]={0};
    if(rest==0)
    {
        if(s[0]==t[0]) printf(",%s",s);
        else printf("%s",s);
        strcpy(t,s);
    }
        for(k=rest;k>0;k--)
        {
            if(k>op) continue;
            else
            {
                str[0]='+';
                str[1]=k+'0';
                strcpy(res,s);strcat(s,str);
                breaks(s,k,rest-k);strcpy(s,res);
            }
        }
}

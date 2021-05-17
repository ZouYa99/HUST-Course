//
//  main.c
//  5.3.1
//
//  Created by 雅 on 2019/11/18.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <string.h>
void reverse(char s[])
{
    int c,j;
    unsigned long k;
    for(j=0,k = strlen(s)-1;j<k;j++,k--)
    { c=s[j];s[j]=s[k];s[k]=c;}
}
int main(void)
{
    int n;
    char a[100];
    int i,t;
    printf("Input a interger");
    scanf("%d",&n);
    for(i=0;i<64;i++){
        a[i]=(n&1)+'0';
        n=n>>1;
    }
    reverse(a);
    for(t=0;t<strlen(a);t++) printf("%c",a[t]);
    return 1;
}

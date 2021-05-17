//
//  main.c
//  5.1
//
//  Created by 雅 on 2019/11/18.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>

void strcate(char [],char []);

void strdelc(char [],char );

int main(void)

{

    char a[50]="Language",b[50]="Programming";

    printf("%s   %s\n",b,a);

    strcate(b,a);    printf("%s   %s\n",b,a);

    strdelc(b,'a');  printf("%s\n",b);

    return 0;

}

void strcate(char t[],char s[])

{

    int i=0,j=0;

    while(t[i++]);i--;

    while((t[i++]=s[j++])!='\0');

}

void strdelc(char s[],char c)

{

    int j,k;

    for(j=k=0;s[j]!='\0';j++)

        if(s[j]!=c)  s[k++]=s[j];

    s[k]='\0';

}

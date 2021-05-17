//
//  main.c
//  8.2
//
//  Created by 雅 on 2019/12/25.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    char ch;
    FILE *fp;
    if(argc!=2){
        printf("Arguments error!\n");
        exit(-1);
    }
    if((fp=fopen(argv[1],"r"))==NULL){
        printf("can't open file");
        exit(-1);
    }
    while((ch=fgetc(fp))!=EOF){
        putchar(ch);
    }
    fclose(fp);
    return 0;
}

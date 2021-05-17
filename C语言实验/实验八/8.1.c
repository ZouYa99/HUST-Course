//
//  main.c
//  8.1
//
//  Created by 雅 on 2019/12/23.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
int main(void){
    short a=0x3132,b=0x3334;
    char ch;
    char buf[10];
    FILE *fp1,*fp2;
    fp1=fopen("D:\\test122.txt", "wb+");
    fp2=fopen("D:\\test2.txt", "w+");
    if(!fp1)
        printf("sdf\n");
    fwrite(&a, sizeof(short), 1, fp1);
    fwrite(&b, sizeof(short), 1, fp1);
    fprintf(fp2, "%hx %hx",a,b);

    rewind(fp1);
    rewind(fp2);

    while((ch = fgetc(fp1)) != EOF) {
        putchar(ch);
    }
    putchar('\n');
    while ((ch = fgetc(fp2)) != EOF) {
        putchar(ch);
    }
    putchar('\n');

    fclose(fp1);
    fclose(fp2);
    return 0;
}

//
//  main.c
//  8.3.2
//
//  Created by 雅 on 2019/12/25.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>

int main(void) {
    FILE *fp;
    float n;
    char ch;
    int i;
    fp=fopen("/Users/zouya/Downloads/test1.dat", "wb+");
    for (i=0; i<10; i++) {
        scanf("%f",&n);
        fwrite(&n, sizeof(float), 1, fp);
    }
    fclose(fp);
    fp=fopen("/Users/zouya/Downloads/test1.dat", "r+");
    for (i=0; i<10; i++) {
        fread(&n, sizeof(float), 1, fp);
        printf("%f\t",n);
    }
    printf("\n");
    fclose(fp);
    fp=fopen("/Users/zouya/Downloads/test1.dat", "r+");
    for (i=0; i<10; i++) {
        fread(&ch, sizeof(char), 1, fp);
        printf("%d",ch);
    }
    printf("\n");
    fclose(fp);
    return 0;
}

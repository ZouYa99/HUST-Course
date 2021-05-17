//
//  main.c
//  6.3.1
//
//  Created by 雅 on 2019/12/4.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
int main(void) {
    long n =0x1234567A;
    char *p=(char*)&n;
    int low,high,k;
    for (k=0; k<4; k++) {
        low=(*p)&0x0f;
        high=((*p)>>4)&0x0f;
        if (low<10) {
            low=low+'0';
        }
        else low=(low-10)+'A';
        if (high<10) {
            high=high+'0';
        }
        else high=(high-10)+'A';
        printf("The %d byte's low 4 bits is:0X%c,high 4 bits is:0X%c.\n",k+1,low,high);
        p++;
    }
    return 0;
}

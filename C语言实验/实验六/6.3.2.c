//
//  main.c
//  6.3.2
//
//  Created by 雅 on 2019/12/4.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#define N 5
int RemoveSame(int [],int );
int main(void) {
    int nums[N];
    int i,lens;
    for (i=0; i<N; i++) {
        scanf("%d",nums+i);
    }
    lens = RemoveSame(nums, N);
    for (int k=0; k<lens; k++) {
        printf("%d\t",*(nums+k));
    }
    return 0;
}
int RemoveSame(int nums[],int n){
    int i,j,number=1;
    int differ[n];
    *differ=*nums;
    int len=1,flag=0;
    for (i=1; i<n; i++,flag=0) {
        for (j=0; j<len; j++) {
            if (*(nums+i)==*(differ+j)) {
                flag=1;break;
            }
        }
        if(!flag){
            *(differ+len)=*(nums+i);
            len++;
            number++;
        }
        }
    if (number>1) {
    for (i=1; i<number; i++) {
        *(nums+i)=*(differ+i);
    }
    }
    return number;
}

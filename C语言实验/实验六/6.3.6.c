//
//  main.c
//  6.3.6
//
//  Created by 雅 on 2019/12/4.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[]) {
    int len = atoi(argv[1]);
    int i,j,k,temp;
    int nums[len];
    for (i=0; i<len; i++) {
        scanf("%d",&nums[i]);
    }
    for (i=0; i<len-1; i++) {
        for (j=0; j<len-i-1; j++) {
            if(nums[j]>nums[j+1]){
                temp=nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
            }
        }
    }
    if (argc==3) {
        for (k=len-1; k>=0; k--) {
            printf("%d\n",nums[k]);
        }
    }
    else{
        for (k=0; k<len; k++) {
        printf("%d\n",nums[k]);
    }
}
    return 0;
}

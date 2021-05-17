//
//  main.c
//  7.3.1
//
//  Created by 雅 on 2019/12/13.
//  Copyright © 2019 雅. All rights reserved.
//

#include <stdio.h>
struct bits{
    unsigned char bit0:1,bit1:1,bit2:1,bit3:1,bit4:1,bit5:1,bit6:1,bit7:1;
};
void f0(int b)
{
    printf("the function0 %d is called!\n",b);
}
void f1(int b)
{
    printf("the function1 %d is called!\n",b);
}
void f2(int b)
{
    printf("the function2 %d is called!\n",b);
}
void f3(int b)
{
    printf("the function3 %d is called!\n",b);
}
void f4(int b)
{
    printf("the function4 %d is called!\n",b);
}
void f5(int b)
{
    printf("the function5 %d is called!\n",b);
}
void f6(int b)
{
    printf("the function6 %d is called!\n",b);
}
void f7(int b)
{
    printf("the function7 %d is called!\n",b);
}
int main(void) {
    void (*p_fun[])(int b)={f0,f1,f2,f3,f4,f5,f6,f7};
    struct bits bit;
    bit.bit0=0;bit.bit1=0;bit.bit2=0;bit.bit3=0;
    bit.bit4=0;bit.bit5=0;bit.bit6=0;bit.bit7=0;//初始化
    bit.bit2=1;
    bit.bit4=1;
    if (bit.bit0==1) {
        p_fun[0](bit.bit0);
    }
    if (bit.bit1==1) {
        p_fun[1](bit.bit1);
    }
    if (bit.bit2==1) {
        p_fun[2](bit.bit2);
    }
    if (bit.bit3==1) {
        p_fun[3](bit.bit3);
    }
    if (bit.bit4==1) {
        p_fun[4](bit.bit4);
    }
    if (bit.bit5==1) {
        p_fun[5](bit.bit5);
    }
    if (bit.bit6==1) {
        p_fun[6](bit.bit6);
    }
    if (bit.bit7==1) {
        p_fun[7](bit.bit7);
    }
    return 0;
}

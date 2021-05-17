#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long ip;
    int a,b,c,d;
    scanf("%lu",&ip);
    for(;ip!=EOF;scanf("%lu",&ip))
    {
        a=(ip&0xff000000)>>24;
        b=(ip&0x00ff0000)>>16;
        c=(ip&0x0000ff00)>>8;
        d=(ip&0x000000ff);
        printf("%d.%d.%d.%d",a,b,c,d);
    }
return 0;
}

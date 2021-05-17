#include <stdio.h>
#include "file.h"
int x,y;
char ch;
int main(void)
{
    x=10;y=20;
    ch=getchar();
    printf("in main x=%d,y=%d,ch is %c\n",x,y,ch);
    func1();
    return 0;
}

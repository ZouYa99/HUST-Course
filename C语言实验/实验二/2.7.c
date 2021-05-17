#include <stdio.h>
#include <stdlib.h>

int main()
{
   unsigned short x,m,n;
   scanf("%hx%hu%hu",&x,&m,&n);
   if((0<=m&&m<=15)&&(1<=n&&n<=16-m))
    x=x<<(16-m-n)&0xffff<<(16-n);
   printf("%#x",x);
   return 0;
}

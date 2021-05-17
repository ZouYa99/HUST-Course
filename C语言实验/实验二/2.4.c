#include <stdio.h>
#include <stdlib.h>

int main()
{
   int n,i,s;
   scanf("%d",&n);
   for(i=0,s=0;n%10!=0||n/10!=0;++i)
    {
    s+=n%10;
    n=n/10;
    }
   printf("The inputting number has %d number,every number's sum is %d",i,s);
   return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
   int m,n,k,p,i,d;
   printf("Input m,n\n");
   scanf("%d%d",&m,&n);
   if(m<n){
    m=m^n;n=m^n;m=m^n;
   }
   k=0;
   while((m|1)!=m&&(n|1)!=n){
    m>>1;
   n>>1;
   k++;
   }
   p=1;
   p<<k;
   while((d=m-n)!=n){
    if(d>n) m=d;
    else m=-(n=d)+m;

   }
   d*=p;
   printf("greatest common divisor:%d",d);
   return 0;
}

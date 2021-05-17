#include <stdio.h>
int zimi(long );
int k;
int main()
{
   scanf("%d",&k);
   long j=1,h=10,s;
   int i,x,y;
   int number=0,z[5];
   for(i=1;i<k;i++)j*=10;
   h*=j;
   for(s=j,x=0;s>=j&&s<h;s++){
    if(zimi(s)==1) {z[x]=s;number++;x++;};
   }
   printf("%d位的自幂数共有%d个：",k,number);
   for(y=0;y<x;y++){
    printf("%d ",z[y]);
   }
   return 0;
}
int zimi(long n){
  int oringal=n;
  int a,b;
  long sin,sum=0;
  int s[k],m;
  for(m=0;m<(k-1);m++) {
    s[m]=n%10;n/=10;
    }
    s[m]=n;
  for(a=0;a<k;a++){
    sin=1;
    for(b=1;b<=k;b++) sin*=s[a];
    sum+=sin;
  }
  if(sum==oringal) return 1;
  else return 0;
}

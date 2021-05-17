#include <stdio.h>
long long sum_fac(int n);
long long s=0;
int main()
{  long long n;
    int k;
    for(k=1;k<=20;k++)
        printf("k=%d\tthe sum is %lld\n",k,sum_fac(k));
return 0;
}
long long sum_fac(int n){
 int i=n;
 static long long fac=1;
 fac*=i;
 s+=fac;
 return s;
}

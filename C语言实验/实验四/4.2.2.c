#include <stdio.h>
long long sum_fac(int n);
int main()
{  long long n;
    int k;
    for(k=1;k<=20;k++)
        printf("k=%d\tthe sum is %lld\n",k,sum_fac(k));
return 0;
}
long long sum_fac(int n){
long long s=0;
 int i;
 long long fac=1;
 if(n==1) return 1;
 else {
 for(i=1;i<=n;i++) fac*=i;
 return fac+sum_fac(--n);}
}

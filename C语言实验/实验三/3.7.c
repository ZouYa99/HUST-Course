#include <stdio.h>
int IsPrime(int );
int main()
{
    int m,i;
    scanf("%d",&m);
    for(i=3;i<m-2;i+=2){
        if(IsPrime(i)==1&&IsPrime(i+2)==1) printf("(%d,%d)  ",i,i+2);
    }

    return 0;
}


int IsPrime(int n){
int k,limit;
if(n==2) return 1;
if(!(n%2)) return 0;
limit=n/2;
for(k=3;k<=limit;k+=2)
    if(!(n%k)) return 0;
return 1;
}

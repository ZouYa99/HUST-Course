#include <stdio.h>
int IsPrime(int );
void gede(int );
int main()
{   int n;
    printf("Input an even interger:");
    scanf("%d",&n);
    if(n>=4&&!(n%2)){
        gede(n);
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
void gede(int n){
    int i,t;
    for(i=2;i<n;i++){
        if(IsPrime(i)==1){
            t=n-i;
            if(IsPrime(t)==1) {printf("%d=%d+%d",n,i,t);break;}
        }
    }
 }

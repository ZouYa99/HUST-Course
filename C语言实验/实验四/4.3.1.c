#include <stdio.h>
long long fabonacci(int n);
long long t[50];
int main()
{
    int i,k,p;
    long long sum=0;
    printf("Input n:");
    scanf("%d",&k);
    for(p=0;p<50;p++) t[p]=-1;
    for(i=1;i<=k;i++){
        t[i-1]=fabonacci(i);
        sum+=t[i-1];
        printf("i=%d\tthe sum is %lld\n",i,sum);
    }
    return 0;
}
long long fabonacci(int n){
if(n==1||n==2) return 1;
else if(t[n-2]>0&&t[n-3]>0) return t[n-2]+t[n-3];
else return fabonacci(n-1)+fabonacci(n-2);
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,d,maxp,tem;
    scanf("%d",&n);
    int pri[n];
    for(i=0;i<n;++i)  scanf("%d",&pri[i]);
    for(d=0,tem=0,maxp=0;d<n-1;++d){
        tem=pri[d+1]-pri[d];
        if(tem<0) tem*=-1;
        if(tem>maxp) maxp=tem;
    }
    printf("%d",maxp);
    return 0;
}

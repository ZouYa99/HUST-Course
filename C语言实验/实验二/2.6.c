#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,t,m;
     scanf("%d",&n);
    int s[n];
    for(m=0;m<n;++m)
        scanf("%d",&s[m]);
    for(i=0,t=0;i<=n-3;++i)
    {
    if(s[i]<s[i+1]&&s[i+1]>s[i+2]) ++t;
    if(s[i]>s[i+1]&&s[i+1]<s[i+2]) ++t;
    }
    printf("%d",t);
return 0;
}

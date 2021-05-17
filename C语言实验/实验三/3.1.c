#include <stdio.h>
#include <stdlib.h>

int main()
{
int i,x,k,flag=0;
printf("本程序判断合数，请输入大于1的整数，Ctrl+z结束\n");
while((scanf("%d",&x)!=EOF)&&flag==0){
     if(x==2) printf("%d 不是合数\n",x);
    i=2; k=x/2+1;
    do{
    if(!(x%i))
        flag=1;
        i++;  }
    while(i<=k);
}
    if(flag==1) printf("%d是合数\n",x);
    else printf("%d 不是合数\n",x);
return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
int i,x,k,flag=0;
printf("�������жϺ��������������1��������Ctrl+z����\n");
while((scanf("%d",&x)!=EOF)&&flag==0){
     if(x==2) printf("%d ���Ǻ���\n",x);
    i=2; k=x/2+1;
    do{
    if(!(x%i))
        flag=1;
        i++;  }
    while(i<=k);
}
    if(flag==1) printf("%d�Ǻ���\n",x);
    else printf("%d ���Ǻ���\n",x);
return 0;
}

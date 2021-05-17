#include <stdio.h>
/*纯粹合数求解器*/
int is(int x,int flag);
int main()
{
int x,flag=0;
printf("本程序判断纯粹合数\n");
for(x=100;x<1000;++x){
 if(is(x,flag)==1) {flag=0;
 if(is(x/10,flag)==1) {flag=0;
 if(is(x/100,flag)==1) printf("%d  ",x);
}
}
}
return 0;
}
int is(int x,int flag){
    int i,k;
    i=2; k=x/2+1;
     while(i<k&&flag==0){
    if(!(x%i))
        flag=1;
        i++; }
return flag;
}

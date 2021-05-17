#include <stdio.h>
#include <stdlib.h>

int main()
{
   	int year,month,day;
	int d,i;
	int mon[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	scanf("%d %d",&year,&d);
	if(!(year%4)&&year%100||!(year%400)) mon[2]=29;
	for(month=1,day=1,i=1;d>=28;++i){
    d-=mon[i];
    month++;
	}
    if(d>0) printf("This day is %d 月 %d 日",month,d);
    if(d==0) printf("This day is %d 月 %d 日 ",month-1,mon[i-1]);
return 0;
}

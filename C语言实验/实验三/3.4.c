#include <stdio.h>
#include <stdlib.h>
int organi(int ,int );
int main()
{
    int i,j,k;
    for(i=0,j=0;j<=i&&i<=9;++i){
        for(k=1;k<=38-2*i;k++) putchar(' ');
        for(;j<=i;j++) printf("%4d",organi(i,j));
        printf("\n");
        j=0;
    }
return 0;
}
int organi(int i,int j){
 int a,b,c;
 int a1,b1,c1;
 for(a1=1,a=1;a1<=j;++a1) a*=a1;
 for(b1=1,b=1;b1<=i;++b1) b*=b1;
 for(c1=1,c=1;c1<=i-j;++c1) c*=c1;
 return b/(a*c);
}

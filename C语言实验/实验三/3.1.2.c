#include <stdio.h>
#include <stdlib.h>

int main()
{   int x;
    float taxx;
    scanf("%d",&x);
    switch(x/1000){
    case 0:taxx=0;break;
    case 1:taxx=0.05*(x-1000);break;
    case 2:taxx=0.10*(x-2000)+50;break;
    case 3:taxx=0.15*(x-3000)+150;break;
    case 4:taxx=0.20*(x-4000)+300;break;
    case 5:case 6:case 7:case 8:case 9:case 10:case 11:case 12:
        taxx=0.25*(x-5000)+500;break;
    }
    printf("%f",taxx);
    return 0;
}

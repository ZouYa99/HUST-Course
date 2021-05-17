#include <stdio.h>
#include<math.h>
#define s(a,b,c) ((a+b+c)/2.0)
#define area(s,a,b,c) ((s)*((s)-(a))*((s)-(b))*((s)-(c)))
int main()
{
    int a,b,c;
    float s_,area_;
    scanf("%d%d%d",&a,&b,&c);
    s_=s(a,b,c);
    area_=area(s_,a,b,c);
    printf("%f  %f",s_,sqrt(area_));
    return 0;
}

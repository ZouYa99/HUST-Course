#include <stdio.h>
enum {lose,win};
int main()
{
float j=1000,y=2000;
    float m[16],n[16];
    int a,b,c,d;
    float number=0;
    unsigned int t;
    int x[4];
    for(a=0,t=0;a<=15&&t<=15;a++,t++){
        for(b=0;b<=3;b++){
            x[b]=(t>>b)&1;
        }
        for(c=0;c<=3;c++){
            if(x[c]==0) {j+=y/4;y=3*y/4;}
            if(x[c]==1) {y+=j/4;j=3*j/4;}
        }
        m[a]=j;n[a]=y;
        j=1000;y=2000;
    }
    for(d=0;d<=15;d++){
        if(m[d]-n[d]>-1000&&m[d]-n[d]<1000) number++;
    }
    printf("%f",number/16);
    return 0;
}

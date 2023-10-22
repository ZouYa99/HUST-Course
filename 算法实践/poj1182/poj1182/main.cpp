//
//  main.cpp
//  poj1182
//
//  Created by ZouYa on 2021/12/23.
//

#include <iostream>
using namespace::std;
#define Max 50010
int father[Max];//每个节点的父节点保存数组
//每个节点与父节点之间的关系
//0表示和父节点同类，1表示吃父节点，2表示被父节点吃
int relation[Max];

//该函数拥有查找某个节点的父节点
int findR(int x){
    if (x==father[x]) {
        //此时的x就是根节点
        return x;
    }
    int root = findR(father[x]);//递归查询根节点
    //先更新x节点和父节点之间的关系，因为x节点的父节点马上就会变成根
    //而根据递归算法，此时x的父节点的父节点一定是根节点，所以以下式子可以得到x与根节点之间的关系
    relation[x] = (relation[x]+relation[father[x]])%3;
    //更新x的父节点为根节点
    father[x] = root;
    return root;
}

int main(int argc, const char * argv[]) {
    int N,K;
    cin>>N>>K;
    int sum=0;
    int i;
    int D,X,Y;
    for (i=1; i<=N; i++) {
        //初始化父亲节点等于自己，而自己和自己的关系为同类也就是0
        father[i]=i;
    }
    while (K--) {//输入K句话
        cin>>D>>X>>Y;
        if (X>N||Y>N||((D==2)&&(X==Y))) {//一定为错误的情况
            sum++;
            continue;
        }
        if (D==1&&X==Y) {//一定为正确的情况
            continue;
        }
        int curRe = D==1?0:1;
        int rx = findR(X);
        int ry = findR(Y);
        if (rx==ry) {
            //X和Y的关系已经确定，需要判断是否与当前输入矛盾
            //(x,y)=(x,rx) (ry,y)
            int alRe = (relation[X]+(3-relation[Y])%3)%3;
            if (alRe!=curRe) {
                //不等则当前为假话
                sum++;
            }
        }else{
            //X和Y的关系到现在还不知道，所以当前一定是真话，那么更新并查集
            father[rx]=ry;
            //(rx,ry)=(rx,x) (x,y) (y,ry)
            relation[rx] = ((3-relation[X])%3+curRe+relation[Y])%3;
        }
    }
    cout<<sum<<endl;
    return 0;
}

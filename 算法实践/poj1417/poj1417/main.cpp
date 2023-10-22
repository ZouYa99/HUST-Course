//
//  main.cpp
//  poj1417
//
//  Created by ZouYa on 2021/12/28.
//

#include <iostream>
using namespace::std;
#define Max 1024
char a[10];
int father[Max];//每个节点的父节点保存数组
//每个节点与父节点之间的关系
//0表示同类，1表示不同类
int relation[Max];
int cnt[Max][2];
int dp[Max][Max],type[Max];
int a0[Max],a1[Max],ca[Max],ys[Max];

//该函数拥有查找某个节点的父节点
int findR(int x){
    if (x==father[x]) {
        //此时的x就是根节点
        return x;
    }
    int root = findR(father[x]);//递归查询根节点
    //先更新x节点和父节点之间的关系，因为x节点的父节点马上就会变成根
    //而根据递归算法，此时x的父节点的父节点一定是根节点，所以以下式子可以得到x与根节点之间的关系
    relation[x]^=relation[father[x]];
    //更新x的父节点为根节点
    father[x] = root;
    return root;
}

//该函数合并两个并查集
void unionT(int x,int y,int re){
    int rx = findR(x);
    int ry = findR(y);
    father[rx]=ry;
    //更新节点之间的关系
    //(rx,ry) = (x,rx)^(y,ry)^(x,y)
    relation[rx]=relation[x]^relation[y]^re;
}

//该函数用来从后向前递归查找好人的编号
void search(int t,int p1){
    if(!t)return;
    if(p1>=a0[t]&&dp[t-1][p1-a0[t]]){
        //在第t组中，如果此时的剩余人数还大于第0组人数，而且查看前一组的dp数量确实是从第0组转移过来的，那么把这组的好人表示为第0组，而且接着递归搜索
        type[t]=0;
        search(t-1,p1-a0[t]);
    }else{
        type[t]=1;
        search(t-1,p1-a1[t]);
    }
}

int main(int argc, const char * argv[]){
    int n,p1,p2,x,y,p;
    while((~scanf("%d%d%d",&n,&p1,&p2))&&(n||p1||p2)){
        p=p1+p2;
        //初始化数据
        for(int i=1;i<=p;++i){
            father[i]=i;
            relation[i]=0;
            cnt[i][1]=cnt[i][0]=0;
        }
        //循环输入n次询问
        while(n){
            --n;
            scanf("%d %d %s",&x,&y,a);
            if(findR(x)!=findR(y)){
                //因为x和y之间存在关系，所以合并x y所在的并查集
                if(*a=='n'){
                    unionT(x,y,1);
                }else unionT(x,y,0);
            }
        }
        //接下来问题转化成0 1背包问题
        for(int i=1;i<=p;++i){
            findR(i);//路径压缩，以便于方便知道当前节点在哪一组并查集中
            //cnt[x][y]中保存以x为父节点且关系为y的数量
            cnt[father[i]][relation[i]]++;
        }
        int t=0;//计数表示总共有几组不联通的并查集
        dp[0][0]=1;
        for(int i=1;i<=p;++i){
            if(cnt[i][0]||cnt[i][1]){
                ca[++t]=i;
                //将以父节点来查找转换成以计数t来查找
                a0[t]=cnt[i][0];
                a1[t]=cnt[i][1];
                ys[i]=t;//标识当前节点在第几组并查集中
                //初始化数量全为0
                for(int j=0;j<=p1;++j)
                    dp[t][j]=0;
                //总数量中加上以第0类人为好人的数量
                for(int j=a0[t];j<=p1;++j)
                    dp[t][j]+=dp[t-1][j-a0[t]];
                //总数量中加上以第1类人为好人的数量
                for(int j=a1[t];j<=p1;++j)
                    dp[t][j]+=dp[t-1][j-a1[t]];
            }
        }
        if(dp[t][p1]^1)//如果最终结果不为1，则就是得到结果不唯一或不存在
            printf("no\n");
        else {
            search(t,p1);//查找出所有的好人
            for(int i=1;i<=p;++i)
                //找出i的父节点所在的并查集组的序号，查看该序号是否和i与父节点的关系属于同一种人，如果是，则代表这个人为好人
                if(type[ys[father[i]]]==relation[i])
                    printf("%d\n",i);
            printf("end\n");
        }
    }
    return 0;
}

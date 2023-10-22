//
//  main.cpp
//  poj3321
//
//  Created by ZouYa on 2021/12/29.
//

#include <iostream>
#include <vector>
#define Max 100005
using namespace::std;
int arr[Max];//树状数组
int n;//输入总共多少个分叉
int apple[Max];//保存对应的分叉点上是否有apple
vector<int> tree[Max];//初始化的时候保存树的连接数据

//保存某一个节点深度优先遍历时，遍历子节点前和遍历字节点后的计数值
int start[Max],endd[Max];

int cnt;//深度优先遍历时对节点进行计数

//返回一个数字x的最低位
int lowbit(int x){
    return x&(-x);
}
//查询index为x的前缀和
int query(int x){
    int res=0;
    while (x) {
        res+=arr[x];
        x-=lowbit(x);
    }
    return res;
}

//更新数组中x位置加上v
void update(int x,int v){
    while (x<=n) {
        arr[x]+=v;
        x+=lowbit(x);
    }
}

void dfs(int r){
    cnt++;
    start[r] = cnt;//当前节点的计数值
    for (int i=0; i<tree[r].size(); i++) {
        dfs(tree[r][i]);
    }
    endd[r] = cnt;//遍历r的子节点后，标注r此时结束的计数值
}

int main(int argc, const char * argv[]) {
    scanf("%d",&n);
    cnt = 0;
    for (int i=0; i<n-1; i++) {//输入n-1条边，构建树
        int a,b;
        scanf("%d%d",&a,&b);
        tree[a].push_back(b);
    }
    dfs(1);//树的根节点一定是1
    for (int i=1; i<=n; i++) {
        update(i, 1);//给每个节点上都加上1，表示当前这个节点上有苹果
        apple[i]=1;//标注当前节点上有苹果
    }
    int m,x;
    char str[5];
    scanf("%d",&m);
    while (m--) {
        scanf("%s%d",str,&x);
        if (str[0]=='Q') {//如果查询
            //查询x的所有子节点后的前缀和，查询x前的子节点的前缀和
            //两者相减得到区间和
            int cur = query(endd[x])-query(start[x]-1);
            cout<<cur<<endl;
        }else{//更改
            if (apple[x]) {//如果当前有苹果，则表示摘下这个苹果
                apple[x] = 0;
                update(x, -1);
            }else{//如果当前没有苹果，则长出一个苹果
                apple[x] = 1;
                update(x, 1);
            }
        }
    }
    return 0;
}

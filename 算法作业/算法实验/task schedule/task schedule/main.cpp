//
//  main.cpp
//  task schedule
//
//  Created by ZouYa on 2021/12/15.
//

#include <iostream>
#include <limits.h>
#include <cstring>
#include <queue>
using namespace std;
struct edge {
    int to, w, next;
} edges[2000];
int index_cnt;
int tag[2000];//表示节点对应的计数数
int mark[2000];

void add_edge(int u, int v, int w) {
    //从前向后的边
    edges[index_cnt].to=v;
    edges[index_cnt].w=w;
    edges[index_cnt].next=tag[u];
    tag[u]=index_cnt++;
    //反向边
    edges[index_cnt].to=u;
    edges[index_cnt].w=0;
    edges[index_cnt].next=tag[v];
    tag[v]=index_cnt++;
}

int bfs(int s, int t) {
    queue<int> q;//bfs queue保存
    memset(mark, 0, sizeof(mark));
    q.push(s);
    mark[s] = 1;
    int top;
    while(!q.empty()) {
        top = q.front();
        q.pop();
        for(int i = tag[top];i+1; i=edges[i].next) {
            int v = edges[i].to;
            int w = edges[i].w;
            if(!mark[v]&&w) {
                mark[v] = mark[top]+1;
                q.push(v);
            }
        }
    }
    return mark[t];
}

int dfs(int s, int t, int flow) {
    if(s==t) return flow;
    int cur_flow=0;
    for(int i=tag[s]; i+1; i=edges[i].next) {
        if(edges[i].w && mark[s]+1 == mark[edges[i].to]) {
            int x = dfs(edges[i].to,t,min(flow, edges[i].w));
            if(x>0) {
                cur_flow+=x;
                flow-=x;
                edges[i].w -= x;
                edges[i^1].w += x;
                if(flow<=0) break;
            }
        }
    }
    if(!cur_flow) mark[s] = -2;
    return cur_flow;
}

int main() {
    int n, m, p, s, e;
    index_cnt = 0;
    memset(tag, -1, sizeof(tag));
    cin>>n;
    cin>>m;
    int l = INT_MAX, r = 0, sum = 0;
    for(int i = 1;i <= n; ++i) {
        cin>>p;
        cin>>s;
        cin>>e;
        sum += p;
        l = l<s?l:s;
        r = r>e?r:e;
        //加入从源点到任务
        add_edge(0, i, p);
        for(int j = s;j <= e; j++) {
            add_edge(i, j+n, 1);
        }
    }
    int out = r+n+1;//出节点的序号
    //日期和出节点相连
    for(int i = l; i <= r; ++i) {
        add_edge(i+n, out, m);
    }
    //调用最大流算法并判断是否和所有任务所需天数加起来一致
    int f = 0;
    while(bfs(0,out)){
        f += dfs(0,out,INT_MAX);
    }
    if (f==sum) {
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
}


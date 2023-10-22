//
//  main.cpp
//  Candies
//
//  Created by ZouYa on 2021/12/31.
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace::std;
#define INF 0x3f3f3f3f
#define maxn 150100

int n, m;
int cnt;//累加值
int pre[maxn], last[maxn];//记录边的顺序
int to[maxn];//记录边的目的节点
int weight[maxn];//记录边的权值
int dis[maxn];//用于Dijkstra算法记录起始点到各个节点的距离

struct Node {
    int index, v;
    Node () {}
    Node (int a, int b) : index(a), v(b) {}
    bool friend operator < (Node x, Node y) {
        //传入Node节点的v值越大，在优先队列中的优先值越小
        //换而言之，就是把边权值最小的边放在优先队列的top，以便查找最短路
        return x.v > y.v;
    }
};

void add_edge(int u, int v, int w) {
    pre[++cnt] = last[u];//记录以x为起点的边的前一条边
    last[u] = cnt;//记录当前边
    to[cnt] = v;//记录当前边的目的节点
    weight[cnt] = w;//记录当前边的权值
}

void dijkstra(int s) {
    //经典dijkstra算法跑最短路，因为不会有负的糖果数
    for(int i = 1; i <= n; i++)
        dis[i] = INF;
    dis[s] = 0;
    priority_queue<Node> pq;
    pq.push(Node(s, 0));
    while(!pq.empty()) {
        Node cur = pq.top();pq.pop();
        int p = last[cur.index];
        while(p != -1) {
            int dr = to[p];
            if(dis[cur.index] + weight[p] < dis[dr]) {
                //如果某个节点的距离比已有的距离点到该节点之间权值之和大，那么就更新这个距离
                dis[dr] = dis[cur.index] + weight[p];
                pq.push(Node(dr, dis[dr]));
            }
            p = pre[p];
        }
    }
}

int main(int argc, const char * argv[]){
    scanf("%d%d", &n, &m);
    cnt = -1;
    memset(last, -1, sizeof(last));
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d",&u,&v,&w);
        //建立u->v, 边权为w的有向边
        //表示添加candies[v]-candies[u]<=w的约束
        add_edge(u, v, w);
    }
    dijkstra(1);
    printf("%d\n", dis[n]);
    return 0;
}

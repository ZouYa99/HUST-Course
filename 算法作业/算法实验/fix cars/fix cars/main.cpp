//
//  main.cpp
//  fix cars
//
//  Created by ZouYa on 2021/12/15.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace::std;
const int inf = 0x3f3f3f3f;
int n, m;
int map[100][100];
int minf;
int s,t;

struct Edge{
    int v, w, flow, next;
    Edge(){}
    Edge(int cv,int cw,int cf,int cn):v(cv),w(cw),flow(cf),next(cn){}
}edges[100*100*10];

int head[100*100*5], k;

bool vis[100*100*5];
int dis[100*100*5];
int pre[100*100*5];

queue <int> q;

bool spfa(){
    memset(dis, 0x3f, sizeof(dis));
    minf = inf;
    
    dis[s] = 0;
    q.push(s);
    
    while(!q.empty()){
        int u = q.front(); q.pop();
        vis[u] = 0;
        
        for(int i = head[u]; ~i; i = edges[i].next){
            int v = edges[i].v;
            if(edges[i].flow && dis[v] > dis[u] + edges[i].w)
            {
                dis[v] = dis[u] + edges[i].w;
                pre[v] = i;
                minf = min(minf,edges[i].flow);
                if(!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dis[t] < inf;
}

void add_edge(int u, int v, int f, int w){
    edges[k] = Edge(v, w, f, head[u]);
    head[u] = k++;
    edges[k] = Edge(u, -w, 0, head[v]);
    head[v] = k++;
}

int main(){
    cin >> m >> n;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j)
        {
            cin>>map[j][i];
        }
    }
    
    int cnt = n;
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= m; ++i){
        for(int k = 1; k <= n; ++k){
            cnt++;
            for(int j = 1; j <= n; ++j)
            {
                add_edge(cnt, j, 1, map[i][j] * k);
            }
        }
    }
    s = 0; t = cnt + 1;
    
    for(int i = 1; i <= n; ++i){
        add_edge(i, t, 1, 0);
    }
    for(int i = n + 1; i <= cnt; ++i){
        add_edge(s, i, 1, 0);
    }
    
    int ans = 0;
    while(spfa()){
        for(int i = t; i != s; i = edges[pre[i]^1].v){
            edges[pre[i]].flow -= minf;
            edges[pre[i]^1].flow += minf;
        }
        ans += minf*dis[t];
    }
    printf("%.2f\n", (double)ans / n);
    return 0;
}

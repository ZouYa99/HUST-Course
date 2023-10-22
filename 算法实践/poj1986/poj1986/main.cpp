//
//  main.cpp
//  poj1986
//
//  Created by ZouYa on 2021/12/31.
//

#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int n, m, e, k;
vector<int>q[100010];//存放边的另一个点
int head[100010], vis[100010], dis[100010], father[100010];//dis为节点到根节点的距离
struct Edge
{
    int to;
    int w;
    int next;
}edge[10000000];

struct Ans
{
    int x;//查询输入时的第一个点
    int y;//查询输入时的第二个点
    int ff;//该查询的结果
}ans[10005];

void add(int a, int b, int c)
{
    edge[e].w = c;
    edge[e].to = b;
    edge[e].next = head[a];
    head[a] = e;
    e++;
}
void init()
{
    int i;
    for (i = 1; i <= n; i++)
        father[i] = i;
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
}
int find(int a)//找根节点
{
    if (father[a] != a)
        father[a] = find(father[a]);
    return father[a];
}

void merge(int x, int y)//合并
{
    int rx = find(x);
    int ry = find(y);
    if (rx != ry)
        father[rx] = ry;
}

void lca(int x)
{
    int i, j;
    vis[x] = 1;//x点标记已被访问过
    for (i = head[x]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (vis[v] == 0)//跳过已经访问过的点
        {
            dis[v] = dis[x] + edge[i].w;
            lca(v);//以v为根节点遍历其子树
            merge(v, x);
        }
    }
    for (i = 0; i < q[x].size(); i++)
    {
        if (vis[q[x][i]] == 1)
        {
            for (j = 0; j < k; j++)
                if (ans[j].x == x && ans[j].y == q[x][i] || ans[j].x == q[x][i] && ans[j].y == x)
                {
                    int t = find(q[x][i]);
                    ans[j].ff = dis[x] + dis[q[x][i]] - 2 * dis[t];
                }
        }
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        init();
        e = 0;
        int i, j;
        int a, b, c;
        char s;
        for (i = 1; i <= m; i++)
        {
            scanf("%d%d%d %c", &a, &b, &c, &s);
            add(a, b, c);//添加边，因为边在后续的遍历可能反向，因此要加两条
            add(b, a, c);
        }
        scanf("%d", &k);
        for (i = 0; i < k; i++)
        {
            scanf("%d%d", &a, &b);
            q[a].push_back(b);//同上，添加点的边的另一个点
            q[b].push_back(a);
            ans[i].x = a;//查询存入ans
            ans[i].y = b;
        }
        lca(1);
        for (i = 0; i < k; i++)
            printf("%d\n", ans[i].ff);//输出ans中的值
    }
    return 0;
}

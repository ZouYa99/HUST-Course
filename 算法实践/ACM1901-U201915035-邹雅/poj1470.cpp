//
//  main.cpp
//  poj1470
//
//  Created by ZouYa on 2021/12/31.
//

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int MAXN = 910;
int n,m;
int flag[MAXN];//标志该节点是否为某个点的子节点（根据这个来找根）
vector<int> G[MAXN];//G[i]表示以i为初节点开始的边组成的vector
int ques[MAXN][MAXN];//ques[i][j]表示查询时查询i和j的LCA（ij是根据输入的顺序）
int vis[MAXN], father[MAXN], cnt[MAXN];

int find(int x)
{
    if (x == father[x])
        return x;
    return x = find(father[x]);
}

void tarjan(int x)
{
    father[x] = x;//将x的根置为x
    for (int i = 0; i < G[x].size(); i++)
    {
        tarjan(G[x][i]);//遍历以子节点G[x][i]的子树
        father[G[x][i]] = x;//还原子节点G[x][i]的父节点
    }
    vis[x] = 1;//该点已经被访问过
    for (int i = 1; i <= n; i++)
    {
        if (ques[x][i] && vis[i])   cnt[find(i)] += ques[x][i];//若i之前已经遍历过，则说明lca为i的根节点
        if (ques[i][x] && vis[i])   cnt[find(i)] += ques[i][x];//同上
    }
}

void init() {//初始化，将各变量内容全部清空
    memset(ques, 0, sizeof(ques));
    memset(vis, 0, sizeof(vis));
    memset(father, 0, sizeof(father));
    memset(cnt, 0, sizeof(cnt));
    memset(flag, 0, sizeof(flag));
    for (int i = 0; i < MAXN; i++)
    {
        G[i].clear();
    }
}

int main()
{
    int x,y,num,s;
    while (~scanf("%d", &n))
    {
        init();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d:(%d)", &x, &num);
            for (int j = 1; j <= num; j++)
            {
                scanf(" %d", &y);
                G[x].push_back(y);//加入边
                flag[y] = 1;//y点为x的子节点，作标记
            }
        }
        int u, v;
        scanf(" %d", &m);//记录查询问题
        for (int i = 1; i <= m; i++)
        {
            scanf(" (%d %d)", &u, &v);
            ques[u][v]++;
        }

        for (s = 1; s <= n; s++)    if (flag[s] == 0) break;//定位根节点s

        tarjan(s);//从根节点开始往下遍历

        for (int i = 1; i <= n; i++)//打印结果，非0值
        {
            if (cnt[i])
                printf("%d:%d\n", i, cnt[i]);
        }
    }
    return 0;
}

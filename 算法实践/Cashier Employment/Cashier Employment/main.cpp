//
//  main.cpp
//  Cashier Employment
//
//  Created by ZouYa on 2021/12/31.
//

#include <iostream>
#include <queue>
#include <cstring>
using namespace::std;
#define maxn 100
#define INF 0x3f3f3f3f
/*
 R[i]表示在第 i 个小时至少也要的人数，
 Ts[i]表示应聘者中可以在第i个小时开始工作的人数,
 s[i]表示前i个小时雇佣的人数
 */
int R[25],Ts[25];
int s[25];
/*
 差分约束如下：
 1. 0 <= s[i]-s[i-1] <= work[i]
 某一个小时雇佣的人数不能超过在这个小时来应聘的总人数
 2.i>=8   need[i] <= s[i] - s[i - 8]
 八个小时前雇佣的人已经下班了，那么i时雇佣的人减去下班的人必须要大于此时所需要的人
 s[24]代表了前24小时雇佣的总人数，也就是我们最终要求出的雇佣人数
 i<8  s[i] + s[24] - s[16 + i] >= need[i]
 此时存在跨天的现象，在7点前都存在前一天的员工还在工作的情况，而雇佣总人数减去前16+i个小时雇佣的人就代表了后来能工作到i点的人，加上第二天雇佣的到i点的人，要比所需要的人多
 3.s[24]-s[0] >= sum sum表示最终我们一天内雇佣的总人数
 出现了sum这个未知数，求解的时候我们需要从小到大枚举sum的值, 直到SPFA求解最短路成功时即可停止, 或者二分枚举sum以加快速度.
 */
int N;//应聘者的人数
struct Edge {
    int u, v, w;//边的起始点，终止点和权值
    int next;
};//建立图的边

Edge edges[maxn];
int dist[maxn], head[maxn], used[maxn], cnt;
bool vis[maxn];

void add(int u, int v, int w){//在图中增加一条边
    edges[cnt] = {u, v, w, head[u]};
    head[u] = cnt++;
}

void add_constraint(int sum){//按照之前写的不等式添加边，代表约束
    for(int i = 1; i <= 24; ++i){
        add(i - 1, i, 0);
        add(i, i - 1, -Ts[i]);
        if(i >= 8)
            add(i - 8, i, R[i]);
        else
            add(16 + i, i, R[i] - sum);
    }
    add(0, 24, sum);
}

int SPFA(int sum){//经典spfa求解最长路
    for(int i = 0; i <= 24; ++i){
        dist[i] = -INF;
        vis[i] = 0;
        used[i] = 0;
    }
    dist[0] = 0;
    vis[0] = 1;
    used[0] = 1;
    queue<int>q;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for(int i = head[u]; i != -1; i = edges[i].next){
            int v = edges[i].v;
            int w = edges[i].w;
            if(dist[v] < dist[u] + w){
                dist[v] = dist[u] + w;
                if(!vis[v]){
                    vis[v] = 1;//标记节点
                    used[v]++;
                    if(used[v] > 24)
                        return 0;
                    q.push(v);
                }
            }
        }
    }
    //如果最后求得的24小时雇佣人数和枚举传入的sum一致，代表此时找到的最长路有效
    return dist[24] == sum;
}

int main (){
    int runtime;
    int flag, st;
    scanf("%d", &runtime);
    while(runtime--){
        flag = 0;
        memset(R, 0, sizeof(R));
        memset(Ts, 0, sizeof(R));
        for(int i = 1; i <= 24; ++i)//因为无法处理负值所以前移一位进行保存
            scanf("%d", &R[i]);//输入每个小时所需要的人数
        scanf("%d", &N);
        for(int i = 1; i <= N; ++i){//统计第st小时时可以雇佣的人数
            scanf("%d", &st);
            Ts[st+1]++;
        }
        for(int i = 0; i <= N; ++i){//枚举sum，也可采用二分法进行枚举
            cnt = 0;
            memset(head, -1, sizeof(head));
            add_constraint(i);
            if(SPFA(i)){//如果此时返回有效spfa，则输出这时枚举到的sum，并且退出不用继续循环
                flag = 1;
                printf("%d\n", i);
                break;
            }
        }
        if(!flag)
            printf("No Solution\n");
    }
    return 0;
}

//
//  main.cpp
//  poj1990
//
//  Created by ZouYa on 2021/12/30.
//

#include <iostream>
#include <algorithm>
#define lowbit(a) ((a)&-(a))
using namespace std;
typedef long long ll;
const ll Max =  1e5;
ll arr[2][Max];//二维树状数组  0:数量统计 1:坐标和
ll n;
struct Edge{
    ll v,w;
}edges[Max];//输入v代表音量，w代表位置
bool cmp(Edge a,Edge b){return a.v<b.v;}

void update(ll x,ll d){
    //在第0维中，更新为到当前牛的数量
    //在第1维中，更新为坐标和
    for(ll i=x;i<=Max-1;i+=lowbit(i))
        arr[d][i] += d?x:1;
}
//查询index为x的前缀和
ll query(ll x,ll d){
    ll ans = 0;
    for(ll i=x;i;i-=lowbit(i))
        ans += arr[d][i];
    return ans;
}

int main(){
    cin >> n;
    for (ll i=1; i<=n; i++) {
        cin >> edges[i].v >> edges[i].w;
    }
    sort(edges+1,edges+1+n,cmp);//按照音量从小到大排序
    //从小到大排序之后，牛i的音量一定比在他前面的牛的音量大，所以可以省略了在两头牛之间比较音量取max大部分，直接取edges[i].v即可
    ll ans = 0;//保存最终的音量结果
    ll lsum,rsum;
    ll num,xsum;
    ll all = 0;
    for (ll i=1; i<=n; i++){
        num = query(edges[i].w,0); //查询到第i头牛的总数
        xsum = query(edges[i].w,1); //比第i头牛小的牛的x坐标位置和
        lsum = num*edges[i].w-xsum; //在牛i左边的位置差和
        //在牛i右边的位置差和
        rsum = all - xsum - (i-num-1)*edges[i].w;
        ans += (lsum+rsum)*edges[i].v;//位置和乘以当前牛的音量
        all += edges[i].w;  //坐标总和
        update(edges[i].w,0);//更新到第i头牛的数量和
        update(edges[i].w,1);//更新到第i头牛的位置坐标和
    }
    cout << ans << endl;
    return 0;
}

/*
 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 40100
int N,cnt,h[maxn];
struct Node{
    //cover变量标记当前节点是在区间左侧还是区间右侧
    int x,h,cover;
}node[maxn<<3];

struct Tree{
    int l,r,cover,len;
}tree[maxn<<3];

bool cmp(Node a,Node b){
    return a.x < b.x;
}

void build_tree(int l,int r,int i){
    //线段树节点l保存左端点对应的高度，r对应右端点对应的高度
    tree[i].l=h[l];
    tree[i].r=h[r];
    if(r==l+1)return;
    int mid=(l+r)>>1;
    //从中间开始递归建立线段树
    build_tree(l,mid,i<<1);//左节点
    build_tree(mid,r,i<<1|1);//右节点
}

void push_up(int l,int r,int i){
    if(tree[i].cover){
        tree[i].len=tree[i].r-tree[i].l;
    }else if(l+1==r)
        tree[i].len=0;
    else
        tree[i].len=tree[i<<1].len+tree[i<<1|1].len;
}

void update_tree(int l,int r,int i,Node node){
    if(tree[i].r<=node.h){
        tree[i].cover+=node.cover;
        push_up(l,r,i);
        return;
    }
    int mid=(l+r)>>1,lson=i<<1,rson=i<<1|1;
    if(tree[lson].r>=node.h)
        update_tree(l,mid,lson,node);
    else{
        update_tree(l,mid,lson,node);
        update_tree(mid,r,rson,node);
    }
    push_up(l,r,i);
}

int main(){
    scanf("%d",&N);
    int a,b;
    for(int i=1;i<=N;i++){
        scanf("%d%d%d",&a,&b,&h[i]);
        node[++cnt].x=a;
        node[cnt].h=h[i];
        node[cnt].cover=1;
        node[++cnt].x=b;
        node[cnt].h=h[i];
        node[cnt].cover=-1;
    }
    //按照节点的x坐标进行从小到大排序
    sort(node+1,node+1+cnt,cmp);
    sort(h+1,h+1+N);
    //对所有保存的高度进行去重
    int s = unique(h+1,h+1+N)-h-1;
    build_tree(0,s,1);
    update_tree(0,s,1,node[1]);
    long long ans=0;
    for(int i=2;i<=cnt;i++){
        //面积坐标等于从第i个x坐标减去前一个坐标，也就是两点之间的距离乘以线段树中的根节点的高度
        //tree线段树一开始建树时保存的值为排序好的高度，而随着每一次的更新，根节点中保存的值都变为了当前node区间对应的最高的高度
        ans+=(long long)(node[i].x-node[i-1].x)*tree[1].len;
        update_tree(0,s,1,node[i]);
    }
    printf("%lld\n",ans);
}

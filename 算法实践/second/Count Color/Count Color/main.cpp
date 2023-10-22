/*
 我们已知颜色不会超过30种，所以可以直接使用int的32位来表示颜色，每一位代表一个颜色。根据位运算来对颜色进行统计，可以避免很多麻烦。
 由此可以定义出三张对颜色定义的操作：
 1.输入颜色t，那么对应的颜色值应该是1<<(t-1)，颜色为1时对应第0位，以此类推
 2.返回一个保存好的颜色v，统计出v中32位二进制中1的个数，代表的就是颜色的总数
 3.在线段树的两个子节点中合并颜色数v1、v2，颜色数总和应该是v1|v2后1的位数
 
 接下去我们只要按照线段树固定思路进行解题即可。
 注意在线段树中，由于我们是从下标1开始的，所以下标i的左子节点就是2*i，而右子节点就是2*i+1，这符合二叉树的定义。
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100100;
//sum求和，add为懒惰标记
int add[maxn<<2];
int sum[maxn<<2];

void push_up(int i){
    sum[i] = sum[i<<1] | sum[i<<1|1];
}

void push_down(int i,int m){
    if(add[i]){
        add[i<<1] = add[i];
        add[i<<1|1] = add[i];
        sum[i<<1] = add[i];
        sum[i<<1|1] = add[i];
        add[i] = 0;
    }
}
void build_tree(int l,int r,int i){
    add[i] = 0;//初始化时所有结点未被标记
    if (l == r){
        sum[i] = 1;//已知初始时board上的颜色为T1
        return ;
    }
    int mid = (l + r) >> 1;
    build_tree(l , mid , i << 1);
    build_tree(mid + 1 , r , i << 1 | 1);
    push_up(i);
}

void update_tree(int L,int R,int c,int l,int r,int i){
    if (L <= l && r <= R){
        add[i] = 1<<(c-1);
        sum[i] = 1<<(c-1);
        return ;
    }
    push_down(i , r - l + 1);
    int mid = (l + r) >> 1;
    if (L <= mid)
        update_tree(L , R , c , l , mid , i << 1);
    if (mid < R)
        update_tree(L , R , c , mid + 1 , r , i << 1 | 1);
    push_up(i);
}

int query_tree(int L,int R,int l,int r,int i){
    if (L <= l && r <= R){
        return sum[i];
    }
    //要取rt子节点的值时，也要先把rt的延迟标记向下移动
    push_down(i , r - l + 1);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (L <= mid)
        ans |= query_tree(L , R , l , mid , i << 1);
    if (mid < R)
        ans |= query_tree(L , R , mid + 1 , r , i << 1 | 1);
    return ans;
}

void swap(int& a,int &b){
    int t = a;
    a = b;
    b = t;
}

int main(){
    int L, T, O;
    int a, b, c;
    scanf("%d%d%d",&L,&T,&O);
    build_tree(1, L, 1);//建树
    while(O--){
        char op[2];
        scanf("%s",op);
        if(op[0] == 'P'){
            scanf("%d%d",&a,&b);
            if(a > b){
                swap(a,b);
            }
            int v = query_tree(a, b, 1, L, 1);
            int ans = 0;
            while(v){
                if(v&1){
                    ans++;
                }
                v>>=1;
            }
            printf("%d\n",ans);
        }
        else{
            scanf("%d%d%d",&a,&b,&c);
            if(a > b){
                swap(a,b);
            }
            update_tree(a, b, c, 1, L, 1);
        }
    }
    return 0;
}

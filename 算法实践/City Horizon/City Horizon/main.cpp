//
//  main.cpp
//  City Horizon
//
//  Created by ZouYa on 2021/12/31.
//

#include <iostream>
#include <algorithm>
using namespace::std;
#define maxn 40010
/*
 所有的矩形的一边在一条直线上，故而所有的矩形可以在这条直线上投影。所以，我们可以把矩形投影成直线上的线段且线段都有一个权值，该权值是矩形的高度Hi。
 于是可以利用线段树进行处理，计算面积并就相当于计算带权的线段并。当某条线段被多次覆盖时，只取高度值最大的进行计算。
 由于题目中矩形的左右坐标的范围非常大(1 <= Ai,Bi <= 10^9)
 如果建立大小为[1, 10^9)的线段树则会占用大量的空间。
 需要采用离散化的思想来处理这个问题。
 将线段的左右端点进行排序，并且赋上新的值，就可以在一个更小的空间内进行处理。
 每次加入一个矩形就是在线段树上插入一条带权的线段。
 如果当前线段完全覆盖了节点所代表的线段，则比较线段的权值大小。
 如果节点所代表的线段的权值小或者在之前未被覆盖，则将其权值更新为当前线段的权值。
 */
struct Building{
    int left,right;//建筑的左右坐标
    int height;//建筑的高度
}buildings[maxn];
bool operator < (const Building &a, const Building &b){
    return a.height < b.height;
}//建筑排序时按照建筑的高度从小到大排序
int discrete_num;//标记离散化的数量值
int N;//建筑数量
//记录所有坐标值，便于离散化，由于一个建筑具有左右两个节点，所以需要把数组放大为两倍
int discrete[maxn*2];
struct Node{
    int l, r;
    long long h,value;
    Node *left, *right;
}tree[maxn*4];//建立线段树保存数值
int node_cnt;//线段树节点计数

void build_tree(Node *root, int s, int e){
    //树的左边节点值为该节点覆盖的左端点值，右边节点值为该节点覆盖的右端点值
    root->l = s;root->r = e;root->h = 0;root->value = 0;
    if (s == e){//如果此时两端的值相等，那么表示无需再往下分
        root->left = root->right = NULL;
        return;
    }
    root->left = tree + (++node_cnt);
    root->right = tree + (++node_cnt);
    int mid = (s + e)>>1;
    //递归建树
    build_tree(root->left, s, mid);
    build_tree(root->right, mid + 1, e);
}

void update_tree(Node *proot, int start, int end, long long h){
    if (start > proot->r || end < proot->l)//[start,end]区间值和节点区间错开时直接返回
        return;
    start = max(start, proot->l);
    end = min(end, proot->r);
    if (start == proot->l && end == proot->r){
        //[start,end]区间值和节点区间正好一致时更新该节点
        proot->h = h;//更新节点的h值为高度值
        //更新节点的value值为面积值，因为此时的l、r都是离散化后的，所以要重新去离散数组中找到真正的x坐标
        proot->value = h * (discrete[proot->r + 1] - discrete[proot->l]);
        return;
    }
    //当前节点的h值在建树过程中会更新为0，如果当前节点在树上，而且左右区间不一致时，递归更新左节点的区间和右节点的区间
    if (proot->h != -1 && proot->r != proot->l){
        update_tree(proot->left, proot->left->l, proot->left->r, proot->h);
        update_tree(proot->right, proot->right->l, proot->right->r, proot->h);
        proot->h = -1;
    }
    //用这个高度去再去递归更新左右子节点的值
    update_tree(proot->left, start, end, h);
    update_tree(proot->right, start, end, h);
    //父节点的value等于左右两节点value和
    proot->value = proot->left->value + proot->right->value;
}

//简单的二分查找，找到某个值在离散化数组中的index
int binary_search(int start, int end, int a){
    int l = start;
    int r = end;
    while (l <= r){
        int mid = l+((r-l)>>1);
        if (discrete[mid] == a){
            return mid;
        }else if(discrete[mid]>a){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return l;
}

int main(int argc, const char * argv[]) {
    discrete_num=0;
    node_cnt = 0;
    scanf("%d",&N);
    for (int i=0; i<N; i++) {
        scanf("%d%d%d",&buildings[i].left,&buildings[i].right,&buildings[i].height);
        discrete[discrete_num++]=buildings[i].left;
        discrete[discrete_num++]=buildings[i].right;
    }
    sort(buildings,buildings+N);//将建筑按照高度从低到高进行排序
    sort(discrete, discrete + discrete_num);//把所有坐标进行排序
    discrete_num = unique(discrete, discrete + discrete_num) - discrete;//去重后得出总共需要离散化的值
    
    build_tree(tree, 0, discrete_num - 2);
    for (int i =0; i < N; i++){
        //二分查找，来找到离散化的数组中的index，此时这个index就代表离散化后的数值
        int l = binary_search(0, discrete_num - 1, buildings[i].left);
        int r = binary_search(0, discrete_num - 1, buildings[i].right);
        //将建筑的高度加入线段树，在离散化的l、r之间的线段值都去更新为当前建筑的高度
        update_tree(tree, l, r - 1, buildings[i].height);
    }
    //线状树的头节点代表的是所有的树的总和
    printf("%lld\n", tree->value);
    return 0;
}

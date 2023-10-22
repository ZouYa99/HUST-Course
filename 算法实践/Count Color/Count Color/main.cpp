//
//  main.cpp
//  Count Color
//
//  Created by ZouYa on 2021/12/31.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1e5 + 5;
int l, t, o, a, b, c;//输入题目时所需要的变量
//lazy数组记录区间修改值，下推标记  color数组保存颜色
int lazy[maxn << 2], color[maxn << 2];

void push_down(int index) {
    if (lazy[index] == 0) return;
    //将左右子节点的值都更新为当前的值
    lazy[index<<1] = lazy[(index<<1)|1] = lazy[index];
    color[index<<1] = color[(index<<1)|1] = lazy[index];
    lazy[index] = 0;
}

int query_tree(int index,int l, int r, int x, int y) {
    //x,y表示查询区间，l,r表示节点的左右端点
    if (x <= l && r <= y) {//如果该节点包含在查询区间内则返回该值
         return color[index];
    }
    push_down(index);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (x <= mid){
        //如果查询区间x小于当前所在区间，那要继续往左边的区间寻找，左子节点的index=2*index
        ans |= query_tree(index<<1, l, mid, x, y);
    }
    if (y > mid){
        //如果查询区间y大于当前所在区间，那要继续往右边的区间寻找，右子节点index=2*index+1
        ans |= query_tree((index<<1)|1, mid + 1, r, x, y);
    }
    return ans;
}

void update_tree(int index, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) {
        color[index] = lazy[index] = v;
        return;
    }
    push_down(index);
    int mid = (l + r) >> 1;
    if (x <= mid){
        update_tree(index << 1, l, mid, x, y, v);
    }
    if (y > mid){
        update_tree((index << 1)|1, mid + 1, r, x, y, v);
    }
    //区间进行合并时采取 或 操作，相当于要把两个数总共有的二进制位数统计出来
    color[index] = color[index<<1] | color[(index<<1)|1];
}

//二进制上的每一位来表示一种颜色,统计x二进制时的1的位数也就是统计此时一共有几种颜色
int count_color(int x) {
    int cnt = 0;
    while (x) {
        if(x & 1) {
            cnt++;
        }
        x >>= 1;
    }
    return cnt;
}

int main(int argc, const char * argv[]) {
    char code[2];
    //开始时板上颜色都为1 进行初始化
    color[1] = lazy[1] = 1;
    scanf("%d%d%d", &l, &t, &o);
    for (int i = 1; i <= o; i++) {
        scanf("%s", code);
        if (code[0] == 'C') {
            scanf("%d%d%d", &a, &b, &c);
            if (a > b) {
                //如果长度区间中a>b,那么传入时两个值也得互换顺序
                //1<<(c - 1)，用二进制位数来表示第几种颜色
                update_tree(1,1,l,b,a,1<<(c - 1));
            }else{
                update_tree(1,1,l,a,b,1<<(c - 1));
            }
        } else {
            scanf("%d%d", &a, &b);
            if (a > b) {
                printf("%d\n", count_color(query_tree(1, 1, l, b, a)));
            }else{
                printf("%d\n", count_color(query_tree(1, 1, l, a, b)));
            }
        }
    }
    return 0;
}


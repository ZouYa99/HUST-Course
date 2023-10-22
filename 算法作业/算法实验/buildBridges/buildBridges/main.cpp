//
//  main.cpp
//  buildBridges
//
//  Created by ZouYa on 2021/11/19.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace::std;
//输入节点的保存
typedef struct{
    int x;
    int y;
} point;
typedef struct{
    int src;
    int dest;
    double weight;
} edge;
//并查集路径压缩优化
typedef struct{
    int parent;
    int rank;
} subset;
int myCmp(edge a, edge b){
    return a.weight < b.weight;
}
int find(subset subsets[], int i){
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void Union(subset subsets[], int x, int y){
    int xroot = find(subsets,x);
    int yroot = find(subsets,y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
double kruskal(vector<edge>& edges,int points){
    int sizeOfEdges = edges.size();
    sort(edges.begin(), edges.end(), myCmp);
    subset* subsets = new subset[(points*sizeof(subset))];
    for (int i=0;i<points ; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    int e=0,i=0;
    edge results[points-1];
    while (e<points-1 && i<sizeOfEdges) {
        edge nextEdge = edges[i++];
        if (nextEdge.weight<10||nextEdge.weight>1000) {
            continue;
        }
        int xroot = find(subsets,nextEdge.src);
        int yroot = find(subsets,nextEdge.dest);
        if (xroot!=yroot) {
            results[e++]=nextEdge;
            Union(subsets,nextEdge.src,nextEdge.dest);
        }
    }
    if (e<points-1) {
        return -0.10;
    }
    double allWeights = 0;
    for (int j=0; j<e; j++) {
        allWeights+=results[j].weight;
    }
    return allWeights*double(100);
}
int main(int argc, const char * argv[]) {
    int n;
    cin>>n;
    point points[n];
    for (int i=0; i<n; i++) {
        cin>>points[i].x;
        cin>>points[i].y;
    }
    vector<edge> edges;
    for(int i=0;i<n;i++){
        for (int j=i+1; j<n; j++) {
            edge current;
            current.src=i;
            current.dest=j;
            current.weight=sqrt(pow(points[i].x-points[j].x, 2)+pow(points[i].y-points[j].y, 2));
            edges.push_back(current);
        }
    }
    double price = kruskal(edges, n);
    if (price<0) {
        cout<<"No!";
    }else{
        cout.setf( ios::fixed);
        cout << setprecision(1) << price << endl;
    }
    return 0;
}

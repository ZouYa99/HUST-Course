//
//  main.cpp
//  stone&score
//
//  Created by ZouYa on 2021/12/14.
//

#include <iostream>
using namespace::std;
int main(int argc, const char * argv[]) {
    // insert code here...
    int n,i,j;
    cin>>n;
    int stone[2*n];
    for (i=0; i<n; i++) {
        cin>>stone[i];
        stone[i+n]=stone[i];
    }
    int sum[2*n];
    sum[0]=stone[0];
    for (i=1; i<2*n; i++) {
        sum[i] = sum[i-1]+stone[i];
    }
    int minm[2*n][2*n],maxm[2*n][2*n];
    memset(minm, 0, sizeof(int)*2*n*2*n);
    memset(maxm, 0, sizeof(int)*2*n*2*n);
    for(i=2*n-1; i >= 0; i--) {
        for(j=i+1; j<i+n&&j<2*n; j++) {
            minm[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                maxm[i][j] = max(maxm[i][j], maxm[i][k] + maxm[k + 1][j] + sum[j] - sum[i - 1]);
                minm[i][j] = min(minm[i][j], minm[i][k] + minm[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }
    int minv = INT_MAX,maxv = 0;
    for (int i = 1; i <= n; i++) {
        maxv = max(maxv, maxm[i][i + n - 1]);
        minv = min(minv, minm[i][i + n - 1]);
    }
    cout<<minv<<endl;
    cout<<maxv<<endl;
    return 0;
}

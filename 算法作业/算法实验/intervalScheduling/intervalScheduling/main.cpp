//
//  main.cpp
//  intervalScheduling
//
//  Created by ZouYa on 2021/11/19.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace::std;
typedef struct{
    int a_time;
    int b_time;
} interval;

int myCmp(interval a,interval b){
    return (a.a_time+max(a.b_time,b.a_time)+b.b_time) < (b.a_time+max(b.b_time,a.a_time)+a.b_time);
}

int main(int argc, const char * argv[]) {
    int n;
    cin>>n;
    vector<interval> array(n);
    for (int i=0; i<n; i++) {
        cin>>array[i].a_time;
    }
    for (int i=0; i<n; i++) {
        cin>>array[i].b_time;
    }
    sort(array.begin(),array.end(),myCmp);
    int a=0,b=0;
    for (int i=0; i<n; i++) {
        a+=array[i].a_time;
        b = max(a,b)+array[i].b_time;
    }
    cout<<b;
    return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
#define MAX 300
#define UNFINDED 0
#define FINDED 1
struct point {
public:
    int x;
    int y;
    double distance[MAX];
    bool status;
    double least_dis;
    int least_dis_num;

    void dis_compute(vector<point> &s) {//计算该点到其他任意点的距离（到自己为0，无效数字）
        double temp;
        for (int i = 0; i < s.size(); i++) {
            temp = sqrt((s[i].x - x) * (s[i].x - x) + (s[i].y - y) * (s[i].y - y));
            if (temp >= 10 && temp <= 1000) distance[i] = temp;
            else distance[i] = 0;
        }
    }

    void least_dis_compute(vector<point> &s) {//计算该点到所有未发现的点中的最小距离
        least_dis = 2000;
        for (int i = 0; i < s.size(); i++) {
            if (distance[i] != 0 && s[i].status == UNFINDED && distance[i] < least_dis) {
                least_dis = distance[i];
                least_dis_num = i;
            }
        }
    }

};

int find_min(vector<point> &N) {
    int temp = 2000;
    int temp_num;
    int i;
    for ( i = 0;  i < N.size(); i++) {
        if(N[i].status == FINDED){
            continue;
        }
        N[i].least_dis_compute( N );
        if (N[i].least_dis < temp) {
            temp = N[i].least_dis;
            temp_num = N[i].least_dis_num;
        }
    }
    if (temp == 2000) return 2000;
    return i-1;
}

int check_over(vector<point> &N) {
    for (int i = 0; i < N.size(); i++)
        if (N[i].status == UNFINDED) {
            
            //cout << "unfind:" << i << endl;
            return 0;
        }
    return 1;
}

int main() {
    int num;
    double length = 0;
    double price;
    int point_num;
    cin >> num;
    vector<point> N(num);
    for (int i = 0; i < num; i++) {//初始化
        for (int k = 0; k < num; k++) {
            N[i].distance[k] = 0;
        }
        N[i].least_dis = 2000;
        N[i].status = UNFINDED;
        cin >> N[i].x;
        cin >> N[i].y;
    }
    for (int i = 0; i < num; i++) {
        N[i].dis_compute(N);
    }

    /*for (int i = 0; i < num; i++) {//初始化
        cout << endl;
        cout << "第" << i << "点信息如下：" << endl;
        cout << "x：" << N[i].x<<" ";
        cout << "y：" << N[i].y << " ";
        cout << "least_dis：" << N[i].least_dis << " ";
        cout << "least_dis_num：" << N[i].least_dis_num << " ";
        cout << "status：" << N[i].status << " ";
    }*/

    N[0].status = FINDED;

    while (check_over(N) == 0) {
        int find_num;
        find_num = find_min(N);
        if (find_num == 2000) {
            cout << "No!"<<endl;
            return 0;
        }
        else {
            N[N[find_num].least_dis_num].status = FINDED;
            length += N[find_num].least_dis;
        }
    }
    price = length * 100;
    cout.setf(ios::fixed);
    cout << setprecision(1) << price << endl;
    return 0;
}

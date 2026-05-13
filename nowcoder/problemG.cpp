#include <iostream>
#include <vector>
#include <string>
using namespace std;
string order[6]; //六种操作的优先级顺序
//k个盘子按照给定策略需要移动多少次
long long solveSmall(int k) {
    vector<int> peg[3];
    //初始时所有盘子都在A柱，数字越小表示盘子越小
    for (int i = k; i >= 1; i--) {
        peg[0].push_back(i);
    }
    int last = -1;      //上一次移动的盘子
    long long cnt = 0;  //移动次数
    while (true) {
        //所有盘子移动到B或C柱时结束
        if (peg[1].size() == k || peg[2].size() == k) {
            return cnt;
        }
        //按优先级依次尝试六种操作
        for (int i = 0; i < 6; i++) {
            int from = order[i][0] - 'A';
            int to = order[i][1] - 'A';
            //起始柱为空，不能移动
            if (peg[from].empty())
                continue;
            int disk = peg[from].back();
            //不能连续移动同一个盘子
            if (disk == last)
                continue;
            //大盘不能放在小盘上
            if (!peg[to].empty() && peg[to].back() < disk)
                continue;
            //执行本次移动
            peg[from].pop_back();
            peg[to].push_back(disk);
            last = disk;
            cnt++;
            break;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    //输入六种操作的优先级
    for (int i = 0; i < 6; i++) {
        cin >> order[i];
    }
    //先模拟前3项，用来推出递推关系
    long long t1 = solveSmall(1);
    long long t2 = solveSmall(2);
    long long t3 = solveSmall(3);
    //假设递推式为ans[n]=a*ans[n-1]+b
    long long a = (t3 - t2) / (t2 - t1);
    long long b = t2 - a * t1;
    long long ans = t1;
    //根据递推式计算n个盘子的答案
    for (int i = 2; i <= n; i++) {
        ans = a * ans + b;
    }
    cout << ans;
    return 0;
}

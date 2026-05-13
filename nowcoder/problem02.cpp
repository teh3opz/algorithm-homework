#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
const long long INF = 1e18;  //表示不可达
int main() {
    int n, L, Maxn, S;
    //多组输入，直到结束
    while (cin >> n >> L >> Maxn >> S) {
        //读取n个补给点 (位置Pi, 花费Ci)
        vector<pair<int, int>> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].first >> points[i].second;  //Pi, Ci
        }
        // 按位置从小到大排序
        sort(points.begin(), points.end());
        //构造数组：起点(0) + 补给点 + 终点(L)
        vector<int> pos;   //位置
        vector<int> cost;  //在该点补满体力的花费
        pos.push_back(0);     //起点位置
        cost.push_back(0);    //初始体力是满的，起点不需要花钱
        for (int i = 0; i < n; i++) {
            pos.push_back(points[i].first);   //补给点位置
            cost.push_back(points[i].second); //补给点花费
        }
        pos.push_back(L);     //终点位置
        cost.push_back(0);    //终点不需要补给
        int m = pos.size();  //一共m=n+2个关键点
        //dp[i] = 到达第i个关键点的最小花费
        vector<long long> dp(m, INF);
        dp[0] = 0;  //起点花费为0
        //队列里存的是候选点的下标j；满足：dp[j] + cost[j] 单调递增
        deque<int> q;
        q.push_back(0);  //起点入队
        //依次计算每个点的最小花费
        for (int i = 1; i < m; i++) {
            //首先移除距离太远的点（跑不到当前点i）
            while (!q.empty() && pos[i] - pos[q.front()] > Maxn) {
                q.pop_front();
            }
            //其次将队首的最优点转移到i
            if (!q.empty()) {
                int j = q.front();
                dp[i] = dp[j] + cost[j];  //从j补满后跑到 i
            }
            //最后把当前点i作为未来的候选点入队
            if (dp[i] < INF) {
                long long val = dp[i] + cost[i];  //从i补满的总花费
                
                //移除队尾比当前点差的候选
                while (!q.empty() && dp[q.back()] + cost[q.back()] >= val) {
                    q.pop_back();
                }
                q.push_back(i);  //入队
            }
        }
        //判断是否能在预算S内到达终点
        if (dp[m - 1] <= S) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}

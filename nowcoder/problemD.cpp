#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;
const int MAXX = 100000;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    //多组数据
    while (cin >> m) {
        //0: 当前没有券
        //1: 当前有券未使用
        vector<int> state(MAXX + 1, 0);
        //该优惠券上一次确定记录的位置
        vector<int> last(MAXX + 1, 0);
        //当前还没使用的?位置
        set<int> qpos;
        int ans = -1; //最早错误行
        for (int i = 1; i <= m; i++) {
            string op;
            cin >> op;
            //损坏记录
            if (op == "?" || op == "？") {
                if (ans == -1)
                    qpos.insert(i);
                continue;
            }
            int x;
            cin >> x;
            //已经找到错误，只读入
            if (ans != -1)
                continue;
            //购买优惠券
            if (op == "I") {
                //正常购买
                if (state[x] == 0) {
                    state[x] = 1;
                    last[x] = i;
                }
                //尝试用?补一个 O x
                else {
                    auto it = qpos.lower_bound(last[x] + 1);

                    if (it != qpos.end() && *it < i) {
                        qpos.erase(it);
                        state[x] = 1;
                        last[x] = i;
                    }
                    else {
                        ans = i;
                    }
                }
            }
            //使用优惠券
            else if (op == "O") {
                //正常使用
                if (state[x] == 1) {
                    state[x] = 0;
                    last[x] = i;
                }
                //尝试用?补一个I x
                else {
                    auto it = qpos.lower_bound(last[x] + 1);
                    if (it != qpos.end() && *it < i) {
                        qpos.erase(it);
                        state[x] = 0;
                        last[x] = i;
                    }
                    else {
                        ans = i;
                    }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

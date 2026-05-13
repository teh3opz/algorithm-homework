#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    long long xp, yp, xs, ys;
    cin >> xp >> yp >> xs >> ys;
    //只关心两个点之间的横向距离和纵向距离
    long long dx = abs(xs - xp);
    long long dy = abs(ys - yp);
    //马的走法关于x、y对称。为了方便计算，保证dx>=dy
    if (dx < dy) {
        swap(dx, dy);
    }
    long long ans;
    //特殊情况：到(1,0)最少需要3步
    if (dx == 1 && dy == 0) {
        ans = 3;
    }
    //特殊情况：到(2,2)最少需要4步
    else if (dx == 2 && dy == 2) {
        ans = 4;
    }
    else {
        //一般情况：dx较大时至少需要(dx+1)/2步，同时每步横纵距离总贡献有限，也至少需要(dx+dy+2)/3步
        ans = max((dx + 1) / 2, (dx + dy + 2) / 3);
        //马每走一步坐标和的奇偶性会改变，步数ans和dx+dy的奇偶性必须一致
        if ((ans + dx + dy) % 2 != 0) {
            ans++;
        }
    }
    cout << ans;
    return 0;
}

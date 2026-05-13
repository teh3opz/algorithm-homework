#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
const ull BASE = 131;
/*
    Manacher算法：求每个位置作为回文中心时，能扩展出的最大回文半径，为了统一处理奇数、偶数长度回文，把字符串s转成：$#a#b#c#
    例如：
    s="abc"  t="$#a#b#c#"
*/
string manacher(const string& s, vector<int>& p) {
    string t = "$#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int m = t.size();
    p.assign(m, 0);
    int center = 0;
    int right = 0;
    for (int i = 1; i < m; i++) {
        //如果 i 在当前最右回文范围内，可以利用对称位置的信息
        if (i < right) {
            p[i] = min(p[2 * center - i], right - i);
        } else {
            p[i] = 1;
        }
        //继续向两边扩展
        while (i - p[i] >= 0 &&
               i + p[i] < m &&
               t[i - p[i]] == t[i + p[i]]) {
            p[i]++;
        }
        //更新当前最右回文区间
        if (i + p[i] > right) {
            right = i + p[i];
            center = i;
        }
    }
    return t;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string A, B;
    cin >> A >> B;
    vector<int> pa, pb;
    //对A和B分别做 Manacher
    string ta = manacher(A, pa);
    string tb = manacher(B, pb);
    int m = ta.size();
    /*
        哈希：preA：处理后的A字符串的正向哈希 sufB：处理后的B字符串的反向哈希
    */
    vector<ull> powBase(m + 1, 1);
    vector<ull> preA(m + 1, 0);
    vector<ull> sufB(m + 2, 0);
    for (int i = 1; i <= m; i++) {
        powBase[i] = powBase[i - 1] * BASE;
    }
    //A的正向哈希
    for (int i = 0; i < m; i++) {
        preA[i + 1] = preA[i] * BASE + ta[i];
    }
    //B的反向哈希
    for (int i = m - 1; i >= 0; i--) {
        sufB[i] = sufB[i + 1] * BASE + tb[i];
    }
    //获取 ta[l..r] 的正向哈希
    auto getAHash = [&](int l, int r) -> ull {
        if (l > r) return 0;
        return preA[r + 1] - preA[l] * powBase[r - l + 1];
    };
    //获取 tb[l..r] 的反向哈希
    auto getBReverseHash = [&](int l, int r) -> ull {
        if (l > r) return 0;
        return sufB[l] - sufB[r + 1] * powBase[r - l + 1];
    };
    int ans = 0;
    /*
        枚举回文中心。
        i是A中处理后字符串ta的中心位置。 j是B中与它对应的位置。
        A的右端点r1 = B的左端点l2 转成加#后的形式后，B中对应位置为i-2。
    */
    for (int i = 2; i < m; i++) {
        int j = i - 2;
        if (j < 0 || j >= m) continue;
        // pa[i]表示A中以i为中心的最长回文半径，pb[j]表示B中以j为中心的最长回文半径，取更大表示当前中心本身能提供的最长回文部分
        int len = max(pa[i], pb[j]);
        //当前回文部分在A中的左边界
        int leftA = i - len + 1;
        //当前回文部分在B中的右边界
        int rightB = j + len - 1;
        //len-1就是当前回文对应的真实长度
        ans = max(ans, len - 1);
        //继续向外扩展并判断：A左边的一段是否等于B右边的一段反过来，用哈希+二分来找最大可扩展长度。
        int l = 0;
        int r = min(leftA, m - 1 - rightB);
        int add = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int aL = leftA - mid;
            int aR = leftA - 1;
            int bL = rightB + 1;
            int bR = rightB + mid;
            if (getAHash(aL, aR) == getBReverseHash(bL, bR)) {
                add = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        //总长度=中间回文长度+两边扩展长度
        ans = max(ans, len - 1 + add);
    }
    cout << ans << '\n';
    return 0;
}

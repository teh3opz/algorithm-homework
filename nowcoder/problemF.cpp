#include <iostream>
#include <vector>
#include <string>
using namespace std;
//KMP判断普通字符串段block在文件名s中的匹配位置
void matchBlock(const string& s, const string& block,
                vector<char>& dp, vector<char>& ndp) {
    int n = s.size();
    int m = block.size();
    vector<int> pi(m, 0);
    //计算KMP前缀数组
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && block[i] != block[j])
            j = pi[j - 1];
        if (block[i] == block[j])
            j++;
        pi[i] = j;
    }
    int j = 0;
    //在s中查找block的所有出现位置
    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != block[j])
            j = pi[j - 1];
        if (s[i] == block[j])
            j++;
        if (j == m) {
            int start = i - m + 1;
            //如果block前的位置可达则block匹配完后的位置也可达
            if (dp[start])
                ndp[start + m] = 1;
            j = pi[j - 1];
        }
    }
}
//判断文件名s是否匹配通配符p
bool check(const string& p, const string& s) {
    int n = s.size();
    //dp[i]表示当前已经匹配到s的前i个字符
    vector<char> dp(n + 1, 0), ndp(n + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < p.size(); ) {
        //?匹配任意一个字符
        if (p[i] == '?') {
            fill(ndp.begin(), ndp.end(), 0);
            for (int j = 0; j < n; j++) {
                if (dp[j])
                    ndp[j + 1] = 1;
            }
            dp.swap(ndp);
            i++;
        }
        //*匹配任意长度字符串
        else if (p[i] == '*') {
            bool ok = false;
            for (int j = 0; j <= n; j++) {
                if (dp[j])
                    ok = true;
                dp[j] = ok;
            }
            i++;
        }
        //连续普通字符作为一个字符串段处理
        else {
            string block;
            while (i < p.size() && p[i] != '?' && p[i] != '*') {
                block += p[i];
                i++;
            }
            fill(ndp.begin(), ndp.end(), 0);
            //用KMP匹配普通字符串段
            matchBlock(s, block, dp, ndp);
            dp.swap(ndp);
        }
    }
    //最后必须刚好匹配完整个s
    return dp[n];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //输入通配符字符串p
    string p;
    cin >> p;
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        if (check(p, s))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}

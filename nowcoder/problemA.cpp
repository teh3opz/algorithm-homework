//第1题：暂未通过
//当前代码仍存在错误，后续补充。
#include <bits/stdc++.h>
using namespace std;
int N, A, B;
vector<int> v;
vector<pair<int,int>> ops;
unordered_set<int> S_add, S_diff;
void doAdd(int d) {
    d = ((d % N) + N) % N;
    if (!d) return;
    for (auto& x : v) x = (x + d) % N;
    ops.push_back({2, d});
}
void doXor(int x) {
    if (!x) return;
    for (auto& val : v) val ^= x;
    ops.push_back({1, x});
}
void doSwap() {
    int pa = -1, pb = -1;
    for (int i = 0; i < N; i++) {
        if (v[i] == A) pa = i;
        if (v[i] == B) pb = i;
    }
    swap(v[pa], v[pb]);
    ops.push_back({0, 0});
}
//判断能否用单次共轭交换值 u 和 w
bool canDirect(int u, int w) {
    if (u == w) return true;
    if ((u == A && w == B) || (u == B && w == A)) return true;
    if (S_add.count(u ^ w)) return true;
    if (S_diff.count(((u - w) % N + N) % N)) return true;
    if (S_diff.count(((w - u) % N + N) % N)) return true;
    return false;
}
//执行单次共轭交换值 u 和 w
void execDirect(int u, int w) {
    if (u == w) return;
    if ((u == A && w == B) || (u == B && w == A)) { doSwap(); return; }

    int tgt = u ^ w;
    //方法1: ADD d, XOR x, SWAP, XOR x, ADD -d
    for (int d = 0; d < N; d++) {
        int ad = (A + d) % N, bd = (B + d) % N;
        if ((ad ^ bd) == tgt) {
            int x = ad ^ u;
            doAdd(d); doXor(x); doSwap(); doXor(x); doAdd(N - d);
            return;
        }
    }
    //方法2: XOR x, ADD d, SWAP, ADD -d, XOR x
    for (int x = 0; x < N; x++) {
        int ax = A ^ x, bx = B ^ x;
        int diff = ((ax - bx) % N + N) % N;
        int td1 = ((u - w) % N + N) % N;
        int td2 = ((w - u) % N + N) % N;
        if (diff == td1) {
            int d = ((u - ax) % N + N) % N;
            doXor(x); doAdd(d); doSwap(); doAdd(N - d); doXor(x);
            return;
        }
        if (diff == td2) {
            int d = ((w - ax) % N + N) % N;
            doXor(x); doAdd(d); doSwap(); doAdd(N - d); doXor(x);
            return;
        }
    }
}
//交换任意两个值u和w（可能需要通过中间值路由）
bool swapVals(int u, int w) {
    if (u == w) return true;
    if (canDirect(u, w)) { execDirect(u, w); return true; }
    // 找中间值m，使得swap(u,m) 和swap(m,w) 都能直接完成
    // 分解: swap(u,w) =swap(u,m) ∘ swap(m,w) ∘ swap(u,m)
    for (int m = 0; m < N; m++) {
        if (m == u || m == w) continue;
        if (canDirect(u, m) && canDirect(m, w)) {
            execDirect(u, m);
            execDirect(m, w);
            execDirect(u, m);
            return true;
        }
    }
    return false;
}
int main() {
    cin >> N >> A >> B;
    v.resize(N);
    for (int i = 0; i < N; i++) cin >> v[i];
    //预处理：计算所有可达的 XOR 目标和差值目标
    for (int d = 0; d < N; d++)
        S_add.insert(((A + d) % N) ^ ((B + d) % N));
    for (int x = 0; x < N; x++)
        S_diff.insert((((A ^ x) - (B ^ x)) % N + N) % N);
    bool fail = false;
    //选择排序：逐个归位
    for (int i = 0; i < N && !fail; i++)
        if (v[i] != i)
            if (!swapVals(v[i], i))
                fail = true;
    //验证排序结果
    if (!fail)
        for (int i = 0; i < N; i++)
            if (v[i] != i) { fail = true; break; }
    if (fail || (int)ops.size() > 32768) {
        cout << -1 << "\n";
    } else {
        cout << ops.size() << "\n";
        for (auto& [t, val] : ops) {
            if (t == 0) cout << 0 << "\n";
            else cout << t << " " << val << "\n";
        }
    }
    return 0;
}

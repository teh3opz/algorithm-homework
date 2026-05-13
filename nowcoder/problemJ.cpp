#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
vector<int> g[MAXN];      //存树的边
int parentNode[MAXN];     //每个点的父节点
int depthNode[MAXN];      //每个点的深度
bool covered[MAXN];       //该点是否已被消防局覆盖
//从消防局位置start出发覆盖距离不超过2的点
void cover(int start) {
    queue<pair<int, int> > q;
    bool vis[MAXN] = {false};
    q.push({start, 0});
    vis[start] = true;
    while (!q.empty()) {
        int u = q.front().first;
        int dis = q.front().second;
        q.pop();
        covered[u] = true;
        //距离为2时不能再继续向外扩展
        if (dis == 2)
            continue;
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push({v, dis + 1});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    parentNode[1] = 0;
    depthNode[1] = 0;
    //输入父节点并建立无向树
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        parentNode[i] = fa;
        depthNode[i] = depthNode[fa] + 1;
        g[i].push_back(fa);
        g[fa].push_back(i);
    }
    vector<int> nodes;
    for (int i = 1; i <= n; i++) {
        nodes.push_back(i);
    }
    //按深度从大到小处理优先处理最深的点
    sort(nodes.begin(), nodes.end(), [](int a, int b) {
        return depthNode[a] > depthNode[b];
    });
    int ans = 0;
    for (int u : nodes) {
        //如果当前点没有被覆盖就需要新建消防局
        if (!covered[u]) {
            int pos = u;
            //在当前未覆盖点的2级祖先处建消防局
            for (int i = 0; i < 2; i++) {
                if (parentNode[pos] != 0)
                    pos = parentNode[pos];
            }
            ans++;
            //标记该消防局能覆盖的所有点
            cover(pos);
        }
    }
    cout << ans;
    return 0;
}

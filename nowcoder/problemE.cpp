#include <iostream>
#include <vector>
using namespace std;
int n;
int x[105], y[105];
bool vis[105];
//DFS找连通块
void dfs(int u) {
    vis[u] = true;
    for (int v = 0; v < n; v++) {
        //同一行或同一列可以到达
        if (!vis[v] && (x[u] == x[v] || y[u] == y[v])) {
            dfs(v);
        }
    }
}
int main() {
    cin >> n;
    //输入坐标
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    int cnt = 0; //连通块数量
    for (int i = 0; i < n; i++) {
        //找到一个新的连通块
        if (!vis[i]) {
            dfs(i);
            cnt++;
        }
    }
    //最少添加点数=连通块数量-1
    cout << cnt - 1;
    return 0;
}

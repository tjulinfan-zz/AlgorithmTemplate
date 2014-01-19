//HDU 2586 LCA 倍增法
//首先预处理出parent[i][j] 表示i点的第2^j个祖先是谁
//询问u v时 先将深度较大的走到深度较小的 然后两个同时向上走
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

const int MAX_V = 40010;
const int MAX_LOG_V = 17;

int n, m;
int dep[MAX_V], dis[MAX_V];
int parent[MAX_V][MAX_LOG_V];
vector<PII> e[MAX_V];

void dfs(int u, int p) {
    parent[u][0] = p;
    for (int k = 1; k < MAX_LOG_V; ++ k) {
        if (parent[u][k - 1] < 0)
            parent[u][k] = -1;
        else
            parent[u][k] = parent[parent[u][k - 1]][k - 1];
    }
    for (size_t i = 0; i < e[u].size(); ++ i) {
        int v = e[u][i].first;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dis[v] = dis[u] + e[u][i].second;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int steps = dep[u] - dep[v];
    for (int k = 0; k < MAX_LOG_V; ++ k) {
        if (steps >> k & 1)
            u = parent[u][k];
    }
    for (int k = MAX_LOG_V - 1; k >= 0; -- k) {
        if (parent[u][k] != parent[v][k]) {
            u = parent[u][k];
            v = parent[v][k];
        }
    }
    return u;
}

void init() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i)
        e[i].clear();
    for (int i = 0; i < n - 1; ++ i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u --, v --;
        e[u].push_back(PII(v, w));
        e[v].push_back(PII(u, w));
    }
}

void solve() {
    dis[0] = dep[0] = 0;
    dfs(0, -1);

    for (int i = 0; i < m; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        u --, v --;
        int p = lca(u, v);
        int ans = dis[u] + dis[v] - 2 * dis[p];
        printf("%d\n", ans);
    }
}

int main() {
    int T;
    cin >> T;
    while (T --) {
        init();
        solve();
    }
    return 0;
}

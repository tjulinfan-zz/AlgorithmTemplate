//POJ 1741 树的分治
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <utility>
#include <climits>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;

const int MAXN = 100010;

int n, k, ans;
int subRoot, minSize;
vector<PII> e[MAXN];
vector<int> dists;
bool vis[MAXN];
int size[MAXN], dist[MAXN], f[MAXN];

//寻找重心
void getRoot(int u, int fa, int totSize) {
    int maxSubSize = 0;
    size[u] = 1; f[u] = fa;
    for (int i = 0; i < e[u].size(); ++ i) {
        int v = e[u][i].first;
        if (v == fa || vis[v]) continue;
        getRoot(v, u, totSize);
        maxSubSize = max(maxSubSize, size[v]);
        size[u] += size[v];
    }
    if (fa != -1)
        maxSubSize = max(maxSubSize, totSize - size[u]);
    if (maxSubSize < minSize) {
        minSize = maxSubSize;
        subRoot = u;
    }
}

void countDist(int u, int fa, int dist) {
    dists.push_back(dist);
    for (int i = 0; i < e[u].size(); ++ i) {
        int v = e[u][i].first;
        if (v == fa || vis[v]) continue;
        countDist(v, u, dist + e[u][i].second);
    }
}

int count(int u, int dist) {
    dists.clear();
    countDist(u, -1, dist);
    sort(dists.begin(), dists.end());

    int ret = 0;
    int l = 0, r = dists.size() - 1;
    while (l < r) {
        while (l < r && dists[l] + dists[r] > k) r --;
        ret += r - l;
        l ++;
    }
    return ret;
}

void work(int u, int totSize) {
    minSize = INT_MAX;
    getRoot(u, -1, totSize);
    u = subRoot;
    vis[u] = true;

    int pCnt = 0;
    for (int i = 0; i < e[u].size(); ++ i) {
        int v = e[u][i].first;
        if (vis[v]) continue;
        pCnt += count(v, e[u][i].second);
    }
    pCnt = count(u, 0) - pCnt;
    ans += pCnt;

    for (int i = 0; i < e[u].size(); ++ i) {
        int v = e[u][i].first;
        if (vis[v]) continue;
        if (v == f[u])
            work(v, totSize - size[u]);
        else
            work(v, size[v]);
    }
}

bool init() {
    scanf("%d%d", &n, &k);
    if (n + k == 0) return false;
    for (int i = 1; i <= n; ++ i)
        e[i].clear();
    for (int i = 0; i < n - 1; ++ i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u].push_back(PII(v, w));
        e[v].push_back(PII(u, w));
    }
    return true;
}

void treeDc() {
    memset(vis, 0, sizeof(vis));
    ans = 0;
    work(1, n);
    printf("%d\n", ans);
}

int main() {
    while (init()) {
        treeDc();
    }
    return 0;
}

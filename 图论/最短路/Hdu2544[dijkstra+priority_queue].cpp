#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

const int maxn = 120000;

typedef pair<int,int> PII;

int n, m, u, v, w;
vector<PII> e[maxn];
priority_queue<PII, vector<PII>, greater<PII> > q;
int flag[maxn];
int d[maxn];

void dijkstra(int s) {
    for (int i = 0; i < n; i++) flag[i] = 0, d[i] = INT_MAX / 2;
    while (!q.empty()) q.pop();
    q.push(PII(0,s)); flag[s] = 1; d[s] = 0;
    for (int k = 0; k < n-1; k++) {
        int u = q.top().second; flag[u] = 1;
        for (size_t i = 0; i < e[u].size(); i++) {
            int v = e[u][i].first, dis = e[u][i].second;
            if (dis + d[u] < d[v]) {
                d[v] = dis + d[u];
                q.push(PII(d[v], v));
            }
        }
        while (flag[q.top().second]) q.pop();
    }
}

int main() {
    while (cin>>n>>m, n) {
        for (int i = 0; i < n; i++) e[i].clear();
        while (m--) {
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;
            e[u].push_back(PII(v, w));
            e[v].push_back(PII(u, w));
        }
        dijkstra(0);
        cout<<d[n-1]<<endl;
    }
    return 0;
}

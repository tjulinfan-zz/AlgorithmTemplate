#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 210;
const int INF = 0x3f3f3f3f;

struct Edge {
    int from, to, cap, flow;
};

vector<Edge> edges;
vector<int> g[MAXN];
int d[MAXN], cur[MAXN];

int init() {
    edges.clear();
    for (int i = 0; i < MAXN; ++i) {
        g[i].clear();
    }
}

int bfs(int s, int t) {
    queue<int> q;
    q.push(s);
    memset(d, -1, sizeof(d));
    d[s] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < g[x].size(); ++i) {
            Edge& e = edges[g[x][i]];
            if (d[e.to] == -1 && e.cap > e.flow) {
                d[e.to] = d[x] + 1;
                q.push(e.to);
                if (e.to == t) return true;
            }
        }
    }
    return false;
}

int dfs(int x, int t, int low) {
    if (x == t) return low;
    int tmp;
    for (int i = 0; i < g[x].size(); ++i) {
        Edge& e = edges[g[x][i]];
        if (d[e.to] == d[x] + 1 &&
            (tmp = dfs(e.to, t, min(low, e.cap - e.flow))) > 0) {
            e.flow += tmp;
            edges[g[x][i] ^ 1].flow -= tmp;
            return tmp;
        }
    }
    return 0;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        flow += dfs(s, t, INF);
    }
    return flow;
}

int main() {
    int n, m;
    while (~scanf("%d%d", &m, &n)) {
        init();

        for (int i = 0; i < m; ++i) {
            int u, v, cap;
            scanf("%d%d%d", &u, &v, &cap);
            edges.push_back((Edge){u, v, cap, 0});
            g[u].push_back(edges.size() - 1);
            edges.push_back((Edge){v, u, 0, 0});
            g[v].push_back(edges.size() - 1);
        }

        // 1 is source, n is sink
        printf("%d\n", dinic(1, n));
    }
    return 0;
}

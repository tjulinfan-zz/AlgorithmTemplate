#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

//maxn 为节点数2倍
const int maxn = 24000;
const int inf = 0x3fffffff;

int T, n, u, v, eid, w;

/*
son数组记录重链 fa记录父亲节点
top记录此节点重链的深度最小节点
low[i]记录i号边深度较大的节点
*/

int ecnt = 0;
int now[maxn], pre[maxn], e[maxn], val[maxn]; //Graph
int depth[maxn], son[maxn], siz[maxn], low[maxn], top[maxn], fa[maxn], cost[maxn];
int seq[maxn], seqcnt, mp[maxn];

void init(int n) {
    ecnt = 0;
    for (int i = 0; i < n; i++) now[i] = -1;
}

void addEdge(int u, int v, int w) {
    e[ecnt] = v; pre[ecnt] = now[u]; val[ecnt] = w; now[u] = ecnt++;
}


void predfs(int u, int p) {
    siz[u] = 1; fa[u] = p; son[u] = -1;
    for (int id = now[u]; id != -1; id = pre[id]) {
        int v = e[id];
        if (p == v) continue;
        depth[v] = depth[u] + 1; cost[v] = val[id];
        low[id>>1] = v;
        predfs(v, u);
        if (son[u] == -1 || siz[v] > siz[son[u]]) {
            son[u] = v;
        }
        siz[u] += siz[v];
    }
}

void dfs(int u, int t) {
    top[u] = t; seq[seqcnt] = cost[u];
    mp[u] = seqcnt++;
    if (son[u] != -1) dfs(son[u], t);
    for (int id = now[u]; id != -1; id = pre[id]) {
        int v = e[id];
        if (v == fa[u] || v == son[u]) continue;
        dfs(v, v);
    }
}

/*
以下为线段树
*/

struct Node {
    int maxval;
} p[maxn*4];

void push_up(int now) {
    p[now].maxval = max(p[now * 2].maxval, p[now * 2 + 1].maxval);
}

void build(int now, int l, int r) {
    if (l == r) p[now].maxval = seq[l];
    else {
        int mid = (l + r) / 2;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
        push_up(now);
    }
}

void update(int now, int l, int r, int pos, int val) {
    if (l == r) p[now].maxval = val;
    else {
        int mid = (l + r) / 2;
        if (pos <= mid) update(now * 2, l, mid, pos, val);
        else update(now * 2 + 1, mid + 1, r, pos, val);
        push_up(now);
    }
}

int query(int now, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return -inf;
    if (ql <= l && qr >= r) {
        return p[now].maxval;
    } else {
        int mid = (l + r) / 2;
        return max(query(now * 2, l, mid, ql, qr),
                    query(now * 2 + 1, mid + 1, r, ql, qr));
    }
}

int solve(int u, int v) {
    int ans = -inf;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        int cur = query(1, 0, seqcnt - 1, mp[top[u]], mp[u]);
        ans = max(ans, cur);
        u = fa[top[u]];
    }
    if (depth[u] < depth[v]) swap(u, v);
    ans = max(ans, query(1, 0, seqcnt - 1, mp[v] + 1, mp[u]));
    return max(0, ans);
}

char cmd[120];

int main() {
    //freopen("in.txt", "r", stdin);
    cin>>T;
    while (T--) {
        scanf("%d", &n);
        init(n);
        for (int i = 0; i < n - 1; i++) {
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        depth[0] = 0; predfs(0, 0);
        seqcnt = 0; dfs(0, 0);
        build(1, 0, seqcnt - 1);
        while (scanf("%s", cmd)) {
            if (cmd[0] == 'Q') {
                scanf("%d%d", &u, &v);
                --u; --v;
                printf("%d\n", solve(u, v));
            } else if (cmd[0] == 'C') {
                scanf("%d%d", &eid, &w);
                --eid;
                update(1, 0, seqcnt - 1, mp[low[eid]], w);
            } else break;
        }
    }
    return 0;
}

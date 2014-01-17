#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN = 5011;
const int MAXM = 20011;

bool vis[MAXM];

int now[MAXN];
int dfn[MAXN], low[MAXN], d[MAXN];

int pre[MAXM], son[MAXM];

int n, edgeCnt, dfnCnt;

void addEdge(int u, int v)
{
    pre[edgeCnt] = now[u];
    son[edgeCnt] = v;
    now[u] = edgeCnt ++;
}

void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++ dfnCnt;
    for (int p = now[u]; p != -1; p = pre[p])
    {
        if (vis[p]) continue;
        vis[p] = vis[p ^ 1] = true;

        int v = son[p];
        if (!dfn[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else
            if (v != fa)
                low[u] = min(low[u], dfn[v]);

    }
}

void init()
{
    edgeCnt = dfnCnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(now, 255, sizeof(now));

    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
}

void solve()
{
    dfs(1, 0);
    memset(d, 0, sizeof(d));
    for (int i = 1; i <= n; ++ i)
    {
        for (int p = now[i]; p != -1; p = pre[p])
            if (low[i] != low[son[p]])
                d[low[i]] ++;
    }

    int leafCnt = 0;
    for (int i = 1; i <= n; ++ i)
        if (d[i] == 1)
            leafCnt ++;
    printf("%d\n", (leafCnt + 1) / 2);
}

int main()
{
    init();
    solve();
    return 0;
}

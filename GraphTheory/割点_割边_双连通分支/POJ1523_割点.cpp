//POJ 1523 割点
//同时求去掉割点后的子图数
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN = 1010;
const int MAXM = 1000010;

int n, m;
int edgeCnt, dfnCnt;
int now[MAXN], dfn[MAXN], low[MAXN], res[MAXN];
int son[MAXM], pre[MAXM], vis[MAXM];

void clear()
{
    edgeCnt = 0;
    dfnCnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(now, 255, sizeof(now));
    memset(res, 0, sizeof(res));
}

void addEdge(int u, int v)
{
    vis[edgeCnt] = 0;
    pre[edgeCnt] = now[u]; son[edgeCnt] = v; now[u] = edgeCnt ++;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ dfnCnt;
    int child = 0;
    for (int p = now[u]; p != -1; p = pre[p])
    {
        if (vis[p]) continue;
        vis[p] = vis[p ^ 1] = true;

        int v = son[p];
        if (!dfn[v])
        {
            child ++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            //是割点
            if (dfn[u] <= low[v])
                res[u] ++;
        }
        else
			low[u] = min(low[u], dfn[v]);
    }

    if (fa == 0)
    {
        if (child > 1)
            res[u] = child;
        else
            res[u] = 0;
    }
    else if (res[u] > 0)
            res[u] ++;
}

bool init()
{
    clear();
    n = 0;
    int u, v;
    while (scanf("%d", &u) != EOF && u)
    {
        scanf("%d", &v);
        if (u > n) n = u;
        if (v > n) n = v;
        addEdge(u, v);
        addEdge(v, u);
    }
    return n > 0;
}

void solve()
{
    tarjan(1, 0);

    bool hasCutp = false;
    for (int i = 1; i <= n; ++ i)
        if (res[i] > 0)
        {
            printf("  SPF node %d leaves %d subnets\n", i, res[i]);
            hasCutp = true;
        }
    if (!hasCutp)
    {
        printf("  No SPF nodes\n");
    }
    printf("\n");
}

int main()
{
    int cs = 0;
    while (init())
    {
        printf("Network #%d\n", ++ cs);
        solve();
    }
    return 0;
}

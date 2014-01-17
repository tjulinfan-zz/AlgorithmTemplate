//POJ 3177 边双连通分量 + 构造双连通子图
/* 很显然，题中要求的图就是一个边双连通图，即边连通度不小于2。
 | 我的方法是在原图中DFS求出所有的桥，然后删除这些桥边，剩下的每个连通块都是一个双连通子图。
 | 把每个双连通子图收缩为一个顶点，再把桥边加回来，最后的这个图一定是一棵树，边连通度为1。
 | 统计出树中度为1的节点的个数，即为叶节点的个数，记为leaf。
 | 至少在树上添加(leaf+1)/2条边，就能使树达到边二连通，所以结果就是(leaf+1)/2。
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;

const int MAXN = 5011;
const int MAXM = 20011;

int now[MAXN], dfn[MAXN], low[MAXN], d[MAXN], color[MAXN];
int pre[MAXM], son[MAXM], vis[MAXM];

stack<int> st;

int n, edgeCnt, dfnCnt, ebccCnt;

void addEdge(int u, int v)
{
    vis[edgeCnt] = 0;
    pre[edgeCnt] = now[u]; son[edgeCnt] = v; now[u] = edgeCnt ++;
}

void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++ dfnCnt;
    st.push(u);
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
            low[u] = min(low[u], dfn[v]);

    }

    if (dfn[u] == low[u])
    {
        ++ ebccCnt;
        while (st.top() != u)
        {
            color[st.top()] = ebccCnt;
            st.pop();
        }
        color[u] = ebccCnt;
        st.pop();
    }
}

void init()
{
    edgeCnt = dfnCnt = ebccCnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(now, 255, sizeof(now));
    memset(color, 255, sizeof(color));

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
            if (color[i] != color[son[p]])
                d[color[i]] ++;
    }

    int leafCnt = 0;
    for (int i = 1; i <= ebccCnt; ++ i)
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

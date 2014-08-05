<<<<<<< HEAD
//HDU 2874	 Connections between cities LCA==RMQ
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAXN 11000
#define MAXM 21000

int tot;
int now[MAXN];
int pre[MAXM], son[MAXM], len[MAXM];

int n;
int pow2[20];
int deep[MAXN], whTree[MAXN], dist[MAXN], pos[MAXN];
int f[MAXM * 4][20];

vector<int> seq;


void edge(int i, int j, int l) //i -> j length: l
{
    pre[++ tot] = now[i];
    now[i] = tot;
    son[tot] = j;
    len[tot] = l;
}

void dfs(int wh, int u, int dep, int dis)
{
    deep[u] = dep;
    dist[u] = dis;
    whTree[u] = wh;

    seq.push_back(u);
    pos[u] = seq.size() - 1;
    for (int p = now[u]; p; p = pre[p])
    {
        if (whTree[son[p]] == -1)
        {
            dfs(wh, son[p], dep + 1, dis + len[p]);
            seq.push_back(u);
        }
    }
}

int min(int v1, int v2)
{
    return deep[v1] < deep[v2] ? v1 : v2;
}

void RMQ_init()
{
    pow2[0] = 1;
    for (int i = 1; i < 20; i ++)
        pow2[i] = pow2[i - 1] * 2;
    for (int i = 0; i < seq.size(); i ++)
        f[i][0] = seq[i];
    int n = seq.size();
    int m = (int)(log(n) / log(2));
    for (int j = 1; j <= m; j ++)
        for (int i = 0; i < n; i ++)
        {
            if (i + pow2[j] - 1 >= n) break;
            f[i][j] = min(f[i][j - 1], f[i + pow2[j - 1]][j - 1]);
        }
}

int RMQ_query(int i, int j)
{
    if (whTree[i] != whTree[j])
        return -1;
    if (pos[i] > pos[j])
        swap(i, j);
    int len = (int)(log(pos[j] - pos[i] + 1) / log(2));
    int fa = min(f[pos[i]][len], f[pos[j] - pow2[len] + 1][len]);
    return dist[i] + dist[j] - dist[fa] * 2;
}

void prepare()
{
    seq.clear();
    memset(whTree, 255, sizeof(whTree));
    int wh = 0;
    for (int i = 1; i <= n; i ++)
        if (whTree[i] == -1)
            dfs(++ wh, i, 0, 0);
}

int main()
{
    int m, q;
    while (scanf("%d%d%d", &n, &m, &q) != EOF)
    {
        tot = 0;
        memset(now, 0, sizeof(now));
        while (m --)
        {
            int u, v, l;
            scanf("%d%d%d", &u, &v, &l);
            edge(u, v, l);
            edge(v, u, l);
        }
        prepare();
        RMQ_init();
        while (q --)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            int len = RMQ_query(a, b);
            if (len == -1)
                printf("Not connected\n");
            else
                printf("%d\n", len);
        }
    }
    return 0;
=======
//HDU 2874	 Connections between cities LCA==RMQ
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAXN 11000
#define MAXM 21000

int tot;
int now[MAXN];
int pre[MAXM], son[MAXM], len[MAXM];

int n;
int pow2[20];
int deep[MAXN], whTree[MAXN], dist[MAXN], pos[MAXN];
int f[MAXM * 4][20];

vector<int> seq;


void edge(int i, int j, int l) //i -> j length: l
{
    pre[++ tot] = now[i];
    now[i] = tot;
    son[tot] = j;
    len[tot] = l;
}

void dfs(int wh, int u, int dep, int dis)
{
    deep[u] = dep;
    dist[u] = dis;
    whTree[u] = wh;

    seq.push_back(u);
    pos[u] = seq.size() - 1;
    for (int p = now[u]; p; p = pre[p])
    {
        if (whTree[son[p]] == -1)
        {
            dfs(wh, son[p], dep + 1, dis + len[p]);
            seq.push_back(u);
        }
    }
}

int min(int v1, int v2)
{
    return deep[v1] < deep[v2] ? v1 : v2;
}

void RMQ_init()
{
    pow2[0] = 1;
    for (int i = 1; i < 20; i ++)
        pow2[i] = pow2[i - 1] * 2;
    for (int i = 0; i < seq.size(); i ++)
        f[i][0] = seq[i];
    int n = seq.size();
    int m = (int)(log(n) / log(2));
    for (int j = 1; j <= m; j ++)
        for (int i = 0; i < n; i ++)
        {
            if (i + pow2[j] - 1 >= n) break;
            f[i][j] = min(f[i][j - 1], f[i + pow2[j - 1]][j - 1]);
        }
}

int RMQ_query(int i, int j)
{
    if (whTree[i] != whTree[j])
        return -1;
    if (pos[i] > pos[j])
        swap(i, j);
    int len = (int)(log(pos[j] - pos[i] + 1) / log(2));
    int fa = min(f[pos[i]][len], f[pos[j] - pow2[len] + 1][len]);
    return dist[i] + dist[j] - dist[fa] * 2;
}

void prepare()
{
    seq.clear();
    memset(whTree, 255, sizeof(whTree));
    int wh = 0;
    for (int i = 1; i <= n; i ++)
        if (whTree[i] == -1)
            dfs(++ wh, i, 0, 0);
}

int main()
{
    int m, q;
    while (scanf("%d%d%d", &n, &m, &q) != EOF)
    {
        tot = 0;
        memset(now, 0, sizeof(now));
        while (m --)
        {
            int u, v, l;
            scanf("%d%d%d", &u, &v, &l);
            edge(u, v, l);
            edge(v, u, l);
        }
        prepare();
        RMQ_init();
        while (q --)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            int len = RMQ_query(a, b);
            if (len == -1)
                printf("Not connected\n");
            else
                printf("%d\n", len);
        }
    }
    return 0;
>>>>>>> 771e6331fcc7e2913b52ff123b6bf756d4d78248
}
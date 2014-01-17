//POJ 1287 Networking -- Kruskal
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF     0x7fffffff
#define MAXN    1000

typedef struct edge
{
    int u, v, w;
} edge;

int n, m;
int father[MAXN];
vector<edge> edges;

bool cmp(const edge& a, const edge& b)
{
    return a.w < b.w;
}

int get_root(int x)
{
    if (father[x] == x) return x;
    father[x] = get_root(father[x]);
    return father[x];
}

bool union_two(int x, int y)
{
    int fx = get_root(x);
    int fy = get_root(y);
    if (fx != fy)
    {
        father[fx] = fy;
        return true;
    }
    return false;
}

int kruskal()
{
    for (int i = 0; i < n;  ++ i)
        father[i] = i;
    int mst = 0;
    for (int i = 0; i < edges.size(); ++ i)
    {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (union_two(u, v))
            mst += w;
    }
    return mst;
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        scanf("%d", &m);
        edges.clear();
        for (int i = 0; i < m; ++ i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u--, v--;
            edges.push_back(edge{u, v, w});
        }
        sort(edges.begin(), edges.end(), cmp);
        printf("%d\n", kruskal());
    }
    return 0;
}

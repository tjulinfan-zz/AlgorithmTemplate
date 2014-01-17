//POJ 1287 Networking -- Prim
#include <cstdio>
#include <cstring>

#define INF     0x7fffffff
#define MAXN    1000

int n, m;
int dist[MAXN][MAXN];
int lowdist[MAXN];

int prim()
{
    int mst = 0;
    for (int i = 0; i < n; ++ i)
        lowdist[i] = (dist[i][0] == -1 ? INF : dist[i][0]);
    lowdist[0] = 0;
    for (int r = 0; r < n - 1; ++ r)
    {
        int mindis = INF, minone;
        for (int i = 0; i < n; ++ i)
            if (lowdist[i] && lowdist[i] < mindis)
            {
                mindis = lowdist[i];
                minone = i;
            }
        if (mindis == INF) break;
        mst += mindis;
        lowdist[minone] = 0;
        for (int i = 0; i < n; ++ i)
            if (lowdist[i] && dist[i][minone] > -1 && dist[i][minone] < lowdist[i])
                lowdist[i] = dist[i][minone];
    }
    return mst;
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        scanf("%d", &m);
        memset(dist, -1, sizeof(dist));
        for (int i = 0; i < m; ++ i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u --, v--;
            if (dist[u][v] == -1 || w < dist[u][v])
                dist[u][v] = dist[v][u] = w;
        }
        printf("%d\n", prim());
    }
    return 0;
}

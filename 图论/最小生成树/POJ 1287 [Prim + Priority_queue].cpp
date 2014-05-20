//POJ 1287 Networking -- Prim + Priority_queue
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

const int MAXN = 1000;

typedef pair<int, int> PII;

int n, m;
int d[MAXN], flag[MAXN];
vector<PII> e[MAXN];
priority_queue<PII, vector<PII>, greater<PII> > q;

int prim(int s)
{
    for (int i = 0; i < n; ++ i)
        d[i] = INT_MAX, flag[i] = 0;
    int mst = 0;
    q.push(PII(s, 0)); flag[s] = 1; d[s] = 0;
    while (!q.empty())
    {
        int u = q.top().second; flag[u] = 1;
        mst += q.top().first;
        for (size_t i = 0; i < e[u].size(); ++ i)
        {
            int v = e[u][i].first, dis = e[u][i].second;
            if (dis < d[v])
            {
                d[v] = dis;
                q.push(PII(dis, v));
            }
        }
        while (!q.empty() && flag[q.top().second])
            q.pop();
    }
    return mst;
}

int main()
{
    while (scanf("%d", &n) != EOF && n)
    {
        scanf("%d", &m);
        for (int i = 0; i < n; ++ i)
            e[i].clear();

        while (m --)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u --, v --;
            e[u].push_back(PII(v, w));
            e[v].push_back(PII(u, w));
        }

        printf("%d\n", prim(0));
    }
    return 0;
}

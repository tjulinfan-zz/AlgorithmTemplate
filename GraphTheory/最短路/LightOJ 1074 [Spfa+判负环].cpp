#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

#define INF 0x7FFFFFFF

int n, m, tot;
int busyness[300], now[300];
int pre[100000], son[100000], val[100000];
int dis[300], cnt[300];
bool inq[300];

void edge(int a, int b, int v)
{
    pre[++ tot] = now[a];
    now[a] = tot;
    son[tot] = b;
    val[tot] = v;
}

bool spfa()
{
    for (int i = 1; i <= n; i ++)
    {
        dis[i] = INF;
        cnt[i] = 0;
        inq[i] = false;
    }
    
    queue<int> q;
    q.push(1);
    inq[1] = false;
    dis[1] = 0;
    cnt[1] ++;
    
    while (!q.empty())
    {
        int u = q.front();
        for (int p = now[u]; p; p = pre[p])
        {
            int v = son[p];
            if (dis[v] > dis[u] + val[p])
            {
                dis[v] = dis[u] + val[p];
                if (!inq[v])
                {
                    cnt[v] ++;
                    inq[v] = true;
                    if (cnt[v] > n) return false;
                    q.push(v);
                }
            }
        }
        inq[u] = false;
        q.pop();
    }
    return true;
}

int cube(int x)
{
    return x * x * x;
}

void init()
{
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> busyness[i];
        
    tot =  0;
    for (int i = 1; i <= n; i ++)
        now[i] = 0;
    cin >> m;
    for (int i = 0; i < m; i ++)
    {
        int u, v;
        cin >> u >> v;
        edge(u, v, cube(busyness[v] - busyness[u]));
    }
}

void query()
{
    spfa();
    int m;
    cin >> m;
    for (int i = 0; i < m; i ++)
    {
        int q;
        cin >> q;
        if (dis[q] == INF || dis[q] < 3)
            cout << "?" << endl;
        else
            cout << dis[q] << endl;
    }
}

int main()
{
    int run_case;
    cin >> run_case;
    for (int ri = 1; ri <= run_case; ri ++)
    {
        init();
        cout << "Case " << ri << ":" << endl;
        query();
    }
}

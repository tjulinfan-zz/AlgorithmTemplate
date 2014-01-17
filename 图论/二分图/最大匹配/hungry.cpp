//POJ 1274	 The Perfect Stall 二分图匹配 匈牙利算法
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAXN 300

int n, m;
int mat[MAXN];
bool vis[MAXN];
bool map[MAXN][MAXN];

bool find(int x)
{
    for (int i = 1; i<= m; ++ i)
        if (map[x][i] && !vis[i])
        {
            vis[i] = true;
            if (mat[i] == 0 || find(mat[i]))
            {
                mat[i] = x;
                return true;
            }
        }
    return false;
}

void hungary()
{
    memset(mat, 0 ,sizeof(mat));
    int match = 0;
    for (int i = 1; i <= n; ++ i)
    {
        memset(vis, 0, sizeof(vis));
        if (find(i))
            match ++;
    }
    printf("%d\n", match);
}

bool read_data()
{
    if (scanf("%d%d", &n, &m) == EOF)
        return false;
    memset(map, 0, sizeof(map));
    for (int i = 1; i <= n; ++ i)
    {
        int cn;
        scanf("%d", &cn);
        for (int r = 0; r < cn; ++ r)
        {
            int x;
            scanf("%d", &x);
            map[i][x] = true;
        }
    }
    return true;
}

int main()
{
    while (read_data())
        hungary();
    return 0;
}

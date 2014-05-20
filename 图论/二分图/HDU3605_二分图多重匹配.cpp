//HDU 3605 二分图多重匹配
//集合X点度1, 集合Y点度可以大于1 求X的最大匹配
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

const int MAXM = 11;
const int MAXN = 100010;

int n, m;
int cap[MAXM];
bool vis[MAXM];
vector<int> match[MAXM];
int link[MAXN][MAXM];

bool find(int x) {
    for (int i = 0; i < m; ++ i)
        if (!vis[i] && link[x][i]) {
            vis[i] = 1;
            if (match[i].size() < cap[i]) {
                match[i].push_back(x);
                return true;
            }
            for (size_t j = 0; j < match[i].size(); ++ j)
            {
                if (find(match[i][j])) {
                    match[i][j] = x;
                    return true;
                }
            }
        }
    return false;
}

void hungary() {
    for (int i = 0; i < m; ++ i)
        match[i].clear();
    bool flag = true;
    for (int i = 0; i < n; ++ i) {
        memset(vis, 0, sizeof(vis));
        if (!find(i)) {
            flag = false;
            break;
        }
    }
    if (flag)
        puts("YES");
    else
        puts("NO");
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j)
                scanf("%d", &link[i][j]);
        for (int i = 0; i < m; ++ i)
            scanf("%d", &cap[i]);
        hungary();
    }
    return 0;
}

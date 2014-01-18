#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 240;

vector<int> e[maxn];
int n, m, u, v;
int flag[maxn];

bool color(int u, int c) {	//È¾É«
    if (flag[u] == -1) {
        flag[u] = c;
        bool ans = true;
        for (size_t i = 0; i < e[u].size(); i++)
            ans = ans && color(e[u][i], c ^ 1);
        return ans;
    } else return flag[u] == c;
}

int main() {
    while (cin>>n>>m) {
        for (int i = 0; i < n; i++) e[i].clear();
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            --u; --v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for (int i = 0; i < n; i++) flag[i] = -1;	//³õÊ¼»¯
        bool ans = true;
        for (int i = 0; i < n; i++)
            if (flag[i] == -1) ans = ans && color(i, 0);
    }
    return 0;
}

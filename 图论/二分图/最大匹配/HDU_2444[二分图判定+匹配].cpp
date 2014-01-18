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

int link[maxn];
bool used[maxn];

bool dfs(int u) {
    for (size_t i = 0; i < e[u].size(); i++) {
        int v = e[u][i];
        if (!used[v]) {
            used[v]=true;
            if(link[v]==-1 || dfs(link[v])) {
                link[v]=u;
                return true;
            }
        }
    }
    return false ;
}

int Xiong()
{
    int res=0;
    for (int i = 0; i < n; i++) link[i] = -1;
    for(int i=0;i<n;i++) {
        if (flag[i]) continue;
        memset(used,false,sizeof(used));
        if(dfs(i))
            res++;
    }
    return res;
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
        if (!ans) {
            cout<<"No"<<endl;
            continue;
        }
        int cnt = Xiong();
        cout<<cnt<<endl;
    }
    return 0;
}

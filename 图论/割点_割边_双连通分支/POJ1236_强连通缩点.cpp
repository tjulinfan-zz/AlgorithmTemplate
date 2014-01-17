#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

const int maxn = 120000;
const int maxm = 480000;

int n,m,u,v;

int son[maxm], pre[maxm],  val[maxm], now[maxn];
int vis[maxm], dfn[maxn], low[maxn], bridge[maxm], color[maxn], indeg[maxn], outdeg[maxn];
int cnt;

void clear(int n) {
    cnt = 0;
    for (int i = 0; i < n; i++) now[i] = -1, dfn[i] = 0, color[i] = -1;
}
void addEdge(int u, int v) {
    vis[cnt] = 0; bridge[cnt] = 0;
    pre[cnt] = now[u]; son[cnt] = v; now[u] = cnt++;
}

stack<int> st;
int num, col;

void tarjan(int u) {
    dfn[u] = low[u] = ++num;
    st.push(u);
    for (int id = now[u]; id != -1; id = pre[id]) {
        int v = son[id];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                bridge[id & (-2)] = 1;
            }
        } else if (color[v] == -1)
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        while (st.top() != u) {
            color[st.top()] = col;
            st.pop();
        }
        color[u] = col++;
        st.pop();
    }
}

int main() {
    while (cin>>n) {
        clear(n);
        for (int i = 0; i < n; i++) {
            while (1) {
                scanf("%d", &v);
                if (v == 0) break;
                --v;
                addEdge(i, v);
            }
        }
        num = col = 0;
        for (int i = 0; i < n; i++)
            if (!dfn[i])
                tarjan(i);
        if (col == 1) {
            puts("1\n0\n"); continue;
        }
        for (int i = 0; i < n; i++) indeg[i] = outdeg[i] = 0;
        for (int i = 0; i < n; i++) {
            for (int id = now[i]; id != -1; id = pre[id])
                if (color[i] != color[son[id]]) indeg[color[son[id]]]++, outdeg[color[i]]++;
        }
        int ans1 = 0, ans2 = 0;
        for (int i = 0; i < col; i++) {
            if (indeg[i] == 0) ans1++;
            if (outdeg[i] == 0) ans2++;
        }
        printf("%d\n", ans1);
        printf("%d\n", max(ans1, ans2));
    }
    return 0;
}

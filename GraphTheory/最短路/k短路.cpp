//SDOI 魔法猪学院
/*
求解用能量sum可以从1到n走多少次（每次路线不能一样）
及最短路+第二短路+第三……《sum
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

const int maxn = 6000;

typedef pair<int,double> PID;
typedef pair<double,int> PDI;

int n, m, u, v, ans;
double sum, w;
vector<PID> e[maxn], rev_e[maxn];
priority_queue<PDI, vector<PDI>, greater<PDI> > q;
int flag[maxn];
double h[maxn];                                     //f[i] = g[i] + h[i]
int times[maxn];                                    //弹出次数

void rev_dijkstra(int s) {
    for (int i = 1; i <= n; i++) flag[i] = 0, h[i] = INT_MAX / 2;
    while (!q.empty()) q.pop();
    q.push(PDI(0,s)); flag[s] = 1; h[s] = 0;
    for (int k = 0; k < n-1; k++) {
        int u = q.top().second; flag[u] = 1;
        for (size_t i = 0; i < rev_e[u].size(); i++) {
            int v = rev_e[u][i].first;
            double dis = rev_e[u][i].second;
            if (dis + h[u] < h[v]) {
                h[v] = dis + h[u];
                q.push(PDI(h[v], v));
            }
        }
        while (flag[q.top().second]) q.pop();
    }
}

void A_star(int s){
    int v, u; double dis, f;
    int i;
    if (h[s] == INT_MAX / 2) return;
    memset(times, 0, sizeof(times));
    while (!q.empty()) q.pop();
    q.push(PDI(0 + h[s],s));
    while (!q.empty()) {
        f = q.top().first;
        u = q.top().second;
        q.pop();
        times[u] ++;
        if (u == n){
                if (f > sum) return;
                ans ++;                            //第ans短路
                sum = sum - f;
                continue;
                }
        for (size_t i = 0; i < e[u].size(); i++) {
            v = e[u][i].first;
            dis = e[u][i].second;
            if (f-h[u]+dis+h[v] <= sum) q.push(PDI(f-h[u]+dis+h[v], v));
        }
    }
}

int main() {
    while (scanf("%d%d%lf", &n, &m, &sum) != EOF) {
        for (int i = 0; i < n; i++) e[i].clear();
        for (int i = 0; i < n; i++) rev_e[i].clear();
        while (m--) {
            scanf("%d%d%lf", &u, &v, &w);
            e[u].push_back(PID(v, w));
            rev_e[v].push_back(PID(u, w));
        }
        rev_dijkstra(n);                                  //求解h[i]
        ans = 0;
        A_star(1);
        printf("%d\n", ans);
    }
    return 0;
}
/*
4 6 14.9
1 2 1.5
2 1 1.5
1 3 3
2 3 1.5
3 4 1.5
1 4 1.5
*/

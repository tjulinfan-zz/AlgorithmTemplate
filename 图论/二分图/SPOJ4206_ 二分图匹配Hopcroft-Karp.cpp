//SPOJ 4206 MATCHING 二分图匹配 Hopcroft-karp算法 O(E * V ^ 0.5)
/*
 | Hopcroft-Karp与匈牙利的唯一区别就在于匈牙利每次只找一条增广路(往往用DFS实现),
 | 而Hopcroft-Karp则是用BFS找出若干条增广路, 然后选择其中的一些进行增广.
 | 这些增广路可能会重叠, 但是不要紧, Hopcroft-Karp利用了最大流算法中的层次图概念,
 | 在BFS的时候先给BFS的每层中的可行点进行标号, 标号每层+1,
 | 找出所有增广路后再选若干起点做DFS, 每次按照标号递增的顺序找到一条增广路,
 | 标号按1递增保证了这条路径一定是BFS中的一条有效路径,
 | 并且每次增广以后将路径上的点的匹配更新, 以防止下一次DFS的时候走了重复的点,
 | 这样一来每次BFS以后至少能找到一条增广路, 运气好的话, 比如一个完全图, 那么只要一次BFS就能找出最大匹配.
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXX = 50010;
const int MAXY = 50010;

int n, m, p;
vector<int> e[MAXX];
int matx[MAXX], maty[MAXY];
int dx[MAXX], dy[MAXY];

bool bfs() {
    bool foundAug = false;
    memset(dx, 0, sizeof(dx));
    memset(dy, 0, sizeof(dy));

    queue<int> q;
    for (int i = 1; i <= n; ++ i)
        if (matx[i] == -1)
            q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < e[x].size(); ++ i) {
            int y = e[x][i];
            if (dy[y] == 0) {
                dy[y] = dx[x] + 1;
                if (maty[y] == -1) {
                    foundAug = true;
                } else {
                    dx[maty[y]] = dy[y] + 1;
                    q.push(maty[y]);
                }
            }
        }
    }
    return foundAug;
}

bool find(int x) {
    for (int i = 0; i < e[x].size(); ++ i) {
        int y = e[x][i];
        if (dy[y] == dx[x] + 1) {
            dy[y] = 0;
            if (maty[y] == -1 || find(maty[y])) {
                matx[x] = y;
                maty[y] = x;
                return true;
            }
        }
    }
    return false;
}

void hopcroftKarp() {
    memset(matx, 255, sizeof(matx));
    memset(maty, 255, sizeof(maty));
    int ans = 0;
    while (bfs()) {
        for (int i = 1; i <= n; ++ i)
            if (matx[i] == -1 && find(i))
                ans ++;
    }
    printf("%d\n", ans);
}

void init() {
    scanf("%d%d%d", &n, &m, &p);

    for (int i = 0; i <= n; ++ i)
        e[i].clear();
    while (p --) {
        int x, y;
        scanf("%d%d", &x, &y);
        e[x].push_back(y);
    }
}

int main() {
    init();
    hopcroftKarp();
    return 0;
}

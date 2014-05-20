#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1080;
#define inf 1000000000
#define _clr(x) memset(x,0xff,sizeof (int)*n)

int s[maxn],t[maxn],l1[maxn],l2[maxn],p,q,ret=0,i,j,k;

int kuhn_munkras(int m,int n,int mat[][maxn],int* match1,int* match2) {
    for (i=0; i<m; i++)
        for (l1[i]=-inf,j=0; j<n; j++)
            l1[i]=mat[i][j]>l1[i]?mat[i][j]:l1[i];
    for (i=0; i<n; l2[i++]=0);
    for (_clr(match1),_clr(match2),i=0; i<m; i++) {
        for (_clr(t),s[p=q=0]=i; p<=q&&match1[i]<0; p++)
            for (k=s[p],j=0; j<n&&match1[i]<0; j++)
                if (l1[k]+l2[j]==mat[k][j]&&t[j]<0) {
                    s[++q]=match2[j],t[j]=k;
                    if (s[q]<0)
                        for (p=j; p>=0; j=p)
                            match2[j]=k=t[j],p=match1[k],match1[k]=j;
                }
        if (match1[i]<0) {
            for (i--,p=inf,k=0; k<=q; k++)
                for (j=0; j<n; j++)
                    if (t[j]<0&&l1[s[k]]+l2[ j]-mat[s[k]][j]<p)
                        p=l1[s[k]]+l2[j]-mat[s[k]][j];
            for (j=0; j<n; l2[ j]+=t[j]<0?0:p,j++);
            for (k=0; k<=q; l1[s[k++]]-=p);
        }
    }
    for (i=0; i<m; i++)
        ret+=mat[i][match1[i]];
    return ret;
}

//以上为模板(浙大)
//二分图最佳匹配,kuhn munkras 算法, 邻接阵形式, 复杂度 O(m*m*n)
//返回最佳匹配值, 传入二分图大小 m,n 和邻接阵 mat,表示权值
//match1,match2 返回一个最佳匹配, 未匹配顶点 match 值为-1
//一定注意 m<=n,否则循环无法终止
//最小权匹配可将权值取相反数


//ZOJ 2342
//a[i]+a[j]>=w[k] (i,j为二分图不同侧点) 求a[i]使sigma{a[i]}最小 可转化为最优匹配

int T, n, m, u, v, w;
int mat[maxn][maxn], fa[maxn], depth[maxn], faid[maxn];
int pre[maxn], now[maxn], e[maxn], num[maxn], val[maxn];
int ecnt;
void addEdge(int u, int v, int w, int id) {
    e[ecnt] = v; pre[ecnt] = now[u]; num[ecnt] = id; val[ecnt] = w; now[u] = ecnt++;
}

void predfs(int u, int p, int d) {
    fa[u] = p; depth[u] = d;
    for (int id = now[u]; id != -1; id = pre[id]) {
        int v = e[id];
        if (v == p) continue;
        faid[v] = id;
        predfs(v, u, d + 1);
    }
}

void conn(int u, int v, int w, int id) {
    if (depth[u] < depth[v]) swap(u, v);
    while (depth[u] > depth[v]) {
        int eid = num[faid[u]];
        mat[eid][id] = max(0, val[faid[u]] - w);
        u = fa[u];
    }
    while (u != v) {
        int eid = num[faid[u]];
        mat[eid][id] = max(0, val[faid[u]] - w);
        u = fa[u];
        eid = num[faid[v]];
        mat[eid][id] = max(0, val[faid[v]] - w);
        v = fa[v];
    }
}

int buf1[maxn], buf2[maxn];
int ansv[maxn];

int main() {
    cin>>T;
    int kk = 0;
    while (T--) {
        if (kk++) puts("");
        scanf("%d%d",&n,&m);
        memset(mat, 0, sizeof(mat));
        memset(now, 0xff, sizeof(now));
        ecnt = 0;
        for (int i = 0; i < n - 1; i++) {
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;
            addEdge(u, v, w, i);
            addEdge(v, u, w, i);
            ansv[i] = w;
        }
        predfs(0, 0, 0);
        for (int i = n - 1; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;
            conn(u, v, w, i - n + 1);
            ansv[i] = w;
        }
        if ( (n-1) * 2 > m ) {
            for (int i = 0; i < m; i++)
                for (int j = 0; j < i; j++)
                    swap(mat[i][j], mat[j][i]);
            kuhn_munkras(m - n + 1, n - 1, mat, buf1, buf2);
            for (int i = 0; i < m; i++) swap(l1[i], l2[i]);
            for (int i = 0; i < m; i++) swap(buf1[i], buf2[i]);
        }
        else kuhn_munkras(n - 1, m - n + 1, mat, buf1, buf2);
        for (int i = 0; i < n - 1; i++)
            ansv[i] -= l1[i];
        for (int i = 0; i < m - n + 1; i++)
            ansv[i + n - 1] += l2[i];
        for (int i = 0; i < m; i++) printf("%d\n", ansv[i]);
    }
    return 0;
}

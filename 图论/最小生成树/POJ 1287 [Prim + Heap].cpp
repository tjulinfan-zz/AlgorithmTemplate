//POJ 1287 Networking -- Prim + Heap
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 1000
#define INF 0x7fffffff

typedef struct edge
{
    int u, v, w, pre;
} Edge;

typedef struct heap_node
{
    int v, no;
} HeapNode;

int n, m, size;;
vector<Edge> edges;
HeapNode h[1000];
int last[MAXN], pos[MAXN]; //pos表示i点在堆数组中的下标;

void add_edge(int u, int v, int w)
{
    edges.push_back(Edge{u, v, w, last[u]});
    last[u] = edges.size() - 1;
}

void swap(int pa, int pb)
{
    HeapNode t = h[pa]; h[pa] = h[pb]; h[pb] = t;
    pos[h[pa].no] = pa;
    pos[h[pb].no] = pb;
}

HeapNode pop()
{
    swap(1, size);
    size --;
    int p = 1;
    while (p * 2 <= size)
    {
        int son = p * 2;
        if (son + 1 <= size && h[son].v > h[son + 1].v)
            son += 1;
        if (h[son].v < h[p].v)
        {
            swap(p, son);
            p = son;
        }
        else
            break;
    }
    return h[size + 1];
}

void relax(int p, int v)
{
    if (v < h[p].v)
    {
        h[p].v = v;
        while (p > 1 && h[p].v < h[p >> 1].v)
        {
            swap(p, p >> 1);
            p >>= 1;
        }
    }
}

int prim()
{
    int mst = 0;
    for (int i = 1; i <= n; ++ i)
        h[i].no = pos[i] = i, h[i].v = INF;
    size = n;
    relax(pos[1], 0);
    while (size > 0)
    {
        HeapNode top = pop();
        mst += top.v;
        for (int p = last[top.no]; p != -1; p = edges[p].pre)
            if (pos[edges[p].v] <= size)
                relax(pos[edges[p].v], edges[p].w);
    }
    return mst;
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        scanf("%d", &m);
        edges.clear();
        memset(last, -1, sizeof(last));
        for (int i = 0; i < m; ++ i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
        printf("%d\n", prim());
    }
    return 0;
}

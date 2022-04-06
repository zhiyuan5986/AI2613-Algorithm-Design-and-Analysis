#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include <queue>
using namespace std;
//本题的思路为Tarjan算法求无向图的桥边+Kruskal算法生成一棵最小生成树
//Tarjan算法的内容见https://visors.github.io/post/tarjan%E6%B1%82%E6%97%A0%E5%90%91%E5%9B%BE%E5%89%B2%E8%BE%B9/
//https://zhuanlan.zhihu.com/p/101923309
//https://blog.csdn.net/qq_39599067/article/details/81321884

//edge
struct edge {
    int start;
    int end;
    int a;
    int b;
    int num;
};
bool operator > (const edge &e1, const edge &e2) {return e1.a > e2.a;}

//DisjointSet
class Set {
public:
    int size;
    int *parent;

    Set(int s) {
        size = s;
        parent = new int[size];
        for (int i=0;i<size;++i) parent[i] = -1;
    }
    void Union(int u, int v)
    {
        int root1 = Find(u);
        int root2 = Find(v);//注意，这里必须要先find root，之前的板子是在外部去find，这里改成了内部find。因为这个导致有些数据集过不了。
        if (root1 == root2) return;
        if (parent[root1] > parent[root2]) {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
        else {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }
    int Find(int x)
    {
        if (parent[x] < 0) return x;
        return parent[x] = Find(parent[x]);
    }
};

//Some global variables
const int MAXN = 1e5+1;
const int MAXE = 5e5+2;
Set s(MAXN);
int dfn[MAXN], low[MAXN];// , fa[MAXN];
int n, m, tot,  num_of_bridge;
long long int cost;
vector<edge> edges[MAXN];

//tarjan algorithm
void tarjan(int start, int num)
{
    dfn[start] = low[start] = ++tot;
    for (int i=0;i<edges[start].size();++i) {
        int y = edges[start][i].end;
        int n = edges[start][i].num;
        if (!dfn[y]) {
            // fa[y] = start;
            tarjan(y,n);
            low[start] = min(low[start],low[y]);
            if (low[y] > dfn[start]) { //这种情况下，start->y是一条桥边
                s.Union(start,y);
                cost += edges[start][i].b;
                ++num_of_bridge;
            }
        }
        else if (num != n) low[start] = min(low[start],dfn[y]); //无向图是用双向的有向边来存储的，所以要规避父节点到自己的这条边。但是有时候确实有重边，这时候需要更新low
    }
}

int main() {
    memset(dfn,0,MAXN);
    // memset(fa,0,MAXN);
    cin >> n >> m;
    tot = 0,cost=0,num_of_bridge=0;
    for (int i = 1; i <= m; i++) {
        int s,t,a,b;
        cin >> s >> t >> a >> b; 
        edges[s].push_back({s,t,a,b,i});
        edges[t].push_back({t,s,a,b,i});
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i,0);

    //Kruskal
    priority_queue<edge,vector<edge>, greater<edge> > q;
    for (int i=1;i<=n;++i) {
        for (int j=0;j<edges[i].size();++j) {
            q.push(edges[i][j]);
        }
    }
    int edgesAccepted = 0;
    while (edgesAccepted < n-num_of_bridge-1) {
        edge e = q.top();
        q.pop();
        int u = s.Find(e.start);
        int v = s.Find(e.end);
        if (u != v) {
            ++edgesAccepted;
            s.Union(u,v);
            cost += e.a;
        }
    }
    // for (int i=1;i<=n;++i) cout << low[i] << ' ';
    cout << cost;
    return 0;
}
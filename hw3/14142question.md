# 题目描述
author: 侯不会 原OJ链接：[https://acm.sjtu.edu.cn/OnlineJudge-old/problem/4142](https://acm.sjtu.edu.cn/OnlineJudge-old/problem/4142).
# Description
近日，由于一场世纪大地震，某国通讯设施全面瘫痪。在灾后重建中，抢修通讯设备成为首要任务。现在，你已经了解该国的基本状况，该国首脑希望你设计一种方案，使得所用的救灾资金尽可能少。 已知该国地形可以简化成包含$n$个点的一张无向图，每个点代表一座城市。由于地震的破坏，该国的城市之间已经只剩下$m$条仍具备通行条件的双向道路。当然，目前该国的所有城市是联通的。现在，该国希望在一些仍能通行的道路下铺设通信电缆，使得任意两个城市之间能够通过通信电缆直接或间接地传递灾情。不过，若某条道路被破坏后，该国的所有城市不再全部联通，则这条道路被认为是危险道路，因为一旦这条道路被次生灾害破坏，那么相应的通信电缆也会被破坏，而且没有其他可供选择的途径来恢复通信。在这样的危险道路上，你只能选择用无线通信设备代替。（注意：在非危险道路上，即使无线设施的费用低于通信电缆的费用，你也只能铺设通信电缆，因为这种方式可靠性更高。）

# Input Format
第一行包含两个正整数$n$和$m$。 接下来共$m$行，第$i$行包含四个整数$s[i]$，$t[i]$，$a[i]$和$b[i]$，分别表示第$i$条道路连接的两座城市，以及在该条道路上铺设电缆和架设无线设备的费用。

# Output Format
第一行包含一个整数，表示最小代价。

# Sample Input
```
8 11
2 6 0 9
2 7 8 6
7 3 4 0
4 8 3 0
4 5 0 0
4 1 1 10
2 4 0 10
7 6 0 10
2 3 2 1
1 4 1 0
1 5 2 4
```
# Sample Output
```
13
```
# 数据范围
对于$30\%$的数据，$n \le 500$，$m \le 3000$。 对于额外$40\%$的数据，数据保证不存在危险道路。 对于$100\%$的数据，$n \le 10^{5}$，$m \le 5 \times 10^{5}$。 在每一部分数据中，均包含若干较小的测试点。
# 解决方案
```cpp
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
```
#  总结
这个算法写了我好久，Tarjan+Kruskal还是比较好想到的，但是具体实现起来有很多坑，比如之前的并查集使用错误，cost要声明为long long int，tarjan算法在有重边的时候的处理方式 (在edge类加上了一个num指代序号)。感谢助教学姐的耐心指教，但愿daydayup！
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

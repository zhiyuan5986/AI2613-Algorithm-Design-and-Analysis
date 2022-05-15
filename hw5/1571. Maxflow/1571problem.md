# 题目描述
给出一个网络图，及其源点汇点，求出其网络最大流。

# 输入格式
第一行包含四个正整数$n,m,s,t$, 分别表示点的个数，有向边的数量，源点序号，汇点序号。

接下来$m$行每行三个正整数，$u_i,v_i,w_i$,表示第$i$条有向边从$u_i$出发，到达$v_i$，能通过的最大流量为$w_i$。

# 输出格式
一个正整数，即为该网络的最大流。

# 样例输入
```
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40
```
# 样例输出
```
50
```
# 数据范围
对于 30% 的数据，保证 $n \le 10$，$m\le 25$。

对于 100% 的数据，保证 $1\le n\le 100$，$1\le m\le 1000$，$0≤w<2^{31}$ 。

# 时空磁盘限制（运行时）
时间限制： 1000 ms
空间限制： 244 MiB
# 解决方案
```cpp
//modified from v3
//https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;
 
#define V 101
long long int graph[V][V];//因为节点数较小，使用邻接矩阵存图

bool bfs(long long int rGraph[V][V], int n, int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 1; v <= n; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {//此时找到了一个可以更新距离信息的节点
                if (v == t) {//如果v等于汇，那么说明存在一条s到t的路径，这条路径被parent数组记录下来了。只需返回即可。
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;//没有到汇的路径，返回false
}
 
long long int EK(long long int graph[V][V], int n, int s, int t)
{
    int u, v;
    long long int rGraph[V][V]; // Residual graph
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
 
    int parent[V]; //用于指代节点的访问顺序
    long long int max_flow = 0; 
 
    while (bfs(rGraph, n,  s, t, parent)) {
        long long int path_flow = LONG_MAX;//这里直接调用limits库的LONG_MAX
        for (v = t; v != s; v = parent[v]) {//找到这条路径上最小的容量
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    return max_flow;
}
 
int main()
{
    int m, n, s, t;
    memset(graph,0,sizeof(graph));
    cin >> n >> m >> s >> t;
    int u, v, w;
    for (int i=0;i<m;++i) {
        cin >> u >> v >> w;
        graph[u][v] += w;
    }
    cout << EK(graph,n, s, t);
 
    return 0;
}
```

# 解决方案2
```cpp
//modified from v4
//modified from v2
//https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
#include <iostream>
#include <string.h>
#include <queue>
#include <limits.h>
using namespace std;

const int MAXN = 101;
const int MAXM = 1001;
int m, n, s, t;
long long int edges[MAXN][MAXN]; //因为节点数较小，使用邻接矩阵存图。似乎不需要另外定义一个残差网络
int parent[MAXN]; //用于指代节点的访问顺序
bool visited[MAXN];

//int min(int a, int b) {return (a > b ? b : a);}

bool bfs()
{
    memset(visited,0,sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    //接下来是BFSloop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v=1;v<=n;++v) {
            if (visited[v] == false && edges[u][v] > 0) {//此时找到了一个可以更新距离信息的节点
                if (v == t) {//如果v等于汇，那么说明存在一条s到t的路径，这条路径被parent数组记录下来了。只需返回即可。
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false; //没有到汇的路径，返回false
}

long long int EK()
{
    long long int max_flow=0; //根据w的范围，此处需要long long
    int u, v;
    while (bfs()) {
        long long int path_flow = LONG_MAX;//由于w的上限是2^31-1，实在是太大了， 这里直接调用limits库的INT_MAX
        for (v = t;v != s;v = parent[v]) { //找到这条路径上最小的容量
            u = parent[v];
            path_flow = min(path_flow,edges[u][v]);
        }
        for (v = t;v != s;v = parent[v]) {
            u = parent[v];//在之前漏了这行！！！！
            edges[u][v] -= path_flow;
            edges[v][u] += path_flow;
        }
        max_flow += path_flow;
        memset(parent,0,sizeof(parent));
    }
    return max_flow;
}

int main()
{
    memset(edges,0,sizeof(edges));
    cin >> n >> m >> s >> t;
    int u, v, w;
    for (int i=0;i<m;++i) {
        cin >> u >> v >> w;
        edges[u][v] += w;
    }
    cout << EK();
    return 0;
}
```
# 总结
本题要求实现上课讲到的Edmond-Karp算法，参考了[https://www.geeksforgeeks.org/ford-fulkerso
n-algorithm-for-maximum-flow-problem/](https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/)。基本思路是：用邻接矩阵存图（因为$n$较小），初始时设每条边的capacity为0，在运行Edmond-Karp算法时，重复调用bfs，用parent数组存储寻找到的path，更新残差网络（residual graph）。注意，本题很坑的一点是会有重边，所以在初始化存边的时候，需要用+=，并且两个图都要用long long int型的数组，否则第6第7数据点过不了（感谢rxygg指出这个问题）。
# 声明
题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

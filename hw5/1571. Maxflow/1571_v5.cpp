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
        long long int path_flow = LONG_MAX;//由于w的上限是2^31-1，实在是太大了， 这里直接调用limits库的INT_MAX
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
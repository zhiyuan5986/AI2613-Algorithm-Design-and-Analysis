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
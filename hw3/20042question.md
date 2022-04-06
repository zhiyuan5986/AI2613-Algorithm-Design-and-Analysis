# 题目描述
给定一个大小为$n$的有权无向图$G$，求出从$S$到$T$的最短路径长度。 第一行四个整数$n,m,S,T$, $n$和$m$分别表示图$G$的点数和边数, $S, T$ 分别表示路径的起点和终点。（保证$S, T$联通）
接下来$m$行，每行三个整数$x，y$和$z$，表示$x$和$y$之间有一条权值为$z$的边。

# 输入格式
第一行四个整数$n,m,S,T$, $n$和$m$分别表示图$G$的点数和边数, $S, T$分别表示路径的起点和终点。（保证$S, T$联通）
接下来$m$行，每行三个整数$x，y$和$z$，表示$x$和$y$之间有一条权值为$z$的边。

# 输出格式
输出一个整数，表示最短路径的长度。

# 样例输入
```
    4 4 1 4
    1 2 3
    1 3 2
    2 4 4
    3 4 7
 ```
 
 #  样例输出
 
 ```
 7
 ```
 
# 数据范围
对于30%的数据，$n \le 3000$。
对于100%的数据，$n \le 10^5, m \le 3 \times 10^5$， 边权非负且不超过$10^9$。

# 空间限制
128MB

# 备注
请注意使用算法的最坏复杂度。

# 解决方案
```cpp
//根据题目要求，应该是用dijktra算法，但是要用堆实现。根据权值大小，要用到long long int 
#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>
using namespace std;

const int MAXN=1e5;
const int MAXM=3e5;

struct edge{
    int e;
    int w;
};

struct min_node {
    int number;
    long long int dis; //number代表节点编号，dis代表此时start到该点的最短距离
};

vector<edge> edges[MAXM];

bool operator > (const min_node &n1, const min_node &n2) {
    return n1.dis > n2.dis;
}

long long int dijkstra(int start, int end, int n)
{
    long long int *distance = new long long int[n+1];
    for (int i=0;i<n+1;++i) distance[i]=1e9+1;
    priority_queue<min_node,vector<min_node>, greater<min_node> > q;
    distance[start]=0;
    q.push({start,0});

    while (!q.empty()) {
        min_node node_x = q.top();
        q.pop();
        for (int i=0;i<edges[node_x.number].size();++i) {
            edge edge_y = edges[node_x.number][i];
            if (distance[edge_y.e]>distance[node_x.number]+edge_y.w) {
                distance[edge_y.e]=distance[node_x.number]+edge_y.w;
                q.push({edge_y.e,distance[edge_y.e]});
            }
        }
    }
    return distance[end];
    
}

int main()
{
    int n, m, S, T, start, end, weight;
    cin >> n >> m >> S >> T;
    for (int i=0;i<m;++i) {
        cin >> start >> end >> weight;
        edges[start].push_back({end,weight});
        edges[end].push_back({start,weight});
    }
    cout << dijkstra(S,T,n);
    return 0;
}
```
 # 总结
 本题基于dijkstra算法，在选择边的过程中使用了二叉堆(priority_queue)，从而加快了程序的执行过程。感谢来自以下文章的思路： https://blog.csdn.net/qq_39630587/article/details/83240036
https://blog.csdn.net/geter_CS/article/details/102580332

# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

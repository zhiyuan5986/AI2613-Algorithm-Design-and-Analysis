# 题目描述
给一个 $n (1\leq n \leq 10^6)$ 个点 $m(1\leq m\leq 10^6)$ 条边的无向图，求 $s$ 到 $t$的最短路的长度。

数据保证，$s$ 出发可以到达$t$。

# 输入格式
请从 stdin 读入。

第一行为四个正整数 $n, m, s, t$。

第二行起 $m$ 行，每行三个非负整数 $u_i, v_i, w_i (0 \leq w_i \leq 1)$，表示从 $u_i$到 $v_i$ 有一条权值为 $w_i$ 的无向边。

# 输出格式
请输出到 stdout 中。

输出一行一个整数，表示 $s$ 到 $t$ 的距离。

# 样例输入
```
4 3 2 1
2 3 1
3 4 0
4 1 1
```
# 样例输出
```
2
```
# 数据范围
Time Limit: 1s

Memory Limit: 128MB

# 备注
虽然但是，如果可能的话，请用 $O(n + m)$ 的做法通过这个题吧。

# 解决方案
```cpp
#include <iostream>
#include <deque>
#include <vector>
//本题参考了https://www.geeksforgeeks.org/0-1-bfs-shortest-path-binary-graph/的相关算法，用双边队列真的挺妙的。
//学到了如何使用vector等来简化代码，提高稳定性。
using namespace std;
const int MAXE = 1e6+1;
struct edge {
    int end;
    int weight;
};
vector <edge> edges[MAXE];
int ZeroOneBFS(int s, int t, int n, int m) 
{
    int *distance = new int[n+1];
    for (int i=0;i<=n;++i) distance[i] = n; //注意此处distance的取值，需要取到n，否则会有三个数据集过不了。
    deque<int> q;
    distance[s] = 0;
    q.push_back(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (int i=0;i<edges[u].size();++i) {
            if (distance[edges[u][i].end] > distance[u]+edges[u][i].weight) {
                distance[edges[u][i].end] = distance[u]+edges[u][i].weight;
                if (edges[u][i].weight == 0) q.push_front(edges[u][i].end);
                else q.push_back(edges[u][i].end);
            }
        }
    }
    return distance[t];
}

void addEdge(int start, int end, int weight) {
    edges[start].push_back({end,weight});
    edges[end].push_back({start, weight});
}

int main()
{
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	int start, end, weight;
	for (int i=0;i<m;++i) {
		cin >> start >> end >> weight;
        addEdge(start, end, weight);
	}
	cout << ZeroOneBFS(s,t,n,m);
	return 0;
}
```
# 总结
本题采用了双端队列，利用了BFS找无权图的最短路径的正确性，将$w$为0的边插入队首，$w$为1的插入队尾即可。
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

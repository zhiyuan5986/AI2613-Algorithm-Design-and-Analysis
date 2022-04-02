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
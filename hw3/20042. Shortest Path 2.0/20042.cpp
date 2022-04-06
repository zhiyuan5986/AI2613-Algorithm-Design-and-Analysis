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
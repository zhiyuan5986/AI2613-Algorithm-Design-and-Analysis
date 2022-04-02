//找资料后发现这题需要用到拓扑排序
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
const int MAXN=1e5+1;
struct edge{
    int end;
    bool flag;
};
vector<int> edges[MAXN];
int inDegree[MAXN];
int order[MAXN];
void topSort(int n)
{
    int order_=1; //每个节点的拓扑排序值
    int s;
    queue<int> q;
    for (int i=1;i<=n;++i) if (!inDegree[i]) q.push(i);
    while (!q.empty()) {
        s = q.front();
        q.pop();
        for (int j=0;j<edges[s].size();++j) {
            if (--inDegree[edges[s][j]] == 0) q.push(edges[s][j]);
        }
        order[s]=order_;
        ++order_;
    }
    
}

int main()
{
    memset(inDegree,0,MAXN);
    memset(order,0,MAXN);
    int n, p1, p2;
    cin >> n >> p1 >> p2;
    int start, end;
    for (int i=0;i<p1;++i) {
        cin >> start >> end;
        edges[start].push_back(end);
        ++inDegree[end];
    }
    topSort(n);
    for (int i=0;i<p2;++i) {
        cin >> start >> end;
        if (order[start] < order[end]) cout << start << ' ' << end << endl;
        else cout << end << ' ' << start << endl;
    }
}
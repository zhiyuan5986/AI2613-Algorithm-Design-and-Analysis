//思路是：把每一个顾客当作无限运力的中转站使用
//every farm connect to its first customer. 
//For latter customer to a farm, add an edge from previous customer to him with capacity INT_MAX
//(I use the array named LastCustomerOfFarm to record the last customer)
//https://acm.sjtu.edu.cn/OnlineJudge/code?submit_id=167634
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;
 
const int MAXM = 1002;
const int MAXN = 102;
int m, n;
int edges[MAXM+MAXN][MAXM+MAXN];
const int s = 0;
const int t = 1102;
int parent[MAXM+MAXN]; //用于指代节点的访问顺序
bool visited[MAXM+MAXN];

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

        for (int v=0;v<MAXM+MAXN;++v) {
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

int EK()
{
    int max_flow=0;
    int u, v;
    while (bfs()) {
        int path_flow =INT_MAX;//由于w的上限是2^31-1，实在是太大了， 这里直接调用limits库的INT_MAX
        for (v = t;v != s;v = parent[v]) { //找到这条路径上最小的容量
            u = parent[v];
            path_flow = min(path_flow,edges[u][v]);
        }
        for (v = t;v != s;v = parent[v]) {
            u = parent[v];
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
    
    int max_pig=0;
    cin >> m >> n;
    for (int i=1;i<=m;++i) cin >> edges[0][i];//把0号节点视作源，从源到某个点代表猪圈的猪数
    //接下来输入n个顾客，分别用n个节点来表征他们。汇用第1102位表示。
    int LastCustomerOfFarm[MAXM];
    memset(LastCustomerOfFarm,-1,sizeof(LastCustomerOfFarm));

    int a;
    for (int i=0;i<n;++i) {//第i个顾客
        cin >> a;
        for (int j=0;j<a;++j) {
            int s;
            cin >> s;
            if (LastCustomerOfFarm[s] == -1) {
                LastCustomerOfFarm[s] = 1001+i;
                edges[s][1001+i] = INT_MAX;
            }
            else {
                edges[LastCustomerOfFarm[s]][1001+i] = INT_MAX;
                LastCustomerOfFarm[s] = 1001+i;
            }
        }
        int need;
        cin >> need;
        edges[1001+i][1102] = need;
    }
    cout << EK();
    return 0;
}
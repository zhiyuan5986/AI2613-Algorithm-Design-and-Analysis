#include <iostream>
#include <queue>
#include <string.h>
#include <limits.h>
using namespace std;

const int MAXN = 33;
const int MAXM = 33;
const int s = 0;
const int t = 1025;
int edges[MAXN*MAXM][MAXN*MAXM];
bool broken[MAXN][MAXM];

int parent[MAXN*MAXM]; //用于指代节点的访问顺序
bool visited[MAXN*MAXM];

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

        for (int v=s;v<=t;++v) {
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
        int path_flow =INT_MAX;
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
//0存储源，1-512存储黑，513-1024存储白，1025存储汇。
void construct(int n, int m)
{
    memset(edges,0,sizeof(edges));
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            if ((i+j)%2 == 0 && !broken[i][j]) {//黑
                if (j+1 <= m && !broken[i][j+1])
                    edges[((i-1)*m+j+1)/2][512+((i-1)*m+j+1)/2+!(i%2)] = INT_MAX; //黑与右边的白，注意此处!(i%2)很重要！！！
                if (i+1 <= n && !broken[i+1][j])
                    edges[((i-1)*m+j+1)/2][512+(i*m+j+1)/2] = INT_MAX; //黑与下边的白
                if (j > 1 && !broken[i][j-1]) 
                    edges[((i-1)*m+j+1)/2][512+((i-1)*m+j-1)/2+!(i%2)] = INT_MAX;//黑与左边的白，注意此处!(i%2)很重要！！！
                if (i > 1 && !broken[i-1][j]) 
                    edges[((i-1)*m+j+1)/2][512+((i-2)*m+j+1)/2] = INT_MAX;//黑与上边的白
            }
        }
    }

    for (int i=1;i<=(m*n)/2+(m*n)%2;++i) edges[s][i] = 1;
    for (int j=513;j<=512+(m*n)/2;++j) edges[j][t] = 1;
}
int main()
{
    int T, n, m, k;
    
    cin >> T;
    for (int i=0;i<T;++i) {//共T组数据
        cin >> n >> m >> k;
        memset(broken,0,sizeof(broken));
        int x, y, num_of_black=0, num_of_white=0;
        for (int j=0;j<k;++j) {
            cin >> x >> y;
            if ((x+y)%2) ++num_of_white;//白格破损数
            else ++num_of_black;//黑格破损数
            broken[x][y] = 1;
        }
        if ((n*m)%2+num_of_black != num_of_white) {cout << "NO" << endl;continue;}//这句话删掉之后，多对了一个
        construct(n,m);
        int max_flow = EK();
        if (m*n-num_of_black-num_of_white != 2*max_flow) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}
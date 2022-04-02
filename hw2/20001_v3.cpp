//这是可以通过的代码版本 
//之前过不了是因为没有考虑到有时候某些点虽然自身和除强联通分量里其他点之外的点有出度，但是强联通分量和外界有出度
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
const int MAXN = 1e5+1;
const int MAXE = 5*1e5+1;
struct edge {
    int end;
};
vector <edge> edges[MAXE];
vector <edge> edges_r[MAXE];
vector<int> order;
vector<int> scc_count;
int BelongToWhichSCC[MAXN];


void dfs(int start, bool visited[], int n)
{
    visited[start] = 1;
    for (int j=0;j<edges[start].size();++j) {
        if (visited[edges[start][j].end] == false) dfs(edges[start][j].end,visited,n);
    }
    order.push_back(start);
}
void dfs_rw(int s, int n) 
{
    bool *visited = new bool[n+1];
    for (int i=0;i<=n;++i) visited[i] = 0;
    for (int i=1;i<=n;++i) {
        if (visited[i] == true) continue;
        dfs(i,visited,n);
    }
    delete [] visited;
}

void dfs_reverse(int start, bool visited[], int n, int SCC, int &count_tmp)
{
    visited[start] = 1;
    ++count_tmp;
    BelongToWhichSCC[start]=SCC;
    // if (!flag) for (int i=0;i<edges_r[start].size();++i) 
    for (int j=0;j<edges_r[start].size();++j) {
        if (visited[edges_r[start][j].end] == false) dfs_reverse(edges_r[start][j].end,visited,n,SCC, count_tmp);
    }
}
int dfs_rw_reverse(int n)
{
    int count=0;
    int SCC=0;
    scc_count.push_back(0);
    int start;
    bool *visited = new bool[n+1];
    for (int i=0;i<=n;++i) visited[i] = 0;
    while(!order.empty()) {
        int count_tmp = 0;
        // int flag = 0;
        start = order.back();
        order.pop_back();
        if (visited[start] == true) continue;
        ++SCC;
        dfs_reverse(start,visited,n,SCC, count_tmp);
        scc_count.push_back(count_tmp);
    }
    delete [] visited;
    return SCC;
}

int main()
{
    memset(BelongToWhichSCC,0,MAXN);
    int n, m, start, end;
    cin >> n >> m;
    for (int i=0;i<m;++i) {
        cin >> start >> end;
        edges[start].push_back({end});
        edges_r[end].push_back({start});
    }
    dfs_rw(1,n);
    int SCC=dfs_rw_reverse(n);
    // for (int i=1;i<n+1;++i) cout << BelongToWhichSCC[i] << ' ';
    // cout << endl;
    int count = 0;
    bool *counted = new bool[SCC+1];
    for (int i=0;i<=SCC;++i) counted[i] = 0;
    for (int i=1;i<=n;++i) {
        for (int j=0;j<edges[i].size();++j) {
            if (!counted[BelongToWhichSCC[i]] && BelongToWhichSCC[i] != BelongToWhichSCC[edges[i][j].end]) {count+=scc_count[BelongToWhichSCC[i]];counted[BelongToWhichSCC[i]]=1;break;} //ERROR! 这里这样写有可能会损失一些和它在同一个edges里面的。
        }
    }
    // for (int i=1;i<=n;++i) {
    //     for (int j=1;j<=n;++j) {
    //         if (BelongToWhichSCC[i] == BelongToWhichSCC[j] && ((BelongToWhichSCC[i]) || (BelongToWhichSCC[j]))) {BelongToWhichSCC[i] =1; BelongToWhichSCC[j] = 1;}
    //     }
    // }
    cout << count;
    return 0;
}
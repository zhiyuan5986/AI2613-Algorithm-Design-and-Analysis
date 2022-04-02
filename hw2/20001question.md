# 题目描述
我们来学习随机游走的基本知识。给定一个（可能有自环，但是没有重边的）有向图$G=(V,E)$，每个节点表示一个状态，每条有向边$(i,j)\in E$都有一个权值$p_{ij}>0$，表示状态转移的概率。如果$(i,j)\not\in E$，我们假设$p_{ij}=0$。这些值满足对于任何$i\in V$, $\sum_{j\in V}p_{ij}=1$。也就是说对于每一个$i\in V$，$\hat P_i=(p_{i1},p_{i2},\dots,p_{in})$构成一个分布。

一个随机游走是下面这样一个随机过程：初始的$X_0\in V$是给定的。对于每一个$t\ge 0$, 如果$X_t=i$，那么我们按照$\hat P_i$来决定$X_{t+1}$ ：$\Pr[X_{t+1}=j] = p_{ij}$. 按照这种方式，我们可以得到一个无穷的随机变量序列$X_0,X_1,\dots,X_t,\dots$ 这个序列被称为一个从$X_0$ 开始的随机游走。

我们说一个状态$i\in V$ 是“瞬时”的，当且仅当如果$X_0=i$，那么有非零的概率，从$X_0$ 开始的随机游走永远回不到$i$ 了，即$\Pr[\exists t>0, X_t=i]<1$ 。这个时候，我们也称$i$ 为“瞬态”。

在算法课上，我们知道一个有向图$G$ 可以被表示成一个由$G=(V,E)$ 中强连通分量构成的有向无环图$H=(V_H,E_H)$ 。换句话说，$V$ 可以被表示成一个划分$V_1,\dots,V_t$ ，满足对每一个$k\in [t]$，$V_k$在$G$ 中的诱导子图$G[V_k]$是强连通的。我们有$V_H = [t]$并且$(k,\ell)\in E_H$ 当且仅当$k\ne\ell$并且存在$i\in V_k, j\in V_{\ell}$ 使得$(i,j)\in E$。

我们在AI2613这门课上会证明下面这样一个结论：一个状态$i\in V$是“瞬态”当且仅当$i$所在的强联通分量在$H$ 中出度不为0。

我们的问题是，输入一个随机游走的有向图$G$ ，输出$G$ 有多少个瞬态。

# 输入格式
第一行包含两个正整数$n$ 和$m$ . 接下来共$m$ 行，第$i$ 行包含两个整数$s_i$，$t_i$, 表示有一条$s_i$到$t_i$的有向边，即$p_{s_i,t_i}>0$.

# 输出格式
第一行包含一个整数，表示瞬态的个数。
# 样例输入
```
8 11
2 6
2 7
7 3
4 8
4 5
4 1
2 4
7 6
2 3
1 4
1 5
```
# 样例输出
```
4
```
# 数据范围
对于30%的数据，$n \le 500$，$m \le 3000$。 对于100%的数据$n \le 10^{5}$，$m \le 5 \times 10^{5}$。

# 解决方案
```cpp
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
```
# 总结
本题就是找出强联通分量（SCC）并且统计哪些SCC具有不为0的出度。主要思想是首先对原图进行一次DFS得到拓扑排序，在对逆向的图按照拓扑排序顺序DFS得到SCC，在这个过程中统计结果。
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

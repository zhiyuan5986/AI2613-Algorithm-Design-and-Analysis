# 题目描述
给出一个有破损格子的正棋盘，和数量不限的1*2形状的棋子。你可以横着或竖着摆放棋子，请你判断棋盘（除破损个格子外）是否能被铺满。

# 输入格式
第一行包含一个正整数$T\le 3$,表示数据的组数。

对于每组数据：

第一行包含三个正整数$n,m,k$分别表示棋盘的行数，列数，破损格子的数量。

接下来$k$行每行两个正整数$x_i,y_i$，表示第$i$个破损的格子在第$x_i$行，第$y_i$列。

# 输出格式
对于每组数据输出一行，如果棋盘可以被覆盖，输出“YES”，否则输出“NO”。

# 样例输入
```
2
4 3 2
1 2
3 3
4 3 2
2 2
3 3
```
# 样例输出
```
YES
NO
```
# 数据范围
对于 100% 的数据，保证 $1\le n,m≤32$, $0\le k < n\times m$。

# 时空磁盘限制（运行时）
时间限制： 1000 ms

空间限制： 244 MiB
# 解决方案
```cpp
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
        //if ((n*m)%2+num_of_black != num_of_white) {cout << "NO" << endl;continue;}//这句话删掉之后，多对了一个
        construct(n,m);
        int max_flow = EK();
        if (m*n-num_of_black-num_of_white != 2*max_flow) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}
```
# 总结
这道题是最大流问题应用于二分匹配的一个案例，增加了broken来提高问题的复杂性。我的思路比较naive：
* 把棋盘划分为黑白两种格子，直接开了一个edges数组来存图，0存储源，1-512存储黑，513-1024存储白，1025存储汇。
* construct函数连接黑白(capacity=$\infty$)、源和黑(capacity=1)、白和汇(capacity=1)。
* 调用之前写好的模板计算最大流max_flow。
* 若最大流乘2刚好和未破损的棋子数相同，则说明可以完全覆盖，输出“YES”。否则输出“NO”。

construct的实现比较烧脑，需要考虑到各种情况，不能弄错。对于黑格左边和右边的白格，需要特别注意的是，在奇偶行有不同的表达式，因为这个问题，第一个测试集一直过不了，后面助教xjj好心告诉了我第一个数据集的内容，经过debug发现是这个问题。

![棋盘](hw5/1572. FulillChessboard/微信图片_20220515093013.jpg)


注意上图中，红色代表黑格编号，蓝色代表白格编号(实际应该再加上512)。
# 声明
题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

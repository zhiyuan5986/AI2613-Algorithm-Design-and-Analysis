# 题目描述
你有$m$个猪圈，每个猪圈中有若干头猪。 有$n$个顾客按顺序来买猪，每个顾客需要若干头猪。 每个顾客都有某几个猪圈的钥匙（只有顾客才拥有钥匙），只有某个猪圈打开后才能分配这个猪圈里的猪，且顾客离开后会把门关闭。
每次你可以决定卖给每个顾客哪些猪（不能多于顾客需要的数量），并且可以在一个顾客买完后，调整没有锁门的猪圈中猪数量，比如，把几个猪圈中的猪全部转到一个猪圈内，请问最后最多能卖掉几头猪。

# 输入格式
输入的第一行是两个整数$m$和$n$。 其中$m$是猪圈的数量,$n$是顾客的数量。
输入的第二行有$m$个整数，表示每个猪圈里分别有多少只猪。
接下来$n$行，每行对应一个顾客的信息，格式如下。
第一个整数$a$表示该顾客拥有多少把钥匙。
接下来$a$个整数表示这些钥匙分别对应哪一些猪圈。
最后一个整数$b$表示该顾客想买多少头猪。

# 输出格式
输出一个整数表示最多可以卖出多少头猪。

# 样例输入
```
3 3
3 1 10
2 1 2 2
2 1 3 3
1 2 6
```
# 样例输出
```
7
```
# 数据范围
对于 100%的数据，保证 $1\leq m \leq 1000, 1 \leq n \leq 100$，每个猪圈里猪的数量不超过$1000$。

# 时空磁盘限制（运行时）
时间限制： 1000 ms

空间限制： 62 MiB
# 解决方案
```cpp
//思路是：把每一个顾客当作无限运力的中转站使用
//every farm connect to its first customer. 
//For latter customer to a farm, add an edge from previous customer to him with capacity INT_MAX
//(I use the array named LastCustomerOfFarm to record the last customer)
//
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
```
# 总结
这道题很巧妙地应用了最大流进行建模。首先，每个猪圈可以看作是从源处收到一定流量的节点，把顾客看作是通向汇的节点。最关键的是，如何将顾客和猪圈连接起来。由题意，每位顾客都拥有分配猪圈的权利，这就可以抽象为，每位顾客可以自己重建一个猪圈，这个猪圈能够向汇点输出，也能够为后续的顾客提供一个广阔的猪圈以供选择（最理想的情况是，最终所有猪圈都合为一体）。
以样例输入为例，构造出如图所示的网络：![样例输入构造的网络](https://img-blog.csdnimg.cn/d422b5067d2a4b51a1fef1f483deee96.png#pic_center)
可以看到，虽然customer3只能接入猪圈2，但是它实际上是可以通过customer1的操作，拿到原本属于猪圈1的猪。但是可以看到，customer3无法拿到属于猪圈3的猪，因为customer2尽管和猪圈1相连，但是没有和猪圈2相连，所以customer2无法将猪圈3的猪运到猪圈2（这其实也是一个时间先后的问题，customer1的操作在customer2之前）。
BTW，我的解法时间较长，可能还存在更优的算法，之后再和同学交流一下。
# 声明
题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

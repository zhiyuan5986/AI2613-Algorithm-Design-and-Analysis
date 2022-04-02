# 题目描述
author: Konpaku 原OJ链接：https://acm.sjtu.edu.cn/OnlineJudge-old/problem/4180

# Description
有一张 $n$ 个点的混合图，编号从 $1$ 至 $n$，图中有 $p_1$条有向边和 $p_2$  条无向边。
你需要为每条无向边定向，使得图中不存在环。若有多组定向方案，输出任意一组即可。

# Input Format
第一行三个整数 $n$, $p_1$ , $p_2$  意义如上。
接下来 $p_1$ 行，每行两个整数 $a$ , $b$ 表示一条由 $a$ 到 $b$ 的有向边。
接下来 $p_2$  行，每行两个整数 $a$ , $b$ 表示一条连接 $a$ , $b$ 的无向边。

# Output Format
输出包括 $p_2$ 行，每行两个整数。
第 $i$ 行的两个整数 $a_i$ , $b_i$ 表示对于第 ii 条无向边，其最终方向由 $a_i$ 指向 $b_i$。
请确保输出的有向边与输入的无向边相对应。
# Sample Input
```
4 2 3
1 2
4 3
1 3
4 2
3 2
```
# Sample Output
```
1 3
4 2
2 3
```
# Data Range
对于20%的数据：$0<n<=10, 0<p1<=10, 0<p2<=5$
对于30%的数据：$0<n<=10, 0<p1<=30, 0<p2<=20$
对于100%的数据：$0<n, p1, p2<=1000000<n,p1,p2<=100000$
数据保证至少存在一种可行解.

# 解决方案
 ```cpp
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
```
# 总结
本题需要对无向边重定向，且保证不成环。不成环可以用拓扑排序的序号来表征（由序号小的指向序号大的一定不会成环）。
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

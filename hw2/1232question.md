# 题目描述
给定一个大小为$n$的有向图$G$，判断其是否有负环。

# 输入格式
第一行两个整数$n$和$m$分别表示图$G$的点数和边数。
接下来$m$行，每行三个整数$x，y$和$z$，表示$x$到$y$有一条权值为$z$的边。

# 输出格式
如果有负环则输出"Yes"，否则输出"No"。（不包括双引号）

# 样例输入
```
    4 4
    2 1 4
    2 3 2
    3 4 2
    4 2 -8
 ```
# 样例输出
```
Yes
```
# 数据范围
对于100%的数据，$n \le 3000, m \le 5000$。
对于所有的边，$-10^4 \le z \le 10^4$。

# 解决方案
```cpp
//注意有重边，用known可以避免重边现象。

#include <iostream>
#include <string.h>
using namespace std;
 
const int MAXN = 3001;
const int MAXE = 5001;
 
int map[MAXN][MAXN];
bool known[MAXN][MAXN];
int dis[MAXN];
 
struct e
{
	int s;
	int e;
}e[MAXE];
bool bellman_ford(int start, int end, int n, int m)
{
	memset(dis,10002,sizeof(dis)); //初始化无穷大
	dis[start] = 0;
	for(int i=0; i<n-1; i++) //n-1次松弛
	{
        bool flag = false;
		for(int j=0; j<m; j++)
		{
			if(dis[e[j].s] + map[e[j].s][e[j].e] < dis[e[j].e])
			{
				dis[e[j].e] = dis[e[j].s] + map[e[j].s][e[j].e];
                flag = true;
			}
		}
        if (!flag) break;
	}
	//判断是否能继续松弛
	for(int i=0; i<m; i++)
	{
		if(dis[e[i].s] + map[e[i].s][e[i].e] < dis[e[i].e])
		{
            return true;
		}
	}
    return false;
}


int main()
{
	memset(known,0,MAXN*MAXN);
    int n, m;
    cin >> n >> m; //node e
    int start, end, weight;
    for (int i=0;i<m;++i) {
        cin >> start >> end >> weight;
		if (!known[start][end] || known[start][end] && map[start][end] > weight) {
			known[start][end]=1;
        	map[start][end]=weight;
        	e[i].s=start;
        	e[i].e=end;
		}
    } 
    bool flag = bellman_ford(1,n,n,m);
    if (flag) cout << "Yes";
    else cout << "No";
    return 0;
}
```
# 总结
本题用Bellman-Ford算法解决，并且需注意有重边，需要检测一遍。（PS：应该可以直接用邻接矩阵来实现本题。）
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

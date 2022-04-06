# 题目描述
你——伟大的赏金猎人，经过了史诗般的战斗后，夺取了属于你的战利品——一个重量为 $w$ 克的金块。

你的 $n$ 个扈从功不可没。根据每个人自己汇报的功劳大小，你决定给第 $i$ 个扈从 $a_i$ 重量的金块，其中 $\sum_i a_i = w$。

在以枪火为筹码谈生意的的比尔吉沃特，没有人做慈善。如果你请比港商行老板帮你分金块，你需要足额支付手续费。如果一个金块在切割前重量为 $x$，你需要为这次分割付出 $x \times p$ 枚的银蛇币，之后金块可以以任意比例被切为两块。

你需要在满足所有扈从的要求的情况下，支付尽可能少的银蛇币。由于银蛇币不可分割，你只需要在最后一次性支付所有切割代价的和向上取整枚银蛇币即可。

# 输入格式
请从 stdin 读入。

第一行三个整数 $n, w, p,(1 \leq n \leq 10 ^ 5, 0 \leq w \leq 10 ^ 7, 0 < p < 100)$，分别表示人数、金块重量、与手续费百分比。

第二行 $n$ 个空格隔开的正整数，第 $i$ 个为第 $i$ 个人需求的重量 $a_i,(a_i \geq 1, \sum_i a_i = w)$。

对于 $30$ 分的数据，$n \leq 15$。

# 输出格式
请输出到 stdout 中。

输出一行一个整数，表示答案。

# 样例输入
```
1 1 1
1
```
```
3 3 50
1 1 1
```
```
3 7 50
4 2 1
```
# 样例输出
```
0
```
```
2
```
```
5
```
# 数据范围
# 备注
三组样例精确答案分别是 $0, 2.5, 5$。

# 限制
Time Limit: 1s 
Memory Limit: 128MB
# 解决方案
```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;
//之前过不了，经过助教老师的提醒，是ceil函数的问题。这个函数返回float，在vscode里面打印出来是整型数，但是OJ平台过不了，加一个int即可
//这题之前想复杂了，研究了好久的背包问题，后来好哥哥提醒可以用哈夫曼树。本题用priority_queue实现了一棵简化版的哈夫曼树。
int main()
{
    int n, w, p, now; //n代表有几个人，w是金块重量。
    cin >> n >> w >> p;
    int *a = new int[n];
    long long int sum=0;
    priority_queue<long long int, vector<long long int>, greater<long long int> > q;
    for (int i=0;i<n;++i) {cin >> now; q.push(now);}
    int num1, num2;
    for (int i=0;i<n-1;++i) {
        num1 = q.top();
        q.pop();
        num2  = q.top();
        q.pop();
        sum += num1+num2;
        q.push(num1+num2);
        // cout << num1+num2 << endl;
    }
    // hfTree tree(a,n);
    // cout << tree.sum << endl;
    // cout << sum << endl;
    cout << int(ceil(sum*p / 100.0));
    // cout << ceil(result*p / 100.0);
    return 0;
}
```
# 总结
之前过不了，经过助教老师的提醒，是ceil函数的问题。这个函数返回float，在vscode里面打印出来是整型数，但是OJ平台过不了，加一个int即可。这题之前想复杂了，研究了好久的背包问题，后来好哥哥提醒可以用哈夫曼树。本题用priority_queue实现了一棵简化版的哈夫曼树。
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

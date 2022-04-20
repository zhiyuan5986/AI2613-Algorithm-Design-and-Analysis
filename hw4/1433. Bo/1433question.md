# 题目描述
博先生掌握了股市内幕消息，因此他想闷声大发财。

对于特定的一只股票，博先生知道了他  $n$ 天内的价格走势，并想借此牟利。但是，如果一次交易太多的被发现的话，人生就要结束了罢。因此，他每天只能做以下三种操作之一：

以当天的价格买入一股。
以当天的价格卖出一股。博先生不能在持有 $0$ 股时卖出。
或者，什么也不做。
博先生现在持有 $0$ 股股票，他希望在第 $n$ 天结束时手里持有 00 股股票。请帮博先生计算一下，他最多能赚多少钱？

# Input
请从 stdin 读入。

第一行一个正整数 $n (1 \leq n \leq 10 ^ 5)$ 表示总天数。

第二行 $n$ 个空格隔开的正整数，第 $i$ 个为第 $i$ 天的价格 $a_i (1 \leq a_i \leq 10^6)$。

对于 $20$ 分的数据，$n \leq 10$。

另有 $20$ 分的数据，$n \leq 500$。

# Output
请输出到 stdout 中。

对于每组数据输出一行一个整数，表示答案。

# Sample Input
```
5
5 4 3 2 1
```
```
9
10 5 4 7 9 12 6 2 10
```
```
20
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4
```
# Sample Output
```
0
```
```
20
```
```
41
```
# Note
对于第一组数据，由于这只股票实在太烂了，因此最优方案是：快跑。

对于第二组数据，最优的交易是：$-5 -4+9+12-2+10 = 20$。

# Constraints
Time Limit: 1s
Memory Limit: 128MB
# 解决方案
```cpp
#include <iostream>
#include <queue>
using namespace std;
//从leetcode上面得到了一些启发https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/solution/mai-mai-gu-piao-de-zui-jia-shi-ji-ii-by-leetcode-s/
//这题有点不同的是，可以同时持有好几股，那么贪心如何实现呢？答案是：用一个优先级队列(最小堆)存储价格，
//输入一个价格后，若比队首大，就让这个价格减去队首，再把该价格入队。
int main()
{
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int> > q;
    long long int profit = 0;
    for (int i=0;i<n;++i) {
        int price;
        cin >> price;
        if (!q.empty())
        {
            int head = q.top();
            if (price > head) {
                profit += price-head;
                q.pop();
                q.push(price);
                //这里的push一定要加，其作用是替代原有的数占位，一旦后续有更大的数进来，可能把这个数踢掉，相当于这个数是一个中介。
                //例如：1,3,4,5,那么最大的收益是(4-1)+(5-3)=5，执行程序，会发现3踢掉了1，输入4又踢掉3，输入5时还是应该踢掉3，这就要求3要入队两次
            }
        }
        q.push(price);
    }
    cout << profit;
    return 0;
}
```
# 总结
本题的想法还是很妙的，参考了leetcode上面的题。[link](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/solution/mai-mai-gu-piao-de-zui-jia-shi-ji-ii-by-leetcode-s/)
本题的区别在于可以同时持有好多股票，那么一种贪心的思路是：若输入的price比队首大，先用大减小，再把大的入队当作小的替身。而每个大又是固定要入队一次的，所以千万要注意可能有两次push！！
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

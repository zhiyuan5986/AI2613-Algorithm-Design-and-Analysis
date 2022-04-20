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

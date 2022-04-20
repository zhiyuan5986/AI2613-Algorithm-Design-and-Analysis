# 题目描述
author: sakiko 原OJ链接：[https://acm.sjtu.edu.cn/OnlineJudge-old/problem/4387](https://acm.sjtu.edu.cn/OnlineJudge-old/problem/4387)

# Description
给定一个长度为$n$的整数序列，求出它的最长上升子序列。
子序列不一定要在原序列中连续，但相对顺序要一致，如$[1, 2]$是$[1, 3, 2]$的一个子序列，而$[2, 3]$不是。

# Input Format
第一行是一个整数$n$,表示序列的长度。
接下来一行$n$个整数，表示该序列。

# Output Format
请输出两行答案。
第一行一个整数表示最长上升子序列的长度。
第二行请输出字典序最小的最长上升子序列。

# Sample Input 1
```
4
1 2 3 4
```
# Sample Output 1
```
4
1 2 3 4
```
# Sample Input 2
```
6
4 5 6 1 2 3
```
# Sample Output 2
```
3
1 2 3
```
# Data Range
对于$30\%$的数据，$n \le 100$。
对于$100\%$的数据，$n \le 10000$，序列元素$\le 10000$。
# 解决方案
```cpp
#include <iostream>
#include <vector>
//这一版是可以过的
//参考了https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/dong-tai-gui-hua-er-fen-cha-zhao-tan-xin-suan-fa-p/
using namespace std;
const int MAXN = 10001;

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    vector<int> dp(n,1);//dp[i]=k 表示以arr[i]结尾的最长递增子序列长度
    vector<int> tail(n+1,0);  //tail[k]=i  表示长度为k的递增子序列的末尾最小数为i
    tail[1]=arr[0];
    int _max=1;
    int index=0;
    for(int i=1;i<n;i++)
    {
        int val=arr[i];
        int l=1;
        int r=_max;
        while(l<=r)  //二分查找第一个比val大的数
        {
            int mid=(l+r)>>1;
            if(tail[mid]<val)
                l=mid+1;
            else
                r=mid-1;
        }
        //tail[l]是第一个比val大的数
        tail[l]=val;
        dp[i]=l;//以i结尾的数 最长的递增子序列长度为l
        if(l>=_max)  //后来的arr[]总是字典序更小字典序更小
        {
            _max=l;
            index=i;
        }
    }
    vector<int> ans(_max);
    cout << _max << endl;
    for(int i=index;i>=0;i--)
    {
        if(dp[i]==_max)
        {
            ans[--_max]=arr[i];
          
        }
        
    }
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<" ";
    
}
```
# 总结
本题其实是leetcode上面的原题[https://leetcode-cn.com/problems/longest-increasing-subsequence/](https://leetcode-cn.com/problems/longest-increasing-subsequence/)
实际实现过程中，参考了大佬的解法[https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/dong-tai-gui-hua-er-fen-cha-zhao-tan-xin-suan-fa-p/](https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/dong-tai-gui-hua-er-fen-cha-zhao-tan-xin-suan-fa-p/)
在参考了这个解法后我写了贪心+二分的代码来实现本题
```cpp
#include <iostream>
#include <vector>
//这一版是可以过的
//参考了https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/dong-tai-gui-hua-er-fen-cha-zhao-tan-xin-suan-fa-p/
using namespace std;
const int MAXN = 10001;

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    vector<int> dp(n,1);//dp[i]=k 表示以arr[i]结尾的最长递增子序列长度
    vector<int> tail(n+1,0);  //tail[k]=i  表示长度为k的递增子序列的末尾最小数为i
    tail[1]=arr[0];
    int _max=1;
    int index=0;
    for(int i=1;i<n;i++)
    {
        int val=arr[i];
        int l=1;
        int r=_max;
        while(l<=r)  //二分查找第一个比val大的数
        {
            int mid=(l+r)>>1;
            if(tail[mid]<val)
                l=mid+1;
            else
                r=mid-1;
        }
        //tail[l]是第一个比val大的数
        tail[l]=val;
        dp[i]=l;//以i结尾的数 最长的递增子序列长度为l
        if(l>=_max)  //后来的arr[]总是字典序更小字典序更小
        {
            _max=l;
            index=i;
        }
    }
    vector<int> ans(_max);
    cout << _max << endl;
    for(int i=index;i>=0;i--)
    {
        if(dp[i]==_max)
        {
            ans[--_max]=arr[i];
          
        }
        
    }
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<" ";
    
}
```
之前我有写过一版动态规划的代码，但是只能过十个样例，一个简略的思路是：$LIS[i]$表示前$i$个点能够得到的最长子序列长度，对于数组中每个元素$a[i]$, 对于$k=1:n-1$,遍历$a[k]$, 在过程中，如果发现一个更小的数，即$a[i]>a[k]$,且$LIS[i] < LIS[k]+1$, 那么直接把$LIS[i]$置为$LIS[k]+1$，且$pre[a[i]]=a[k]$。另一种情况，如果$a[i]>a[k]$且$LIS[i] = LIS[k]+1$，比较$a[k]$和$a[i]$目前的最小字典序的大小$j$，如果$a[k]$的字典序比$j$小，则更新j和$pre[a[k]]$。代码如下：
```cpp
#include <iostream>
#include <stack>
// #include <cassert>
using namespace std;
const int MAXN = 10001;
int pre[MAXN];
//按字典序很好实现，只需要在选择最长串时同时考虑最后一位的数字大小即可。

//修改自v5
int main()
{
    int n;
    cin >> n;
    int *a = new int[n+1];
    // int *prev = new int[n+1];
    int *LIS = new int[n+1];
    for (int i=1;i<=n;++i) cin >> a[i];
    for (int i=0;i<=n;++i) {LIS[i] = 0;pre[i] = -1;}
    int maxi=1,j,tail = a[1];//maxi,tail用作标记所有路径中字典序最小的那一条路径，j用作每一个a[i]的字典序最小值
    LIS[1] = 1;
    bool flag = false;
    for (int i=2;i<=n;++i) {
        flag = false;
        j = n+1;
        for (int k=1;k<i;++k) {
            if (a[i] > a[k] && LIS[i] == LIS[k]+1) {
                if (a[k] < j) {//比上一个字典序小
                    pre[a[i]] = a[k];
                    j = a[k];
                }
                flag = true;
            } 
            if (a[i] > a[k] && LIS[i] < LIS[k]+1) {
                LIS[i] = LIS[k]+1;
                pre[a[i]] = a[k];
                flag = true;
                j = a[k];
                if (LIS[i] == maxi && tail > a[i] || LIS[i] > maxi) {
                    maxi = LIS[i];
                    tail = a[i];
                }
            }

        }
        if (!flag) {//若没能有一个前向
            LIS[i] = 1;
            if (maxi == 1 && tail > a[i]) tail = a[i];
        }
        
    }
    // stack<int> s;
    // cout << maxi<< endl;
    // for (int i=0;i<maxi;++i) {
    //     s.push(tail);
    //     tail = prev[tail];
    // }
    // for (int i=0;i<maxi;++i) {
    //     cout << s.top() << ' ';
    //     s.pop();
    // }
    cout << maxi << endl;
    int *output = new int[maxi+1];
    for (int i=maxi;i>0;i--)
    {
        output[i]=tail;
        tail=pre[tail];
    }
    for (int i=1;i<=maxi;i++)
    {
        cout << output[i] << ' ';
    }
    // cout << endl;
    // for (int i=1;i<=n;++i) cout << pre[i] << ' ';
    return 0; 
}
```
这份代码最大的问题就是，$pre$数组用的是元素来存，这里应该用下标，否则有反例$3,4,5,1,4$。还有就是$LIS$的值相等时，应该让$a[k] <= a[pre[i]]$和$a[tail] >= a[i]$这两处要取等。感谢助教学姐指出错误。
```cpp
#include <iostream>
#include <stack>
// #include <cassert>
using namespace std;
// const int MAXN = 10001;
// int pre[MAXN];
//按字典序很好实现，只需要在选择最长串时同时考虑最后一位的数字大小即可。

//修改自v6
int main()
{
    int n;
    cin >> n;
    int *a = new int[n+1];
    // int *prev = new int[n+1];
    int *LIS = new int[n+1];
    int *pre = new int[n+1];
    for (int i=1;i<=n;++i) cin >> a[i];
    for (int i=0;i<=n;++i) {LIS[i] = 0;pre[i] = n+1;}
    int maxi=1,j,tail = 1;//maxi,tail用作标记所有路径中字典序最小的那一条路径，j用作每一个a[i]的字典序最小值
    LIS[1] = 1;
    bool flag = false;
    for (int i=2;i<=n;++i) {
        flag = false;
        // j = pre[a[i]];
        for (int k=1;k<i;++k) {
            if (a[i] > a[k] && LIS[i] == LIS[k]+1) {
                if (a[k] <= a[pre[i]]) {//比上一个字典序小，=不能漏
                    pre[i] = k;
                    // pre[a[i]] = a[k];
                }
                flag = true;
            } 
            if (a[i] > a[k] && LIS[i] < LIS[k]+1) {
                LIS[i] = LIS[k]+1;
                pre[i] = k;
                flag = true;
                // j = a[k];
                if (LIS[i] == maxi && a[tail] >= a[i] || LIS[i] > maxi) {
                    maxi = LIS[i];
                    tail = i;
                }
            }

        }
        if (!flag) {//若没能有一个前向
            LIS[i] = 1;
            if (maxi == 1 && a[tail] > a[i]) tail = i;
        }
        
    }
    // stack<int> s;
    // cout << maxi<< endl;
    // for (int i=0;i<maxi;++i) {
    //     s.push(tail);
    //     tail = prev[tail];
    // }
    // for (int i=0;i<maxi;++i) {
    //     cout << s.top() << ' ';
    //     s.pop();
    // }
    cout << maxi << endl;
    int *output = new int[maxi+1];
    for (int i=maxi;i>0;i--)
    {
        output[i]=a[tail];
        tail=pre[tail];
    }
    for (int i=1;i<=maxi;i++)
    {
        cout << output[i] << ' ';
    }
    // cout << endl;
    // for (int i=1;i<=n;++i) cout << pre[i] << ' ';
    return 0; 
}
```
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。


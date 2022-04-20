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
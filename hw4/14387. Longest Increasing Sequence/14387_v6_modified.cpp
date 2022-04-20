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
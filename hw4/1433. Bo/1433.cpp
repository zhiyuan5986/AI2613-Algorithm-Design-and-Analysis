#include <iostream>
#include <string.h>
#include <queue>
#include <cstdio>
// #include <cmath>
using namespace std;
const int MAXN = 3001;
long long int profit[2][MAXN];
int price[MAXN];
priority_queue<int> minimum[MAXN];
//先跑起来再说
int main()
{
    memset(profit,0,2*MAXN);
    int n, count=0, mini=1e6+1;
    cin >> n;
    for (int i=1;i<=n;++i) {
        cin >> price[i];
        count -= price[i];
        profit[1][i]=count;
        minimum[i].push(price[i]);
    }
    for (int i=0;i<=n;++i) cout << profit[0][i] << '\t';
    cout << endl;
    for (int i=0;i<=n;++i) cout << profit[1][i] << '\t';
    cout << endl;

    int flag;
    for (int i=0;i<n;++i) {
        for (int i=0;i<=n;++i) cout << profit[0][i] << '\t';
        cout << endl;
        for (int i=0;i<=n;++i) cout << profit[1][i] << '\t';
        cout << endl;
        
        flag = i%2;//确定本次操作针对profit哪一行，从第0行开始
        for (int j=0;j<n-i;++j) {
            mini = minimum[j+1].top();

            if (i == 0) {
                profit[flag][j] = profit[1-flag][j+1]+mini;
                minimum[j] = minimum[j+1];
                minimum[j].pop();
            }
            else {
                int a = profit[1-flag][j+1]+mini;
                int b = profit[flag][j+1]+price[i+1];
                if (a > b) {
                    profit[flag][j] = a;
                    minimum[j] = minimum[j+1];
                    minimum[j].pop();
                }
                else {
                    profit[flag][j] = b;
                    minimum[j] = minimum[j+1];
                }
            }
            
        } 
    }
    cout << profit[n][0];


    return 0;
}
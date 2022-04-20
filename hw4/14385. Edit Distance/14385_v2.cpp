#include <iostream>
#include <string>
using namespace std;
//本题需要注意的是，尽可能使用添加或删除。

const int MAXN=3001;
int F[MAXN][MAXN];
int min(int a, int b, int c)
{
    int mini = (a < b) ? a : b;
    return ((mini < c) ? mini : c);
}
int main()
{
    int m, n, x, y;
    cin >> x >> y;
    string a,b;
    cin >> a;
    cin >> b;
    // cout << a << endl;
    // cout << b << endl;
    m = a.size();
    n = b.size();
    // cout << m << endl << n << endl;
    //int mini = (m < n) ? m : n; 
    for (int i=0;i<=n;++i) F[0][i] = i*x;
    for (int i=1;i<=m;++i) {
        F[i][0] = i*x;
        for (int j=1;j<=n;++j) {
            F[i][j] = min(F[i-1][j-1]+y*(!(a[i-1] == b[j-1])),F[i-1][j]+x,F[i][j-1]+x);//这里错了，会用到已经修改过的值
        }
    }
    cout << F[m][n];
    return 0;
}
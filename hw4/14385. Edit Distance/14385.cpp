#include <iostream>
#include <string>
using namespace std;
//本题需要注意的是，尽可能使用添加或删除。
//这份代码之前报错是因为忘记删掉调试部分了
const int MAXN=3001;
int F[2][MAXN];//采用flag去节省空间，因为每次只需要两行的信息就够了
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
    int flag = 1;
    for (int i=1;i<=m;++i) {
        flag = i%2;
        F[flag][0] = i*x;
        for (int j=1;j<=n;++j) {
            F[flag][j] = min(F[1-flag][j-1]+y*(!(a[i-1] == b[j-1])),F[1-flag][j]+x,F[flag][j-1]+x);
        }
    }
    cout << F[flag][n];
    return 0;
}
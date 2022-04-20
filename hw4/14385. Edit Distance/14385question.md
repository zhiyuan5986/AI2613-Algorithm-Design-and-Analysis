# 题目描述
author: sakiko 原OJ链接：[https://acm.sjtu.edu.cn/OnlineJudge-old/problem/4385](https://acm.sjtu.edu.cn/OnlineJudge-old/problem/4385)

# Description
给定两个字符串，需要你求出他们的编辑距离。
这里我们假设添加或删除一个字符的代价为$x$,修改一个字符的代价为$y$，并有$y<2x$。

# Input Format
第一行两个整数$x$和$y$分别表示插入删除字符和修改字符的代价。
接下来两行，是我们需要求出编辑距离的两个字符串。

# Output Format
请输出这两个字符串的编辑距离。

# Sample Input 1
```
1 1
abc
abc
```
# Sample Output 1
```
0
```
# Sample Input 2
```
2 3
snowy
slow
```
# Sample Output 2
```
5
```
# Data Range
对于$30\%$的数据，字符串长度$\le 100$。
对于$100\%$的数据，字符串长度$\le 3000$。
$1 \le x, y \le 20$。 字符串均由小写字母组成。
# 解决方案1
```cpp
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
```
# 解决方案2
```cpp
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
```
# 总结
本题是课上讲到的编辑距离的变种，$y\le 2x$保证了不会有添加plus删除<修改的情况，第二份代码使用了一个flag来表征下标，能够节省挺多空间。
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

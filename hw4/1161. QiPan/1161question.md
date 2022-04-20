# 题目描述
给定一个大小为$m \times n$的棋盘,其中有一些格子是破损的。破损的格子不能摆放棋子，但是不影响棋子移动。请求出摆放马（数量不限）使得他们不会互相攻击的方案数。 这里马的攻击范围是日字形（参考国际象棋规则）。

# 输入格式
输入第一行三个整数$m,n,k$, $m$和$n$表示棋盘的大小，$k$表示破碎格子的个数。
接下来$k$行，每行两个整数表示破损格子的位置。

# 输出格式
输出一个整数，表示方案数。由于方案可能过多，请输出对$(10^9+7)$取模的值。

# 样例输入
```
3 3 1
1 1
```
# 样例输出
```
68
```
# 数据范围
对于 100%的数据，保证$1 \leq m \leq 200$，$1 \leq n \leq 6$。
# 解决方案
```cpp
#include <iostream> 
using namespace std; 
const int MOD = 1e9 + 7; 
int dp[222][65][65]; 
int broken[222]={0}; 
//dp[i][j][k]: i is the row we choose now, j is the state of the i'th row, k is the state of the (i-1)'th row 
//本题参考了rxygg的代码,我在充分理解了他的思路以后借鉴了他的写法,感谢!
//本题的主要思路是,用二进制来表示每一行的棋子分布,由于限制了1<=n<=6,这个方法不会溢出.
//
int main(int argc, char *argv[]) 
{ 
    int m, n, k; 
    scanf("%d %d %d", &m, &n, &k); 
    for (int i = 0; i < k; i++) 
    { 
        int x, y; 
        scanf("%d %d", &x, &y); 
        broken[x] += 1 << (y - 1); //用位来存储破损的棋子位置
    } 
    for (int i = 2; i <= m; i++) //遍历每一行
    { 
        for (int j = 0; j < (1 << n); j++) //j是当前行的排列组合方式,例如对于n=5,j可以是二进制的00000~11111,代表某一位有无棋子
            { 
                bool flag1=j & broken[i]; 
                if (flag1) 
                    { 
                        continue; 
                    } 
                for (int k = 0; k < (1 << n); k++) { //k是上一行的棋子分布
                    bool flag2=(k << 2) & j || (k >> 2) & j || k & broken[i - 1]; //上一行的马对我的影响
                    if (!flag2) { 
                        if (i == 2) { //没有再上一行的马影响
                            dp[2][j][k] = 1; 
                        } 
                        else { 
                            for (int p = 0; p < (1 << n); p++) { //p指代再上一行的棋子分布
                            bool flag3=(p << 1) & j || (p >> 1) & j || broken[i - 2] & p; //再上一行的马对我的影响
                                if (!flag3) { 
                                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][k][p]) % MOD; //对于第i行第j列的格子,用一个数组dp[i][i]去存上一行的各种情况下,这一行具有的种类数.
                                } 
                            } 
                        } 
                    } 
                } 
            } 
    } 
    int output = 0; 
    for (int i = 0; i < (1 << n); i++) { 
        for (int j = 0; j < (1 << n); j++) { 
            output = (output + dp[m][i][j]) % MOD; 
        } 
    } 
    printf("%d", output); 
    return 0;
} 
```
# 总结
本题是在rxygg的提示下得到的，这题非常巧妙地使用了位运算来表征各行的棋子分布情况，堪称位运算运用的经典。
# 声明
本文的题目版权属于TA、代码思路和代码均为rxygg的智慧结晶，仅作学习和分享，如有侵权，请联系删除。

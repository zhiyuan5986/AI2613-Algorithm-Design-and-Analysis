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
 
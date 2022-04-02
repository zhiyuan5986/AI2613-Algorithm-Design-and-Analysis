# 题目描述
给定 $n$ 个正整数，请找出其中的第 $k$ 小的数。

输入可能有重复数字，此时第$k$ 小的值定义为唯一的 $x$，满足 公式
$(| \lbrace y \mid y < x \rbrace | < k) \land (|\lbrace y \mid y \geq x\rbrace | \geq n - k)$,
也即将整个序列从小到大排序后的第 $k$ 个数。

# 输入格式
由于输入可能很大，本题采用奇怪的方式读入。你可以直接使用这段代码完成读入。

**请注意**，输入存储在 $a[1\dots n]$里，$0$ 不存内容。

其中，$1 \leq k \leq n \leq 4\times 10 ^ 7， 0 \leq a_i < 2^{31}$ 。

```cpp
const int N = 4e7 + 1;
int n, k;
int a[N];
void read_input_data() {
    int m;
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    unsigned int z = a[m];
    for (int i = m + 1; i <= n; i++) {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}
```
# 输出格式
请输出到 stdout 中。

输出一行，包含一个整数，为你的答案。

# 样例输入
```
3 3 3
2 3 3
5 4 1
1919810
```
# 样例输出
```
3
737192472
```
# 数据范围
Time Limit: 1s

Memory Limit: 512MB

# 备注
第二组样例实际上代表的数是 $[1919810, 132030712, 737192472, 1757748577, 642384501]$。

输入格式解释：

输入第一行，三个正整数。输入第二行 $m$ 个空格隔开的整数，表示 $a_1, \dots , a_m$。
$a_{m+1},\dots, a_n$使用 xorshift 随机生成器生成，
$$
\begin{aligned} 
a_{m + i} &= z_i \bmod 2 ^ {31}, 
\end{aligned}
$$
其中，
$$
\begin{aligned}
z_0 &= a_m \\
x_i &= z_{i - 1}\oplus (z_{i -1} \times 2 ^ {13}) (\bmod 2^{32}) \\
y_i &= x_i \oplus \left \lfloor \frac {x_i} {2 ^ {17}}\right \rfloor (\bmod 2 ^ {32}) \\
z_i &= y_{i - 1}\oplus (y_{i -1} \times 2 ^ {5}) (\bmod 2^{32}) 
\end{aligned}
$$

# 解决方案
```cpp
#include <iostream>
using namespace std;

const int N = 4e7 + 1;
int n, k;
int a[N];
void read_input_data() {
    int m;
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    unsigned int z = a[m];
    for (int i = m + 1; i <= n; i++) {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}
int median(int a[], int low, int high) 
{
    int mid = (low+high)/2;
    if (a[low] < a[mid] && a[mid] < a[high]) return mid;
    else if (a[low] >= a[mid] && a[high] >= a[low]) return low;
    else return high;
}

int divide(int a[], int low, int high)
{
    if (low >= high) return low;
    int index = median(a,low,high);
    int tmp = a[index];
    a[index] = a[low];
    a[low] = tmp;
    do {
        while (low < high && a[high] > tmp) --high;
        if (low < high) {a[low] = a[high];++low;}
        while (low < high && a[low] < tmp) ++low;
        if (low < high) {a[high] = a[low];--high;}
    } while (low != high);
    a[low] = tmp;
    return low;
}

int quickSort(int a[], int low, int high, int k) 
{
    int mid = divide(a,low,high);
    if (mid == k) return a[mid];
    else if (mid < k) return quickSort(a,mid+1,high, k);
    else return quickSort(a,low,mid-1, k);
}

int main()
{
    read_input_data();
    cout << quickSort(a,1,n,k) << endl;
    return 0;
}
```
# 总结
本题用了快排的思想，若mid恰好等于k，那么结果就得到了。需要注意pivot的选取，用median可以保证不被一些数据集坑到。
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

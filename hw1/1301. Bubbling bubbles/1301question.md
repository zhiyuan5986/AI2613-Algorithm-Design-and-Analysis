# 题目描述
给定一个长度为 $n$ 的排列，元素标号为 $1 \dots n$。

如果对这个排列进行冒泡排序，那么每个元素会被交换若干次。

请输出每个元素在进行冒泡排序时，参与了多少次交换。

我们将以以下代码为标准计算交换次数。
```cpp
void bubble_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        } // after i-th inner iteration, a[n - i] is correct
    }
}
```
# 输入格式
请从 stdin 读入。
输入第一行一个正整数 $n (1 \leq n \leq 10^6)$。
第二行包含 $n$ 个空格隔开整数表示排列，第 $i$ 个数为排列第 $i$ 位 $a_i (1 \leq a_i \leq n)$。输入保证 $n$ 个数互不相同。
# 输出格式
请输出到 stdout 中。
输出一行 $n$ 个由空格隔开的数，第 $i$ 个数表示 $i$ 被交换了多少次。
# 样例输入
```
4
1 2 3 4
```
```
4
4 3 2 1
```
```
3
2 3 1
```
# 样例输出
```
0 0 0 0
```
```
2 3 3 3
```
```
2 1 1
```
# 数据范围
Time Limit: 1s
Memory Limit: 512MB
# 解决方案
```cpp
#include <iostream>
using namespace std;
//用归并排序的思想，计算每个数的逆序对数量

void merge(int a[], int left, int mid, int right, int answer[])
{
    int *tmp = new int[right-left+1];
    int i = left, j = mid, k = 0;
    int tmp_count = 0;
    while (i < mid && j <= right)
        if (a[i] < a[j]) {answer[a[i]-1] += tmp_count;tmp[k++] = a[i++];}
        else {
            while (j <= right && a[j] < a[i]){++tmp_count;tmp[k++] = a[j++];}
            //for (int index=mid;index<j;++index) ++answer[a[index]-1];
            if (j > right) {answer[a[i]-1] += tmp_count;tmp[k++] = a[i++];}
        }
    //for (int index=mid;index<=right;++index) answer[a[index]-1] += mid-i;
    while (i < mid) {
        answer[a[i]-1] += tmp_count;
        tmp[k++] = a[i++];
    }
    while (j <= right) tmp[k++] = a[j++];
    for (i=0,k=left;k <= right;) a[k++] = tmp[i++]; 
}
void mergeSort(int a[], int left, int right, int answer[])
{
    if (left == right) return;
    int mid = (left+right)/2;
    mergeSort(a,left,mid,answer);
    mergeSort(a,mid+1,right,answer);
    merge(a,left,mid+1,right, answer);
    // if (n == 1) return a;
    // int *b = merge(a,n/2,count);
    // int *c = merge(a+n/2,n-n/2,count);
    // int i,j,k;
    // i = j = k = 0;
    // merge()
}
int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    int *b = new int[n];
    int *answer = new int[n];
    for (int i=0;i<n;++i) {cin >> a[i];answer[i] = 0;b[i] = a[i];}
    // int a[] = {4,3,7,1,2,8,6,5};
    mergeSort(a,0,n-1,answer);
    // cout << count << endl;
    for (int i=0;i<n;++i) answer[i] *= 2;
    for (int i=0;i<n;++i) answer[b[i]-1] += 1+i-b[i];
    for (int i=0;i<n;++i) cout << answer[i] << ' ';
    return 0;
}
```
# 总结
本题用了归并排序的思想，每次统计对应位上有多少个逆序对。注意我用到了某个位置处左大、左小、右大、右小的个数的一些关系。
# 声明
本人对代码保有版权，但是题目来自校内OJ平台，本人没有题目的版权。如有侵权，请联系本人删除。

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
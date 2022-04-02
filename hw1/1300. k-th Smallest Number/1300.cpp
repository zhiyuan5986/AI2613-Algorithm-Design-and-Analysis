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
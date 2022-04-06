#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;
//之前过不了，经过助教老师的提醒，是ceil函数的问题。这个函数返回float，在vscode里面打印出来是整型数，但是OJ平台过不了，加一个int即可
//这题之前想复杂了，研究了好久的背包问题，后来好哥哥提醒可以用哈夫曼树。本题用priority_queue实现了一棵简化版的哈夫曼树。
int main()
{
    int n, w, p, now; //n代表有几个人，w是金块重量。
    cin >> n >> w >> p;
    int *a = new int[n];
    long long int sum=0;
    priority_queue<long long int, vector<long long int>, greater<long long int> > q;
    for (int i=0;i<n;++i) {cin >> now; q.push(now);}
    int num1, num2;
    for (int i=0;i<n-1;++i) {
        num1 = q.top();
        q.pop();
        num2  = q.top();
        q.pop();
        sum += num1+num2;
        q.push(num1+num2);
        // cout << num1+num2 << endl;
    }
    // hfTree tree(a,n);
    // cout << tree.sum << endl;
    // cout << sum << endl;
    cout << int(ceil(sum*p / 100.0));
    // cout << ceil(result*p / 100.0);
    return 0;
}

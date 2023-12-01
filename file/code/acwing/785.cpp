#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 1e5 + 10;
int n;
int a[N];
void quick_sort(int q[], int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1;
    int mid = q[l + r >> 1];
    while (i < j)
    {
        do
            i++;
        while (q[i] < mid);
        do
            j--;
        while (q[j] > mid);
        if (i < j)
            swap(q[i], q[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}
int main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    quick_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}
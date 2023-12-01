#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 1e5 + 10;
int n;
int a[N], tmp[N];
void merge_sort(int a[], int l, int r)
{
    if (l >= r)
        return;
    int mid = l + r >> 1;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);
    int k = 0;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (a[i] >= a[j])
            tmp[k++] = a[j++];
        else
            tmp[k++] = a[i++];
    }
    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];
    for (int i = l, j = 0; i <= r; i++, j++)
        a[i] = tmp[j];
    return;
}
int main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    merge_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    return 0;
}
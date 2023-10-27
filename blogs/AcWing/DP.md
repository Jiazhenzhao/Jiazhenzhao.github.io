# 动态规划

[TOC]

## 背包问题

### 01背包

> ​ 每件物品只能用一次，找到在容量 V 内的最大价值

- [01背包问题](https://www.acwing.com/problem/content/2/)

​ 用DP分析法分析之后可以得到如下的结果，我们定义了`f[i][j]`，表示从前`i`个物品中选取容量为`j`的最佳选择情况，所以我们进行状态计算的时候可以分为选不选第`i`个物品，从而得到如下的计算公式
$$
f[i][j]=max(f[i-1][j],f[i-1][j-v[i]]+w[i])
$$
​ 这样我们可以得到二维朴素版的01背包求解

```c++
for (int i = 1; i <= n; i++)
 for (int j = 0; j <= m; j++)
 {
  f[i][j] = f[i - 1][j];
  if (j > v[i])
  f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
 }
```

​ 然后我们可以发现每次进行状态转移的时候我们只用到了`i-1`没有用到`i-2`等，同时`j`也只用到了`j`和`j-v[i]`因此我们可以考虑使用`滚动数组`来优化代码到一维，每次`i`代表了循环到第`i`轮拿去`0-m`的最优选择，因此每次遇到更优解的时候都会进行覆盖。但是因为我们每次都会用到上一轮的状态所以我们循环重量的时候应该从大大小，不然会污染结果

> ​ 加入我们需要更新`f[7]`用到了`f[6]`但是当我们从小到大开始遍历的时候`f[6]`一定已经被计算过一次，也就是此时`f[6]`是第`i`轮更新的结果，而不是第`i-1`轮

```c++
for (int i = 1; i <= n; i++)
 for (int j = m; j >= v[i]; j--)
  f[j] = max(f[j], f[j - v[i]] + w[i]);
```

### 完全背包

> ​ 每件物品能用无数次，找到在容量 V 内的最大价值

- [完全背包问题](acwing.com/problem/content/3/)

​ 完全背包进行状态划分的时候我们可以按照取得数量进行划分，然后出来了一个三维的朴素做法

> ​ 当我们枚举的带有数量的时候，我们每次需要和自身取一个最大值，因为不能确定哪一次的`f[i][j]`是最大值

```c++
for (int i = 1; i <= n; i++)
 for (int j = 0; j <= m; j++)
  for (int k = 0; k * v[i] <= j; k++)
   f[i][j] = max(f[i][j], f[i-1][j-k*v[i]]+k*w[i]);
```

​ 由下面的式子我们可以对三维做法进行一个优化
$$
f[i][j]=max(f[i-1][j],f[i-1][j-v[i]]+w[i],f[i-1][j-2*v[i]]+2*w[i])...
$$

$$
f[i][j-v[i]]=max(f[i-1],[j-v[i]],f[i-1][j-2*v[i]]+w[i])+...
$$

$$
所以我们得到：f[i][j]=max(f[i][j-v]+w,f[i-1][j])
$$

​ 二维做法

```c++
for (int i = 1; i <= n; i++)
 for (int j = 0; j <= m; j++)
 {
  f[i][j] = f[i - 1][j];
  if (j > v[i])
   f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
 }
```

​ 这个时候我们可以发现和01背包类似，我们可以继续优化到一维，但是这里需要使用从小到大枚举，因为我们用到的是第`i`轮的数值

```c++
 for(int i = 1 ; i<=n ;i++)
    for(int j = v[i] ; j<=m ;j++)
    {
            f[j] = max(f[j],f[j-v[i]]+w[i]);
    }
```

### 多重背包

> ​ 每一种物品都有各自的数量，找到在容量 V 内的最大价值

- [多重背包问题 I](https://www.acwing.com/problem/content/4/)

​ 多重背包每次枚举数量即可

```c++
for(int i = 1;i <= n;i++)
        for(int j = 0;j <=m;j++)
            for(int k= 0;k <= s[i] && j >= v[i] * k;k++)
                f[i][j] = max(f[i][j],f[i-1][j-v[i] * k] + w[i] * k);
```

- [多重背包问题 II](https://www.acwing.com/problem/content/5/)

​ 当数据量过大的时候，我们使用三重循环就会超过时间的限制，因此我们可以将`s`拆分为二进制数，然后利用二进制的组成来达到组成小于等于`s`的任意值，比如10可以分为1 2 4 3，我们在使用01背包的时候可以考虑是否选取，这样的话就可以构成了 0-10 之间的任意数，也就是相当于去了 s 的任意情况

```c++
int main(void)
{
 cin >> n >> m;
 int cnt = 0;
 for (int i = 1; i <= n; i++)
 {
  int a, b, s;
  cin >> a >> b >> s;
  int k = 1;
  while (k <= s)
  {
   cnt++;
   v[cnt] = b * k;
   w[cnt] = a * k;
   s -= k;
   k = k * 2;
  }
  if (s > 0)
  {
   cnt++;
   v[cnt] = b * s;
   w[cnt] = a * s;
  }
 }
 n = cnt;
 for (int i = 1; i <= n; i++)
  for (int j = m; j >= v[i]; j--)
   f[j] = max(f[j], f[j - v[i]] + w[i]);
 cout << f[m] << endl;
 return 0;
}
```

### 分组背包

> ​ 有许多不同类别的物品，每一种类别中只能选择一个物品

- [分组背包问题](https://www.acwing.com/problem/content/description/9/)

​ 分组背包问题，我们需要枚举每一个组别中的物品，然后别的就和01背包类似，只需要分为选或不选两种情况即可

```c++
 for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
        {
            f[i][j]=f[i-1][j];  //不选
            for(int k=0;k<s[i];k++)
                if(j>=v[i][k])
                    f[i][j]=max(f[i][j],f[i-1][j-v[i][k]]+w[i][k]);  
        }
```

## 线性DP

- `Exp`

  - 线性DP处理的一般就是题目中存在线性关系或者近似线性关系的问题

  - 一般DP问题都是在最后进行操作

- [数字三角形](https://www.acwing.com/problem/content/900/)

> ​ `f[i][j]`代表从起点走到`i,j`点的距离的最大值
>
> ​ 状态计算的时候比较左上和右上下来的点即可

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N= 550,INF = 1e9;
int a[N][N],f[N][N];
int n,m;
int main(void)
{
    cin >> n;
    for(int i = 1;i <= n ; i ++)
        for(int j = 1 ; j <= i ; j ++)
            cin >> a[i][j];
    for (int i = 0; i <= n; i ++ )
        for (int j = 0; j <= i + 1; j ++ )
            f[i][j] = -INF;
    f[1][1]= a[1][1];
    for(int i = 2 ; i <= n ; i ++)
        for(int j = 1 ; j <= i ; j ++ )
            f[i][j] = max(f[i-1][j-1] + a[i][j],f[i-1][j] + a[i][j]);
    int res = -INF;
    for(int i = 1 ; i <= n ; i ++)
        res = max(res,f[n][i]);
        cout << res << endl;
    return 0;
}
```

- [最长上升子序列](https://www.acwing.com/problem/content/897/)

> ​ `f[i]`代表前`f[i]`中严格单调递增的数列的值
>
> ​ 每次只需要比较遍历新加入的 i 即可

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 1e5 + 10;
int n;
int a[N], f[N];
int main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (a[i] > a[j])
                f[i] = max(f[i], f[j] + 1);
        }
    }
    int res = 0;
    for (int i = 0; i <= n; i++)
        res = max(res, f[i]);
    cout << res << endl;
    return 0;
}
```

- [最长上升子序列 II](https://www.acwing.com/problem/content/898/)

> ​ 我们可以发现 每个`f[i]`都记录了一个最大值，但是有些值我们用不到，因此我们可以设置一个数组记录了满足递增子序列的长度不同的结尾最小的值，然后我们可以发现该数组一定是一个单调递增的数组，所以我们可以通过二分找到每个`i`应该插入的位置，进而求到了最长上升子序列的长度

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 1e5 + 10;
int n;
int a[N], q[N];
int main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int len = 0;
    q[0] = -2e9;
    for (int i = 0; i < n; i++)
    {
        int l = 0, r = len;
        while (l < r)
        {
            int mid = l + r + 1 >> 1;
            if (a[i] > q[mid])
                l = mid;
            else
                r = mid - 1;
        }
        len = max(len, r + 1);
        q[r + 1] = a[i];
    }
    cout << len << endl;
    return 0;
}
```

- [最长公共子序列](https://www.acwing.com/problem/content/899/)

> ​ `f[i][j]`代表了在A的前`i`个字符和B的前`j`个字符中的最长公共子序列
>
> ​ 我们只需要考虑 第`i`个和第`j`个字母是否选取，并且当都选取的时候处理相等或者不相等的情况

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 1010;
int n, m;
int f[N][N];
char a[N], b[N];
int main(void)
{
    cin >> n >> m;
    cin >> a + 1 >> b + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (a[i] == b[j])
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    cout << f[n][m] << endl;
    return 0;
}
```

- [最短编辑距离](https://www.acwing.com/problem/content/904/)

> ​ `f[i][j]`表示从`a[1-i]`变成`b[1-j]`的最小次数
>
> ​ 我们只需要考虑最后一位的操作即可，增加、删除或者是替换，然后去一个最小值即可

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 1010;
int n, m;
char a[N],b[N];
int f[N][N];
int main(void)
{
    cin >> n >> a + 1 >> m >> b + 1;
    for(int i = 1; i <= m ; i++) f[0][i] = i;
    for(int i = 1; i <= n ; i++) f[i][0] = i;
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1; j <= m ; j ++)
        {
            f[i][j] = min(f[i-1][j] + 1,f[i][j-1] + 1);
            if(a[i] == b[j]) f[i][j] = min(f[i][j],f[i-1][j-1]);
            else f[i][j] = min(f[i][j],f[i-1][j-1] + 1);
        }
    cout << f[n][m] << endl;    
    return 0;
}
```

- [编辑距离](https://www.acwing.com/problem/content/901/)

> ​ 解题思路就是利用上一题，然后暴力遍历即可

```c++
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e1 + 5, M = 1e3 + 10;

int n, m;
char str[M][N];
int dp[N][N];

int edit_distance(char a[], char b[])
{
    int la = strlen(a + 1), lb = strlen(b + 1);
    for (int i = 0; i <= lb; i++) {
        dp[0][i] = i;
    }
    for (int i = 0; i <= la; i++) {
        dp[i][0] = i;
    }
    for (int i = 1; i <= la; i++) {
        for (int j = 1; j <= lb; j++) {
            dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (a[i] != b[j]));
        }
    }
    return dp[la][lb];
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> (str[i] + 1);
    }

    while (m--) {
        int res = 0;
        char s[N];
        int limit;
        cin >> (s + 1) >> limit;
        for (int i = 0; i < n; i++) {
            if (edit_distance(str[i], s) <= limit) {
                res++;
            }
        }
        cout << res << endl;
    }
    return 0;
}
```

## 区间DP

> ​ 区间DP一般就是指区间的划分问题，枚举的一般是区间长度

> ​ `f[i][j]`代表了从`i`和`j`中选取的最小代价
>
> ​ 在选定的区间内进行状态的计算，最小代价就是合并区间的代价的最小取和加上整体的区间和

- [石子合并](https://www.acwing.com/problem/content/284/)

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 330;
int a[N], s[N];
int f[N][N];
int n;
int main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // 前缀和数组
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + a[i];
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            f[i][j] = 1e8;
            for (int k = i; k < j; k++)
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
        }
    }
    cout << f[1][n] << endl;
    return 0;
}
```

## 计数类DP

- [整数划分](https://www.acwing.com/problem/content/902/)

> ​ 我们可以当作完全背包问题，并且数字的可选数量为无穷
>
> ​ 表示总和为`i`，总个数为`j`的方案数：我们也可以根据区间的最小值进行划分，一种是含有`1`的情况`f[i-1][j-1]`，当不含有`1`的时候我们可以得到`f[i-j][j-1]`

```c++
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, mod = 1e9 + 7;

int n;
int f[N];

int main()
{
    cin >> n;

    f[0] = 1;
    for (int i = 1; i <= n; i ++ )
        for (int j = i; j <= n; j ++ )
            f[j] = (f[j] + f[j - i]) % mod;

    cout << f[n] << endl;

    return 0;
}
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, mod = 1e9 + 7;

int n;
int f[N][N];

int main()
{
    cin >> n;

    f[1][1] = 1;
    for (int i = 2; i <= n; i ++ )
        for (int j = 1; j <= i; j ++ )
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % mod;

    int res = 0;
    for (int i = 1; i <= n; i ++ ) res = (res + f[n][i]) % mod;

    cout << res << endl;

    return 0;
}
```

## 数位统计类DP

## 状态压缩DP

​ 状态压缩类DP，一般是指将状态用二进制表示，不然的话可能需要很大的数组来表示所有的状态，用了二进制表示后就可以很简便的记录下所有的状态，一般就是记录满足正确状态的情况。

- [蒙德里安的梦想](https://www.acwing.com/problem/content/293/)

> ​ `f[i][j]`表示从`i-1`列中伸出方块的数量，我们只枚举横着放置方块的情况，而且我们需要保证放置的状态和前一列的状态不能重新重复、中间的间隙必须书偶数不能为奇数，因为我们剩下的都必须是竖直放置

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int N = 12, M = 1 << 12;
int n, m;
long long f[N][M];
bool st[M];
vector<int> state[M];
int main(void)
{
    while (cin >> n >> m, n || m)
    {
        // 预处理所有状态 i 代表了从 0~2^n 之间所有的二进制数
        for (int i = 0; i < 1 << n; i++)
        {
            int cnt = 0;
            st[i] = true;
            for (int j = 0; j < n; j++)
            {
                if (i >> j & 1)
                {
                    if (cnt & 1)
                        st[i] = false;
                    cnt = 0; // break
                }
                else
                    cnt++;
            }
            if (cnt & 1)
                st[i] = false;
        }
        
        for (int i = 0; i < 1 << n; i++)
        {
            state[i].clear();
            for (int j = 0; j < 1 << n; j++)
                if ((j & i) == 0 && st[j | i])
                    state[i].push_back(j);
        }
        // 状态转移
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 1; i <= m; i++)
            for (int j = 0; j < 1 << n; j++)
                for (auto k : state[j])
                    f[i][j] += f[i - 1][k];
        cout << f[m][0] << endl;
    }
    return 0;
}
```

- [最短Hamilton路径](https://www.acwing.com/problem/content/93/)

> ​ `f[i][j]`表示用过了前`i`个点，并且当前是在`j`这个点的路径最小值
>
> ​ 由题意我们发现我们只需要考虑哪些点被用过，以及终点是哪里，所以我们可以用二进制表示每个点的使用情况，然后遍历所有的情况，我们需要保证当前状态包含`i`，且前一个`k`状态不含`i`

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 20, M = 1 << N;
int n;
int f[M][N];
int w[N][N];
int main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> w[i][j];
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;
    for (int i = 0; i < 1 << n; i++)
        for (int j = 0; j < n; j++)
            if (i >> j & 1)
                for (int k = 0; k < n; k++)
                    if (i >> k & 1)
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
    cout << f[(1 << n) - 1][n - 1] << endl;
    return 0;
}
```

## 树形DP

- [没有上司的舞会](https://www.acwing.com/problem/content/287/)

> ​ 树形DP我们用`f[u][0]`代表该节点是否参与，0不参与1参与，接着考虑参与的时候和不参与的时候子树的值

```c++
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 6010;

int n;
int h[N], e[N], ne[N], idx;
int happy[N];
int f[N][2];
bool has_fa[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    f[u][1] = happy[u];

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dfs(j);

        f[u][1] += f[j][0];
        f[u][0] += max(f[j][0], f[j][1]);
    }
}

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i ++ ) scanf("%d", &happy[i]);

    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, a);
        has_fa[a] = true;
    }

    int root = 1;
    while (has_fa[root]) root ++ ;

    dfs(root);

    printf("%d\n", max(f[root][0], f[root][1]));

    return 0;
}
```

## 记忆化搜索

​ 记忆化搜索时一种实现DP的方式，属于优化后的DFS，因为DFS会重复搜索很多地方，而DP会保留一次的结果

​ 记忆化搜索相当于多次剪枝儿的DFS

​ 动态规划相当于用数组记录下较多的状态，避免了重复的遍历与访问，***把计算过的子问题保存下来***

> 评论解释记忆化搜索和动态规划
>
> [acwing](https : // <www.acwing.com/solution/content/46450/>  ) [知乎](https: // zhuanlan.zhihu.com/p/438406757)
>
> ​ 记忆化搜索，本质还是 **动态规划**，只是实现方式采用了 **深度优先搜索** 的形式，但是它不像 **深度优先搜索**那样 **重复** 枚举所有情况，而是把已经计算的子问题保存下来，这样就和动态规划的思想不谋而合了

- [滑雪](https://www.acwing.com/problem/content/903/)

> ​ 记忆化搜索只是`dp`的一种实现方式，记忆化搜索可以实现然而普通递推不能实现的问题（或实现起来非常麻烦的问题）就用记忆化搜索， 比如这题；我们假设`f[i][j]`表示滑到坐标`(i,j)`所能滑到的最长长度。那么对于状态f[i][j]而言，它可以由`f[i-1][j],f[i][j-1],f[i+1][j],f[i][j+1]`四个状态推得，然而我们使用普通的递推（两个for）只能得到上、左两个方向的状态，右、下两个方向的状态却无从得知，因此使用递推就不能满足我们的要求，如果再补上两个for覆盖右、下状态，那么时间复杂度就变为了`N^4`，很明显会TLE
>
> ​ 其中`f[i][j]`记录的是从`[i,j]`出发路径的最大值

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 330;
int h[N][N];
int f[N][N];
int n,m;
int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};
int dp(int x,int y)
{
    int &v = f[x][y];
    if(v != -1) return v;
    v = 1;
    for(int i = 0;i<4;i++)
    {
        int a = x+dx[i],b = y+dy[i];
        if(x >= 1&&x<=n&&y>=1&&y<=m&&h[x][y] < h[a][b])
            v = max(v,dp(a,b)+1);
    }
    return v;
}
int main(void)
{
    cin >> n >> m;
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=m;j++)
            cin >> h[i][j];
    memset(f,-1,sizeof(f));
    int res = 0;
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=m;j++)
            res = max(res,dp(i,j));
    cout << res << endl;
    return 0;
}
```

> ​ 动态规划本质和DFS一样，相当于优化的DFS，利用数组记录下了已经操作过的子问题的状态

# 数据结构

[TOC]

- [模板](https://www.acwing.com/blog/content/404/)

## 链表

### 单链表

> ​	模板

```c++
// head存储链表头，e[]存储节点的值，ne[]存储节点的next指针，idx表示当前用到了哪个节点
int head, e[N], ne[N], idx;
// 初始化
void init()
{
    head = -1;
    idx = 0;
}

// 在链表头插入一个数a
void insert(int a)
{
    e[idx] = a, ne[idx] = head, head = idx ++ ;
}

// 将头结点删除，需要保证头结点存在
void remove()
{
    head = ne[head];
}
```

- [单链表](https://www.acwing.com/problem/content/828/)

> ​	这里的单链表都是头插法，idx 代表了当前使用到了哪个点，e[idx] 代表值，ne[idx] 代表下一个点。

```c++
#include <iostream>
using namespace std;
const int N = 1e5+10;
int head,e[N],ne[N],idx;
void insetrt_to_head(int x)
{
    e[idx] = x;
    ne[idx] = head;
    head = idx++;
}
void insert(int k,int x)
{
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx++;
}
void remove(int k)
{
    ne[k] = ne[ne[k]];
}
int main(void)
{
    int m;
    cin>>m;
    head = -1;
    idx = 0;
    while(m--)
    {
        int k,x;
        string op;
        cin>>op;
        if(op == "H")
        {
            cin>>x;
            insetrt_to_head(x);
        }
        else if (op == "I")
        {
            cin>> k >> x;
            insert(k-1,x);
        }
        else 
        {
            cin>>k;
            if(k == 0)
            {
                head = ne[head];
            }
            else remove(k-1);
        }
    }
    for(int i = head;i != -1;i = ne[i])
        cout<<e[i]<<" ";
    cout<<endl;
    return 0;
}
```

### 双链表

> ​	模板

```c++
// e[]表示节点的值，l[]表示节点的左指针，r[]表示节点的右指针，idx表示当前用到了哪个节点
int e[N], l[N], r[N], idx;
// 初始化
void init()
{
    //0是左端点，1是右端点
    r[0] = 1, l[1] = 0;
    idx = 2;
}
// 在节点a的右边插入一个数x
void insert(int a, int x)
{
    e[idx] = x;
    l[idx] = a, r[idx] = r[a];
    l[r[a]] = idx, r[a] = idx ++ ;
}
// 删除节点a
void remove(int a)
{
    l[r[a]] = l[a];
    r[l[a]] = r[a];
}
```

- [双链表](https://www.acwing.com/problem/content/829/)

```c++
#include <iostream>

using namespace std;

const int N = 100010;

int m;
int e[N], l[N], r[N], idx;

// 在节点a的右边插入一个数x
void insert(int a, int x)
{
    e[idx] = x;
    l[idx] = a, r[idx] = r[a];
    l[r[a]] = idx, r[a] = idx ++ ;
}

// 删除节点a
void remove(int a)
{
    l[r[a]] = l[a];
    r[l[a]] = r[a];
}

int main()
{
    cin >> m;

    // 0是左端点，1是右端点
    r[0] = 1, l[1] = 0;
    idx = 2;

    while (m -- )
    {
        string op;
        cin >> op;
        int k, x;
        if (op == "L")
        {
            cin >> x;
            insert(0, x);
        }
        else if (op == "R")
        {
            cin >> x;
            insert(l[1], x);
        }
        else if (op == "D")
        {
            cin >> k;
            remove(k + 1);
        }
        else if (op == "IL")
        {
            cin >> k >> x;
            insert(l[k + 1], x);
        }
        else
        {
            cin >> k >> x;
            insert(k + 1, x);
        }
    }
    for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << ' ';
    cout << endl;

    return 0;
}
```

## 栈

> ​	栈是一种先进先出的数据结构，类似于一个桶先进来的最后再出去，用数组模拟栈的时候只用记录栈顶即可，进栈就是尾部加一，出栈就是尾部减一

- [模拟栈](https://www.acwing.com/problem/content/830/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int stk[N],tt;
int main()
{
    int m;
    cin >> m;
    while (m -- )
    {
        string op;
        int x;
        cin >> op;
        if(op == "push")
        {
            cin >> x;
            stk[++ tt] = x;
        }
        else if(op == "pop")
            tt --;
        else if(op == "query")
            cout << stk[tt] << endl;
        else
            cout << (tt == 0 ? "YES" : "NO" )<< endl;
    }
    return 0;
}
```

> 模板

```c++
// tt表示栈顶
int stk[N], tt = 0;
// 向栈顶插入一个数
stk[ ++ tt] = x;
// 从栈顶弹出一个数
tt -- ;
// 栈顶的值
stk[tt];
// 判断栈是否为空
if (tt > 0)
{

}
```

- [表达式求值](https://www.acwing.com/problem/content/3305/)

> ​	这一题我们考虑使用了二叉树类比存储，并且假设二叉树的根节点的优先级最低，因此我们可以了逐步求出子树的值，定义两个数组分别存储操作类型和被操作的数值进行求解，遇见括号就先进行求解括号内的值

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
const int N = 1e5 + 10;

stack <int> num;
stack <char> op;

void eval()
{
    auto b = num.top(); num.pop();
    auto a = num.top(); num.pop();
    auto c = op.top(); op.pop();
    int x;
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else x = a / b;
    num.push(x);
}


int main()
{
    unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    string s;
    cin >> s;
    int res = 0;
    for(int i = 0 ; i < s.size() ; i ++)
    {
        if(isdigit(s[i]))
        {
            int x = 0 , j = i;
            while(j < s.size() && isdigit(s[j]))
                x = x * 10 + s[j ++] - '0';
            i = j - 1;
            num.push(x);
        }
        else if(s[i] == '(') op.push(s[i]);
        else if(s[i] == ')')
        {
            while (op.top() != '(') eval();
            op.pop();

        }
        else 
        {
            while(op.size() && pr[op.top()] >= pr[s[i]] && op.top() != '(') eval();
            op.push(s[i]);
        }
    }
    while (op.size()) eval();
    cout << num.top() << endl;
    return 0;
}
```

### 单调栈

- [单调栈](https://www.acwing.com/problem/content/832/)

> ​	在此题中我们可以考虑使用一个栈记录已经走过的值的最小值，每次把值加入到栈中，每次遇见大于栈顶的值的时候就将栈顶弹出，保证栈内是一个递增的序列

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 +10;
int stk[N],q[N];
int tt, n;
int main()
{
    cin >> n;
    for(int i = 0 ; i < n ; i ++)
        cin >> q[i];
    memset(stk,-1,sizeof stk);
    for(int i = 0 ; i < n ; i ++)
    {
        while(stk[tt] >= q[i]) tt --;
        cout << stk[tt] << " ";
        stk[ ++ tt] = q[i];
    }
    return 0;
}
```

## 队列

> ​	队列是一种先进先出的数据结构，可以类比为排队，先来的先出去。用数组进行模拟的时候我们需要记录队头和队尾，每次从队尾加入数据，从队头弹出数据

- [模拟队列](https://www.acwing.com/problem/content/831/)

```c++
#include <iostream>

using namespace std;

const int N = 100010;

int m;
int q[N], hh, tt = -1;

int main()
{
    cin >> m;

    while (m -- )
    {
        string op;
        int x;

        cin >> op;
        if (op == "push")
        {
            cin >> x;
            q[ ++ tt] = x;
        }
        else if (op == "pop") hh ++ ;
        else if (op == "empty") cout << (hh <= tt ? "NO" : "YES") << endl;
        else cout << q[hh] << endl;
    }
    return 0;
}
```

> 模板
>
> 1. 普通队列：
>
> ```c++
> // hh 表示队头，tt表示队尾
> int q[N], hh = 0, tt = -1;
> 
> // 向队尾插入一个数
> q[ ++ tt] = x;
> 
> // 从队头弹出一个数
> hh ++ ;
> 
> // 队头的值
> q[hh];
> 
> // 判断队列是否为空
> if (hh <= tt)
> {
> 
> }
> ```
>
> 2. 循环队列
>
> ```c++
> // hh 表示队头，tt表示队尾的后一个位置
> int q[N], hh = 0, tt = 0;
> 
> // 向队尾插入一个数
> q[tt ++ ] = x;
> if (tt == N) tt = 0;
> 
> // 从队头弹出一个数
> hh ++ ;
> if (hh == N) hh = 0;
> 
> // 队头的值
> q[hh];
> 
> // 判断队列是否为空
> if (hh != tt)
> {
> 
> }
> ```

### 单调队列

- [单调队列](https://www.acwing.com/problem/content/832/)

> ​	我们可以考虑用一个队列一直维护一个大小为 k 的窗口，保证队列内的队头是最大或者是最小值，如果不是就将队尾减一，直到加入最大或最小值

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 1e6 + 10;
int a[N],q[N];
queue<int> mx,mn;
int hh,tt = -1;
int main()
{
    int n,k;
    cin >> n >> k;
    for(int i = 0 ; i < n ; i ++) cin >> a[i];
    for(int i = 0 ; i < n ; i ++)
    {
        if(hh <= tt && i - k + 1 > q[hh]) hh ++;
        while(hh <= tt && a[q[tt]] >= a[i]) tt --;
        q[++ tt] = i;
        if(i >= k - 1 ) cout <<a[q[hh]] <<" ";
    }
    cout << endl;
    hh = 0 , tt = -1 ;
    for(int i = 0 ; i < n ; i ++)
    {
        if(hh <= tt && i - k + 1 > q[hh]) hh ++;
        while(hh <= tt && a[q[tt]] <= a[i]) tt --;
        q[++ tt] = i;
        if(i >= k - 1) cout << a[q[hh]] <<" ";
    }
    return 0;
}
```

## KMP

> ​	kmp中最重要的概念就是`最长公共前后缀`我们需要找到并且初始化 ne 数组，ne 数组中存储的是指从 0~ne数组值的字符串和 从j-ne数组值到j 的字符串值相等，并且是最大的能匹配的值，预处理出来 ne 数组，里面保存的值为最大公共匹配字符串

- [KMP字符串](https://www.acwing.com/problem/content/833/)

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6 + 10;
char p[N],s[N];
int n,m;
int ne[N];
int main(void)
{
    cin >> n >> p + 1 >> m >> s+1;
    for(int i = 2 , j = 0 ; i<=n;i ++)
    {
        while(j && p[i] != p[j + 1]) j = ne[j];
        if(p[i] == p[j + 1]) j ++ ;
        ne[i]  = j;
    }
    for(int i = 1 , j = 0 ; i <= m ; i ++)
    {
        while(j && s[i] != p[j + 1]) j = ne[j];
        if(s[i] == p[j + 1]) j++;
        if(j == n)
        {
            cout << i - n << " ";
            j = ne[j];
        }
    }
    return 0;
}
```

## Trie树

> ​	构建 Trie 树的主要思想是将一个字符串利用二维数组存储下来，每次根据字符串位置上的字符进行传递，利用 p 来存储是否存在该字符。
>
> ​	也就是利用二维数组的第一维记录是第几层，第二位记录哪个字符

- [Trie字符串统计](https://www.acwing.com/problem/content/837/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int son[N][26], cnt[N], idx;
int n;
void insert(string str)
{
    int p = 0;
    for (auto c : str)
    {
        int x = c - 'a';
        if (son[p][x] == 0)
            son[p][x] = ++idx;
        p = son[p][x];
    }
    cnt[p]++;
}
int query(string s)
{
    int p = 0;
    for (auto c : s)
    {
        int x = c - 'a';
        if (son[p][x] == 0)
            return 0;
        p = son[p][x];
    }
    return cnt[p];
}
int main(void)
{
    cin >> n;
    while (n--)
    {
        string op;
        string str;
        cin >> op >> str;
        if (op == "I")
            insert(str);
        else
            cout << query(str) << endl;
        ;
    }
    return 0;
}
```

- [最大异或对]()

> ​	这个思想也跟Trie树一样，不过我们存储的是所有数的二进制位，也可以形成一个类似于二进制树的数据结构，然后在进行异或运算，每次寻找最佳的情况。

```c++
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010, M = 3100010;

int n;
int a[N], son[M][2], idx;

void insert(int x)
{
    int p = 0;
    for (int i = 30; i >= 0; i -- )
    {
        int &s = son[p][x >> i & 1];
        if (!s) s = ++ idx;
        p = s;
    }
}

int search(int x)
{
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i -- )
    {
        int s = x >> i & 1;
        if (son[p][!s])
        {
            res += 1 << i;
            p = son[p][!s];
        }
        else p = son[p][s];
    }
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
    {
        scanf("%d", &a[i]);
        insert(a[i]);
    }

    int res = 0;
    for (int i = 0; i < n; i ++ ) res = max(res, search(a[i]));

    printf("%d\n", res);

    return 0;
}
```

> ​	模板
>
> ```c++
> int son[N][26], cnt[N], idx;
> // 0号点既是根节点，又是空节点
> // son[][]存储树中每个节点的子节点
> // cnt[]存储以每个节点结尾的单词数量
> 
> // 插入一个字符串
> void insert(char *str)
> {
>     int p = 0;
>     for (int i = 0; str[i]; i ++ )
>     {
>         int u = str[i] - 'a';
>         if (!son[p][u]) son[p][u] = ++ idx;
>         p = son[p][u];
>     }
>     cnt[p] ++ ;
> }
> 
> // 查询字符串出现的次数
> int query(char *str)
> {
>     int p = 0;
>     for (int i = 0; str[i]; i ++ )
>     {
>         int u = str[i] - 'a';
>         if (!son[p][u]) return 0;
>         p = son[p][u];
>     }
>     return cnt[p];
> }
> ```

## 并查集

> ​	并查集主要的作用是维护一个集合或是一个集合的关系，通过祖宗节点来维护多个集合

```c++
(1)朴素并查集：

    int p[N]; //存储每个点的祖宗节点

    // 返回x的祖宗节点
    int find(int x)
    {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    // 初始化，假定节点编号是1~n
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    // 合并a和b所在的两个集合：
    p[find(a)] = find(b);

(2)维护size的并查集：

    int p[N], size[N];
    //p[]存储每个点的祖宗节点, size[]只有祖宗节点的有意义，表示祖宗节点所在集合中的点的数量

    // 返回x的祖宗节点
    int find(int x)
    {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    // 初始化，假定节点编号是1~n
    for (int i = 1; i <= n; i ++ )
    {
        p[i] = i;
        size[i] = 1;
    }

    // 合并a和b所在的两个集合：
    size[find(b)] += size[find(a)];
    p[find(a)] = find(b);


(3)维护到祖宗节点距离的并查集：

    int p[N], d[N];
    //p[]存储每个点的祖宗节点, d[x]存储x到p[x]的距离

    // 返回x的祖宗节点
    int find(int x)
    {
        if (p[x] != x)
        {
            int u = find(p[x]);
            d[x] += d[p[x]];
            p[x] = u;
        }
        return p[x];
    }

    // 初始化，假定节点编号是1~n
    for (int i = 1; i <= n; i ++ )
    {
        p[i] = i;
        d[i] = 0;
    }

    // 合并a和b所在的两个集合：
    p[find(a)] = find(b);
    d[find(a)] = distance; // 根据具体问题，初始化find(a)的偏移量
```

- [合并集合](https://www.acwing.com/problem/content/838/)

> ​	朴素并查集，每次合并集合即可

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int p[N];
int n,m;
int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++) p[i] = i;
    while(m --)
    {
        string op;
        int a,b;
        cin >> op >> a >> b;
        if(op == "M")
        {
           p[find(a)] = find(b);
        }else{
            cout << (find(a) == find(b) ? "Yes" : "No") << endl;
        }
    }
    return 0;
}
```

- [连通块中点的数量](https://www.acwing.com/problem/content/839/)

> ​	记录祖宗节点所在树的节点的个数的并查集

```c++
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int p[N],cnt[N];
int n,m;
int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main(void)
{
    cin >> n >> m;
    for(int i = 1;i<=n;i++) 
    {
        p[i] = i;
        cnt[i] = 1;
    }
    while(m--)
    {
        int a,b;
        string op;
        cin >> op;
        if(op == "C")
        {
            cin >> a >> b;
            if(find(a) != find(b))
            {
                cnt[find(b)] += cnt[find(a)];
                p[find(a)] = find(b);
            }
        }
        else if(op == "Q1")
        {
            cin >> a >> b;
            if(find(a) == find(b)) cout<<"Yes"<<endl;
            else  cout<<"No"<<endl;
        }
        else 
        {
            cin >> a;
            cout << cnt[find(a)]<<endl;
        }
    }
    return 0;
}
```

- [食物链](https://www.acwing.com/problem/content/242/)

> ​	维护到祖宗节点距离的并查集，通过到祖宗节点的距离来判断关系

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int p[N];
int d[N];
int n,m;
int find(int x)
{
    if(x != p[x])
    {
        int t = find(p[x]);
        d[x] += d[p[x]];
        p[x] = t;
    }
    return p[x];
}
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n ; i ++) p[i] = i;
    int res = 0;
    while (m -- )
    {
        int a , b ,c;
        cin >> a >> b >> c;
        if(c > n || b > n) res ++;
        else
        {
            int px = find(b) , py = find(c);
            if(a == 1)
            {
                if(px == py && (d[b] - d[c]) % 3) res ++;
                else if(px != py)
                {
                    p[px] = py;
                    d[px] = d[c] - d[b];
                }
            }
            else
            {
                if(px == py && (d[b] - d[c] - 1) % 3) res ++;
                else if(px != py)
                {
                    p[px] = py;
                    d[px] = d[c] + 1 - d[b];
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}
```

## 堆

> ​	堆结构主要维护了一个大根堆或是小根堆，即对于每一个树来说，根节点都是最小或最大的点，所以我们主要用到了一个 up 操作和一个 down 操作，分别代表着一个点向上移动和向下移动

- [堆排序](https://www.acwing.com/problem/content/840/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N =  1e5 +10;
int h[N],cnt;
int n,m;
void down(int x)
{
    int t = x;
    if(cnt >= 2 * x && h[t] > h[2 * x]) t = 2 * x;
    if(x * 2  + 1<= cnt && h[t] > h[2 * x + 1]) t = 2 * x + 1;
    if(t != x)
    {
        swap(h[t],h[x]);
        down(t);
    }
}
int main()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++) cin >> h[i];
    cnt = n;
    for(int i = n / 2; i  ; i --) down(i);
    while(m --)
    {
        cout << h[1] << " ";
        h[1] = h[cnt --];
        down(1);
    }
    return 0;
}
```

- [模拟堆](https://www.acwing.com/problem/content/841/)

> ​	因为我们需要记录插入点的位次，所以我们需要构建一个映射关系记录位次和数值的对应关系，此外 up 操作只需要和根节点做比较即可，因为根节点是极值

```c++
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

const int N = 100010;

int h[N], ph[N], hp[N], cnt;

void heap_swap(int a, int b)
{
    swap(h[a], h[b]);
    swap(ph[hp[a]],ph[hp[b]]);
    swap(hp[a], hp[b]);
    
}
void down(int u)
{
    int t = u;
    if (u * 2 <= cnt && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= cnt && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (u != t)
    {
        heap_swap(u, t);
        down(t);
    }
}

void up(int u)
{
    while (u / 2 && h[u] < h[u / 2])
    {
        heap_swap(u, u / 2);
        u >>= 1;
    }
}
int main()
{
    int n, m = 0;
    scanf("%d", &n);
    while (n -- )
    {
        char op[5];
        int k, x;
        scanf("%s", op);
        if (!strcmp(op, "I"))
        {
            scanf("%d", &x);
            cnt ++ ;
            m ++ ;
            ph[m] = cnt, hp[cnt] = m;
            h[cnt] = x;
            up(cnt);
        }
        else if (!strcmp(op, "PM")) printf("%d\n", h[1]);
        else if (!strcmp(op, "DM"))
        {
            heap_swap(1, cnt);
            cnt -- ;
            down(1);
        }
        else if (!strcmp(op, "D"))
        {
            scanf("%d", &k);
            k = ph[k];
            heap_swap(k, cnt);
            cnt -- ;
            up(k);
            down(k);
        }
        else
        {
            scanf("%d%d", &k, &x);
            k = ph[k];
            h[k] = x;
            up(k);
            down(k);
        }
    }
    return 0;
}
```

## 哈希表

> ​	哈希表是一种映射关系，也就是将一段字符串或者是很大的数值映射到一个很简单的数值上面。
>
> ```c++
> (1) 拉链法
>     int h[N], e[N], ne[N], idx;
> 
>     // 向哈希表中插入一个数
>     void insert(int x)
>     {
>         int k = (x % N + N) % N;
>         e[idx] = x;
>         ne[idx] = h[k];
>         h[k] = idx ++ ;
>     }
> 
>     // 在哈希表中查询某个数是否存在
>     bool find(int x)
>     {
>         int k = (x % N + N) % N;
>         for (int i = h[k]; i != -1; i = ne[i])
>             if (e[i] == x)
>                 return true;
> 
>         return false;
>     }
> 
> (2) 开放寻址法
>     int h[N];
> 
>     // 如果x在哈希表中，返回x的下标；如果x不在哈希表中，返回x应该插入的位置
>     int find(int x)
>     {
>         int t = (x % N + N) % N;
>         while (h[t] != null && h[t] != x)
>         {
>             t ++ ;
>             if (t == N) t = 0;
>         }
>         return t;
>     }
> ```

- [模拟散列表](https://www.acwing.com/problem/content/842/)

> ​	取模来进行哈希，处理冲突使用拉链法或者开放寻址法

```c++
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;
const int Q = 200003;
const int null = 0x3f3f3f3f;
int h[Q];
int get(int x)
{
    int k = (x % Q + Q)% Q;         // 映射 
    while(h[k] != null && h[k] != x)
    {
        k++;
        if(k == Q) k = 0; 
    }
    return k; // k 要么是 空余位置 要么是 已存在k的位置
}
int main(void)
{
    int n;
    cin>>n;
    memset(h,0x3f,sizeof h);
    int x;
    while(n--)
    {
        string op;
        cin>>op;
        if(op == "I")
        {
            cin>>x;
            h[get(x)] = x;
        }
        else 
        {
            cin>>x;
            if(h[get(x)] != null) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
    }
}

#include <cstring>
#include <iostream>
using namespace std;
const int N = 100003;
int ne[N],e[N],idx,h[N];
void find(int x)
{
    int k = (x % N + N)% N;
    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx++;
}
bool get(int x)
{
    int k = (x % N + N)% N;
    for(int i = h[k];i != -1;i = ne[i])
    {
        if(e[i] == x) return true;
    }
    return false;
}
int main(void)
{
    int n;
    int x;
    memset(h,-1,sizeof h);
    cin>>n;
    while(n--)
    {
        string op;
        cin>>op;
        if(op == "I")
        {
            cin>>x;
            find(x);
        }
        else 
        {
            cin>>x;
            if(get(x)) cout<<"Yes"<<endl;
            else  cout<<"No"<<endl;
        }
    }
}
```

- [字符串哈希](https://www.acwing.com/problem/content/843/)

> ​	把字符串当成一个 P 进制的数 ，一般为 131 or 13331；**每一段**属于原字符串的子串都能用一个整数来表示，然后求匹配时按照位数的优先顺序进行左移在进行相减，得到了最终结果；用 unsigned long long 来存储 省去了取 mod 操作

$$
y=hash(S的P进制表示)modQ
$$

$$
h[l,r] = h[r] - h[l-1] * p[r - l + 1]
$$

![image-20230105112010884](E:\SoftWare\Typora\新建文件夹\image-20230105112010884.png)

> 核心思想：将字符串看成P进制数，P的经验值是131或13331，取这两个值的冲突概率低
> 小技巧：取模的数用2^64，这样直接用unsigned long long存储，溢出的结果就是取模的结果
>
> h[k]存储字符串前k个字母的哈希值, p[k]存储 P^k mod 2^64

```C++
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long ULL;
const int P = 131,N = 1e5 + 10;
ULL p[N],h[N];
char s[N];
int n,m;
ULL get(int l,int r)
{
    return h[r] - h[l - 1] * p[r - l + 1]; 
}
int main(void)
{
    cin >> n >> m ;
    cin >> s+1;
    p[0] = 1;
    for(int i = 1; i<= n ; i ++)
    {
        h[i] = h[i-1] * P + s[i];
        p[i] = p[i-1] * P;
    }
    while(m --)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);

        if (get(l1, r1) == get(l2, r2)) puts("Yes");
        else puts("No");
    }
    return 0;
}
```


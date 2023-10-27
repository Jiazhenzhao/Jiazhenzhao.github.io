# 搜索与图论

[TOC]

## DFS

​	DFS，深度优先搜索算法，一般用于求排列和递归等问题，使用时最需要注意的问题是注意的递归的逻辑以及终止条件，在设计递归算法的时候一定要考虑到如何终止以及何时终止？这里给出两道例题来做示例。

- [排列数字](https://www.acwing.com/problem/content/844/)

```c++
#include <iostream>
#include <algorithm>
using namespace std;
int n ;
int path[10];
int flag[10];
void dfs(int u)
{
    if(u == n) // 终止条件
    {
        for(int i = 0 ; i < n ; i ++) cout << path[i] <<" ";
        cout << endl;
        return;
    }// 实现逻辑
    for(int i = 1 ; i <= n ; i ++)
    {
        if(!flag[i])
        {
            flag[i] = 1;
            path[u] = i ;
            dfs(u+1);
            flag[i] = 0;
        }
    }
}
int main(void)
{
    cin >> n;
    dfs(0);
    return 0;
}
```

- [n-皇后问题](https://www.acwing.com/problem/content/845/)

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20;
int col[N],dg[N],udg[N],row[N];
int n;
char g[N][N];
void dfs(int x,int y,int s)
{
    if(y == n) x = x + 1, y = 0;
    
    
    if(x == n)
    {
        if(s == n)
        {
            for(int i = 0 ; i < n ; i ++) puts(g[i]);
            puts("");
        }
        return ;
    }
    g[x][y] = '.';
    dfs(x,y+1,s);
    
    if(!row[x] && !col[y] && !dg[x + y] && !udg[x - y + n])
    {
        g[x][y] = 'Q';
        row[x] = col[y] = dg[x + y] = udg[x - y + n] = true;
        dfs(x,y + 1,s + 1);
        row[x] = col[y] = dg[x + y] = udg[x - y + n] = false;
        g[x][y] = '.';
    }
    
}
int main(void)
{
    cin >> n ;
    for(int i = 0 ; i < n ; i ++)
        for(int j = 0 ; j < n ; j ++)   
            g[i][j] = '.';
    dfs(0,0,0);
    return 0;
}

#include <iostream>
using namespace std;
const int N = 20;
char g[N][N];
int n;
bool col[N],dg[N],udg[N],flag[N];
void dfs(int u)
{
    if( u == n  )
    {
          
        for(int i = 0 ; i < n ; i ++) puts(g[i]);
        puts("");
        return ;
    }
    // 近似全排列
    for(int i = 0 ; i < n ; i ++)
    {
        if(!col[i] && !dg[u + i] && !udg[n - u + i])
        {
            g[u][i] = 'Q';
            col[i] = dg[u + i] = udg[n - u + i] = true;
            dfs(u + 1);
            col[i] = dg[u + i] = udg[n - u + i] = false;
            g[u][i] = '.';
        }
    }   
    
}
int main(void)
{
    cin >> n;
    for(int i = 0 ; i < n ; i ++)
        for(int j = 0 ; j < n ; j ++)
            g[i][j] = '.';
  
    dfs(0);
    return 0;
}
*
```

## BFS

​	BFS，宽度优先搜索算法，主要用于迷宫问题、最短路问题等，主要利用队列实现，通过不断向队列中加入和弹出元素来实现相应的思路，最核心的逻辑是记录所需要保证的状态以及维护算法中的队列，保证不出现死循环等。

- [走迷宫](https://www.acwing.com/problem/content/846/)

> ​	记录偏移量数组，从坐标为（1，1）开始加入数组，每次遍历上下左右四个方向，如果可以行走就加入到队列中，并且维护一个d距离数组记录各个点到起点的距离。

```c++
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 110;
int g[N][N],d[N][N];
int n,m;
int dx[4] = {0,1,0,-1} , dy[4] = {1,0,-1,0};
int bfs()
{
    memset(d,-1,sizeof(d));
    queue<pair<int,int>> q;
    d[0][0] = 0;
    q.push({0,0});
    while(q.size())
    {
        auto t = q.front();
        q.pop();
        for(int i = 0 ; i < 4 ; i ++)
        {
            int x = t.first  + dx[i] , y = t.second + dy[i];
            if(x < n && x >= 0 && y < m && y >= 0 && d[x][y] == -1 && g[x][y] == 0)
            {
                d[x][y] = d[t.first][t.second] + 1;
                q.push({x,y});
            }
        }
    }
    return d[n-1][m-1]; 
}
int main(void)
{
    cin >> n >> m;
    for(int i = 0 ; i < n ; i ++)
        for(int j = 0 ; j < m ; j ++)
            cin >> g[i][j];
    cout << bfs() << endl;
    return 0;
}
```

- [八数码](https://www.acwing.com/problem/content/847/)

> ​	此题的解决思路也是利用BFS算法的思想，我们可以将初始地图状态转化为一个字符串，然后将字符串推入到队列中，每次从队列中弹出一个字符串，在其中寻找到x的位置接着遍历上下左右四个方向，将可以走通的情况推入队列中，同时利用哈希表维护d数组，当出现了答案时直接输出。

```c++
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <map>
#include <cstring>
using namespace std;

int bfs(string s)
{
    queue<string> q;
    unordered_map<string,int> d;
    d[s] = 0;
    string end = "12345678x";
    q.push(s);
    int dx[4] = {0,1,0,-1} , dy[4] = {1,0,-1,0};
    while(q.size())
    {
        auto t = q.front();
        q.pop();
        if(t == end) return d[t];
        int distance = d[t];
        int k = t.find('x');
        int x = k / 3 , y = k % 3;
        for(int i = 0 ; i < 4 ; i ++)
        {
            int ax = x + dx[i] , ay = y + dy[i];
            if(ax < 3 && ax >= 0 && ay >= 0 && ay < 3)
            {
                swap(t[ax*3 + ay] , t[k]);
                if(!d.count(t))
                {
                    d[t] = distance + 1 ;
                    q.push(t);
                }
                swap(t[ax*3 + ay] , t[k]);
            }
        }
    }
    return -1;
}
int main(void)
{
    string s;
    for(int i = 0 ; i < 9 ; i ++)
    {
        char c ;
        cin >> c;
        s += c;
    }
    cout << bfs(s) << endl;
    return 0;
}
```

## 树与图的存储

- 树是一种特殊的图，与图的存储方式相同
- 对于无向图中的边ab，存储两条有向边a->b, b->a
- 因此我们可以只考虑有向图的存储

(1) 邻接矩阵：g[a] [b] 存储边a->b

(2) 邻接表：

```c++
// 对于每个点k，开一个单链表，存储k所有可以走到的点。h[k]存储这个单链表的头结点
int h[N], e[N], ne[N], idx;

// 添加一条边a->b
void add(int a, int b)
{
    e[idx] = b, ne[++++++++++++] = h[a], h[a] = idx ++ ;
}

// 初始化
idx = 0;
memset(h, -1, sizeof h);
```

## 树与图的遍历

> 时间复杂度 O(n+m)O(n+m), n 表示点数，m 表示边数

### 深度优先遍历

```c++
int dfs(int u)
{
    st[u] = true; // st[u] 表示点u已经被遍历过

    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j]) dfs(j);
    }
}
```

- [树的重心](https://www.acwing.com/problem/content/848/)

> ​	这题的主要思路是遍历每一个点，求出当删除这个点之后剩余的子树中点的最大值最小的点，我们可以利用递归的思想在遍历节点的时候同时求出以它为根节点的子树的大小，然后将这个子树和剩余的点的大小做对比，从而得到了最终的重心节点。

```c++
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 10 , M = 2*N;
int n,idx;
int h[N],e[M],ne[M];
bool st[N];

int res = N;
void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
int dfs(int x)
{
    st[x] = true;
    int sum = 1 , ans = 0;
    for(int i = h[x] ; i != -1 ; i = ne[i])
    {
        int j = e[i];
        if(st[j]) continue;
        int s = dfs(j);
        sum += s; // 总数 + s
        ans = max(ans , s); // 
    }
    // 这里的 ans 只是求了一个最大值的情况
    ans = max(ans , n - sum);
    // 这里的 res 记录的才是最终的最小值的节点值的大小
    res = min(res,ans);
    return sum;
}
int main(void)
{
    memset(h,-1,sizeof h);
    cin >> n;
    for(int i = 0 ; i < n - 1 ; i ++)
    {
        int a,b;
        cin >> a >> b;
        add(a,b) , add(b,a);
    }
    dfs(1);
    cout << res << endl;
    return 0;
}
```

### 宽度优先遍历

```c++
queue<int> q;
st[1] = true; // 表示1号点已经被遍历过
q.push(1);

while (q.size())
{
    int t = q.front();
    q.pop();

    for (int i = h[t]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true; // 表示点j已经被遍历过
            q.push(j);
        }
    }
}
```

- [图中点的层次](https://www.acwing.com/problem/content/849/)

> ​	基本的BFS找最短路的实现过程，这里同样也可以用Dijkstra来解决，设置所有的权重为1即可

```c++
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 + 10 ,M = 2 * N;
int h[N], e[M] , ne[M], idx;
int n,m;
int dist[N];
void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++ ;
}
void bfs()
{
    memset(dist,-1,sizeof(dist));
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while(q.size())
    {
        auto t = q.front();
        int distance = dist[t];
        q.pop();
        for(int i = h[t] ; i != -1 ; i = ne[i])
        {
            int j = e[i];
            if(dist[j] == -1)
            {
                q.push(j);
                dist[j] = distance + 1;
            }
        }
    }
}
int main(void)
{
    memset(h,-1,sizeof h);
    cin >> n >> m;
    while(m --)
    {
        int a,b;
        cin >> a >> b;
        add(a,b);
    }
    bfs();
    cout << dist[n] << endl;
    return 0;
}
```

### 拓扑排序

```c++
bool topsort()
{
    int hh = 0, tt = -1;

    // d[i] 存储点i的入度
    for (int i = 1; i <= n; i ++ )
        if (!d[i])
            q[ ++ tt] = i;

    while (hh <= tt)
    {
        int t = q[hh ++ ];

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (-- d[j] == 0)
                q[ ++ tt] = j;
        }
    }
    // 如果所有点都入队了，说明存在拓扑序列；否则不存在拓扑序列。
    return tt == n - 1;
}
```

- [拓扑排序](https://www.acwing.com/problem/content/850/)

> ​	拓扑排序是指一个序列中不存在自环，在具体求解过程中我们可以通过入度和出度两个概念来求解拓扑序列，我们从入度为0的点开始求解，每次将他后面的点的入度减一，然后如果此时入度为0，则接着入队从而不断扩大序列，最后在进行总点数的判断。

```c++
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 +10;
int h[N],e[N],ne[N],idx;
int d[N],q[N];
int n,m;
void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++ ;
}
int topsort()
{
    int hh = 0 , tt = -1;
    for(int i = 1 ; i <= n ; i ++)
        if(!d[i])
            q[++ tt] = i;
    while(hh <= tt)
    {
        int t = q[hh ++];
        for(int i = h[t] ; i != -1; i = ne[i])
        {
            int j = e[i];
            d[j] --;
            if(d[j] == 0) q[++ tt] = j;
        }
    }
    return tt == n-1;
}
int main(void)
{
    memset(h,-1,sizeof h);
    cin >> n >> m;
    while(m --)
    {
        int a , b;
        cin >> a >> b;
        add(a,b);
        d[b] ++;
    }
    if(topsort())
    {
        for(int i = 0 ; i < n ; i ++) cout << q[i] << " ";
        cout << endl;
    }else {
        cout << -1 << endl;
    }

    return 0;
}
```

## 最短路

### 朴素Dijkstra算法

> 时间复杂是 O(n^2 + m), n 表示点数，m 表示边数

​	朴素Dijkstra算法主要应用于稠密图，邻接表存储，并且不存在负权边的情况，他的主要实现思路是循环 n 次，每次找到一个 t 代表当前所有点到起点的最短距离（这里和 Prim 算法做一个区分，Prim 算法中求的是距离集合的最短距离），然后用这个 t 点来更新其他点到这个 t 点的距离。

- [Dijkstra为什么不能处理负权边？](https://www.acwing.com/solution/content/6320/)

- [Dijkstra算法求最短路](https://www.acwing.com/problem/content/851/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 550;
int n,m;
int g[N][N];
int dist[N];
bool st[N];
void dijkstra()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    for(int i = 0 ; i < n ; i ++)
    {
        int t = -1;
        for(int j = 1; j <= n ; j ++)
            if(!st[j] && (t == -1 || dist[t] > dist[j])) // 找到最短的距离
                t = j ;
        for (int j = 1 ; j <= n ; j ++)
            if(dist[j] > dist[t] + g[t][j])
                dist[j] = dist[t] + g[t][j];
        st[t] = true;
    }
}
int main()
{
    memset(g,0x3f,sizeof g);
    cin >> n >> m;
    while (m -- )
    {
        int a,b,c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b],c);
    }
    dijkstra();
    if(dist[n] == 0x3f3f3f3f) cout << -1 << endl;
    else cout << dist[n] << endl;
}
```

### 堆优化版Dijkstra算法

> 时间复杂度 O(m log n), n 表示点数，m 表示边数

​	堆优化Dijkstra算法主要应用于稀疏图，用邻接表存储，主要实现思路是，优化了朴素做法中的求最短距离的过程并且利用了BFS的思想，采用堆来存储所有的距离，用一个 pair <int, int>  数组来存储到起点的距离和当前点的编号，每次只需要取出堆顶元素即可得到最短距离，然后再用该元素更新其他元素到起点的距离。

- [Dijkstra求最短路 II](https://www.acwing.com/problem/content/852/)

```c++
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int,int> PII;
const int N = 1e6 + 10;
int h[N],e[N],ne[N],w[N],idx; 
int dist[N];
int n,m;
bool st[N]; 
void add(int a,int b,int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++ ;
}
int dijkstra()
{
    memset(dist,0x3f,sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    dist[1] = 0;
    heap.push({0,1});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        int dis = t.first,ver = t.second;
        if(st[ver]) continue;
        st[ver] = true;
        for(int i = h[ver];i != -1 ; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[ver] + w[i])
            {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j],j});
            }
        }
    }
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}
int main(void)
{
    cin >> n >> m;
    memset(h,-1,sizeof h);
    while(m --)
    {
        int a,b,c;
        cin >> a >> b >> c;
        add (a,b,c);
    }
    cout << dijkstra() << endl;
    return 0;
}
```

这里 与 spfa 算法进行个区分  

> -  dijsktra 算法一般在取得编号后就进行判断 是否进行 continue 环节
>
> -  spfa 算法 则在 for 循环和 if 循环 之后判断该值是否使用过
> -  dijkstra 保证了每个点只会被使用一次，而spfa则一个点可能被多次使用
>
> ​	SPFA可以处理负权边，但是不能处理有负权回路的图；而Dijkstra不能处理带有负权边和负权回路的图，因为Dijkstra算法在计算最短路径时，不会因为负边的出现而更新已经计算过(收录过)的顶点的路径长度；
> ​	总结一下：Bellman-ford可以处理任意带负权边和负权环的图，SPFA可以处理带负权边的图，Dijkstra只能处理带正权边的图；当然，从时间复杂度的效率来讲，是反过来的。

### Bellman-ford算法

> 时间复杂度 O(nm), n 表示点数，m 表示边数

​	Bellman-ford算法可以处理存在负权边的图并且有边数限制的最短路问题，利用结构体来存储边之间的权重，主要实现过程是遍历所有的结构体存储下的边，每一次更新指向边的距离，但是这里需要引入一个中间的记录数组，因为有可能出现一次更新循环中被更新过的 a 点又去更新了另外一个点，造成了错误。

- [有边数限制的最短路问题](https://www.acwing.com/problem/content/855/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 550,M = 10010;

struct Edge
{
    int a,b,c;
}edges[M];
int n,m,k;
int dist[N];
int last[N];
void bellman_ford()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    for(int i = 0 ; i < k ;i ++)
    {
        memcpy(last,dist,sizeof dist);
        for(int j = 0 ; j< m ; j ++)
        {
            auto e = edges[j];
            dist[e.b] = min(dist[e.b], last[e.a] + e.c);
        }
    }
}
int main(void)
{
    cin >> n >> m >> k;
    for(int i = 0;i<m;i++)
    {
        int x,y,z;
        cin >> x >> y >> z;
        edges[i] = {x,y,z};
    }
    bellman_ford();
    if (dist[n] > 0x3f3f3f3f / 2) puts("impossible");
    else printf("%d\n", dist[n]);
    return 0;
}
```

### Spfa 算法

> 时间复杂度 平均情况下 O(m)，最坏情况下 O(nm)， n 表示点数，m 表示边数

​	可以处理存在负权边的图的最短路求解问题，利用链表进行存储，主要实现思路是对Bellman-ford算法的优化，bellman-ford算法是对所有的边都取了最短距离，而 spfa 算法利用队列将每次被更新的边加入队列中，然后利用该队列在继续更新剩下的边。

​	bellman 算法 保留了所有到这个点的前一个点的最短距离，但这样的话 无疑会有一些边是未曾用过的而 spfa 算法就是只记录了会被更新的节点并用这个点来更新别的点，Bellman_ford算法会遍历所有的边，但是有很多的边遍历了其实没有什么意义，我们只用遍历那些到源点距离变小的点所连接的边即可，**只有当一个点的前驱结点更新了，该节点才会得到更新**；因此考虑到这一点，我们将创建一个队列每一次加入距离被更新的结点。

​	spfa 中节点被删除后就需要将他的状态改为未使用，因为被更新过的点也可能被再次更新，这就是与dijkstra算法最大的区别。

- [分析spfa](https://www.acwing.com/solution/content/9306/)

- [spfa求解最短路](https://www.acwing.com/problem/content/853/)

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 +10;
int h[N],w[N],e[N],ne[N],idx;
int dist[N];
bool st[N];
void add(int a,int b,int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}
void spfa()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    queue<int>q;
    q.push(1);
    st[1] = true;
    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;
        for(int i = h[t] ; i != -1 ; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if(!st[j]) // 这里只会存放已经被更新过的边 ，， 如果被更新了 且不再队列中才会被继续添加
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}
int main(void)
{
    int n,m;
    cin >> n >> m;
    memset(h,-1,sizeof h);
    while(m --)
    {
        int a,b,c;
        cin >> a>> b >> c;
        add(a,b,c);
    }
    spfa();
    if(dist[n] == 0x3f3f3f3f) cout << "impossible" << endl;
    else cout << dist[n] << endl;
    return 0;
}
```

### Floyd算法

> 时间复杂度是O(n^3)，n是点数

​	Floyd算法主要应用于多次询问最短路的操作，因此使用邻接矩阵来存储，并在初始化的时候将对角线元素设置为 0 ，其余设置为0x3f3f3f3f，然后三重循环得到每个点到别的点的最短距离。

- [Floyd求最短路](https://www.acwing.com/problem/content/856/)

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 210,INF = 1e9;
int g[N][N];
int n,m,q;
void Floyd()
{
    for(int k = 1 ;k <= n ;k ++)
        for(int i = 1 ;i <= n ; i ++)
            for(int j = 1; j <= n ;j ++)
            g[i][j] = min(g[i][j] , g[i][k] + g[k][j]);
}
int main(void)
{
    cin >> n >> m >> q;
    for(int i = 1; i <= n ; i ++)
        for(int j = 1; j <= n ; j ++)
            if(i == j) g[i][j] = 0;
            else g[i][j] = INF;
    while(m --)
    {
        int a,b,c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b] , c);
    }
    Floyd();
    while(q -- )
    {
        int x,y;
        cin >> x >> y;
        if(g[x][y] > INF / 2) cout <<"impossible" << endl;
        else cout << g[x][y] << endl;
    }
    return 0;
}
```

## 最小生成树

### Prim算法求最小生成树

> 时间复杂度是 O(n2+m), n 表示点数，m 表示边数

​	Prim 算法适用于稠密图，使用邻接矩阵存储，主要实现思路和 dijkstra 类似，通过不断扩大集合，每次将距离当前集合最短的点加入到集合中，并用这个点来更新其他点到该集合的距离，进而求出了最小生成树，这里需要注意的是 dist 数组存储的是到集合的距离而不是到第一个点的距离，这也是为什么后面更新距离的时候使用 g[t] [j]来更新距离。

- [ Prim算法求最小生成树](https://www.acwing.com/problem/content/860/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 550;
int g[N][N];
int n,m;
int res;
int dist[N];
bool st[N];
int Prim()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    res = 0;
    for(int i = 0 ; i < n ; i ++)
    {
        int t = -1;
        for(int j = 1 ; j <= n ; j ++)
            if(!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        if(i && dist[t] == 0x3f3f3f3f) return 0x3f3f3f3f;
        if(i) res += dist[t];
        for(int j = 1 ; j <= n ; j ++)
            dist[j] = min(dist[j],g[t][j]);
        st[t] = true;
    }
    return res;
}
int main()
{
    memset(g,0x3f,sizeof g);
    cin >> n >> m;
    while (m -- )
    {
        int a,b,c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b],c);
    }
    int res = Prim();
    if(res == 0x3f3f3f3f) cout << "impossible" << endl;
    else cout << res << endl;
    return 0;
}
```

### Kruskal算法求最小生成树

> 时间复杂度是 O(mlogm)， n 表示点数，m 表示边数

​	处理稀疏图，主要实现思路将所有边的权重记录下来，并且通过结构体**按照权重来进行排序 ** 排序保证是最小生成树，然后使用并查集不断将权重最小的两个点联系起来，最后通过加入点的数量来进行判断是否生成成功。

- [Kruskal算法求最小生成树](https://www.acwing.com/problem/content/861/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10 , M = 2 * N;
const int INF = 0x3f3f3f3f;
int p[N];
int n,m;
struct Edges
{
    int a,b,w;
    bool operator < (const Edges & W)const 
    {
        return w < W.w;
    }
}edges[M];
int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    else return p[x];
}
int Kruskal()
{
    int res = 0 , cnt = 0;;
    sort(edges,edges + m);
    for(int i = 1 ;  i <= n ; i ++) p[i] = i;
    for(int i = 0 ; i < m ; i ++)
    {
        int a = edges[i].a , b  = edges[i].b , w = edges[i].w;
        a = find(a) , b = find(b);
        if(a != b)
        {
            p[b] = a;
            res += w;
            cnt ++;
        }
    }
    if(cnt < n - 1) return INF;
    return res;
}
int main()
{
    cin >> n >> m;
    for(int i = 0 ;i < m ; i ++)
    {
        int a,b,c;
         cin >> a >> b >> c;
         edges[i] = {a,b,c};
    }
    int t = Kruskal();
    if(t == INF) cout <<"impossible" << endl;
    else cout << t <<endl;
    return 0;
}
```

## 二分图算法

### 染色法判断是不是二分图

> 时间复杂度是 O(n+m) , n 表示点数，m 表示边数

通过设置color数组来进行分类，遍历所有的点，然后通过递归来不断进行染色

利用染色 1，2 来给点做上标记，并利用 dfs 的过程来进行深度的判断

如果 bool 类型的 dfs 返回 false 的话，代表染色失败，即存在冲突，不满足二分图的性质

如果当前点没有染色，就利用 dfs 把他染成 3 - x 色，如果有颜色 并且相等的话

直接返回 false

- [染色法判定二分图](https://www.acwing.com/problem/content/862/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 +10 , M = 2 * N;
int h[N], e[M], ne[M], idx;
int n,m;
int color[N];
void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
bool dfs(int u,int x)
{
    color[u] = x;
    for(int i = h[u] ; i != -1 ; i = ne[i])
    {
        int j = e[i];
        if(!color[j])
        {
            if(!dfs(j,3-x)) return false;
        }
        else if (color[j] == x) return false;
    }
    return true;
}
int main()
{
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while (m -- )
    {
        int a,b;
        cin >> a >> b ;
        add(a, b), add(b,a);
    }
    bool flag = true;
    for(int i = 1 ; i <= n ; i ++)
    {
        if(!color[i])
        {
            if(!dfs(i,1))
            {
                flag = false;
                break;
            }
        }
    }
    if(flag) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
```

### 匈牙利算法求解二分图最大匹配

> 时间复杂度是 O(nm), n 表示点数，m 表示边数

​	根本原理 是遍历每一个点，然后去找到该点指向的点，再跟着判断 该点是否已经被别的点所匹配或是被别的点匹配的那个点 是否可以匹配别的点 如果 可以 就会替代上一个匹配的点，就是一个递归的过程，for 循环里面每次都会初始化所有的为 false 原因是 让每个人都会进行完美的递归 保证了 最佳答案的出现（把所有妹子清空）即初始化。也就是不管妹子有没有对象，都尝试一下。

- [二分图的最大匹配](https://www.acwing.com/problem/content/863/)

```c++
#include <iostream>
#include <cstring>
using namespace std;
const int N = 550,M = 100010;
int n1,n2,m;
bool st[N];
int h[N],e[M],ne[M];
int idx;
int match[N];
void add(int a,int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}
bool find(int x)
{
    for(int i = h[x]; i != -1 ; i = ne[i])
    {
        int j = e[i];
        if(!st[j])
        {
            st[j] = true;
            if(match[j] == 0 || find(match[j]))
            {
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}
int main(void)
{
    cin >> n1 >> n2 >> m;
    memset(h,-1,sizeof h);
    while(m--)
    {
        int a,b;
        cin >> a >> b;
        add(a,b);
    }
    int res = 0;
    for(int i = 1;i<=n1;i++)
    {
        memset(st,false,sizeof st);
        if(find(i)) res ++;
    }
    cout << res << endl;
    return 0;
}
```


# 基础算法

[TOC]

**[代码模板](https://www.acwing.com/blog/content/277/)**

## 排序

### 快速排序

> 时间复杂度为 nlogn 级别

​	主要思想是每次选取一个基准（一般是以中间为基准），然后从数组的头尾开始进行比较，保证基准的左边都是小于基准的数，基准的右边都是大于基准的数，然后通过同样的方式递归处理分离出来的两个数组，最后得到结果。

> **分治思想 双指针运算**
>
> - 选取基准（一般是以中间为基准）
>
> - 选取做边界 i 和有边界 j ，不断与所选的基准值进行比较，直到找到比基准值大或小的值，进行二者的交换
>
> - 递归同上处理基准值的左右区间

- [快速排序](https://www.acwing.com/problem/content/787/)

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int q[N];
int n;
void quick_sort(int q[],int l,int r)
{
    if(l >= r ) return ;
    int i = l - 1  ,j = r + 1 , mid = q[l+r >> 1];
    while(i < j)
    {
        do i ++; while(q[i] < mid );
        do j --; while(q[j] > mid );
        if(i < j) swap(q[i],q[j]);
    }
    quick_sort(q,l,j);
    quick_sort(q,j+1,r);
}
int main(void)
{
    cin >> n;
    for(int i = 0 ; i < n ; i++) cin >> q[i];
    quick_sort(q,0,n-1);
    for (int i = 0; i < n; i ++ ) printf("%d ", q[i]);
    return 0;
}
```

- [求第K个数](https://www.acwing.com/problem/content/788/)

```c++
#include <iostream>
using namespace std;
const int N = 1e5+ 10;
int n,k;
int a[N];
void quick_sort(int q[], int l,int r)
{
    if(l >= r) return ;
    int mid = q[l + r >> 1];
    int i = l - 1 , j = r + 1;
    while(i < j)
    {
        do i ++ ; while(q[i] < mid);
        do j -- ; while(q[j] > mid);
        if(i < j ) swap(q[i],q[j]);
    }
    quick_sort(q,l,j),quick_sort(q,j + 1 , r);
}
int main()
{
    cin >> n >> k;
    for(int i = 0 ; i < n ; i ++) cin >> a[i];
    quick_sort(a,0,n-1);
    cout << a[k - 1] << endl;
    return 0;
}
```

### 归并排序

> 

​	归并排序是通过将一个区间不断的缩小，从而保证两个区间都是一个递增区间，然后将两个区间进行比较合并之后形成了一个新的区间，接着通过不断的递归过程实现了继续排序的操作。

> **分治思想 区间划分**
>
> - 不断进行区间的划分缩小，直到划分成最小区间（长度为一）
>
> - 进行递归处理，定义出一个临时数组用来存放区间左右两侧的比较大小后的结果
>
> - 把临时数组的值赋予到原数组中，即把原两个数组合二为一

- [归并排序](https://www.acwing.com/problem/content/789/)

```c++
#include <iostream>
using namespace std;
const int N = 1e5 +10;
int q[N],tmp[N];
int n;
void merge_sort(int q[],int l,int r)
{
    if(l >= r) return ;
    int mid = l + r >> 1;
    merge_sort(q,l,mid) , merge_sort(q,mid + 1 , r);
    int k = 0;
    int i = l , j = mid + 1;
    while(i <= mid && j <= r)
    {
        if(q[i] > q[j]) tmp[k ++] = q[j ++];
        else tmp[k ++] = q[i ++];
    }
    while(i <= mid)  tmp[k++] = q[i++] ;
    while(j <= r)    tmp[k++] = q[j++] ;
    for(int i = l , j = 0 ; i <= r ; j ++ , i ++)
        q[i] = tmp[j];
    return ;
}
int main(void)
{
    cin >> n;
    for(int i = 0 ; i < n ; i ++) cin >> q[i];
    merge_sort(q,0,n-1);
    for (int i = 0; i < n; i ++ ) printf("%d ", q[i]);
    return 0;
}
```

- [逆序对的数量](https://www.acwing.com/problem/content/790/)

> ​	利用归并排序的思路，再递归子区间的时候将左边区间大于右边区间的数量记录下来即可

```c++
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int a[N], tmp[N];
LL merge_sort(int q[], int l, int r)
{
    if (l >= r) return 0;
    int mid = l + r >> 1;
    LL res = merge_sort(q, l, mid) + merge_sort(q, mid + 1, r);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else
        {
            res += mid - i + 1;
            tmp[k ++ ] = q[j ++ ];
        }
    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];
    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);
    cout << merge_sort(a, 0, n - 1) << endl;
    return 0;
}

```

## 二分算法

> ​	二分是一种思考问题的思路，重在理解而不是记录代码，二分思想的主要含义是通过每次将一个区间分成两部分，寻找答案所在的那一部分区间，然后继续缩小区间，直到找到答案。l = mid 对应 l + r + 1 >> 1; r = mid 对应 l + r >> 1;

### 整数二分

- [数的范围](https://www.acwing.com/problem/content/791/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int n,q;
int a[N];
int main()
{
    cin >> n >> q;
    for(int i = 0 ; i < n ; i ++) cin >> a[i];
    while(q --)
    {
        int x;
        cin >> x;
        int l = 0 , r = n - 1;
        while(l < r)
        {
            int mid = l + r >> 1;
            if(a[mid] >= x) r = mid;
            else l = mid + 1;
        }
        if(a[l] != x)
        {
            cout <<"-1 -1" << endl;
            continue;
        }
        cout << l << " ";
        l = 0 , r = n - 1;
        while(l < r)
        {
            int mid = l + r + 1>> 1;
            if(a[mid] <= x) l = mid ;
            else r = mid - 1;
        }
        cout << r << endl;
    }
    return 0;
}
```

### 浮点数二分

> ​	浮点数二分可以不用考虑 +1 的情况，直接取一半即可

- [数的三次方根](https://www.acwing.com/problem/content/792/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
    double x;
    cin >> x;
    double l = -1000 , r = 1000;
    while(r - l > 1e-8)
    {
        double mid = (l + r) /2;
        if(mid * mid * mid >= x) r = mid;
        else l = mid;
    }
    printf("%.6lf",l);
    return 0;
}
```

## 高精度加减乘除

> ​	为了防止出错误，一般都会加上去除前导 0 操作

### 高精度加法

​	高精度加法的主要思想是将相加的两个数存储到数组中，然后一位一位的相加，每次记录进位与后面的数相加，最后得到的数组的值就是高精度加法的值。

> - 利用字符串输入近两个长数字串，并利用 vector 来进行存储 转换后的字符串（倒序存储）
>
> - 进行两个 vector 大小的判断，从而保证选取最大的数据范围
>
> - 在 add 函数中定义出一个变量 t 用于上一次加法之后多余的十位数

- [高精度加法](https://www.acwing.com/problem/content/793/)

```c++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int>add(vector<int> a,vector<int> b)
{
    vector<int> c;
    if(a.size() < b.size()) return add(b,a);
    int t = 0;
    for(int i = 0 ; i  < a.size(); i ++)
    {
        t += a[i];
        if(i < b.size()) t += b[i];
        c.push_back(t%10);
        t /=10;
    }
    if (t) c.push_back(t);
    return c;
}
int main(void)
{
    string a,b;
    cin >> a >> b;
    vector <int>A,B;
    for (int i = a.size() - 1; i >= 0; i -- ) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i -- ) B.push_back(b[i] - '0');
    auto C = add(A, B);

    for (int i = C.size() - 1; i >= 0; i -- ) cout << C[i];
    cout << endl;
    return 0;
}
```

### 高精度减法

​	高精度减法的思路和加法类似，不过为了保证计算结果中不出现负数，我们需要先 cmp 一下保证是大数减去小数，然后每次推入数组时为了不推入负数我们也需要对结果进行取模操作，同时保留进位，下一次计算时加入其中。

> - 由于长度和大小不同，为了防止出现负号的情况，需要用 cmp 函数比较一下
>
> - 用 t 来表示上一次计算的借位
>
> - 每次会进行  (t+10) % 10 操作 防止推入负数

- [高精度减法](https://www.acwing.com/problem/content/794/)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(vector<int> a,vector <int> b)
{
    if(a.size() != b.size()) return a.size() > b.size();
    for(int i = a.size() - 1 ;i >= 0  ; i --)
    {
        if(a[i] != b[i])
            return a[i] > b[i];
    }
    return true;
}
vector<int> sub(vector<int> a,vector <int> b)
{
    vector <int> c;
    int t = 0;
    for(int i = 0 ; i < a.size() ; i ++)
    {
        t = a[i] - t;
        if(i < b.size()) t -= b[i];
        c.push_back((t+10) % 10);
        if(t < 0) t = 1;
        else t = 0;
    }
    while(c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}
int main(void)
{
    string a,b;
    cin >> a>> b;
    vector<int> A,B,C;
    for(int i = a.size() - 1 ; i >= 0 ; i --) A.push_back(a[i] - '0');
    for(int i = b.size() - 1 ; i >= 0 ; i --) B.push_back(b[i] - '0');
    if(cmp(A,B)) C = sub(A,B);
    else{
        C = sub(B,A);
        cout << "-";
    }
    for(int i = C.size() - 1 ; i >= 0 ; i --) cout << C[i]  ;
    cout << endl;
    return 0;
}
```

### 高精度乘法

​	和前面都类似，不过计算之后 t 需要除以十

> - 当 t 不为 0 的时候，需要继续进行操作
>
> - 去除前导 0 
>
> - 需要判断是否再 a 的 size 内

- [高精度乘法](https://www.acwing.com/problem/content/794/)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> mul(vector<int> a,int b)
{
    vector <int> c;
    int t = 0;
    for(int i = 0 ; i < a.size() || t; i ++)
    {
        if(i < a.size())t = t + a[i] * b;
        c.push_back(t % 10);
        t = t / 10;
    }
    while(c.size() > 1&& c.back() == 0) c.pop_back();
    return c;
}
int main(void)
{
    string a;
    int b;
    cin >> a;
    cin >> b;
    vector<int> A,C;
    for(int i = a.size() - 1 ; i >= 0 ; i --) A.push_back(a[i] - '0');
    // for(int i = b.size() - 1 ; i >= 0 ; i --) B.push_back(b[i] - '0');
    C = mul(A,b);
    for(int i = C.size() - 1 ; i >= 0 ; i--) cout << C[i];
    return 0;
}
```

​	两个大数相乘时

```c++
#include <iostream>
#include <vector>

using namespace std;

vector<int> mul(vector<int> &A, vector<int> &B) {
    vector<int> C(A.size() + B.size(), 0); // 初始化为 0，且999*99最多 5 位

    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < B.size(); j++)
            C[i + j] += A[i] * B[j];

    int t = 0;
    for (int i = 0; i < C.size(); i++) { // i = C.size() - 1时 t 一定小于 10
        t += C[i];
        C[i] = t % 10;
        t /= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back(); // 必须要去前导 0，因为最高位很可能是 0
    return C;
}

int main() {
    string a, b;
    cin >> a >> b; // a = "1222323", b = "2323423423"

    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0');

    auto C = mul(A, B);

    for (int i = C.size() - 1; i >= 0; i--)
        cout << C[i];

    return 0;
}
```

### 高精度除法

​	与前面不同的是，计算的时候从高位开始计算，因为除法的计算逻辑就是从高位开始计算，可以类比正常的除法计算过程，然后每次用余数 r 来进行计算，但是最后需要 reverse 一下，为了更好的匹配输出结果。

> 需要从高位数开始进行运算
>
> 每次都是取余操作
>
> 结束后需要 reverse 一下，可以更好匹配前面的值

```c++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> divv(vector<int> a,int b,int & r)
{
    vector<int> c;
    for(int i = a.size() - 1 ; i >= 0 ; i --)
    {
        r = r * 10 + a[i];
        c.push_back(r / b);
        r = r % b;
    }
    reverse(c.begin(),c.end());
    while(c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}
int main(void)
{
    string a;
    int b;
    cin >> a >> b;
    vector<int> A,c;
    for(int i = a.size() - 1 ; i >= 0 ; i -- ) A.push_back(a[i] - '0');
    int r = 0;
    c = divv(A,b,r);
    for(int i = c.size() - 1 ; i >= 0 ; i --) cout << c[i];
    cout << endl;
    cout << r << endl;
    return 0;
}
```

## 前缀和与差分

> ​	前缀和数组就是构建一个数组，这个数组记录了原数组前 i 位的和
>
> ​	差分数组就是构建了一个前缀和数组的逆数组，即原数组是差分数组的前缀和
>
> ​	前缀和和差分操作都需要数组下标从 1 开始，防止数组越界

### 一维前缀和

​		构建一维前缀和数组只需要再输入原数组的时候记录下前 n 项和即可，然后求区间的值的时候就是利用前缀和数组直接相减即可。

- [前缀和](https://www.acwing.com/problem/content/797/)

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 +10;
int a[N];
int s[N];
int n,m;
int main(void)
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++) cin >> a[i];
    for(int i = 1 ; i <= n ; i++) a[i] += a[i-1];
    while(m --)
    {
        int l,r;
        cin >> l >> r;
        cout << a[r] - a[l-1] << endl;
    }
    return 0;
}
```

### 二维前缀和

[题解](https://www.acwing.com/solution/content/3797/)

![image-20230104155056303](E:\SoftWare\Typora\新建文件夹\image-20230104155056303.png)

> ​	如图可以推出计算前缀和计算公式为

$$
S[i,j]=S[i,j−1]+S[i−1,j]−S[i−1,j−1]+a[i,j]
$$

> ​	而求解的公式为

$$
S[x2,y2]−S[x1−1,y2]−S[x2,y1−1]+S[x1−1,y1−1]
$$

> ​	求二维前缀和跟一维前缀和类似，我们只需要求出`s[i] = s[i-1] + a[i]`即可

- [子矩阵的和](https://www.acwing.com/problem/content/798/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1010;
int n,m,q;
int g[N][N],s[N][N];
int main()
{
    cin >> n >> m >> q;
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1 ;j <= m ; j ++)
            cin >> g[i][j];
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1; j <= m ; j ++)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j -1] + g[i][j];
    while(q --)
    {
        int x1,x2,y1,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x1 - 1][y2] - s[x2][y1-1] + s[x1 -1][y1-1] << endl;
    }
    return 0;
}
```

### 一维差分

​	构建差分数组相当于构建前缀和数组的逆数组，他的前 n 项和就是前缀和数组，可以直接用插入的方式来求出差分数组，一般用于区间的加减。

> ​	因为初始的时候数组的值默认为 0，因此 b 数组可以认为在初始情况下就是 a 数组的差分数组，所以每次 insert( i , i ,a[i]) 就相当于在 i ~ i 这个区间插入了 a[i] 这个数（insert函数就是在区间l到r上加入c）

- [差分](https://www.acwing.com/problem/content/799/)

```c++
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N],b[N];
void insert(int l,int r,int c)
{
    b[l] = b[l] + c;
    b[r+1] = b[r+1] - c;
}
int main(void)
{
    int n,m;
    cin>> n >> m;
    for(int i = 1;i<=n;i++)
        cin>>a[i];
    for(int i = 1;i<=n;i++)
        insert(i,i,a[i]);
    while(m--)
    {
        int l, r, c;
        cin >> l >> r >> c;
        insert(l,r,c);
    }
    for(int i = 1;i<=n;i++) b[i] += b[i-1];
    for(int i = 1;i<=n;i++) cout<<b[i]<<" ";
}
```

### 二维差分

- [题解](https://www.acwing.com/solution/content/27325/)

![20201217174836198](E:\SoftWare\Typora\新建文件夹\20201217174836198.png)

> ​	构建二维差分数组和构建一维差分数组道理类似，都是通过insert函数来求出差分数组之后再求前缀和数组，都可以理解为最简单的 `b[l] + c , b[r] - c`

$$
	b[x1][y1] += c,
    b[x1][y2 + 1] -= c,
    b[x2 + 1][y1] -= c,
    b[x2 + 1][y2 + 1 ] += c,
$$

- [差分矩阵](https://www.acwing.com/problem/content/description/800/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1010;
int a[N][N],b[N][N];
int n,m,k;
void insert(int x1 ,int y1 ,int x2 ,int y2 ,int c)
{
    b[x1][y1] += c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y1] -= c;
    b[x2 + 1][y2 + 1 ] += c;
}
int main()
{
    cin >> n >> m >> k;
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1; j <= m ; j ++)
            cin >> a[i][j];
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1; j <= m ; j ++)
            insert(i,j,i,j,a[i][j]);
    while (k -- )
    {
        int x1,y1,x2,y2,c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1,y1,x2,y2,c);
    }
    for(int i = 1; i <= n ; i ++)
        for(int j = 1; j <= m ; j ++)
            b[i][j] = b[i -1][j] + b[i][j-1] - b[i-1][j-1] + b[i][j];
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1; j <= m ; j ++)
            cout << b[i][j] <<" ";
        cout << endl;
    }
        
    return 0;
}
```

## 双指针算法

> ```c++
> for (int i = 0, j = 0; i < n; i ++ )
> {
>  	while (j < i && check(i, j)) j ++ ;
>  	// 具体问题的逻辑
> }
> ```
>
> 常见问题分类：
> 	(1) 对于一个序列，用两个指针维护一段区间
> 	(2) 对于两个序列，维护某种次序，比如归并排序中合并两个有序序列的操作
> 	(3) 双指针一般用于处理线性即具有单调性的操作

- [最长连续不重复子序列](https://www.acwing.com/problem/content/801/)

> ​	主要思想就是双指针，两个指针从开头出发，用一个`flag`数组维护不重复子序列，用一个`res`记录最长的值，当`flag`数组记录的值不为`0`的时候移动`j`指针

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 +10;
int q[N];
int flag[N];
int main(void)
{
    int res = 0;
    int n;
    cin >> n;
    for(int i = 0 ; i < n ; i ++) cin >> q[i];
    for(int i = 0 , j = 0 ; i < n;i++)
    {
        if( !flag[q[i]] )
        {
            flag[q[i]] ++;
            res = max (res,i - j + 1);
        }
        else{
            i --;
            flag[q[j ++]] --;
        }
    }
    cout << res << endl;
    return 0;
}
```
> ​	简化写法如下，可以使用` while `循环条件减少`if`判断次数

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N =  1e5 + 10;
int n;
int q[N];
int flag[N];
int main(void)
{
    cin >> n;
    int res = 0;
    for(int i = 0 ; i < n ; i ++) cin >> q[i];
    for(int i = 0 , j = 0; i < n ; i ++)
    {
        flag[q[i]] ++;
        while(j < i && flag[q[i]] > 1 ) flag[q[j ++ ]] --;
        res = max(res,i - j + 1);
    }
    cout << res << endl;
    return 0;
}
```

- [数组元素的目标和](https://www.acwing.com/problem/content/802/)

> ​	用暴力循环两重`for`循环会超时，所以使用双指针进行优化，`i`从`a`数组头开始，`j`从`b`数组尾部开始
>
> ​	**优化的主要部分就是 `j` 只会走一次**

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int a[N],b[N];
int main(void)
{
    int n,m,x;
    cin >> n >> m >> x;
    for(int i = 0 ; i < n ; i ++) cin >> a[i];
    for(int i = 0 ; i < m ; i ++) cin >> b[i];
    
    for(int i = 0 , j = m - 1; i < n ; i ++)
    {
        while(j >= 0 && a[i] + b[j] > x) j --;
        if(j >= 0 && a[i] + b[j] == x) cout << i << " "  << j << endl;
    }
    return 0;
}
```

- [判断子序列](https://www.acwing.com/problem/content/2818/)

> 简单双指针算法的应用，记录两个数组来进行比较
>
> 遇见了`i`和`j`值相等时就进行`i++`,但是每一回合`j`都会自加

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int a[N],b[N];
int main(void)
{
    int n,m;
    cin >> n >> m;
    for(int i = 0 ; i < n ; i ++) cin >> a[i];
    for(int i = 0 ; i < m ; i ++) cin >> b[i];
    int i = 0 , j = 0;
    while(i < n && j < m)
    {
        if(a[i] == b[j]) i ++;
        j ++;
    }
    if(i == n) cout <<"Yes" << endl;
    else cout <<"No" << endl;
    return 0;
}
```

## 位运算

主要利用`lowbit`方法来进行的判断，一个数值减去他与他负数的结果就是去掉了一个`1`

> 原码 00100100
> 反码 11011100
> 二者进行 & 操作之后的结果为
> 00000100

所以此时的值减去这个`&`的值就是减掉了一个`1`
```c++
#include <iostream>
#include <algorithm>
using namespace std;
int main(void)
{
    int n ;
    cin >> n;
    while(n --)
    {
        int x,num = 0;
        cin >> x;
        while(x) x -= x & -x, num ++;
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
```

## 离散化

​	离散化的核心思想就是将较大的下标映射到一个较小的范围，也就是将涉及的范围很大但是操作数量很少的数值映射到一个较小的范围中。

```c++
vector<int> alls; // 存储所有待离散化的值
sort(alls.begin(), alls.end()); // 将所有值排序
alls.erase(unique(alls.begin(), alls.end()), alls.end());   // 去掉重复元素
// 二分求出x对应的离散化的值
int find(int x) // 找到第一个大于等于x的位置
{
    int l = 0, r = alls.size() - 1;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1; // 映射到1, 2, ...n
}
```

> ​	关于为什么要进行排序去重，因为我们希望保留的是被操作或使用过的下标，我们只需要记录他是否被使用过即可并不需要保留多个结果，我们在使用的时候用到的都是映射过的下标，这跟他在离散过程中存储几次并没有关系。我们只要通过映射之后都可以找到对应的下标。
>
> ​	为什么用二分进行查找？因为数组经过排序之后已经是个有序数组，我们通过二分就可以查找到他的位置，然后就可以在对应的新数组中进行操作。

- [区间和](https://www.acwing.com/problem/content/804/)

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> PII;
const int N = 300010;

vector<int> alls;
vector<PII>add , query;

int n,m;
int a[N],s[N];

int find(int x)
{
    int l = 0, r = alls.size() - 1;
    while(l < r)
    {
        int mid = l +r >>1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}
int main()
{
    cin >> n >> m;
    for(int i = 0 ; i < n ; i ++)
    {
        int x,c;
        cin >> x >> c;
        alls.push_back(x);
        add.push_back({x,c});
    }
    for(int i = 0 ; i < m ; i ++)
    {
        int l,r;
        cin >> l >> r;
        query.push_back({l,r});
        
        alls.push_back(l);
        alls.push_back(r);
    }
    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());
    // 处理插入
    for (auto item : add)
    {
        int x = find(item.first);
        a[x] += item.second;
    }

    // 预处理前缀和
    for (int i = 1; i <= alls.size(); i ++ ) s[i] = s[i - 1] + a[i];

    // 处理询问
    for (auto item : query)
    {
        int l = find(item.first), r = find(item.second);
        cout << s[r] - s[l - 1] << endl;
    }
    return 0;
}
```

## 区间合并

> ```c++
> // 将所有存在交集的区间合并
> void merge(vector<PII> &segs)
> {
>     vector<PII> res;
> 
>     sort(segs.begin(), segs.end());
> 
>     int st = -2e9, ed = -2e9;
>     for (auto seg : segs)
>         if (ed < seg.first)
>         {
>             if (st != -2e9) res.push_back({st, ed});
>             st = seg.first, ed = seg.second;
>         }
>         else ed = max(ed, seg.second);
> 
>     if (st != -2e9) res.push_back({st, ed});
> 
>     segs = res;
> }
> 
> ```

- [区间合并](https://www.acwing.com/problem/content/805/)

> ​	区间合并问题可以看作贪心，我们将所有的数值按照左端点进行排序，然后遍历所有的操作，比较当前区间的终点和下一个区间的起点的关系，同时记录 cnt 数量，进而得到最后的区间个数，即结果。

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 +10;
pair<int,int> a[N];
int n;
int main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++)
    {
        int l,r;
        cin >> l >> r;
        a[i] = {l,r};
    }
    sort(a + 1 ,a + 1 + n);
    int cnt = n;
    for(int i = 1 ; i < n ; i ++)
    {
        if(a[i].second >= a[i + 1].first)
        {
            cnt --;
            a[i + 1].first = a[i].first;
            a[i + 1].second = max(a[i + 1].second , a[i].second);
        }
    }
    cout << cnt << endl;
    return 0;
}
```


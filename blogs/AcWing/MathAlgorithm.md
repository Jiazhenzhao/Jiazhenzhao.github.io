# 数论

- [模板](https://www.acwing.com/blog/content/406/)

## 质数

### 试除法判定质数

- [试除法判定质数](https://www.acwing.com/problem/content/868/)

> ​	直接判断`2-n-1`是否存在能被`n`整除的数即可，如果存在则不是质数
>
> ​	这里做的优化是因为，当一个数能被 `d`整除的时候那`n/d`一定也能被整除，所以我们只需要枚举到`n/i`即可，因为大于`n/i`的数如果可以被整除，一定已经在之前被判断过了

```c++
bool is_prime(int x)
{
    if (x < 2) return false;
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
            return false;
    return true;
}
```

### 分解质因数

> ​	分解质因数用到了算数基本定理，也就是每个数都可以分解成质数指数相乘的积
>
> ​	关于最后的 `x>1`是因为每个数最多只有一个大于`sqrt(n)`的质因子，当最后剩下的数值大于一的时候那他就是最后的一个质因子并且指数为一

$$
算数基本定理：N=p1^{a1}∗p2^{a2}…∗pn^{an}
$$

- [分解质因数](https://www.acwing.com/problem/content/869/)

```c++
void divide(int x)
{
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
        {
            int s = 0;
            while (x % i == 0) x /= i, s ++ ;
            cout << i << ' ' << s << endl;
        }
    if (x > 1) cout << x << ' ' << 1 << endl;
    cout << endl;
}
```

### 筛质数

- [筛质数](https://www.acwing.com/problem/content/870/)

- 朴素筛法

> ​	朴素筛法是每次用遍历到的所有数，不论是合数还是质数，都会筛掉后面的数，时间复杂度是`O(nlog n)`级别的

```c++
void get_primes(int x)
{
    for(int i = 2 ; i <= x ;i ++)
    {
        if(!st[i]) primes[cnt ++] = i;
        for(int j = i ; j <= n ; j += i)	st[j] = true;
    }
}
```

- 埃式筛法

> ​	埃式筛法和朴素筛法相比改进的是每次只用质数进行筛数，因为所有的合数都能被一个质数筛掉，所以能被这个质数筛掉的合数筛掉的合数也一定能被这个质数筛掉

```c++
void get_primes(int x)
{
    for(int i = 2 ; i <= x ; i ++)
    {
          if(!st[i])
          {
              primes[cnt ++] = i;
              for(int j = i ; j <= n ; j += i)	st[j] = true;
          }
	}
}
```

- 线性筛法

> ​	线性筛法是保证了每个合数都只会被他的最小质因子筛掉，因为埃式筛法也会存在一个合数被多个质数筛的情况的出现，这里 for 循环的条件为 `<= n/i` 的原因是因为，每个数都只会被最小质因子筛掉，而当大于 `n/i` 的时候，已经不能保证是最小质因子来筛了
>
> ​	关于为什么能保证每次都是最小质因子来筛？当`i%primes[j] == 0` 的时候，我们的枚举是从最小质因子开始的，所以可以保证`primes[j]`是`i`的最小质因子，所以`primes[j]`也是`primes[j] * i `的最小质因子；当`i%primes[j] != 0`的时候，也因为我们是从小到大枚举所有的质因子，所以`primes[j]`同样是`primes[j] * i`的最小质因子；同时，假如一个合数的最小质因子是`primes[j]`那么当我们`i`枚举到`x/primes[j]`的时候，这个合数就会被筛掉
>
> ​	关于我们为什么能保证每个数只被筛一次？因为每个合数都有一个最小质因子，我们只会用他的最小质因子来进行筛选。

```c++
void get_primes(int x)
{
    for(int i = 2;  i <= x; i ++)
    {
        if(!st[i]) primes[cnt ++] = i;
        for(int j = 0 ; primes[j] <= n / i ; j ++)
        {
        	st[primes[j] * i] = true;
            if(i % primes[j] == 0); break;
        }
	}
}
```

## 约数

### 试除法求约数

> ​	遍历所有的数，因为`i和x/i`对应，所以我们只需要枚举`x/i`次即可

- [试除法求约数](https://www.acwing.com/problem/content/871/)

```c++
vector<int> get_divisors(int x)
{
    vector<int> res;
    for (int i = 1; i <= x / i; i ++ )
        if (x % i == 0)
        {
            res.push_back(i);
            if (i != x / i) res.push_back(x / i);
        }
    sort(res.begin(), res.end());
    return res;
}
```

### 求约数个数

> 如果 N = p1^c1 * p2^c2 * ... *pk^ck
> 约数个数： (c1 + 1) * (c2 + 1) * ... * (ck + 1)
> 约数之和： (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)

> ​	由算数基本定理可以得到，每一个数都可以分解为质数的指数相乘的式子，因此我们可以考虑将所有的质数的因子记录下来，最后所有因子的自由组合就是约数的个数

- [约数个数](https://www.acwing.com/problem/content/872/)

```c++
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;
const int mod = 1e9 + 7;
int n;
unordered_map<int,int>primes;
void get(int x)
{
	
	for(int i = 2; i <= x/ i; i++)
	{
		if(x % i == 0)
		{
			while(x % i == 0) primes[i]++,x/=i;
		}
	}
	if(x > 1) primes[x] ++;
}
int main(void)
{
	cin >> n;
	while(n --)
	{
		int x;
		cin >> x;
		get(x);

	}
	long long res = 1;
	for(auto prime : primes) res = (long long ) res * (prime.second + 1)  % mod;
	cout << res << endl;
	return 0;
} 
```

### 求约数之和

- [约数之和](https://www.acwing.com/problem/content/873/)

> ​	这个我们可以进行一个展开

$$
(p_1^0 + p_1^1 + p_1^2 + ...+p_1^{a_1})*...*(p_k^0 + p_k^1 + p_k^2 + ...+p_k^{a_k})
$$

> ​	和下面这个相等

$$
(p1^0*p2^0*...*pk^0)+(p1^1*p2^1*...*pk^1)+...+(p1^k*p2^k*...*pk^k)
$$

> ​	这就求出了约数之和的结果，并且这样的求法并不只是针对多数相乘的结果，单个的数字也可以进行求解

```c++
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 1e9 +7;
unordered_map<int,int> primes;
void get(int x)
{
    for(int i = 2;i <= x/i;i++)
    {
        while(x%i == 0)
        {
            x = x / i;
            primes[i]++;
        }
    }
    if(x > 1) primes[x] ++;
}
int main(void)
{
    int n;
    cin >> n;
    while(n--)
    {
        int x;
        cin >> x;
        get(x);
    }
    LL res = 1;
    for(auto prime : primes)
    {
        LL a = prime.first;
        LL b = prime.second;
        LL t = 1; 
        while(b -- ) t = (t * a + 1) % mod; // Important;;
        res = res * t %mod;
    }
    cout << res << endl;
    return 0;
}
```

### 最大公约数

​	如果一个`d`可以整除`a`和`b`那么由裴属定理就可以得到，`d` 能整除 `a+b` ，也能整除 `ax+by`，又因为 `a%b = a - b * c `,此时 `x = 1 , y = -c` 所以我们就可得到，`d` 能整除 `a和b` ，同时也能整除 `b 和 a%b`，由此我们就得到了欧几里得定律

- [最大公约数](https://www.acwing.com/problem/content/874/)

```c++
int gcd(int a,int b)
{
    return b ? gcd(b,a%b) : a;
}
```

- 最小公倍数  `a * b / gcd(a,b)`

```c++
int lcm(int a,int b)
{
    return a * b / gcd(a,b);
}
```

## 欧拉函数

> ​	欧拉函数球的是从 1~N 中与N互质的个数，计算公式为

$$
N*\frac{p^1-1}{p_1}*\frac{p^2-1}{p_2}*...*\frac{p^m-1}{p_m}
$$

> ​	从图中我们可以观察到我们只需要利用算数基本定理分解数字的时候计算即可，同时这里可以先计算除法再计算乘法，防止数字溢出

- [欧拉函数](https://www.acwing.com/problem/content/875/)

```c++
LL oula(int x)
{
    LL res = x;
    for(int i = 2;i <= x/i;i++)
    {
        if(x% i == 0)
        {
            while(x % i == 0)
            {
                x = x/i;
            }
            res =  (LL) res / i * (i-1);
        }
    }
    if(x > 1) res = (LL) res / x *(x-1);
    return res;
}
```

- [筛法求欧拉函数](https://www.acwing.com/problem/content/876/)

​	我们可以在求线性筛质数的时候筛出欧拉函数

​	当它是质数的时候那和他互质的个数就是 p-1 个

​	当它不是质数的时候，并且`i % primes[j] == 0`的时候，我们可以知道此时`primes[j]`是i的最小质因子，所以再求 i 的欧拉函数已经计算过`primes[j]`了，因此我们可以得到
$$
oula(i*primes[j])=oula(i)*primes[j]
$$
​	当`i%primes[j] != 0`的时候，我们也知道`primes[j]`是`i*primes[j]`的最小质因子，但是还没有计算过，所以
$$
oula(i*primes[j])=oula(i)*primes[j]*\frac{primes[j] - 1}{primes[j]}
$$

$$
==>oula(i*primes[j])=oula(i)*(primes[j]-1)
$$

```c++
int primes[N], cnt;     // primes[]存储所有素数
int euler[N];           // 存储每个数的欧拉函数
bool st[N];         // st[x]存储x是否被筛掉


void get_eulers(int n)
{
    euler[1] = 1;
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i])
        {
            primes[cnt ++ ] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0)
            {
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
}
```

## 快速幂

> ​	快速幂用来求一个`数a的b次方mod p`的结果，我们可以考虑将 b 次幂转化成二进制数，每次进行相乘和取模操作

- [快速幂](https://www.acwing.com/problem/content/description/877/)

```c++
求 m^k mod p，时间复杂度 O(logk)。

int kmp(int m, int k, int p)
{
    int res = 1 % p, t = m;
    while (k)
    {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
```

- [快速幂求逆元](https://www.acwing.com/problem/content/878/)

> ​	因为题目给出了 p 为质数，因此我们只需要考虑 `b^(m-2)` 即可，也就是直接求快速幂即可，但是需要做出一个特判，因为乘法逆元要求了必须是互质的两个数，其中 p 已经为质数了，所以只需要保证 a 不是 p 的倍数即可
>
> ​	互质：两个数的最大公因数为 1

```c++
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
LL qmi(int a,int k,int p)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = (LL)res * a %p;
        a = (LL)a*a % p;
        k = k >> 1;
    }
    return res;
}
int main(void)
{
    int n;
    cin >> n;
    while(n--)
    {
        int a,p;
        cin >> a >> p;
        LL res = qmi(a,p-2,p);
        if(a % p == 0) cout << "impossible" << endl;
        else cout << res << endl;
    }
    return 0;
}
```

## 扩展欧几里得算法

- [扩展欧几里得算法](https://www.acwing.com/problem/content/879/)

$$
ax+by=gcd(a,b)
$$

$$
ax+b=gcd(a,b)=gcd(b,a\%b)
$$

$$
bx’ +a\%by'=gcd(b,a\%b)
$$

$$
a\%b=(a - [a/b] * b) =>bx'+ay'-[a/b]*b*y'=>ay'+b(x'-[a/b]*b)=gcd(a,b)
$$

> ​	综上所述我们每次只需要在传统欧几里得算法的时候，将 `x=y' y=x'-[a/b]*y'`即可

```c++
// 求x, y，使得ax + by = gcd(a, b)
int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a/b) * x;
    return d;
}
```

- [线性同余方程](https://www.acwing.com/problem/content/880/)

$$
所求为：ax≡b(mod m) ==>ax=m(-y)+b 
$$

$$
ax + my = b
$$

有解条件为 `gcd(a,m)|b`,然后用扩展欧几里得求解即可

```c++
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n -- )
    {
        int a, b, m;
        scanf("%d%d%d", &a, &b, &m);

        int x, y;
        int d = exgcd(a, m, x, y);
        if (b % d) puts("impossible");
        else printf("%d\n", (LL)b / d * x % m);
    }

    return 0;
}
```

## 组合数求解

> ​	快速幂求逆元就代表着

$$
b^{-1} ==> 快速幂求逆元，也就是倒数
$$

### 组合数求解Ⅰ

> ​	对于数据范围不太的的时候我们可以直接递推求出所有的Cab，关于公式的解释，我们可以假设有一个数区部取，当它不取的时候就相当于我们从剩下的 `a-1`中选取`b-1`个；当选取这个数的时候就相当于从`a`中选取剩下的`b-1`个数值
>
> ​	**对于询问次数较多，并且给定 ab 不大的值，**可以利用递推进行**预处理**，处理出 从 C11 到 Cab 的值       n^2

$$
C_{a}^{b} = C_{a-1}^{b-1}+C_{a}^{b-1}
$$

- [求组合数 I](https://www.acwing.com/problem/content/887/)

```c++
// c[a][b] 表示从a个苹果中选b个的方案数
for (int i = 0; i < N; i ++ )
    for (int j = 0; j <= i; j ++ )
        if (!j) c[i][j] = 1;
        else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
```

### 组合数求解Ⅱ

> ​	**对于询问次数不算特别多，并且给定 ab 的值较大的值**，可以利用组合数的逆推（上下阶乘） 方式，**预处理**出来 分子的阶乘和分母的阶乘的逆元，然后直接利用公式输出 res 即可	  nlogn

$$
C_a^b=\frac{a!}{b!*(a-b)!}
$$

- [求组合数 II](https://www.acwing.com/problem/content/888/)

```c++
首先预处理出所有阶乘取模的余数fact[N]，以及所有阶乘取模的逆元infact[N]
如果取模的数是质数，可以用费马小定理求逆元
int qmi(int a, int k, int p)    // 快速幂模板
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

// 预处理阶乘的余数和阶乘逆元的余数
fact[0] = infact[0] = 1;
for (int i = 1; i < N; i ++ )
{
    fact[i] = (LL)fact[i - 1] * i % mod;
    infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
}
```

### 组合数求解Ⅲ

​	**对于询问次数不多，给出 ab 的值特别大的值**，可以利用 `lucas` 定律来求解
$$
C_a^b=C_{a\%p}^{b\%p}*C_{a/p}^{b/p}(mod P)
$$
​	这里需要注意的点主要是 返回 `lucas` 定律的值必须时 `lucas` `a/p,b/p`因为 可能再 ab 除以 p 之后的到的值仍然大于大于p，这样的话求 Cab 可能会出现错误；其中定理计算公式为
$$
C_a^b=\frac{a!}{b!(a-b)!}=\frac{(a-b+1)*(a-b+2)*...a}{b!}
$$


- [求组合数 III](https://www.acwing.com/problem/content/889/)

```c++
//若p是质数，则对于任意整数 1 <= m <= n，有：
 //C(n, m) = C(n % p, m % p) * C(n / p, m / p) (mod p)

int qmi(int a, int k, int p)  // 快速幂模板
{
    int res = 1 % p;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

int C(int a, int b, int p)  // 通过定理求组合数C(a, b)
{
    if (a < b) return 0;

    LL x = 1, y = 1;  // x是分子，y是分母
    for (int i = a, j = 1; j <= b; i --, j ++ )
    {
        x = (LL)x * i % p;
        y = (LL) y * j % p;
    }

    return x * (LL)qmi(y, p - 2, p) % p;
}

int lucas(LL a, LL b, int p)
{
    if (a < p && b < p) return C(a, b, p);
    return (LL)C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}
```

### 组合数求解Ⅳ

- [求组合数 IV](https://www.acwing.com/problem/content/890/)

​	**对于所求的值不进行取模的运算**，分为三步走，第一步用质数筛法，筛出前n个数中的质数，第二步，利用除法求出每个数质因数的倍数的个数，然后利用高精度乘法求出最终p的结果

​	简单来说就是因为操作的数值过大，我们可以考虑使用质数的指数运算来进行简化
$$
C_a^b=\frac{a!}{b!(a-b)!}
$$
​	因此我们第一步先筛出所有的质数，然后求出`a!`和`b!`以及`(a-b)!`的质数数量，最后再利用高精度乘法求出最终结果
$$
且a!中出现质因子p的次数为:[a/p]+[a/p^2]+....+[a/p^n]
$$
​	一个数整除另外一个数得到的结果就是这个数中所有大于被除数的个数,因为任何一个数都可以理解为数字的相加组成的,当一个数除另外一个数得到的数可以看作被除数的倍数,因此原数字可以看作被除数的相加,也就代表了有几个数可以整除它.

​	所以我们遍历所有的质因子的平方直到质因子的平方大于a结束

> ​	当12除2的时候结果为6,所以12是2的6倍,也就是代表了从1到12中一共有6个数是2的倍数,也就是能整除2,所以a/p可以求出a!中是p的倍数的个数

```c++
//当我们需要求出组合数的真实值，而非对某个数的余数时，分解质因数的方式比较好用：
//    1. 筛法求出范围内的所有质数
//    2. 通过 C(a, b) = a! / b! / (a - b)! 这个公式求出每个质因子的次数。 n! 中p的次数是 n / p + n / p^2 + n / p^3 + 
//    3. 用高精度乘法将所有质因子相乘

int primes[N], cnt;     // 存储所有质数
int sum[N];     // 存储每个质数的次数
bool st[N];     // 存储每个数是否已被筛掉


void get_primes(int n)      // 线性筛法求素数
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int get(int n, int p)       // 求n！中的次数
{
    int res = 0;
    while (n)
    {
        res += n / p;
        n /= p;
    }
    return res;
}

vector<int> mul(vector<int> a, int b)       // 高精度乘低精度模板
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }

    while (t)
    {
        c.push_back(t % 10);
        t /= 10;
    }

    return c;
}

get_primes(a);  // 预处理范围内的所有质数

for (int i = 0; i < cnt; i ++ )     // 求每个质因数的次数
{
    int p = primes[i];
    sum[i] = get(a, p) - get(b, p) - get(a - b, p);
}

vector<int> res;
res.push_back(1);

for (int i = 0; i < cnt; i ++ )     // 用高精度乘法将所有质因子相乘
    for (int j = 0; j < sum[i]; j ++ )
        res = mul(res, primes[i]);
```

- [满足条件的01序列](https://www.acwing.com/problem/content/891/)

> ​	给定n个0和n个1，它们按照某种顺序排成长度为2n的序列，满足任意前缀中0的个数都不少于1的个数的序列的数量为： Cat(n) = C(2n, n) / (n + 1)

```c++
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, mod = 1e9 + 7;


int qmi(int a, int k, int p)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}


int main()
{
    int n;
    cin >> n;

    int a = n * 2, b = n;
    int res = 1;
    for (int i = a; i > a - b; i -- ) res = (LL)res * i % mod;

    for (int i = 1; i <= b; i ++ ) res = (LL)res * qmi(i, mod - 2, mod) % mod;

    res = (LL)res * qmi(n + 1, mod - 2, mod) % mod;

    cout << res << endl;

    return 0;
}
```

![35805_f4228ae4c7-组合数](E:\SoftWare\Typora\新建文件夹\35805_f4228ae4c7-组合数-16730050350041.png)

## 容斥原理

## 博弈论

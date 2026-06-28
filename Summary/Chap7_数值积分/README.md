## 知识点总结
本章内容对应的[PPT1](../../PPT/第7章%20数值积分-第一次课-2026.pdf),[PPT2](../../PPT/第7章%20数值积分-第二次课-2026.pdf)，对应的[代码](../../Code/数值积分方法.cpp)

快速索引
- [知识点总结](#知识点总结)
- [Newton-Cotes公式](#newton-cotes公式)
  - [代数精度](#代数精度)
  - [余项分析](#余项分析)
- [复化求积公式](#复化求积公式)
  - [复化梯形公式](#复化梯形公式)
  - [Romberg求积方法](#romberg求积方法)
- [Gauss求积公式](#gauss求积公式)
  - [代权函数的高斯求积公式](#代权函数的高斯求积公式)

数值积分要干什么
一句话——对函数取点然后按照积分定义以面积代积分。

**插值型求积公式**
以Lagrange差值多项式代替原函数进行积分

$$L_n(x)=\sum_{i=0}^nl_i(x)f(x_i)$$

于是有

$$\int_a^bf(x)\mathrm{d}x=\sum_{j=0}^n\left[\int_a^b\sum_{i=0}^nl_i(x)\mathrm{d}x\right]f(x_i)+\int_a^bR(x)\mathrm{d}x$$

取

$$f(x)\approx\sum_{j=0}^n\left[\int_a^b\sum_{i=0}^nl_i(x)\mathrm{d}x\right]f(x_i)=\sum_{i=0}^nA_if(x_i)$$

称为插值型求积公式

## Newton-Cotes公式
和Newton-Cotes法一样，取等距节点 $x_i=a+ih,h=\dfrac{b-a}{n},i=0,1,2,\dots,n$

则此时的求积系数为

$$A_i=\int_a^b\prod_{j=0,j\neq i}^n\dfrac{x-x_j}{x_i-x_j}\mathrm{d}x=h\left(\prod_{j=0,j\neq i}^n\dfrac{1}{k-j}\right)\int_0^n\prod_{j=0,j\neq i}^n(t-j)\mathrm{d}t=\dfrac{(b-a)(-1)^{n-j}}{nj!(n-j)!}\int_0^n\prod_{j=0,j\neq i}^n(t-j)\mathrm{d}t$$

定义Cotes系数

$$C_i^{(n)}=\dfrac{(-1)^{n-i}}{ni!(n-i)!}\int_0^n\prod_{j=0,j\neq i}^n(t-j)\mathrm{d}t,\enspace i=0,1,2,\dots,n$$

则求积公式变为

$$\int_a^bf(x)\mathrm{d}x\approx(b-a)\sum_{j=0}^nC_j^{(n)}f(x_j)$$

称为 $n$ 阶闭型Newton-Cotes求积公式

实际上我们常用的 $n$ 只有 $1,2,3,4$

|公式名称| $n$ | $C^{(n)}_0$ | $C^{(n)}_1$ | $C^{(n)}_2$ | $C^{(n)}_3$ | $C^{(n)}_4$ |
|---|---|---|---|---|---|---|
|梯形公式| $1$ | $\dfrac{1}{2}$ | $\dfrac{1}{2}$ ||||
|Simpson公式| $2$ | $\dfrac{1}{6}$ | $\dfrac{4}{6}$ | $\dfrac{1}{6}$ |||
|Newton公式| $3$ | $\dfrac{1}{8}$ | $\dfrac{3}{8}$ | $\dfrac{3}{8}$ | $\dfrac{1}{8}$ ||
|Cotes公式| $4$ | $\dfrac{7}{90}$ | $\dfrac{32}{90}$ | $\dfrac{12}{90}$ | $\dfrac{32}{90}$ | $\dfrac{7}{90}$ |

代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中已经给出了常用的Cotes系数（工程上 $n$ 一般不会超过 $8$ ），其中 `C[i][j]` 对应于 $C^{(i)}_j$

```cpp
const vector<vector<double>> C = {
    {},
    {1./2, 1./2},
    {1./6, 4./6, 1./6},
    {1./8, 3./8, 3./8, 1./8},
    {7./90, 32./90, 12./90, 32./90, 7./90},
    {19./288, 75./288, 50./288, 50./288, 75./288, 19./288},
    {41./840, 216./840, 27./840, 272./840, 27./840, 216./840, 41./840},
    {751./17280, 3577./17280, 1323./17280, 2989./17280, 2989./17280, 1323./17280, 3577./17280, 751./17280},
    {989./28350, 5888./28350, -928./28350, 10496./28350, -4540./28350, 10496./28350, -928./28350, 5888./28350, 989./28350}
};
```

此外，代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中的`Newton_Cotes()`函数还实现了一般情况下的Newton-Cotes公式，其中参数 `double n` 为Cotes公式的阶数。

```cpp
double Newton_Cotes(double (*f)(double), double a, double b, double n)
{
    double res = 0, h = (b - a) / n;
    for(int i = 0; i <= n; i ++) res += C[n][i] * f(a + i * h);
    res *= (b - a);
    return res;
}
```

### 代数精度
定义：对于一个数值求积公式，如果对于 $m$ 阶多项式精确成立；对于 $m+1$ 阶多项式不精确成立，则这个求积公式具有 $m$ 阶代数精度。

**Newton-Cotes公式代数精度定理：**  $n$ 阶 Newton-Cotes公式至少具有 $n$ 阶代数精度，当 $n$ 为偶数时则具有 $n+1$ 阶代数精度

### 余项分析
由Lagrange差值公式的余项

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n+1)}(\xi)\prod_{i=0}^n(x-x_i)$$

可以得

$$R(f)=\dfrac{h^{n+2}}{(n+1)!}\int_0^nf^{(n+1)}(\xi)\left[\prod_{j=0}^n(t-j)\right]\mathrm{d}t$$

直接记结论
| $n=1$ 时（梯形公式）| $n=2$ 时（Simpson公式）| $n=4$ （Cotes公式）|
|---|---|---|
| $R(f)=-\dfrac{(b-a)^3}{12}f^{(2)}(\xi),\space\xi\in(a,b)$ | $R(f)=-\dfrac{(b-a)^5}{2880}f^{(4)}(\xi),\space\xi\in(a,b)$ | $R(f)=-\dfrac{(b-a)^7}{1935360}f^{(6)}(\xi),\space\xi\in(a,b)$ |

## 复化求积公式
**核心思想：** 细分区间减小误差

### 复化梯形公式
对每个小区间使用梯形公式，得

$$\int_a^bf(x)\mathrm{d}x\approx\dfrac{h}{2}\left[f(a)+2\sum_{i=1}^{n-1}f(x_i)+f(b)\right]=T_n,\enspace h = \dfrac{b - a}{n}$$

余项

$$R(f)=-\dfrac{h^2}{12}(b-a)f^{''}(\xi),\space\xi\in(a,b)$$

实际上，我们没有必要记这个公式，直接对每个区间使用Simpson公式和Cotes公式再求和，即可得到复化Simpson公式和复化Cotes公式。

### Romberg求积方法
从复化梯形公式可以看出来，当我们希望增加节点时，不必一个一个增加，直接在相邻两个节点中间增加一个新的节点即可。

即，插入前

$$T_n=\sum_{k=0}^{n-1}h\dfrac{f(x_k)+f(x_{k+1})}{2}$$

插入后

$$T_{2n}=\sum_{k=0}^{n-1}\dfrac{h}{2}\left[\dfrac{f(x_k)+f(x_{k+\frac{1}{2}})}{2}+\dfrac{f(x_{k+\frac{1}{2}})+f(x_{k+1})}{2}\right]=\dfrac{T_n}{2}+\dfrac{h}{2}\sum_{k=0}^{n-1}f(x_{k+\frac{1}{2}})$$

这样就可以通过迭代法计算复化梯形公式。代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中的`comp_ti`函数实现了复化梯形求积公式。

```cpp
double comp_ti(double (*f)(double), double a, double b)
{
    double Tk, Tkk, e = 1, h = b - a;
    Tk = h / 2 * (f(a) + f(b));
    int k = 2;
    while (e > EPS)
    {
        Tkk = Tk / 2;
        h /= 2;
        for(int i = 1; i <= k / 2; i ++) Tkk += h * f(a + (2 * i - 1) * h);
        e = fabs(Tkk - Tk);
        cout << "k=" <<  k << " Tk=" << Tk << " e=" << e << endl;
        Tk = Tkk;
        k *= 2;
    }
    return Tk;
}
```

然后再通过复化梯形积分 $\lbrace T_1, T_2, T_4, T_8, \dots\rbrace$ 计算复化Simpson积分

$$S_{n} = \dfrac{4}{4-1}T_{2n}-\dfrac{1}{4-1}T_n$$

再计算复化Cotes公式

$$C_{n} = \dfrac{4^2}{4^2-1}S_{2n}-\dfrac{1}{4^2-1}S_n$$

再计算复化Romberg公式

$$R_{n} = \dfrac{4^3}{4^3-1}C_{2n}-\dfrac{1}{4^3-1}C_n$$

这样做有什么用呢，当然会在比较少的迭代次数内达到比较高的精度。

代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中的`Romberg`函数实现了Romnerg方法，其中的参数 `int r` 为需要计算到的 $R_{2^r}$。
```cpp
void Romberg(double (*f)(double), double a, double b, int r)
{
    vector<vector<double>> tscr;
    int k = r + 5;
    tscr.push_back(vector<double> (k, 0));
    double h = b - a;
    tscr[0][1] = h / 2 * (f(a) + f(b));
    for(int i = 2; i < k; i ++)
    {
        h /= 2;
        tscr[0][i] = tscr[0][i - 1] / 2;
        for(int j = 1; j <= ((1 << (i - 1)) / 2); j ++) tscr[0][i] += h * f(a + h * (2 * j - 1));
    }

    for(int i = 1; i < 4; i ++)
    {
        k -= 1;
        tscr.push_back(vector<double> (k, 0));
        for(int j = 1; j < k; j ++) tscr[i][j] = (tscr[i - 1][j + 1] * pow(4, i) - tscr[i - 1][j]) / (pow(4, i) - 1);
    }

    vector<char> name = {'T', 'S', 'C', 'R'};
    for(int i = 0; i < 4; i ++)
    {
        int tmp = r + 3 - i;
        for(int j = 1; j <= tmp; j ++) printf("%c%d=%lf ", name[i], 1 << j, tscr[i][j]);
        cout << endl;
    }
    return;
}
```

## Gauss求积公式
之前讨论的插值型积分公式，都是以等距节点为前提，很容易想到如果我们改变积分节点，即将公式 $\int_a^bf(x)=\sum_{i=0}^nA_if(x_i)$ 中 $A_i,x_i$ 均设为可变参数则会提高计算精度。

积分公式

$$\int_a^bf(x)\mathrm{d}x\approx\sum_{k=0}^nA_kf(x_k)$$

我们使之有 $2n+1$ 阶积分精度，可得到下面的方程组：

$$\begin{cases}
    \sum_{k=0}^nA_k=b-a\\
    \sum_{k=0}^nA_kx_k=\dfrac{1}{2}\left(b^2-a^2\right)\\
    \sum_{k=0}^nA_kx_k^2=\dfrac{1}{4}\left(b^3-a^3\right)\\
    \vdots\\
    \sum_{k=0}^nA_kx_k^{2n+1}=\dfrac{1}{2n+2}\left(b^{2n+2}-a^{2n+2}\right)\\
\end{cases}$$

求解以上非线性方程组，求得高斯点 $\left(x_0,x_1,\dots,x_n\right)$ 以及高斯系数 $\left(A_0,A_1,\dots,A_n\right)$

对于一般的情况我们通常计算在区间 $[0,1]$ 上的高斯点和高斯系数，而对于其他积分区间，进行变量代换转换到对应区间上即可。

则问题化为求解非线性方程组

$$F(X)=\begin{bmatrix}
    \sum_{k=0}^nA_k-1\\
    \sum_{k=0}^nA_kx_k-\dfrac{1}{2}\\
    \sum_{k=0}^nA_kx_k^2-\dfrac{1}{3}\\
    \vdots\\
    \sum_{k=0}^nA_kx_k^{2n+1}-\dfrac{1}{2n+2}\\
\end{bmatrix}=0$$

其中

$$X = \left[A_0,A_1,\dots,A_n,x_0,x_1,\dots,x_n\right]^T$$

$$\nabla F=\begin{bmatrix}
    1 & 1 & \dots & 1& 0 & 0 & \dots & 0 \\
    x_0 & x_1 & \dots & x_n & A_0 & A_1 & \dots & A_n \\
    x_0^2 & x_1^2 & \dots & x_n^2 & 2A_0x_0 & 2A_1x_1 & \dots & 2A_nx_n \\
    \vdots & \vdots & \ddots & \vdots & \vdots & \vdots & \ddots & \vdots \\
    x_0^{2n+1} & x_1^{2n+1} & \dots & x_n^{2n+1} & (2n+1)A_0x_0^{2n} & A_1x_1^{2n} & \dots & A_nx_n^{2n} \\
\end{bmatrix}$$

然后，用牛顿法解方程组，迭代方程为

$$\Delta x^{(k)}=-\left[\nabla F\left(x^{(k)}\right)\right]^{-1}F\left(x^{(k)}\right)$$

### 代权函数的高斯求积公式
考察积分

$$\int_a^b\rho(x)f(x)\mathrm{d}x$$

我们称 $\rho(x)$ 为权函数，如果对于 $f(x)$ 次数不超过 $2n+1$ 的多项式都有以下式子准确成立

$$\int_a^b\rho(x)f(x)\mathrm{d}x=\sum_{k=0}^nA_kf(x_k)$$

则称为高斯型积分，不难发现 $\rho(x)\equiv1$ 时纪委普通积分。

代码[Guass求积公式.py](../../Code/Guass求积公式.py)中实现了一般的带权函数高斯求积公式

其中给出了两种计算的 $\int_0^1\rho(x)f(x)$ 准确值的方式

一是当 $\rho(x)$ 是多项式函数时，直接使用解析解，其中参数 `r:float` 表示 $\rho(x)=x^r$。
```python
def CulInt(r: float, n: int) -> float:
    return 1 / (n + r + 1)
```

二是当 $\rho(x)$ 不是多项式函数时，依靠数值Cotes公式来计算

```python
def rho(x: float) -> float:
    return 1.

def culInt(n: int) -> float:
    res, step = 0, 1e-4
    i = 0
    c = [7./90, 32./90, 12./90, 32./90, 7./90]
    while i < (1 - 0) / step:
        a, b = i * step, (i + 1) * step
        s = (b - a) / 4
        for j in range(5):
            p = a + j * s
            res += (rho(p) * (p ** n) * c[j]) * step
        i += 1
    return res
```

再计算时需要你手动调整代码来实现。
```python
def F(x: list[float]) -> list[float]:
    res = [0.] * (2 * N + 2)
    for i in range(2 * N + 2):
        for j in range(N + 1):
            res[i] += x[j] * x[j + N + 1] ** i
        # res[i] -= CulInt(R, i) # 解析解
        res[i] -= culInt(i) # 数值解
    return res
```
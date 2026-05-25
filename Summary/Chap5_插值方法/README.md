本章内容对应的[PPT1](../../PPT/第5章%20插值方法与计算实验-第一次课.pdf) , [PPT2](../../PPT/第5章%20插值方法与计算实验-第二次课-带计算实验.pdf)

## 知识点总结

快速索引
- [知识点总结](#知识点总结)
- [Lagrange插值](#lagrange插值)
  - [差值公式](#差值公式)
  - [差值余项](#差值余项)
- [Newton插值](#newton插值)
  - [差商](#差商)
  - [Newton插值公式](#newton插值公式)
- [等距节点插值](#等距节点插值)
  - [差分](#差分)
  - [等距节点插值公式](#等距节点插值公式)
    - [前插公式](#前插公式)
    - [后插公式](#后插公式)
  - [代码实现](#代码实现)
- [分段低次插值](#分段低次插值)
  - [分段线性插值](#分段线性插值)
  - [分段二次插值](#分段二次插值)
  - [插值余项](#插值余项)
- [Hermite插值](#hermite插值)
  - [插值公式（省流）](#插值公式省流)
  - [差值余项](#差值余项-1)
- [样条插值](#样条插值)
  - [三次样条插值](#三次样条插值)
    - [三类边界条件](#三类边界条件)

先弄清楚插值法是干什么

对 $y = f(x)$ 已知在 $a \leq x_0 < x_1 \dots < x_n \leq b$ 上的值为 $y_0, y_1,\dots,y_n$。插值法就是要找函数 $\phi(x)$ 来逼近 $f(x)$ 。要求 $\phi(x_i)=y_i , (i=0,1,2,\dots,n)$成立。

## Lagrange插值
### 差值公式
多项式来拟合函数，目标

$$P_n(x)=l_0(x)y_0+l_1(x)y_1+\dots+l_n(x)y_n=\sum_{k=0}^nl_k(x)y_k$$

其中 $l_i(x),(i=0,1,2,\dots,n)$ 应满足如下良好性质

$$l_i(x_j)=\delta_{ij}=\begin{cases}
    1 & i = j \\
    0 & i \neq j
\end{cases} (i,j = 0,1,2,\dots,n)$$

故我们找到的 Lagrange 差值公式为

$$P_n(x)=\sum_{i=0}^n\left(\prod_{j=0,j\neq i}^n\dfrac{x-x_j}{x_i-x_j}\right)y_i$$

代码[插值方法.cpp](../../Code/插值方法.cpp)中的 `Lagrange` 函数实现了 Lagrange 插值法。已知的插值节点定义为全局变量、输入 `double x` 为需要拟合的节点

```cpp
double Lagrange(double x)
{
    double res = 0;
    for(int i = 0; i <= N; i ++)
    {
        double tmp = Y[i];
        for(int j = 0; j <= N; j ++)
        {
            if(j == i) continue;
            tmp *= (x - X[j]) / (X[i] - X[j]);
        }
        res += tmp;
    }
    return res;
}
```

### 差值余项

直接记结论， $f(x)$ 的差值函数 $P_n(x)$ 在区间 $[a,b]$ 上的误差函数

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n+1)}(\xi)(x-x_0)(x-x_1)(x-x_2)\dots(x-x_n)$$

其中 $\xi\in[a,b]$ 且依赖于 $x$。

~~证明如下~~

对于固定的 $x$ 有

$$\begin{aligned}
    \phi(x) & = f(x)-P_n(x)-R_n(x)\\
    & =f(x)-P_n(x)-k(x)\prod_{i=0}^{n}(x-x_i)\\
    &=0
\end{aligned}$$

在 $[a,b]$ 上 $\phi(x)=0,\phi(x_i)=0(i=0,1,2,\dots,n)$ ， $\phi(x)$ 有 $n+2$ 个零点，则 $\phi^{(n+1)}(x)$ 在 $[a,b]$ 上至少有 $1$ 个零点 $\xi$ ，故

$$\phi^{(n+1)}(\xi)=f^{(n+1)}(\xi)-(n+1)!k(x)=0$$

$$k(x)=\dfrac{1}{(n+1)!}f^{(n=1)}(\xi)$$

最终得 

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n+1)}(\xi)(x-x_0)(x-x_1)(x-x_2)\dots(x-x_n)$$

## Newton插值

为了有承袭性我们取Newton差值多项式为

$$P_n(x)=a_0+a_1(x-x_0)+a_2(x-x_0)(x-x_1)+\dots+a_n(x-x_0)(x-x_1)\dots(x-x_{n-1})$$

即 

$$\begin{cases}
    p_n(x) = p_{n-1}(x)+a_n(x-x_0)(x-x_1)\dots(x-x_{n-1})\\
    p_n(x_i) = f(x_i)
\end{cases}$$

这样我们就相当于先找 $l_i(x)$ 再找其系数

### 差商
~~作者觉得这东西会用来算系数就行，没啥纠结的，定义什么的不重要~~

| $x_i$ | $f(x_i)$ | 0阶差商 | 1阶差商 | 2阶差商 | 3阶差商 | 4阶差商 |
|---|---|---|---|---|---|---|
| $x_0$ | $f[x_0] = y_0$ | $y_0$ |||||
| $x_1$ | $f[x_1]=y_1$ | $y_1$ | $f[x_1, x_0] = \frac{y_1-y_0}{x_1-x_0}$ ||||
| $x_2$ | $f[x_2]=y_2$ | $y_2$ | $f[x_2, x_1]=\frac{y_2-y_1}{x_2-x_1}$ | $f[x_2,x_0]=\frac{f[x_2,x_1]-f[x_1,x_0]}{x_2-x_0}$ |||
| $x_3$ | $f[x_3]=y_3$ | $y_3$ | $f[x_3,x_2]=\frac{y_3-y_2}{x_3-x_2}$ | $f[x_3,x_1]=\frac{f[x_3,x_3]-f[x_2,x_1]}{x_3-x_1}$ | $f[x_3,x_0]=\frac{f[x_3,x_1]-f[x_2,x_0]}{x_3-x_0}$ ||
| $x_4$ | $f[x_4]=y_4$ | $y_4$ | $f[x_3,x_2]=\frac{y_3-y_2}{x_3-x_2}$ | $f[x_4,x_2]=\frac{f[x_4,x_3]-f[x_3,x_2]}{x_4-x_2}$ | $f[x_4,x_1]=\frac{f[x_4,x_2]-f[x_3,x_1]}{x_4-x_1}$ | $f[x_4,x_0]=\frac{f[x_4,x_1]-f[x_3,x_0]}{x_4-x_0}$ |

代码[插值方法.cpp](../../Code/插值方法.cpp)中的 `cal_cs()` 函数实现了计算差商表的功能。其中的插值节点定义为全局变量，返回一个存有差商表的二维容器。

```cpp
vector<vector<double>> cul_cs()
{
    vector<vector<double>> c(N + 1, vector<double> (N + 1, NAN));
    for(int i = 0; i <= N; i ++)
    {
        for(int j = i; j <= N; j ++)
        {
            if(i == 0) c[i][j] = Y[j];
            else c[i][j] = (c[i - 1][j] - c[i - 1][j - 1]) / (X[i] - X[i - j]);
        }
    }
    return c;
}
```

### Newton插值公式
如上递归计算即可，并且可以得到 Newton 法的系数即为上表对角线上的系数

$$a_i = f[x_0,x_1,\dots,x_i]\enspace(i=0,1,\dots,n)$$

Newton插值公式为

$$P_n(x)=a_0 + \sum_{i=1}^n\left[a_i\prod_{j=0}^{i - 1}(x-x_j)\right]$$

[插值方法.cpp](../../Code/插值方法.cpp)中的 `newton()` 函数则实现了Newton插值法，输入 `double x` 为需要拟合的节点。

```cpp
double Newton(double x)
{
    vector<vector<double>> c = cul_cs();
    double res = 0;
    for(int i = 0; i <= N; i ++)
    {
        double tmp = c[i][i];
        for(int j = 0; j < i; j ++) tmp *= (x - X[j]);
        res += tmp;
    }
    return res;
}
```

## 等距节点插值
Newton法的特例， $x_k=x_0+kh,(k=0,1,2,\dots)$ ，可据此改进Newton插值。

### 差分
定义：
- 向前差分： $\Delta y_k=y_{k+1}-y_k$ 为 $x_k$ 一阶向前差分，再次基础上可以递推出 $\Delta^m y_k=\Delta^{m-1} y_{k+1}-\Delta^{m-1} y_k$ 为 $x_k$ 的 $m$ 阶向前差分。
- 向后差分： $\nabla y_k=y_k-y_{k-1}$ 为 $x_k$ 的一阶向后差分，在此基础上可以递推出 $\nabla^m y_k=\nabla^{m-1}y_k-\nabla^{m-1}y_{k-1}$ 为 $x_k$ 的 $m$ 阶向后差分。

查分表应该能帮助更好的理解，实际编程我们也是维护一个差分表。

向前差分表
| $x_i$ | $y_i$ | $1$阶差分 | $2$阶差分 | $3$阶差分 | $4$阶差分 |
|---|---|---|---|---|---|
| $x_0$ | $y_0$ | $\Delta y_0=y1-y0$ | $\Delta^2y_0 = \Delta y_1-\Delta y_0$ | $\Delta^3 y_0=\Delta^2y_1-\Delta^2y_0$ | $\Delta^4y_0=\Delta^3y_1-\Delta^3y_0$ |
| $x_1$ | $y_1$ | $\Delta y_1=y2-y1$ | $\Delta^2y_1 = \Delta y_2-\Delta y_1$ | $\Delta^3 y_1=\Delta^2y_2-\Delta^2y_1$ ||
| $x_2$ | $y_2$ | $\Delta y_2=y3-y2$ | $\Delta^2y_2 = \Delta y_3-\Delta y_2$ |||
| $x_3$ | $y_3$ | $\Delta y_3=y4-y3$ ||||
| $x_4$ | $y_4$ |||||

向后差分表
| $x_i$ | $y_i$ | $1$阶差分 | $2$阶差分 | $3$阶差分 | $4$阶差分 |
|---|---|---|---|---|---|
| $x_0$ | $y_0$ |||||
| $x_1$ | $y_1$ | $\nabla y_1=y_1-y_0$ ||||
| $x_2$ | $y_2$ | $\nabla y_2=y_2-y_1$ | $\nabla^2y_2=\nabla y_2-\nabla y_1$ |||
| $x_3$ | $y_3$ | $\nabla y_3=y_3-y_2$ | $\nabla^2y_3=\nabla y_3-\nabla y_2$ | $\nabla^3y_3=\nabla^2y_3-\nabla^2y_2$ ||
| $x_4$ | $y_4$ | $\nabla y_4=y_4-y_3$ | $\nabla^2y_4=\nabla y_4-\nabla y_3$ | $\nabla^3y_4=\nabla^2y_4-\nabla^2y_3$ | $\nabla^4y_4=\nabla^3y_4-\nabla^3y_3$ |

不难发现，向前差分与向后差分的关系为 $\Delta^my_k=\nabla^my_{k+m}$

### 等距节点插值公式
<h5> 作者认为这部分内容课件上表述不清，难以理解公式，尤其是无法很好地区分前插与后插公式，故作调整 </h5>

差分与差商的关系

$$f[x_0,x_1,\dots,x_m]=\dfrac{1}{m!}\dfrac{1}{h^m}\Delta^my_0=\dfrac{1}{m!}\dfrac{1}{h^m}\nabla^my_m \qquad{(1)}$$

#### 前插公式

由于 $x_k=x_0+kh,(k = 0,1,2,\dots)$ ，设需要拟合的点为 $x=x_0+th$

$$l_i(x)=\prod_{j=0}^{i-1}(x-x_j)=h^i\prod_{j=0}^{i-1}(t-j)$$

故可得等距节点前插值公式：

$$P_n(x)=y_0+\sum_{i=1}^n\left[\dfrac{\Delta^iy_0}{i!}\prod_{j=0}^{i-1}(t-j)\right]$$

当然按照 $(1)$ 式可以直接得到所谓利用了后差分的“后插值公式”

$$P_n(x)=y_0+\sum_{i=1}^n\left[\dfrac{\nabla^iy_i}{i!}\prod_{j=0}^{i-1}(t-j)\right]$$

但这与课件上给出的公式不合，虽然都可以正确计算但是我们需要作出一些改变。

#### 后插公式
在这里我们定义 $b \geq x_0 > x_{-1} >\dots>x_{-n}\geq a$ ，且 $x_{-k}=x_0-kh\enspace(k=0,1,2,\dots,n;h>0)$

这样，就实现了差分定义与等距下标规则在数学表达上的统一

定义需要拟合的点为 $x=x_0+th$ 得到与课件上相同的后插公式

$$P_n(x)=y_0+\sum_{i=1}^{n}\left[\dfrac{\nabla^iy_0}{i!}\prod_{j=0}^{i-1}(t+j)\right]$$

### 代码实现
[插值方法.cpp](../../Code/插值方法.cpp)中的 `insert_ahead` 函数实现了向前插值，其中输入 `double t` 为 $x=x_0+th$ 中的 $t$
```cpp
double insert_ahead(double t)
{
    vector<vector<double>> qc(N + 1, vector<double>(N + 1, 0));
    for(int i = 0; i <= N; i ++) qc[i][0] = Y[i];
    for(int j = 1; j <= N; j ++)
    {
        for(int i = 0; i <= N - j; i ++) qc[i][j] = qc[i + 1][j - 1] - qc[i][j - 1];
    }

    double res = Y[0], fac = 1.;
    for(int i = 1; i <= N; i ++)
    {
        fac *= i;
        double tmp = 1;
        for(int j = 0; j < i; j ++) tmp *= (t - j);
        res += qc[0][i] * tmp / fac;
    }
    return res;
}
```
[插值方法.cpp](../../Code/插值方法.cpp)中的 `inster_last` 函数实现了向前插值，其中输入 `double t` 为 $x=x_0+th$ 中的 $t$
```cpp
double inster_last(double t)
{
    vector<vector<double>> hc(N + 1, vector<double>(N + 1, 0));
    for(int i = 0; i <= N; i ++) hc[i][0] = Y[i];
    for(int j = 1; j <= N; j ++)
    {
        for(int i = j; i <= N; i ++) hc[i][j] = hc[i][j - 1] - hc[i - 1][j - 1];
    }

    double res = Y[N], fac = 1.;
    for(int i = 1; i <= N; i ++)
    {
        fac *= i;
        double tmp = 1;
        for(int j = 0; j < i; j ++) tmp *= t + j;
        res += hc[N][i] * tmp / fac;
    }
    return res;
}
```

**注意：** 一般来说四种插值的方法的结果应该是完全一样的，但是由于计算误差的限制，当 `N` 过大时，等距节点插值可能会体现出较大的误差，一般也只用到 $2$ 阶等距节点插值就行了。

## 分段低次插值
多项式拟合的次数过高，容易造成过拟合

**核心思想：** 分段降低次数，公式和Lagrange法一样

### 分段线性插值

$P(x)$ 在每个子区间 $[x_i,x_{i+1}],(i=0,1,2,\dots,n-1)$ 上是一次插值多项式

$$P(x)=\dfrac{x-x_{i+1}}{x_i-x_{i+1}}y_i+\dfrac{x-x_i}{x_{i+1}-x_i}y_{i+1}$$

### 分段二次插值
选取与节点 $x$ 最近的三个节点 $x_{i-1},x_i,x_{i+1}$ 进行二次插值。

$$f(x)\approx p_2(x)=\sum_{k=i-1}^{i+1}\left(y_k\prod_{j=i-1,j\neq k}^{i+1}\dfrac{x-x_j}{x_k-x_j}\right)$$

### 插值余项
记住Lagrange插值余项

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n+1)}(\xi)(x-x_0)(x-x_1)(x-x_2)\dots(x-x_n)$$

分段一次插值，若 $\left|f^{(2)}(x)\right|\leq m$ ，区间长度为 $h$ 则根据均值不等式

$$|R_1(x)|\leq \dfrac{mh^2}{8}$$

## Hermite插值
**核心思想：** 在插值节点不仅要函数值相等、一阶导数也相等。

已知节点 $a=x_0<x_1<\dots<x_n=b$ 且 $f(x)$ 在节点上有

$$f(x_i) = y_i,\enspace f^{'}(x_i)=y^{'}_i,\enspace i=0,1,2,\dots,n$$

构造一个次数不高于 $2n+1$ 次的多项式一定可以满足要求。

令

$$H_{2n+1}(x)=\sum_{i=0}^{n}h_i(x)f(x_i)+\sum_{i=0}^ng_i(x)f^{'}(x_i)$$

其中，基函数 $h_i(x),g_i(x)$ 应满足

$$\begin{cases}
    h_i(x_j)=\delta_{ij}\\
    h^{'}(x_j)=0
\end{cases}
\begin{cases}
    g_i(x_j)=0\\
    g^{'}_i(x_j)=\delta_{ij}
\end{cases},
\delta_{ij}=\begin{cases}
    i & i=j\\
    0 & i \neq j
\end{cases} (i,j = 0,1,2,\dots,n)$$

借鉴Lagrange插值法的基函，我们令

$$h_i(x)=(ax+b)\left[l_i(x)\right]^2f(x_i)\\g_i(x)=(cx+d)\left[l_i(x)\right]^2f^{'}(x_i)$$

其中，先取对数再求导可以方便地求出 $l^{'}_i(x)$

$$l_i(x)=\prod_{j=0,j\neq i}^n\dfrac{x-x_j}{x_i-x_j},\enspace l_i^{'}(x)=l_i(x)\sum_{j=0,j\neq i}^n\dfrac{1}{x_i-x_j}$$

求得

$$\begin{cases}
    a = -2\sum_{j=0,j\neq i}^n\dfrac{1}{x_i-x_j}\\
    b = 1 + 2x_i\sum_{j=0,j\neq i}^n\dfrac{1}{x_i-x_j}\\
    c = 1\\
    d = -x_i
\end{cases}$$

### 插值公式（省流）

故最终得Hermite插值多项式为

$$H_{2n+1}(x)=\sum_{i=0}^nf(x_i)\left[1-2(x-x_i)\sum_{j=0,j\neq i}^n\dfrac{1}{x_i-x_j}\right][l_i(x)]^2+\sum_{i=0}^nf^{'}(x)(x-x_i)[l_i(x)]^2$$

### 差值余项
类似于 Lagrange 插值

$$R_{2n+1}(x)=\dfrac{f^{(2n+2)}(\xi)}{(2n+2)!}\left[\prod_{i=0}^n(x-x_i)\right]$$

## 样条插值
**定义:** 
- $S(x)$ 在每子区间上是不超过 $k$ 次多项式
- $S(x)$ 在每子区间上有 $k-1$ 阶导数

则称 $S(x)$ 是 $k$ 次样条函数。

$Excel$ 文件 [三次样条插值计算实验.xlsx](../../Excel/插值方法/三次样条插值计算实验.xlsx) 为上课实验的文件，其中已经提前写好了大量的公式，~~作者猜测期末考试应该也是这个模式~~

### 三次样条插值
这是最常用的方法。依然是在 $a \leq x_0 < x_1 \dots < x_n \leq b$ 上插值拟合。

直接上结论，在区间 $[x_i,x_{i+1}]$ 上的三次样条插值函数为

$$S_i(x)=M_i\dfrac{(x_{i+1}-x)^3}{6h_i}+M_{i+1}\dfrac{(x-x_i)^3}{6h_i}+\left(\dfrac{y_i}{h_i}-\dfrac{M_i}{6}h_i\right)(x_{i+1}-x_i)+\left(\dfrac{y_{i+1}}{h_i}-\dfrac{M_{i+1}}{6}h_i\right)(x-x_i)$$

其中 $h_i=x_i-x_{i-1},\enspace i=1,2,\dots,n$ ，关键就是如何求解公式中的 $M_i$

$$
 \begin{bmatrix}
 2 & \lambda_0 &  &  &  \\
 \mu_1 & 2 & \lambda_1 &  &  \\
 & \dots & \dots & \dots &  \\
 &  & \mu_{n-1} & 2 & \lambda_{n-1} \\
 &  &  & \mu_N & 2 \\
\end{bmatrix}
\begin{bmatrix}
M_0 \\
M_1 \\
\dots \\
M_{n-1} \\
M_n \\
\end{bmatrix}=\begin{bmatrix}
d_0 \\
d_1 \\
\dots \\
d_{n-1} \\
d_n \\
\end{bmatrix}
$$

现在问题变为了，如何确定系数矩阵中的 $\mu_i,\lambda_i,d_i$

**递推关系**

$$
\begin{cases}
    \mu_i=\dfrac{h_i}{h_{i-1}+h_i} ,\enspace \lambda_i = 1 - \mu_i\\
    d_i=\dfrac{6}{h_{i-1}+h_i}\left(\dfrac{y_{i+1}-y_i}{h_i}-\dfrac{y_i-y_{i-1}}{h_{i-1}}\right)
\end{cases}
$$

而 $\lambda_0, d_0,\mu_n,d_n$ 则由边界条件决定。

#### 三类边界条件

- 第 $1$ 类边界条件： $S^{''}(x_0)=M_0,S^{''}(x_n)=M_n$

$$\lambda_0=0, d_0=2y^{''}_0,\mu_n=0,d_n=2y_n^{''}$$

- 第 $2$ 类边界条件： $S^{'}(x_0)=y_0^{'},S^{'}(x_n)=y^{'}_n$

$$\lambda_0=1,\mu_n=1,d_0=\dfrac{6}{h_1}\left(\dfrac{y_1-y_0}{h_1}-y_0^{'}\right),d_n=\dfrac{6}{h_n}\left(y^{'}_n-\dfrac{y_{n-1}-y_n}{x_{n-1}-x_n}\right)$$

- 第 $3$ 类边界条件： $f(x)$n 是周期函数，满足条件 $S(x_0)=S(x_n),S^{'}(x_0^+)=S^{'}(x_n^-),S^{''}(x_0^+)=S^{''}(x_n^-)$

$$\begin{cases}
    M_n=M_0\\
    \lambda_n M_1+\mu_nM_{n-1}+2M_n=d_n
\end{cases}$$

其中 $\mu_n=\dfrac{h_n}{h_n-h_1},\lambda_n=1-\mu_n,d_n=6\left(\dfrac{y_1-y_0}{h_1}-\dfrac{y_n-y_{n-1}}{h_n}\right)(h_1,h_n)^{-1}$

有
$$
 \begin{bmatrix}
 2 & \lambda_0 &  &  & \mu_1 \\
 \mu_1 & 2 & \lambda_1 &  &  \\
 & \dots & \dots & \dots &  \\
 &  & \mu_{n-1} & 2 & \lambda_{n-1} \\
\lambda_n &  &  & \mu_N & 2 \\
\end{bmatrix}
\begin{bmatrix}
M_1 \\
M_2 \\
\dots \\
M_{n-1} \\
M_n \\
\end{bmatrix}=\begin{bmatrix}
d_1 \\
d_2 \\
\dots \\
d_{n-1} \\
d_n \\
\end{bmatrix}
$$

<h5>说实话，作者也没有很看明白这个样条插值，大部分照搬PPT罢了</h5>
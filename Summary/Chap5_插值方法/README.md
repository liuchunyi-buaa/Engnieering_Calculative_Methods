## 知识点总结

快速索引
- [知识点总结](#知识点总结)
- [Lagrange插值](#lagrange插值)
  - [差值公式](#差值公式)
  - [差值余项](#差值余项)
- [Newton插值](#newton插值)
  - [差商](#差商)

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

### 差值余项

直接记结论， $f(x)$ 的差值函数 $P_n(x)$ 在区间 $[a,b]$ 上的误差函数

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n=1)}(\xi)(x-x_0)(x-x_1)(x-x_2)\dots(x-x_n)$$

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

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n=1)}(\xi)(x-x_0)(x-x_1)(x-x_2)\dots(x-x_n)$$

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

| $x_i$ | $f(x_i)$ | 0 | 1 | 2 | 3 | 4|
|---|---|---|---|---|---|---|
| $x_0$ | $y_0$ | $y_0$ |||||
| $x_1$ | $y_1$ | $y_1$ | $f[x_1, x_0] = \frac{y_1-y_0}{x_1-x_0}$ ||||
| $x_2$ | $y_2$ | $y_2$ | $f[x_2, x_1]=\frac{y_2-y_1}{x_2-x_1}$ | $f[x_2,x_0]=\frac{f[x_2,x_1]-f[x_1,x_0]}{x_2-x_0}$ |||
| $x_3$ | $y_3$ | $y_3$ | $f[x_3,x_2]=\frac{y_3-y_2}{x_3-x_2}$ | $f[x_3,x_1]=\frac{f[x_3,x_3]-f[x_2,x_1]}{x_3-x_1}$ | $f[x_3,x_0]=\frac{f[x_3,x_1]-f[x_2,x_0]}{x_3-x_0}$ ||
| $x_4$ | $y_4$ | $y_4$ | $f[x_3,x_2]=\frac{y_3-y_2}{x_3-x_2}$ | $f[x_4,x_2]=\frac{f[x_4,x_3]-f[x_3,x_2]}{x_4-x_2}$ | $f[x_4,x_1]=\frac{f[x_4,x_2]-f[x_3,x_1]}{x_4-x_1}$ | $f[x_4,x_0]=\frac{f[x_4,x_1]-f[x_3,x_0]}{x_4-x_0}$ |
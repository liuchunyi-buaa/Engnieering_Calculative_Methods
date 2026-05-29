## 知识点总结
本章内容对应的[上课PPT](../../PPT/第8章%20常微分方程数值解法（理论）-2026.pdf)，[实验PPT](../../PPT/第8章%20常微分方程数值解法（实验）-2026.pdf)

快速索引
- [知识点总结](#知识点总结)
- [Euler法](#euler法)
- [梯形法](#梯形法)
- [Eular预估-校正公式](#eular预估-校正公式)
- [Taylor方法](#taylor方法)
- [Runge-Kutta 方法](#runge-kutta-方法)
  - [二阶Runge-Kutta方法](#二阶runge-kutta方法)
  - [四阶Runge-Kutta方法](#四阶runge-kutta方法)

讨论一阶常微分方程的基本形式为

$$\begin{cases}
    \dfrac{\mathrm{d}y}{\mathrm{d}x}=f(x,y)\\
    y(x_0)=y_0
\end{cases},\space a\leq x\leq b$$

数值解法的基本思路为在 $[a,b]$ 上解 $y(x)$ 的点列 $x_i = x_{i-1} + h$ 上的近似值 $y_i$ 。

## Euler法

设节点为 $x_k = x_0 + kh\space(k = 0,1,2,\dots,n)$ ，得欧拉方法计算公式为

$$y_{k+1}=y_k+h\cdot f(x_k,y_k)$$

用积分的方法来看待

$$y_{k+1}-y_k=\int_{x_k}^{x_{k+1}}y^{'}(x)\mathrm{d}x$$

用矩形公式来计算，得

$$y(x_{k+1})\approx y(x_k)+hf(x_k,y_k)$$

代码[常微分方程的数值解法.cpp](../../Code/常微分方程的数值解法.cpp)中的 `Euler()` 函数实现了一般形式的Euler法解常微分方程
```cpp
double Euler(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        yn = yn + h * f(xn, yn);
        xn += step;
    }
    return yn;
}
```

## 梯形法

在计算 $y_{k+1}-y_k=\int_{x_k}^{x_{k+1}}y^{'}(x)\mathrm{d}x$ 时使用梯形公式

则有

$$y_{k+1}=y_k+h\dfrac{f(x_k,y_k)+f(x_{k+1},y_{k+1})}{2}$$

可见这个式子就是 $y_{k+1}=g(y_{k+1})$ 的不动点方程，构造迭代方程

$$\begin{cases}
    y_{k+1}^{(0)}=y_k+hf(x_k,y_k)\\
    y_{k+1}^{(i+1)}=y_k+\dfrac{h}{2}\left(f(x_k,y_k)+f\left(x_{k+1},y_{k+1}^{(i)}\right)\right),\space(i=0,1,2,\dots)
\end{cases}$$

代码[常微分方程的数值解法.cpp](../../Code/常微分方程的数值解法.cpp)中的 `trap()` 函数实现了一般形式的梯形公式解常微分方程
```cpp
double trap(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double yk =yn + h * f(xn, yn), e = 1.;
        while (e > EPS)
        {
            double ykk = yn + h / 2 * (f(xn, yn) + f(xn + h, yk));
            e = fabs(ykk - yk);
            yk = ykk;
        }
        yn = yk;
        xn += step;
    }
    return yn;
}
```

## Eular预估-校正公式
其实就是梯形公式只迭代一次就结束

$$\begin{cases}
    y_{k+1}^{(0)}=y_k+hf(x_k,y_k)\\
    y_{k+1}=y_k+\dfrac{h}{2}\left(f(x_k,y_k)+f\left(x_{k+1},y_{k+1}^{(0)}\right)\right)
\end{cases}$$

代码[常微分方程的数值解法.cpp](../../Code/常微分方程的数值解法.cpp)中的 `Euler_imp()` 函数实现了一般形式的Euler预估公式解常微分方程
```cpp
double Euler_imp(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double tmp = yn + h * f(xn, yn), xnn = xn + h;
        yn = yn + h / 2 *(f(xn, yn) + f(xnn, tmp));
        xn += step;
    }
    return yn;
}
```

Eular 预估-校正方法的局部阶段误差为 $O(h^3)$

## Taylor方法
该方法就是进行泰勒展开，然后舍去可以接受的阶段误差。

$$\begin{cases}
    y_{n+1}=y_n+hf(x_n, y_n)+\dfrac{h^2}{2}f^{'}(x_n,y_n)+\dots+\dfrac{h^p}{p!}f^{(p-1)}(x_n,y_n)
    y_0=\alpha
\end{cases}$$

## Runge-Kutta 方法
**基本思想：** 用不同点的函数值作线性组合，构造近似公式，实现在尽可能多的与 Taylor展开式的前几项相同。

一般显式的 Runge-Kutta方法可以写成

$$\begin{cases}
    y_{n+1}=y+\sum_{i=1}^Nc_ik_i\\
    k_1=hf(x_n,y_n)\\
    \vdots\\
    k_i=hf\left(x_n+\alpha_ih,y_n+\sum_{j=1}^{i-1}\beta_{ij}k_j\right)\\
    \vdots
\end{cases}$$

具体的推导过程作者看了也很懵逼，直接记结论吧

### 二阶Runge-Kutta方法

常用的有两种，休恩方法
$$\begin{cases}
    y_{n+1}=y_n+\dfrac{k_1+3k_2}{4}\\
    k_1 = hf(x_n,y_n)\\
    k_2=hf(x_n+\dfrac{2}{3}h,y_n+\dfrac{2}{3}k_1)
\end{cases}$$

代码[常微分方程的数值解法.cpp](../../Code/常微分方程的数值解法.cpp)中的 `Runge_Kutta2()` 函数实现了一般形式二阶Runge-Kutta法解常微分方程
```cpp
double Runge_Kutta2(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double k1 = h * f(xn, yn);
        double k2 = h * f(xn + 2 * h / 3, yn + 2 * k1 / 3);
        yn = yn + (k1 + 3 * k2) / 4;
        xn += step;
    }
    return yn;
}
```

同样的，较常用的是 Euler 预估校正公式

$$\begin{cases}
    y_{n+1}=y_n+\dfrac{k_1+k_2}{2}\\
    k_1 = f(x_n,y_n)\\
    k_2 = f(x_n+h,y_n+k_1)
\end{cases}$$

### 四阶Runge-Kutta方法
经典四级四阶R-K公式
$$\begin{cases}
    y_{n+1}=y_n+\dfrac{k_1+2k_2+2k_3+k_4}{6}\\
    k_1 = f(x_n, y_n)\\
    k_2 = f(x_n+\dfrac{1}{2}h, y_n+\dfrac{1}{2}k_1)\\
    k_3 = f(x_n+\dfrac{1}{2}h, y_n+\dfrac{1}{2}k_2)\\
    k_4 = hf(x_n+h, y_n+k_3)
\end{cases}$$

代码[常微分方程的数值解法.cpp](../../Code/常微分方程的数值解法.cpp)中的 `Runge-Kutta4()` 函数实现了一般形式的四阶Runge-Kutta方法解常微分方程
```cpp
double Runge_Kutta4(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double k1 = h * f(xn, yn);
        double k2 = h * f(xn + step / 2, yn + k1 / 2);
        double k3 = h * f(xn + step / 2, yn + k2 / 2);
        double k4 = h * f(xn + step / 2, yn + k3);
        yn = yn + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        xn += step;
    }
    return yn;
}
```

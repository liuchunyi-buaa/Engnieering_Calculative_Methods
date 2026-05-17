## 知识点总结
本节内容对应的[PPT](../../PPT/第2章%20非线性方程的数值解法.pdf)

快速索引
- [知识点总结](#知识点总结)
- [算法](#算法)
  - [二分法](#二分法)
  - [一般迭代法](#一般迭代法)
  - [牛顿迭代法](#牛顿迭代法)
  - [弦截法](#弦截法)
- [误差分析](#误差分析)
  - [二分法相关误差分析](#二分法相关误差分析)
    - [收敛性](#收敛性)
    - [事前误差分析](#事前误差分析)
  - [一般迭代法的收敛性判断](#一般迭代法的收敛性判断)
  - [迭代法的迭代速度 ⭐️⭐️⭐️](#迭代法的迭代速度-️️️)

## 算法
两大类：
- 区间收缩法
- 迭代法

### 二分法
代码[非线性方程组的数值解法.cpp](../../Code/非线性方程组的数值解法.cpp)，中的 `bisec` 函数实现了一般形式上的二分法，可以求解区间 $[l, r]$ 上的方程 $func(x) = 0$

注：`double (*func)(double)` 为函数指针，调用时填写你的函数名称即可
```cpp
double bisec(double l, double r, double (*func)(double))
{
    double mid, e = 1.;
    while (e > eps)
    {
        mid = (l + r) / 2;
        if(func(mid) * func(l) < 0) r = mid;
        else if(func(mid) * func(r) < 0) l = mid;
        e = fabs(r - l);
    }
    return mid;
}
```

### 一般迭代法
1. 将方程 $f(x)$ 构造为 $x = g(x)$ 的迭代形式
2. 选取初值 $x_0$
3. $x_{k + 1} = g(x_k)$ 迭代
4. $|x_{k + 1}-x_k| < \varepsilon$ 停止迭代

关键是构造 $g(x)$，以下的牛顿迭代法

### 牛顿迭代法
迭代公式：
$$x_{k + 1}=x_k-\dfrac{f(x)}{f^{'}(x)}$$
几何意义：切线零点不断靠近函数零点。

代码[非线性方程组的数值解法.cpp](../../Code/非线性方程组的数值解法.cpp)中的 `newton` 函数实现了一般形式上的牛顿迭代法。以 `x0` 为起点，开始迭代导数为 `ff` 的函数 `f` 的零点。
```cpp
double newton(double x0, double (*f)(double), double (*ff)(double))
{
    double xk = x0, xkk, e=1.;
    while(e > eps)
    {
        xkk = xk - f(xk) / ff(xkk);
        e = fabs(xkk - xk);
        xk = xkk;
    }
    return xk;
}
```
**注意：** 注意初值的选取，对于多零点和函数，不同的初值会求出不同的零点。牛顿法不宜用于零点斜率为 $0$ 的函数。

### 弦截法
一句话，用割线斜率代替切线斜率。
迭代公式：
$$x_{k+1}=x_k-\dfrac{f(x_k)}{f(x_k) - f(x_{k-1})}(x_k-x_{k-1})$$
代码[非线性方程组的数值解法.cpp](../../Code/非线性方程组的数值解法.cpp)中的 `secant` 函数实现了一般形式上的弦截法。
```cpp
double secant(double x0, double x1, double (*f)(double))
{
    double xkk, xk = x1, xk_ = x0, e = 1.;
    while(e > eps)
    {
        xkk = xk - f(xk) / (f(xk) - f(xk_)) * (xk - xk_);
        e = fabs(xkk - xk);
        xk_ = xk, xk = xkk; // 注意这里的幅值顺序不能调换
    }
    return xkk;
}
```

---

## 误差分析
这里的误差指的是结果的误差，即零点的误差，所以应该用 $|x-x^\*|$ 来估计，不是 $|f(x)|$

### 二分法相关误差分析
#### 收敛性
$$|x_{k+1}-x^\*|\leq|x_{k + 1} - x_k| = \dfrac{|x_k-x_{k-1}|}{2} = \dfrac{|a-b|}{2^k}$$
故 $\lim_{k\to+\infty}|x_{k+1}-x^\*|=0$

#### 事前误差分析
由$|x_{k+1}-x^\*|\leq \dfrac{|a-b|}{2^k}$ 得 $k \geq \log_2\left(\dfrac{|a-b|}{\varepsilon}\right)$，故 $k =  \left \lceil \dfrac{\ln|a-b|-\ln\varepsilon}{\ln2}\right \rceil$

### 一般迭代法的收敛性判断
不是所有的 $x=g(x)$ 形式都可以收敛，关键是找 $g(x)$ 需要满足的条件。

这个条件就是 **李普希兹条件:** 

在一个区间 $\Delta$ 内，所有的 $|g(x) - g(y)| \leq L |x-y|,\enspace 0 < L < 1$。

等价于：$g^{'}(x)$ 在 $\Delta$ 内连续，且 $|g^{'}(x)| \leq L < 1$。

满足以上条件的 $g(x)$ 在 $\Delta$ 内迭代均收敛到 $x^\*$。

误差估计 $|x_k-x^\*|\leq \dfrac{L^k}{1 - L}|x_1 - x_0|$。

### 迭代法的迭代速度 ⭐️⭐️⭐️
老师说这个要考

定义 $\dfrac{e_{k + 1}}{e_k^p}\to C$ 的迭代格式为 $p$ 阶收敛。

牛顿法迭代速度分析：

在 $x^\*$ 处泰勒展开：
$$f(x^\*)=0=f(x_k)+f^{'}(x)(x^\*-x_k)+\dfrac{1}{2}f^{''}(\xi)(x^\*-x_k)^2$$
整理得
$$x^\*=x_k-\dfrac{f(x_k)}{f^{'}(x_k)}-\dfrac{f^{''}(x_k)}{2f(x)}(x^\* - x_k)^2$$
不难发现
$$x^\*-x_{k+1}=-\dfrac{f^{''}(x_k)}{2f(x)}(x^\* - x_k)^2$$
故
$$\dfrac{e_{k+1}}{e_k}=\dfrac{f^{''}(x_k)}{2f(x)}\to\dfrac{f^{''}(x^\*)}{f^{'}(x^\*)}$$
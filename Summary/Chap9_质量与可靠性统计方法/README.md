## 知识点总结

快速索引
- [知识点总结](#知识点总结)
- [基本定义](#基本定义)
  - [数字特征](#数字特征)
  - [常用分布](#常用分布)
    - [正态分布（Gauss分布）⭐️⭐️⭐️](#正态分布gauss分布️️️)
    - [泊松分布](#泊松分布)
    - [$t$ 分布](#t-分布)
  - [显著水平与 T 检验](#显著水平与-t-检验)
    - [单样本 T 检验](#单样本-t-检验)
    - [配对样本 T 检验](#配对样本-t-检验)
    - [独立样本 T 检验](#独立样本-t-检验)

## 基本定义
### 数字特征
**期望**
- 离散型随机变量

$$E(x)=\sum_i^{\infty}x_ip(x_i)$$

- 连续型随机变量

$$E(X)=\int_{-\infty}^{+\infty}xf(x)\mathrm{d}x$$

**方差**

定义： $D(x)=E\left\lbrace\left[x-E(X)\right]^2\right\rbrace=E\left(X^2\right)-\left[E(x)\right]^2$

计算期望即可

### 常用分布
#### 正态分布（Gauss分布）⭐️⭐️⭐️
$$f(x)=\dfrac{1}{\sqrt{2\pi}}e^{-\dfrac{(x-\mu)^2}{2\sigma^2}}$$

**标准正态分布**

$x\sim N(0,1)$ 为标准正态分布

密度函数 $\phi(x)=\frac{1}{\sqrt{2\pi}}e^{-\frac{x^2}{2}}$

分布函数 $\Phi(x)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^x e^{-\frac{x^2}{2}} \mathrm{d}x$

代码 [正态分布.cpp](../../Code/正态分布.cpp) 中给出了利用梯形公式计算标准正态分布密度函数和分布函数的实现方法。

`phi` 函数直接计算 $\phi(x)=\frac{1}{\sqrt{2\pi}}e^{-\frac{x^2}{2}}$

```cpp
double phi(double x)
{
    return exp(-x * x / 2.) / (sqrt(2 * M_PI));
}
```

`Phi` 函数利用梯形公式计算了 $\Phi(x)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^x e^{-\frac{x^2}{2}} \mathrm{d}x$ ，由于负无穷在计算机中无法到达，故将公式作出调整 

$$\begin{aligned}
  \Phi(x) & =\frac{1}{\sqrt{2\pi}}\int_{-\infty}^x e^{-\frac{x^2}{2}} \mathrm{d}x \\
  & =\frac{1}{\sqrt{2\pi}}\int_{-\infty}^0 e^{-\frac{x^2}{2}} \mathrm{d}x + \frac{1}{\sqrt{2\pi}}\int_0^x e^{-\frac{x^2}{2}} \mathrm{d}x \\
  & =0.5 + \frac{1}{\sqrt{2\pi}}\int_0^x e^{-\frac{x^2}{2}} \mathrm{d}x
\end{aligned}$$

实际是从 $0$ 开始积分
```cpp
double Phi(double x)
{
    const double step = STEP;
    if(x == 0.) return 0.5;
    else if(x > 0)
    {
        double res = 0.5;
        for(int i = 0; i < x / step; i ++) res += phi((i + 0.5) * step) * step;
        return res;
    }
    else
    {
        double res = 0.5;
        for(int i = 0; i < -x / step; i ++) res -= phi(-(i + 0.5) * step) * step;
        return res;
    }
}
```

#### 泊松分布
$$p(X) = \dfrac{\lambda^xe^{-\lambda}}{x!}, x = 0,1,2,\dots$$

其中 $\lambda > 0$ 

#### $t$ 分布
设 $X \sim N(0,1), Y\sim\chi^2(n)，且 $X,Y$ 独立，则称随机变量

$$t=\dfrac{X}{\sqrt{Y/n}}$$

服从自由度为 $n$ 的 $t$ 分布，记为 $t\sim t(x)$。

$t$ 分布的上 $\alpha$ 分位点为大于这个点的概率为 $\alpha$ ，小于这个点的概率为 $1 - \alpha$ 。在 $\text{Excel}$ 中的 `=TINV(probability, degrees_freedom)` 的函数可以计算自由度为 `degrees_freedom` 的 $t$ 分布的上 `probability` 分位数。

### 显著水平与 T 检验

说白了，就是小概率事件不会在一起试验中发生，所以就是这个事件出现的概率是多少。

#### 单样本 T 检验

判断均值是否大于或等于或小于某个给定值

$$H_0:\mu = \mu_0 \enspace\enspace H_1:\mu>\mu_0 \enspace\enspace \alpha$$

取假设统计量 $t = \dfrac{\overline{X}-\mu_0}{S_{\overline{X}}}$ 用自由度为 $n-1$ 的 $t$ 分布来检验。

#### 配对样本 T 检验

与单样本 T 检验类似，取 $d_i=x_i-y_i$ 对 $d$ 作单样本 T 检验。

注意：一般的问题为验证两个样本的均值有无明显差别，所以 $\mu_0 = 0$ 。

假设统计量 $t = \dfrac{\overline{d} - 0}{s_d/\sqrt{n}}$ 自由度为 $n - 1$ 。

#### 独立样本 T 检验

适用条件
- 两样本数均来自正态分布整体
- 两样本方差相等

目标：比较两样本总体均值是否相同

$$t = \dfrac{\overline{X_1} - \overline{X_2}}{s_{\overline{X_1} - \overline{X_2}}}=\dfrac{\overline{X_1} - \overline{X_2}}{\sqrt{\dfrac{S_1^2(n_1-1)+S_2^2(n_2-1)}{n_1+n_2-2}\left(\dfrac{1}{n_1}+\dfrac{1}{n_2}\right)}}$$

其实你可以直接使用 $\text{Excel}$ 中的 `=TTEST(array1, array2, tails, type)` 函数计算。其中，设置 `type = 2` ，选择等方差假设
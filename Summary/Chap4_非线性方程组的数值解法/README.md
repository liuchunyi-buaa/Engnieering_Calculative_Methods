## 知识点总结

快速索引
- [知识点总结](#知识点总结)
- [简单迭代法及其收敛性](#简单迭代法及其收敛性)
  - [迭代公式](#迭代公式)
  - [收敛性判别](#收敛性判别)
- [Newton型算法](#newton型算法)
- [最速下降搜索法](#最速下降搜索法)

非线性方程组的一般形式

$$
\begin{cases}
    f_1\left(x_1, x_2, \dots, x_n\right) = 0 \\
    f_1\left(x_1, x_2, \dots, x_n\right) = 0 \\
    \vdots\\
    f_m\left(x_1, x_2, \dots, x_n\right) = 0
\end{cases}
$$
令
$$
x=\begin{pmatrix}
x_1\\
x_2\\
\vdots\\
x_n
\end{pmatrix},
F(x)=\begin{pmatrix}
    f_1(x)\\
    f_2(x)\\
    \vdots\\
    f_m(x)
\end{pmatrix}
$$

则非线性方程组可以写为 $F(x)=0$

## 简单迭代法及其收敛性
### 迭代公式
迭代法的思想就是找不动点。

将 $F(x)=0$ 写成便于迭代的形式 $x=\Phi(x)$，则迭代公式 $x_{k+1}=\Phi(x_k)$

### 收敛性判别
区间 $D\in\R^n$， $x,y\in D$ ，若 $||\Phi^{'}(x)<1||$（或等价表述为$||\Phi(x)-\Phi(y)||\leq L||x-y||$，其中$L < 1$）则
- $\Phi(x)$ 在 $D$ 上有唯一的不动点 $x^\*$ 满足 $x^\*=\Phi(x^\*)$
- 从区间 $D$ 内的任意起点都收敛到 $x^\*$

同样也有 Jacobi 迭代法和 Gauss-Seidel 迭代法。

## Newton型算法

将 $F\left(x_{k+1} \right)$ 在 $F\left(x_{k} \right)$ 附近进行泰勒展开

$$F\left(x_{k+1}\right)=F\left(x_k\right)+\nabla F\left(x_k \right)\Delta x+ \nabla^2F\left(\xi\right)\Delta x^2$$

令 $F\left(x_{k+1}\right)=0$ 并忽略高阶小项，得

$$\Delta x = -\left(\nabla F\left(x_k \right)\right)^{-1}F\left(x_k\right)$$

故我们可以得到 Jacobi 迭代式

$$\begin{cases}
    \Delta x = -\left(\nabla F\left(x_k \right)\right)^{-1}F\left(x_k\right)\\
    x_{k+1} = x_k + \Delta x
\end{cases}$$

关键难点在于正确求出 $\nabla F(x)$ 。

## 最速下降搜索法

和梯度下降法原理相同，思想：将求零点问题转换为求极值问题

对于方程组 $F(x) = [f_1(x), f_2(x), \dots, f_n(x)]^T = 0$

构造 $\varphi(x)=\dfrac{1}{2}F(x)^TF(x)=\dfrac{1}{2}[f_1(x)^2+f_2(x)^2+,\dots,+f_n(x)^2]$

问题转换为了求 $\varphi(x)$ 得最小值。

下降方向： $p=-\nabla\varphi(x)=-F(x)^T\nabla F(x)$

下降步长：依然将 $\varphi\left(x_{k+1} \right)$ 在 $\varphi\left(x_{k} \right)$ 附近进行泰勒展开

$$
\begin{aligned}
    \varphi\left(x^{k+1}\right)&=\varphi\left(x^{k}+\alpha_kp^{(k)}\right)\\
    &\approx\varphi\left(x^{k}\right)+\alpha_k(p^{(k)}) ^T \nabla\varphi(x^k)\\
    &=\varphi\left(x^{k}\right)-\alpha_k(p^{(k)}) ^Tp^{(k)}
\end{aligned}$$

依然希望 $\varphi\left(x^{k+1}\right)=0$，得 $\alpha_k=\dfrac{\varphi\left(x^{k}\right)}{(p^{(k)}) ^Tp^{(k)}}$

注： $\nabla\varphi\left(x\right),x$ 均是列向量

故最速下降法的迭代公式为

$$x^{k+1}=x^k+\dfrac{\varphi\left(x^{k}\right)}{(p^{(k)}) ^Tp^{(k)}}p^{(k)}$$


$\text{Excel}$ 文件[计算实验（不动点迭代法）-学生.xlsx](../../Excel/非线性方程组的数值解法/计算实验（不动点迭代法）-学生.xlsx) 和 [计算实验（牛顿法+最速下降法）-学生(1).xlsx](../../Excel/非线性方程组的数值解法/计算实验（牛顿法+最速下降法）-学生(1).xlsx) 为课堂实验的文件。
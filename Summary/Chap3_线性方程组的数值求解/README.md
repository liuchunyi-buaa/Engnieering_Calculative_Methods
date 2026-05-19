## 知识点总结
本节内容对应的[PPT](../../PPT/第3章%20线性方程组的数值求解.pdf)

快速索引
- [知识点总结](#知识点总结)
- [范数与方程的形态、条件数](#范数与方程的形态条件数)
  - [向量的范数](#向量的范数)
  - [矩阵的范数](#矩阵的范数)
  - [方程的性态](#方程的性态)
  - [方程的条件数](#方程的条件数)
- [高斯消去法](#高斯消去法)
- [迭代法](#迭代法)
  - [Jacobi迭代法](#jacobi迭代法)
  - [Gauss-Seidel迭代法](#gauss-seidel迭代法)
  - [松弛法](#松弛法)
  - [收敛性质](#收敛性质)

本节研究的对象是 $n$ 阶线性方程组

$$
\begin{cases}
a_{11}x_1 + a_{12}x_2 + \dots + a_{1n} = b_1 \\
a_{21}x_1 + a_{22}x_2 + \dots + a_{2n} = b_2 \\
\vdots \\
a_{n1}x_1 + a_{n2}x_2 + \dots + a_{nn} = b_n
\end{cases}$$

转化为矩阵形式为 $Ax=b$，当 $|A| \neq 0$，则方程组有唯一解。

## 范数与方程的形态、条件数
### 向量的范数
有向量 $x = (x_1, x_2, \dots ,x_n)$

统一形式： $||x||_p=\left(|x_1|^p+|x_2|^p+\dots+|x_n|^p\right)^{\frac{1}{p}}$

常用向量范数

$$||x||_1=|x_1|+|x_2|+\dots+|x_n|$$

$$||x||_2=\sqrt{x_1^2+x_2^2+\dots+x_n^2}$$

$$||x||_{\infty}=max\{|x_1|+|x_2|+\dots+|x_n|\}$$

### 矩阵的范数

矩阵的范数等于范数最大的行向量的范数。

常用矩阵范数

$$\|A\|_1 = \max_{1\leq j\leq n} \left\lbrace\sum_{i=1}^n |a_{ij}|\right\rbrace$$

$$||A||_{\infty}=\max_{1\leq i\leq n}\left\lbrace\sum_{j=1}^n|a_{ij}| \right\rbrace$$

$$||A||_2=\sqrt{\lambda_{\max}(A^TA)}$$

其中 $\lambda_{\max}(A^TA)$ 表示 $A^TA$ 的最大特征值。

Frobenius范数

$$||A||_F=\sqrt{\sum_{i=1}^n\sum_{j=1}^na_{ij}^2}$$

**注意：** 课件上将 $||A||_2$ 与 $||A||_F$ 相混淆了

### 方程的性态
兑线性方程组

$$Ax=b$$

$A$ 和 $b$ 有微小扰动对解的影响。

$(A+\Delta A)(x+\Delta x)=(b+\Delta b)$ 中 $\Delta x$ 受 $\Delta A,\Delta b$ 的影响大小。

### 方程的条件数

矩阵 $A$ 的条件数 $\textrm{Cond}A=||A||*||A^{-1}||$

$\textrm{Cond}A\geq 1$ ， $\textrm{Cond}A$ 越小方程的扰动对解的影响最小、性态越好。

---

## 高斯消去法

思路：将 $A$ 通过行列变换转化为上三角矩阵。并在过程中不断选择主元。

## 迭代法

对线性方程组：

$$
\begin{cases}
a_{11}x_1+a_{12}x_2+\dots a_{1n} = b_1 \\
a_{21}x_1+a_{22}x_2+\dots a_{2n} = b_2 \\
\vdots\\
a_{n1}x_1+a_{n2}x_2+\dots a_{nn} = b_n \\
\end{cases}$$

移项变换为

$$ \begin{cases}
x_1 = -\dfrac{1}{a_{11}}(0+a_{12}x_2+\dots+a_{1n}x_n)+\dfrac{b_2}{a_{11}} \\
x_2 = -\dfrac{1}{a_{22}}(a_{21}x_1+0+\dots+a_{2n}x_n)+\dfrac{b_2}{a_{22}} \\
\vdots\\
x_n = -\dfrac{1}{a_{nn}}(a_{n1}x_1+a_{n2}x_2+\dots+0)+\dfrac{b_n}{a_{nn}} \\
\end{cases}$$

取 

$$A=\begin{pmatrix}
a_{11} & \dots & a_{1n} \\
\vdots & \ddots & \vdots \\
a_{n1} & \dots & a_{nn} \\
\end{pmatrix},
D=\begin{pmatrix}
a_{11} &  &  &  \\
 & a_{22} &  &  \\
 &  & \ddots &  \\
 &  &  & a_{nn} \\
\end{pmatrix}, b=\begin{pmatrix}
b_1 \\
b_2 \\
\vdots \\
b_n\end{pmatrix}$$

不难发现 

$$D^{-1}=\begin{pmatrix}
\dfrac{1}{a_{11}} &  &  &  \\
 & \dfrac{1}{a_{22}} &  &  \\
 &  & \ddots &  \\
 &  &  & \dfrac{1}{a_{nn}} \\
\end{pmatrix}$$

则 

$$x=-D^{-1}((A-D)x-b) \qquad {(1)}$$

这就是一个不动点方程

### Jacobi迭代法
直接利用 $(1)$ 式，完全由 $x^{(k)} = \left(x^{(k)}_1, x^{(k)}_2, \dots,x^{(k)}_n\right)^T$ 计算 $x^{(k+1)} = \left(x^{(k+1)}_1, x^{(k+1)}_2, \dots,x^{(k+1)}_n\right)^T$

$$x^{(k+1)}=-D^{-1}((A-D)x^{(k)}-b)$$

### Gauss-Seidel迭代法
**核心思想：** Jacobi迭代法中计算 $x_i^{(k+1)}$ 时，已经得到了 $x_1^{(k+1)},\dots,x_{i-1}^{(k+1)}$，用已经得到的分量去算其余分量。

迭代公式

$$x_i^{(k+1)}=-\dfrac{1}{a_{ii}}\left(\sum_{j=1}^{i-1}a_{ij}x_j^{(k+1)}+\sum_{j=i+1}^{n}a_{ij}x_j^{(k)}\right)+\dfrac{b_i}{a_{ii}}\qquad{(2)}$$

### 松弛法
由 $(2)$ 式可以得到 

$$\Delta x_i=x_i^{(k+1)}-x_i^{(k)}=-\dfrac{1}{a_{ii}}\left(\sum_{j=1}^{i-1}a_{ij}x_j^{(k+1)}+\sum_{j=i}^{n}a_{ij}x_j^{(k)}\right)+\dfrac{b_i}{a_{ii}}$$

考虑加速迭代速率，引入松弛因子 $\omega$ 使得

$$x^{(k+1)} = x^{(k)}+\omega\Delta x$$

从而的到松弛法迭代公式。

$$x^{(k+1)}_i=x^{(k)}_i-\dfrac{\omega}{a_{ii}}\left(\sum_{j=1}^{i-1}a_{ij}x_j^{(k+1)}+\sum_{j=i}^{n}a_{ij}x_j^{(k)}\right)+\dfrac{\omega b_i}{a_{ii}}$$

亦可写成与课件上相似的形式

$$x^{(k+1)}_i=(1-\omega)x^{(k)}_i-\dfrac{\omega}{a_{ii}}\left(\sum_{j=1}^{i-1}a_{ij}x_j^{(k+1)}+\sum_{j=i+1}^{n}a_{ij}x_j^{(k)}\right)+\dfrac{\omega b_i}{a_{ii}}$$

### 收敛性质
迭代法的迭代通式可表示为

$$x^{(k+1)}=Mx^{(k)}+f,\enspace k=0, 1, 2, \dots \qquad{(\textrm{I})}$$

由 $(\textrm{I})$ 式产生的向量序列收敛且极限与初值无关**当且仅当** $\rho(M)<1$ 即矩阵谱半径小于 $1$。(迭代法可用的条件)

**谱半径：** $\rho(M)=\max\lbrace|\lambda_1|, |\lambda_2|, \dots, |\lambda_n|\rbrace$，即特征值最大的绝对值

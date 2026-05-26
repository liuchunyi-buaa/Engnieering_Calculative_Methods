## 知识点总结
本章内容对应的[PPT](../../PPT/第6章%20函数的数值拟合与计算实验-2025版.pdf)
本章内容的课堂实验[Excel](../../Excel/函数的数值拟合/函数的数值拟合_课堂实验.xlsx)

快速索引
- [知识点总结](#知识点总结)
- [最小二乘法](#最小二乘法)

**问题定义**
使曲线能够在整体上刻画这组点的变化趋势而不需要通过每个点。

给 $m+1$ 对数据 $(x_i,y_i),i=0,1,2,\dots,m$ ，进行拟合。

选取 $n+1$ 个**连续且线性无关**的基函数 $\varphi_i(x),i=0,1,2,\dots,n$ ，得曲线族

$$P(x)=\sum_{i=0}^na_i\varphi(x)$$

## 最小二乘法
实现 $\sum_{i=0}^m\left(P(x_i)-y_i\right)^2$ 最小化

取

$$\delta(a_0,a_1,\dots,a_n)=\sum_{i=0}^m\left[\sum_{j=0}^na_j\varphi_j(x_i)-y_i\right]^2$$

使

$$\dfrac{\partial\delta}{\partial a_k}=0 ,\enspace k=0,1,2,\dots,n$$

得

$$\sum_{j=0}^n\left[a_j\sum_{i=0}^m\varphi_k(x_i)\varphi_j(x_i)\right]=\sum_{i=0}^my_i\varphi_k(x_i)$$

对于 $k=0,1,2,\dots,n$ 均要求成立，得以下方程组

$$
\begin{bmatrix}
\sum_{i=0}^m\varphi_0(x_i)\varphi_0(x_i) & \sum_{i=0}^m\varphi_1(x_i)\varphi_0(x_i) & \dots & \sum_{i=0}^m\varphi_0(x_i)\varphi_n(x_i) \\
\sum_{i=0}^m\varphi_1(x_i)\varphi_0(x_i) & \sum_{i=0}^m\varphi_1(x_i)\varphi_1(x_i) & \dots & \sum_{i=0}^m\varphi_1(x_i)\varphi_n(x_i) \\
\vdots & \vdots & \ddots & \vdots \\
\sum_{i=0}^m\varphi_n(x_i)\varphi_0(x_i) & \sum_{i=0}^m\varphi_n(x_i)\varphi_1(x_i) & \dots & \sum_{i=0}^m\varphi_n(x_i)\varphi_n(x_i) \\
\end{bmatrix}
\begin{bmatrix}
    a_0 \\
    a_1 \\
    \vdots \\
    a_n
\end{bmatrix}
=
\begin{bmatrix}
\sum_{i=0}^my_i\varphi_0(x_i) \\
\sum_{i=0}^my_i\varphi_1(x_i) \\
\vdots \\
\sum_{i=0}^my_i\varphi_n(x_i) \\
\end{bmatrix}
$$

实际上，我们在 $\text{Excel}$ 中常常把这些用向量表示，这样便于计算也便于理解。定义 
```math
x=(x_0,x_1,x_2\dots,x_m) \\
y=(y_0,y_1,y_2,\dots,y_m) \\
\varphi_j=[\varphi_j(x_0),\varphi_j(x_1),\varphi_j(x_2),\dots,\varphi_j(x_m)]
```

则上面的方程组可以化简为

$$
\begin{bmatrix}
\varphi_0\cdot\varphi_0 & \varphi_0\cdot\varphi_1 & \dots & \varphi_0\cdot\varphi_n \\
\varphi_1\cdot\varphi_0 & \varphi_1\cdot\varphi_1 & \dots & \varphi_1\cdot\varphi_n \\
\vdots & \vdots & \ddots & \vdots \\
\varphi_n\cdot\varphi_0 & \varphi_n\cdot\varphi_1 & \dots & \varphi_n\cdot\varphi_n \\
\end{bmatrix}
\begin{bmatrix}
    a_0 \\
    a_1 \\
    \vdots \\
    a_n
\end{bmatrix}
=
\begin{bmatrix}
y\cdot\varphi_0 \\
y\cdot\varphi_1 \\
\vdots \\
y\cdot\varphi_n \\
\end{bmatrix}
$$

向量点乘可以使用 $\text{Excel}$ 中的 `=SUMPRODUCT()` 函数进行计算。

## 矛盾方程组
设矛盾方程组

$$Ax=B$$

其中， $A$ 是 $m\times n$ 的系数矩阵，且 $m>n$ ， $x$ 是 $n\times1$ 的未知向量， $b$ 是 $m\times1$ 的常数向量。

目标：从严格等于零变为误差最小，用最小二乘法。

$$I=\sum_{i=1}^me_i^2=e^te=(b-Ax)^T(b-Ax)$$

整理得

$$I=b^Tb-2x^TA^Tb+x^TA^TAx$$

求极小值，即偏导为 $0$ 

$$\dfrac{\partial I}{\partial x}=-2A^Tb+2A^TAx$$

得解矛盾方程组的法方程

$$A^TAx=A^Tb$$
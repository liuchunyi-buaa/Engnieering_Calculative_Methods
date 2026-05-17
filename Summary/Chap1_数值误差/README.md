## 知识点总结
本节内容对应的[PPT](../../PPT/第1章课程导论、数值误差.pdf)

### 误差来源

1. 模型误差 **（客观存在）**：<u>建立的数学模型和实际问题之间的差别带来的误差</u>，如理想化模型等。
2. 观测无擦好 **（客观存在）**：对物理量观测的误差不可避免。
3. 截断误差 **（计算方法与过程引起）**：计算中有限过程代替无限过程。
4. 舍入误差 **（计算方法与过程引起）**：四舍五入引起的误差。

---

### 绝对误差与绝对误差限
一句话，误差就是 $真实值-观测值$
#### 绝对误差
设 $x$ 是准确值 $x^\*$ 的近似值，称 $e$ 是近似值x的绝对误差,简称误差。
$$e=x^*-x$$
#### 绝对误差限
称 $\varepsilon$ 为绝对误差限，简称误差限。

$$\left| \varepsilon \right| = \left| x^\* - x \right| \leq \varepsilon$$

则有 $x^\* = x \pm \varepsilon,\enspace x-\varepsilon\leq x^\* \leq x + \varepsilon$

~~例：~~ 用毫米刻度的直尺测量一长度为 $x^*$ 的物体，测得其长度的近似值为 $x = 
123mm$ ，由于直尺以毫米为刻度，所以其误差不超过 $0.5mm$，即 $\varepsilon = 0.5mm$ ~~（现在知道为什么基物实验里 $\Delta_仪$ 是最小刻度的一半了吧）~~

### 相对误差与相对误差限
一句话，相对误差就是 $绝对误差\div真实值$
#### 相对误差

$$e_r=\dfrac{e}{x^\*}=\dfrac{x^\*-x}{x^\*}$$
通常由下式计算：

$$\overline{e_r}=\dfrac{e}{x}=\dfrac{x^\*-x}{x}$$

~~废话，这个式子里不一样有 $x^\*$~~
#### 相对误差限

$$\left| e_r\right |\leq\varepsilon_r$$

---

### 有效数字 ⭐️⭐️⭐️
老师说这个期末必考

**定义：** 如果近似值 $x$ 的**误差限**是其某一位上的半个单位，且该位直到 $x$ 的第 $1$ 位非零数字一共有 $n$ 位，则称近似值 $x$ 有 $n$ 位有效数字。

例：取 $x^\*=1.732050808$
- 取 $x_1 = 1.73$，则 $|e|=0.002050808,|e_1|\leq0.005,\varepsilon_1=0.005$。所以是 $3$ 位有效数字。
- 取 $x_2=1.7320$，则 $|e_2|=0.000050808,0.00005<|e_2|\leq0.0005,\varepsilon_2 =0.0005$，所以是 $4$ 位有效数字。

由定义不难证明：**四舍五入到哪一位，有效数字就到哪一位**。

~~课件上还有补充内容：精确度、近似数计算规则~~

---

### 数据误差的影响
作者认为该部分证明了解即可，记住结论要紧。

#### ~~基于泰勒公式的证明~~
考虑函数的误差与变量误差的关系，令精确值 $y^\*=f\left(x_1^\*, x_2^\* \right)$，观测值 $y=f\left(x_1,x_2 \right)$。

由泰勒公式

$$f\left(x_1^\*, x_2^\*\right)\approx f\left(x_1, x_2 \right) + \dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_1}\left(x^\*-x_1 \right)+\dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_2}\left(x^\*-x_2 \right)$$

则

$$e\left(y \right)=y^\*-y\approx\dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_1}e\left(x_1 \right)+\dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_2}e\left(x_2 \right)$$

$$e_r\left(y \right)\approx\dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_1} \dfrac{x_1}{y} e_r\left(x_1 \right)+\dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_2}\dfrac{x_2}{y}e_r\left(x_2 \right)$$

#### 常用结论 ⭐️
**注意：这里是 $\approx$ 而不是 $=$**

$$\begin{aligned}
e\left(x_1+x_2 \right)\approx e\left(x_1 \right) + e(x_2)\\
e\left(x_1-x_2 \right) \approx e(x_1) - e(x_2)\\
e(x_1x_2)\approx x_2e(x_1)+x_1e(x_2)\\
e\left(\dfrac{x_1}{x_1} \right) \approx \dfrac{e(x_1)}{x_2}-\dfrac{x_1e(x_1)}{x_2^2},\enspace x_2 \neq 0
\end{aligned}$$

计算 $e_r(f(x_1,x_2))$ 使用公式 $e_r\left(y \right)\approx\dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_1} \dfrac{x_1}{y} e_r\left(x_1 \right)+\dfrac{\partial f\left(x_1, x_2 \right)}{\partial x_2}\dfrac{x_2}{y}e_r\left(x_2 \right)$ 计算即可，这里不再详细列出。

---

### ~~机器数系~~
~~说实话，我真不觉得这个会考~~
#### 进制转换
记住 $b$ 进制下的数表示为 $\Sigma a_i b^i$，辅以取余和整除的性质，以十进制为桥梁即可，整数小数都一样。
#### 数的浮点表示
<p align="center">
  <img src="assets/float32_storage.svg" alt="浮点数表示", width="95%"/>
</p>

#### ~~机器数系~~
就是把前面浮点数的表示改改参数。

---

### 误差危害的防治
#### 数值稳定的计算公式
$$\left| \dfrac{e_{n+1}}{e_n}\right|\leq1$$
即误差不会指数爆炸

#### 减小误差八股文
- 尽量避免相近两数相减
- 使用数值稳定的计算公式
- 尽量避免用绝对值很大的数作乘数
- 防止大数“吃掉”小数
- 简化计算步骤，减少运算次数（秦九韶法）

### 课堂上机题
$$f(x)=a_0x^n+a_1x^{n-1}+\dots+a_n$$
令 $x=1.001, n=9999,a_n=1+n$

秦九韶法：
$$f(x)=\left(\left(\left((a_0x+a_1)x \dots \right)x+a_{n-1} \right)x \right)+a_n$$

观察：
1. 计算时间差异
2. 计算结果差异
3. 采用指数函数比较结果

具体实现可参考[秦九韶法参考代码](../../Code/秦九韶法.cpp)


**Output**
```
Method 1: n = 9999 x = 1.001 f = 2.19276e+10 t = 42.039ms
Method 2: n = 9999 x = 1.001 f = 2.19276e+10 t = 0.015ms
Method 3: n = 9999 x = 1.001 f = 2.19276e+10 t = 0.071ms
```

---
<a href="https://github.com/liuchunyi-buaa">
    <img src="https://img.shields.io/badge/Author-刘纯一-3776AB?logo=github&logoColor=white" />
</a>
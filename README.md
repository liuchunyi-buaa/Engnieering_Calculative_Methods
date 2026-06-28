# 工程计算方法 ♿️ 复习仓库hhh

<p align="center">
  <a href="https://github.com/liuchunyi-buaa">
    <img src="https://img.shields.io/badge/Author & Maintainer-刘纯一-3776AB?logo=github&logoColor=white" alt="Author" />
  </a>
  <a href="https://github.com/Ordinary-High">
    <img src="https://img.shields.io/badge/Maintainer-高逸凡-2EA44F?logo=github&logoColor=white" alt="Author" />
  </a>
</p>

<p align="center">
  <b>在这个AI横行的时代，仍有非遗传承人手搓知识点总结与代码🪬<br>考试时可直接复用的代码🧑‍🦼 + 分章节的知识点梳理📖 + 历次作业答案📚<br>如果对你有帮助的话，给个⭐️吧</b>
</p>

---

## ⚠️ 免责声明

该仓库中的代码与知识点总结均是作者根据自己的理解和习惯编写，**并不保证完全正确**，仅供参考，望批判使用。如有疑问，请以课本和老师授课内容为准。

---

## 📖 仓库介绍

本仓库创建初衷是为了作者自己复习和整理「工程计算方法」课程代码以便考试使用。想到反正要穿到 GitHub上管理，不如分享出来供复习参考。

**课程信息**：2025–2026 学年春学期，刘杰老师授课。

### 📂 各文件夹说明

- **[Code](Code/)** — 存放参考代码，为了考试时可以快速复用，作者大量采用**宏定义（`#define`）和全局变量**，使用时阅读文件头部注释，在标记的位置按需修改参数，编译/运行即可。包含 C++ 和 Python 两种语言实现。

- **[PPT](PPT/)** — 上课所用的完整课件（PDF 格式），共 11 章，部分章节分多次课讲授。

- **[Summary](Summary/)** — 作者分章节整理的知识点总结，按知识点归为文件夹，**建议复习时从这个文件夹开始**。文档中已在合适的位置链接到了对应的 PPT 和代码文件。

- **[Excel](Excel/)** — 课堂实验所用的 Excel 文件，并总结了常用 Excel 函数，涵盖插值方法、函数拟合、线性方程组求解、非线性方程求解、质量与可靠性统计等内容。

- **[Homework](Homework/)** - 课程作业及其解答

- **[计算方法（合并）(2).pdf](计算方法（合并）(2).pdf)** — 电子版课本。

---

## 📁 仓库结构

```
.
├── Code/                           # 参考代码（可直接复用）
│   ├── 非线性方程的数值解法.cpp
│   ├── 线性方程组的数值求解.cpp
│   ├── 插值方法.cpp
│   ├── 数值积分方法.cpp
│   ├── 常微分方程的数值解法.cpp
│   ├── 正态分布.cpp
│   ├── 秦九韶法.cpp
│   ├── 线性搜索算法.cpp
│   ├── 排序算法.cpp
│   ├── 树的遍历算法.cpp
│   ├── 图的遍历与最短路径.cpp
│   ├── Guass求积公式.py
│   ├── 非线性方程组的数值解法.py
│   ├── 函数的数值拟合.py
│   ├── 线性方程组的数值求解.py
│   ├── sample_graph.txt
│   └── README.md
│
├── PPT/                            # 上课课件（PDF）
│   ├── 第1章课程导论、数值误差.pdf
│   ├── 第2章 非线性方程的数值解法.pdf
│   ├── 第3章 线性方程组的数值求解.pdf
│   ├── 第4章 非线性方程组的数值求解.pdf
│   ├── 第5章 插值方法与计算实验-第一次课.pdf
│   ├── 第5章 插值方法与计算实验-第二次课-带计算实验.pdf
│   ├── 第6章 函数的数值拟合与计算实验-2025版.pdf
│   ├── 第7章 数值积分-第一次课-2026.pdf
│   ├── 第7章 数值积分-第二次课-2026.pdf
│   ├── 第8章 常微分方程数值解法（理论）-2026.pdf
│   ├── 第8章 常微分方程数值解法（实验）-2026.pdf
│   ├── 第9章 质量与可靠性统计方法.pdf
│   ├── 第9章 质量与可靠性统计方法与计算实验（二）-2026.pdf
│   ├── 第10章 线性搜索与排序算法.pdf
│   ├── 第11章 网络与图相关算法(2026).pdf
│   └── 考前辅导-2026.pdf
│
├── Summary/                        # 知识点总结（按章节）
│   ├── Chap1_数值误差/
│   ├── Chap2_非线性方程组的数值解法/
│   ├── Chap3_线性方程组的数值求解/
│   ├── Chap4_非线性方程组的数值解法/
│   ├── Chap5_插值方法/
│   ├── Chap6_函数的数值拟合/
│   ├── Chap7_数值积分/
│   ├── Chap8_常微分方程数值解法/
│   ├── Chap9_质量与可靠性统计方法/
│   ├── Chap10_线性搜索与排序算法/
│   ├── Chap11_网络与图相关算法/
│   └── README.md
│
├── Excel/                          # Excel 课堂实验文件
│   ├── 非线性方程组的数值解法/
│   ├── 线性方程组的数值求解/
│   ├── 插值方法/
│   ├── 函数的数值拟合/
│   ├── 质量与可靠性统计方法/
│   └── README.md
│
├── Homework/                       # 课程作业及解答
│   ├── 第1次作业/
│   ├── 第2次作业/
│   ├── 第3次作业/
│   ├── 第4次作业/
│   ├── 第5次作业/
│   ├── 第6次作业/
│   ├── 第7次作业/
│   ├── 第8次作业/
│   ├── 第9次作业/
│   ├── 第10次作业/
│   ├── 第11次作业/
│   ├── 第12次作业/
│   └── 第14次作业/
│
├── 计算方法（合并）(2).pdf           # 电子版课本
├── requirements.txt                # Python 依赖
├── CHANGELOG.md                    # 更新日志
├── CLAUDE.md                       # Claude Code 使用指南
├── LICENSE                         # MIT 许可证
└── README.md                       # 本文件
```

---

## 📌 版本要求

### Python 环境

> 本项目 Python 代码仅使用了 `numpy`、`math`、`types` 三个模块。类型标注 `list[float]` 由 [PEP 585](https://peps.python.org/pep-0585/) 引入，需 Python ≥ 3.9。

| 项目   | 最低要求 | 推荐版本                | 依据                                                                     |
| ------ | -------- | ----------------------- | ------------------------------------------------------------------------ |
| Python | **3.9**  | 3.11+                   | PEP 585 类型标注语法（`list[float]`）自 Python 3.9 起可用（2020/10/05）  |
| NumPy  | **1.21** | 1.26.4（< 2.0）         | [NumPy 1.21.0](https://pypi.org/project/numpy/1.21.0/) 发布于 2021/06/22，支持 Python ≥ 3.7；[NumPy 2.0](https://numpy.org/news/) 存在 ABI 不兼容且需 Python ≥ 3.10 |

> ⚠️ **注意**：NumPy 2.x（2024/06 发布）有 [breaking changes](https://numpy.org/devdocs/numpy_2_0_migration_guide.html)，且 NumPy 2.1+ 要求 Python ≥ 3.10。为保证 Python 3.9 用户的兼容性，requirements.txt 将 NumPy 约束在 `<2.0`。

一键安装：

```bash
pip install -r requirements.txt
```

### C++ 环境

> **作者开发环境**：macOS + Apple Clang（Xcode 16），C++17，`-std=c++17` 编译。

| 项目     | 最低要求                    | 推荐版本                     | 依据                                                                                    |
| -------- | --------------------------- | ---------------------------- | --------------------------------------------------------------------------------------- |
| C++ 标准 | **C++11**                   | C++17                        | 代码中 `vector<vector<double>>`（无空格）为 C++11「右尖括号改进」[特性](https://isocpp.org/wiki/faq/cpp11-language-misc#right-angles) |
| GCC      | **4.8+**                    | 9+                           | [GCC 4.8.1](https://gcc.gnu.org/gcc-4.8/) 起对 C++11 提供完整支持                      |
| Clang    | **3.3+**                    | 10+                          | Clang 3.3 起完整支持 C++11                                                              |
| MSVC     | **2015**（v14.0）           | 2019+                        | Visual Studio 2015 起支持 C++11 核心特性                                                |

编译示例：

```bash
# GCC / Clang
g++ -std=c++11 文件名.cpp -o 输出名

# MSVC
cl /std:c++11 文件名.cpp
```

---

## 🚀 快速开始

### 代码使用方式

`Code/` 文件夹下的代码均通过**宏定义**和**全局变量**来配置参数，使用时只需：

1. 打开对应 `.cpp` / `.py` 文件
2. 阅读文件头部的注释说明
3. 在标记的位置修改 `#define` 宏或全局变量（如方程系数、初始值、步长等）
4. 编译/运行即可

> **考试建议**：考前把所有代码结合课堂知识改改参数跑一遍，熟悉修改流程。

### 复习路线建议

1. **从 [Summary](Summary/) 开始** — 按章节阅读知识总结，快速回顾理论与公式
2. **对照 [PPT](PPT/)** — 结合课件巩固细节与例题
3. **动手跑 [Code](Code/)** — 修改参数运行代码，验证理解
4. **实操 [Excel](Excel/)** — 完成课堂实验题目，掌握 Excel 计算技巧

### 克隆仓库

```bash
git clone https://github.com/liuchunyi-buaa/Engnieering_Calculative_Methods.git
cd Engnieering_Calculative_Methods
pip install -r requirements.txt   # Python 依赖（可选）
```

---

<p align="center">
  仓库持续更新中✍🏻<br>
  <sub>如有错误或改进建议，欢迎 <a href="mailto:24374180@buaa.edu.cn">联系我们</a> 或提交 Issue / Pull Request。</sub>
</p>

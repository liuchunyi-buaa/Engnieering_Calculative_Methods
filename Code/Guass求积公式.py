import numpy as np
import math
import types

N = 2 # 多项式的次数
EPS = 1e-9 # 误差限
R = 0 # 权函数的次数（如果为多项式）


# 可以设置不是多项式的权函数
def rho(x: float) -> float:
    return 1.


def culInt(n: int) -> float:
    res, step = 0, 1e-4
    i = 0
    c = [7./90, 32./90, 12./90, 32./90, 7./90]
    while i < (1 - 0) / step:
        a, b = i * step, (i + 1) * step
        s = (b - a) / 4
        for j in range(5):
            p = a + j * s
            res += (rho(p) * (p ** n) * c[j]) * step
        i += 1
    return res


def CulInt(r: float, n: int) -> float:
    return 1 / (n + r + 1)


def F(x: list[float]) -> list[float]:
    res = [0.] * (2 * N + 2)
    for i in range(2 * N + 2):
        for j in range(N + 1):
            res[i] += x[j] * x[j + N + 1] ** i
        res[i] -= CulInt(R, i) # 解析解
        # res[i] -= culInt(i) # 数值解
    return res


def naF(x: list[float]) -> list[list[float]]:
    res = [[0.] * (2 * N + 2) for _ in range(2 * N + 2)]
    for i in range(2 * N + 2):
        for j in range(N + 1):
            res[i][j] = x[N + j + 1] ** i
        for j in range(N + 1, 2 * N + 2):
            if i == 0:
                res[i][j] = 0
                continue
            res[i][j] = i * x[j - N - 1] * x[j] ** (i - 1)
    return res

def display(x: list[float]):
    for i in range(N + 1):
        print(f"A{i}={x[i]}", end=' ')
    for i in range(N + 1, 2 * N + 2):
        print(f"X{i - N - 1}={x[i]}", end=" ")
    print()


xk = [1/N for _ in range(N + 1)] + [i / (N + 2) for i in range(1, N + 2)]
e = 1
r = 0
while e > EPS:
    r += 1
    f, nf = np.array(F(xk)), np.array(naF(xk))
    nf_inv = np.linalg.inv(nf)
    dx = - nf_inv @ f
    e = sum(np.abs(dx))
    print(f"{r}: e={e}")
    display(xk)
    xk += dx


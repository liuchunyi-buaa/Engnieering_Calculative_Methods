import numpy as np

# 在这里修改插值节点 X 和 Y，下标从 0 开始
X = [0.5, 1.2, 2.8, 3.7, 4.5]
Y = [0.5278, 0.9875, -1.3239, 0.2325, 0.6741]

# 边界条件模式: 1 / 2 / 3
#   1: 给定两端二阶导数 S''(x0), S''(xn)           → 填写 M0_GIVEN, MN_GIVEN
#   2: 给定两端一阶导数 S'(x0), S'(xn)              → 填写 Y0_PRIME, YN_PRIME
#   3: 周期边界条件 (要求 y0 == yn)                 → 无需额外参数
MODE = 2

# 第1类边界条件 (MODE=1)
M0_GIVEN = 2.0
MN_GIVEN = 2.0

# 第2类边界条件 (MODE=2)
Y0_PRIME = 3.4512
YN_PRIME = 2.2734

# 拟合输出区间 [A, B] 及步长
A = 0.0
B = 4.5
STEP = 0.5


def thomas(a, b, c, d):
    m = len(d)
    cp, dp = np.zeros(m), np.zeros(m)
    cp[0] = c[0] / b[0]
    dp[0] = d[0] / b[0]
    for i in range(1, m):
        denom = b[i] - a[i] * cp[i - 1]
        if i < m - 1:
            cp[i] = c[i] / denom
        dp[i] = (d[i] - a[i] * dp[i - 1]) / denom
    d[m - 1] = dp[m - 1]
    for i in range(m - 2, -1, -1):
        d[i] = dp[i] - cp[i] * d[i + 1]
    return d


def solve_cyclic(a, b, c, d, cl, cr):
    m = len(d)
    aT, bT, cT = a.copy(), b.copy(), c.copy()
    aT[0] = 0.0
    cT[m - 1] = 0.0
    bT[0] -= cl * cr
    bT[m - 1] -= 1.0
    u = np.zeros(m); v = np.zeros(m)
    u[0] = cl; u[m - 1] = 1.0
    v[0] = cr; v[m - 1] = 1.0
    y = thomas(aT, bT, cT, d.copy())
    z = thomas(aT.copy(), bT.copy(), cT.copy(), u.copy())
    r = np.dot(v, y) / (1.0 + np.dot(v, z))
    return y - r * z


def compute_M(X, Y, mode, **kw):
    n = len(X) - 1
    h = [X[i + 1] - X[i] for i in range(n)]

    if mode in (1, 2):
        m = n + 1
        a = np.zeros(m); b = np.full(m, 2.0); c = np.zeros(m); d = np.zeros(m)

        if mode == 1:
            b[0] = 1.0; d[0] = kw['M0']
            b[n] = 1.0; d[n] = kw['Mn']
        else:
            c[0] = 1.0
            d[0] = 6.0 / h[0] * ((Y[1] - Y[0]) / h[0] - kw['y0p'])
            a[n] = 1.0
            d[n] = 6.0 / h[n-1] * (kw['ynp'] - (Y[n] - Y[n-1]) / h[n-1])

        for i in range(1, n):
            mu = h[i-1] / (h[i-1] + h[i])
            lam = h[i] / (h[i-1] + h[i])
            a[i] = mu; c[i] = lam
            d[i] = 6.0 / (h[i-1] + h[i]) * ((Y[i+1] - Y[i]) / h[i] - (Y[i] - Y[i-1]) / h[i-1])

        return list(thomas(a, b, c, d))

    else:
        m = n
        a = np.zeros(m); b = np.full(m, 2.0); c = np.zeros(m); d = np.zeros(m)

        lam0 = h[0] / (h[0] + h[n-1])
        mu0 = h[n-1] / (h[0] + h[n-1])
        c[0] = lam0
        d[0] = 6.0 / (h[0] + h[n-1]) * ((Y[1] - Y[0]) / h[0] - (Y[n] - Y[n-1]) / h[n-1])

        for i in range(1, n - 1):
            mu = h[i-1] / (h[i-1] + h[i])
            lam = h[i] / (h[i-1] + h[i])
            a[i] = mu; c[i] = lam
            d[i] = 6.0 / (h[i-1] + h[i]) * ((Y[i+1] - Y[i]) / h[i] - (Y[i] - Y[i-1]) / h[i-1])

        mu_last = h[n-2] / (h[n-2] + h[n-1])
        lam_last = h[n-1] / (h[n-2] + h[n-1])
        a[n-1] = mu_last
        d[n-1] = 6.0 / (h[n-2] + h[n-1]) * ((Y[n] - Y[n-1]) / h[n-1] - (Y[n-1] - Y[n-2]) / h[n-2])

        M0n = solve_cyclic(a, b, c, d, mu0, lam_last)
        return list(M0n) + [M0n[0]]


def spline(x, X, Y, M):
    n = len(X) - 1
    if x <= X[0]: i = 0
    elif x >= X[n]: i = n - 1
    else:
        for k in range(n):
            if X[k] <= x <= X[k + 1]: i = k; break
    hi = X[i+1] - X[i]
    dr = X[i+1] - x
    dl = x - X[i]
    return (M[i] * dr**3 / (6*hi) + M[i+1] * dl**3 / (6*hi) +
            (Y[i]/hi - M[i]*hi/6) * dr + (Y[i+1]/hi - M[i+1]*hi/6) * dl)


if __name__ == '__main__':
    kw = {}
    if MODE == 1: kw = {'M0': M0_GIVEN, 'Mn': MN_GIVEN}
    elif MODE == 2: kw = {'y0p': Y0_PRIME, 'ynp': YN_PRIME}
    M = compute_M(X, Y, MODE, **kw)
    n = len(X) - 1
    h = [X[i+1] - X[i] for i in range(n)]

    print("M:")
    for i in range(n + 1):
        print(f"  M[{i}] = {M[i]:.12f}")

    print("mu & lambda:")
    if MODE in (1, 2):
        if MODE == 1:
            print(f"  i=0: mu=0, lambda=0")
        else:
            print(f"  i=0: mu=0, lambda=1")
        for i in range(1, n):
            mu = h[i-1] / (h[i-1] + h[i])
            lam = h[i] / (h[i-1] + h[i])
            print(f"  i={i}: mu={mu:.6f}, lambda={lam:.6f}")
        if MODE == 1:
            print(f"  i={n}: mu=0, lambda=0")
        else:
            print(f"  i={n}: mu=1, lambda=0")
    else:
        lam0 = h[0] / (h[0] + h[n-1])
        mu0 = h[n-1] / (h[0] + h[n-1])
        print(f"  i=0: mu={mu0:.6f}, lambda={lam0:.6f}")
        for i in range(1, n - 1):
            mu = h[i-1] / (h[i-1] + h[i])
            lam = h[i] / (h[i-1] + h[i])
            print(f"  i={i}: mu={mu:.6f}, lambda={lam:.6f}")
        mu_last = h[n-2] / (h[n-2] + h[n-1])
        lam_last = h[n-1] / (h[n-2] + h[n-1])
        print(f"  i={n-1}: mu={mu_last:.6f}, lambda={lam_last:.6f}")

    print("midpoint check:")
    for i in range(n):
        xm = (X[i] + X[i+1]) / 2
        print(f"  S({xm:.4f}) = {spline(xm, X, Y, M):.12f}")

    print(f"interval [{A}, {B}] step={STEP}:")
    x = A
    while x <= B + 1e-12:
        print(f"  {x:.6f} {spline(x, X, Y, M):.12f}")
        x += STEP

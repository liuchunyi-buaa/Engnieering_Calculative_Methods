from math import log, cos, exp
import numpy as np

t = [2 ** i for i in range(7)]
w = [4.22, 4.02, 3.85, 4.59, 3.44, 3.02, 2.59]

# 在这里修改已知的节点
X = [log(i) for i in t]
Y = [log(i) for i in w]

# 在这里设置基函数
Phi = [lambda x: x, lambda x: 1]

m = len(X)
n = len(Phi)

Phi_vals = np.array([[phi(x) for x in X] for phi in Phi])

G = np.array([[np.dot(Phi_vals[k], Phi_vals[j]) for j in range(n)] for k in range(n)])
b = np.array([np.dot(Y, Phi_vals[k]) for k in range(n)])

a = np.linalg.solve(G, b)

print("G ="); print(G)
print("b ="); print(b)
print("a ="); print(a)

print(f"A={exp(a[1]):.6f}, s={a[0]:.6f}")
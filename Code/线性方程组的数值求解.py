import numpy as np

# 在这了定义你的 Ax=B 以及初值和误差限
# 注意 A 的主对角线上不要有 0
A = [[1, 1, 0, 0],
     [0, 1, 0, -2],
     [0, -1, 1, 1],
     [0, -1, 0, 3]]
B = [1, 1, 1, 1]
INIT = [1, 1, 1, 1]
EPS = 1e-6


def Jacobi(a, b, x0):
    x = np.array([x0 for _ in range(2)], dtype=np.float64)
    a = np.array(a, dtype=np.float64)
    b = np.array(b, dtype=np.float64)
    d = np.diag(np.diag(a))                    
    print("Jacobi")
    cnt, e = 0, 1.
    while e > EPS and cnt < 100:
        k, kk = cnt % 2, (cnt + 1) % 2
        cnt += 1
        x[kk] = -np.linalg.inv(d) @ (((a - d) @ x[k]) - b)
        e = sum(abs(x[k] - x[kk]))
        print(f"{cnt} x =", *x[kk], f"e = {e}")
    return x[cnt % 2]


def Gauss_Seidel(a, b, x0):
    x = np.array([x0 for _ in range(2)], dtype=np.float64)
    a = np.array(a, dtype=np.float64)
    b = np.array(b, dtype=np.float64)
    dl = np.tril(a)                             
    u  = np.triu(a, 1)                          
    print("Gauss-Seidel")
    cnt, e = 0, 1.
    while e > EPS and cnt < 100:
        k, kk = cnt % 2, (cnt + 1) % 2
        cnt += 1
        x[kk] = np.linalg.solve(dl, b - u @ x[k])
        e = sum(abs(x[k] - x[kk]))
        print(f"{cnt} x =", *x[kk], f"e = {e}")
    return x[cnt % 2]


def Relaxation(a, b, x0, omega=0.9):
    x = np.array([x0 for _ in range(2)], dtype=np.float64)
    a = np.array(a, dtype=np.float64)
    b = np.array(b, dtype=np.float64)
    dl = np.tril(a)                             
    u  = np.triu(a, 1)
    cnt, e = 0, 1.
    while e > EPS and cnt < 100:
        k, kk = cnt % 2, (cnt + 1) % 2
        cnt += 1
        x_gs = np.linalg.solve(dl, b - u @ x[k])      
        x[kk] = x[k] + omega * (x_gs - x[k])          
        e = sum(abs(x[k] - x[kk]))
        print(f"{cnt} x =", *x[kk], f"e = {e}")
    return x[cnt % 2]


if __name__ == "__main__":
    ans = Jacobi(A, B, INIT)
    print("Jacobi result:", *ans, end="\n\n")

    ans = Gauss_Seidel(A, B, INIT)
    print("Gauss-Seidel result:", *ans, end="\n\n")

    ans = Relaxation(A, B, INIT, omega=0.9)
    print("Relaxation result:", *ans)

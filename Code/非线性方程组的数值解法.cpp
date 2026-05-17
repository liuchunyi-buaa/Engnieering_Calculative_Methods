#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

#define eps 1e-6

double f(double x)
{
    return exp(x) + 2 * x;
}

double f_(double x)
{
    return exp(x) + 2;
}

double bisec(double l, double r, double (*func)(double))
{
    double mid, e = 1.;
    while (e > eps)
    {
        mid = (l + r) / 2;
        if(func(mid) * func(l) < 0) r = mid;
        else if(func(mid) * func(r) < 0) l = mid;
        e = fabs(r - l);
    }
    return mid;
}

double newton(double x0, double (*f)(double), double (*ff)(double))
{
    double xk = x0, xkk, e=1.;
    while(e > eps)
    {
        xkk = xk - f(xk) / ff(xkk);
        e = fabs(xkk - xk);
        xk = xkk;
    }
    return xk;
}

double secant(double x0, double x1, double (*f)(double))
{
    double xkk, xk = x1, xk_ = x0, e = 1.;
    while(e > eps)
    {
        xkk = xk - f(xk) / (f(xk) - f(xk_)) * (xk - xk_);
        e = fabs(xkk - xk);
        xk_ = xk, xk = xkk; // 注意这里的幅值顺序不能调换
    }
    return xkk;
}

int main()
{
    printf("%lf\n", bisec(-2, 4, f));
    printf("%lf\n", newton(1, f, f_));
    printf("%lf\n", secant(-1, 1, f));
    return 0;
}
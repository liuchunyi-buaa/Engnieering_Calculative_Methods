#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define h 1e-2
#define A 0.
#define B 2.
#define Y0 1.
#define EPS 1e-9

double func(double x, double y)
{
    return x - y + 1;
}

double Euler(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        yn = yn + h * f(xn, yn);
        xn += step;
    }
    return yn;
}

double Euler_imp(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double tmp = yn + h * f(xn, yn), xnn = xn + h;
        yn = yn + h / 2 *(f(xn, yn) + f(xnn, tmp));
        xn += step;
    }
    return yn;
}

double trap(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double yk =yn + h * f(xn, yn), e = 1.;
        while (e > EPS)
        {
            double ykk = yn + h / 2 * (f(xn, yn) + f(xn + h, yk));
            e = fabs(ykk - yk);
            yk = ykk;
        }
        yn = yk;
        xn += step;
    }
    return yn;
}

double Runge_Kutta2(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double k1 = h * f(xn, yn);
        double k2 = h * f(xn + 2 * h / 3, yn + 2 * k1 / 3);
        yn = yn + (k1 + 3 * k2) / 4;
        xn += step;
    }
    return yn;
}

double Runge_Kutta4(double (*f)(double, double), double l, double r, double y0, double step)
{
    double xn = l, yn = y0;
    while (xn < r)
    {
        double k1 = h * f(xn, yn);
        double k2 = h * f(xn + step / 2, yn + k1 / 2);
        double k3 = h * f(xn + step / 2, yn + k2 / 2);
        double k4 = h * f(xn + step / 2, yn + k3);
        yn = yn + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        xn += step;
    }
    return yn;
}

int main()
{
    cout << "Euler " << Euler(func, A, B, Y0, h) << endl;
    cout << "Euler_imp " << Euler_imp(func, A, B, Y0, h) << endl;
    cout << "trap " << trap(func, A, B, Y0, h) << endl;
    cout << "Runge-Kutta2 " << Runge_Kutta2(func, A, B, Y0, h) << endl;
    cout << "Runge-Kutta4 " << Runge_Kutta4(func, A, B, Y0, h) << endl;
}
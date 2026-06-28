#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define EPS 1e-6 // 误差限
#define A 0 // 区间[a, b]左端点
#define B 1. // 区间[a, b]右端点

// Cotes系数列表
const vector<vector<double>> C = {
    {},
    {1./2, 1./2},
    {1./6, 4./6, 1./6},
    {1./8, 3./8, 3./8, 1./8},
    {7./90, 32./90, 12./90, 32./90, 7./90},
    {19./288, 75./288, 50./288, 50./288, 75./288, 19./288},
    {41./840, 216./840, 27./840, 272./840, 27./840, 216./840, 41./840},
    {751./17280, 3577./17280, 1323./17280, 2989./17280, 2989./17280, 1323./17280, 3577./17280, 751./17280},
    {989./28350, 5888./28350, -928./28350, 10496./28350, -4540./28350, 10496./28350, -928./28350, 5888./28350, 989./28350}
};

// 待积分函数
double funcToInt(double x)
{
    return exp(-x);
}

double Newton_Cotes(double (*f)(double), double a, double b, double n)
{
    double res = 0, h = (b - a) / n;
    for(int i = 0; i <= n; i ++) res += C[n][i] * f(a + i * h);
    res *= (b - a);
    return res;
}

double comp_ti(double (*f)(double), double a, double b)
{
    double Tk, Tkk, e = 1, h = b - a;
    Tk = h / 2 * (f(a) + f(b));
    int k = 2;
    while (e > EPS)
    {
        Tkk = Tk / 2;
        h /= 2;
        for(int i = 1; i <= k / 2; i ++) Tkk += h * f(a + (2 * i - 1) * h);
        e = fabs(Tkk - Tk);
        cout << "k=" <<  k << " Tk=" << Tk << " e=" << e << endl;
        Tk = Tkk;
        k *= 2;
    }
    return Tk;
}

void Romberg(double (*f)(double), double a, double b, int r)
{
    vector<vector<double>> tscr;
    int k = r + 5;
    tscr.push_back(vector<double> (k, 0));
    double h = b - a;
    tscr[0][1] = h / 2 * (f(a) + f(b));
    for(int i = 2; i < k; i ++)
    {
        h /= 2;
        tscr[0][i] = tscr[0][i - 1] / 2;
        for(int j = 1; j <= ((1 << (i - 1)) / 2); j ++) tscr[0][i] += h * f(a + h * (2 * j - 1));
    }

    for(int i = 1; i < 4; i ++)
    {
        k -= 1;
        tscr.push_back(vector<double> (k, 0));
        for(int j = 1; j < k; j ++) tscr[i][j] = (tscr[i - 1][j + 1] * pow(4, i) - tscr[i - 1][j]) / (pow(4, i) - 1);
    }

    vector<char> name = {'T', 'S', 'C', 'R'};
    for(int i = 0; i < 4; i ++)
    {
        int tmp = r + 3 - i;
        for(int j = 1; j <= tmp; j ++) printf("%c%d=%lf ", name[i], 1 << j, tscr[i][j]);
        cout << endl;
    }
    return;
}

int main()
{
    cout << "梯形公式: " << Newton_Cotes(funcToInt, A, B, 1) << endl;
    cout << "\nSimpson公式: " << Newton_Cotes(funcToInt, A, B, 2) << endl;
    cout << "\nNewton公式: " << Newton_Cotes(funcToInt, A, B, 3) << endl;
    cout << "\nCotes公式: " << Newton_Cotes(funcToInt, A, B, 4) << endl;
    cout << "\n复化梯形公式: \n" << comp_ti(funcToInt, A, B) << endl;
    cout << "\nRomberg:" << endl;
    Romberg(funcToInt, A, B, 8);
}
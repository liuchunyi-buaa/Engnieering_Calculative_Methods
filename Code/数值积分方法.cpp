#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

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

double funcToInt(double x)
{
    return 1./x;
}

double Newton_Cotes(double (*f)(double), double a, double b, double n)
{
    double res = 0, h = (b - a) / n;
    for(int i = 0; i <= n; i ++) res += C[n][i] * f(a + i * h);
    res *= (b - a);
    return res;
}

int main()
{
    cout << "梯形公式: " << Newton_Cotes(funcToInt, 1, 2, 1) << endl;
    cout << "Simpson公式: " << Newton_Cotes(funcToInt, 1, 2, 2) << endl;
    cout << "Newton公式: " << Newton_Cotes(funcToInt, 1, 2, 3) << endl;
    cout << "Cotes公式: " << Newton_Cotes(funcToInt, 1, 2, 4) << endl;
}
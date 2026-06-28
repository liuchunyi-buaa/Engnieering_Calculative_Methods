/*
线性方程组的数值求解一共有两个文件
该文件使用的是逐个元素计算的方法，没有使用矩阵运算
*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;

// 你需要在这里修改方程组的形状和误差限
#define N 4
#define EPS 1e-6

// 在这里修改方程组，注意要与你之前设置的方程组形状对应
// 注意，如果你使用这个文件的话，必须保证 a 主对角线上的元素不为0
const vector<vector<double>> a = {
    {1, 1, 0, 0},
    {0, 1, 0, -2},
    {0, -1, 1, 1},
    {0, -1, 0, 3}
};
const vector<double> b = {1, 1, 1, 1};
// 在这设置初始点
const vector<double> init_point = {1, 1, 1, 1};

vector<double> Jacobi()
{
    cout << "Jacobi" << endl;
    vector<vector<double>> x(2, init_point);
    double e = 1.;
    int cnt = 0;
    while(e > EPS)
    {
        int k = cnt % 2, kk = (cnt + 1) % 2;
        cnt ++;
        for(int i = 0; i < N; i ++)
        {
            x[kk][i] = b[i];
            for(int j = 0; j < N; j ++)
            {
                if(j == i) continue;
                x[kk][i] -= a[i][j] * x[k][j];
            }
            x[kk][i] /= a[i][i];
        }
        e = 0;
        for(int i = 0; i < N; i ++) e += fabs(x[kk][i] - x[k][i]);
        cout << "cnt=" << cnt << " ";
        for(int i = 0; i < N; i ++) cout << x[kk][i] << " ";
        cout << "e=" << e << endl;
    }
    return x[cnt % 2];
}

vector<double> Guass_Seidel()
{
    cout << "Guass_Seidel" << endl;
    vector<vector<double>> x(2, init_point);
    double e = 1.;
    int cnt = 0;
    while(e > EPS)
    {
        int k = cnt % 2, kk = (cnt + 1) % 2;
        cnt ++;
        for(int i = 0; i < N; i ++)
        {
            x[kk][i] = b[i];
            for(int j = 0; j < i; j ++) x[kk][i] -= a[i][j] * x[kk][j];
            for(int j = i + 1; j < N; j ++) x[kk][i] -= a[i][j] * x[k][j];
            x[kk][i] /= a[i][i];
        }
        e = 0;
        for(int i = 0; i < N; i ++) e += fabs(x[kk][i] - x[k][i]);
        cout << "cnt=" << cnt << " ";
        for(int i = 0; i < N; i ++) cout << x[kk][i] << " ";
        cout << "e=" << e << endl;
    }
    return x[cnt % 2];
}

vector<double> Relaxation(double w)
{
    cout << "Relaxation" << endl;
    vector<vector<double>> x(2, init_point);
    double e = 1.;
    int cnt = 0;
    while(e > EPS)
    {
        int k = cnt % 2, kk = (cnt + 1) % 2;
        cnt ++;
        for(int i = 0; i < N; i ++)
        {
            double d = b[i];
            for(int j = 0; j < i; j ++) d -= a[i][j] * x[kk][j];
            for(int j = i; j < N; j ++) d -= a[i][j] * x[k][j];
            x[kk][i] = x[k][i] + w * d / a[i][i];
        }
        e = 0;
        for(int i = 0; i < N; i ++) e += fabs(x[kk][i] - x[k][i]);
        cout << "cnt=" << cnt << " ";
        for(int i = 0; i < N; i ++) cout << x[kk][i] << " ";
        cout << "e=" << e << endl;
    }
    return x[cnt % 2];
}

int main()
{
    vector<double> ans = Jacobi();
    for(int i = 0; i < N; i ++) cout << ans[i] << " ";
    cout << "\n" << endl;

    ans = Guass_Seidel();
    for(int i = 0; i < N; i ++) cout << ans[i] << " ";
    cout << "\n" << endl;

    ans = Relaxation(0.9);
    for(int i = 0; i < N; i ++) cout << ans[i] << " ";
    cout << "\n" << endl;

    return 0;
}
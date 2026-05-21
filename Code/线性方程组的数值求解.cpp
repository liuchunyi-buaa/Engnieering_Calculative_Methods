#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;
#define N 4
#define EPS 1e-10

const vector<vector<double>> a = {
    {12, 2, 1, 1},
    {1, 9, 1, 2},
    {2, 2, 10, 1},
    {2, 1, 2, 8}
};
const vector<double> b = {1, 1.5, 3, 2};
const vector<double> init_point = {1, 100, 1, 1};

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

int main()
{
    vector<double> ans = Jacobi();
    for(int i = 0; i < N; i ++) cout << ans[i] << " ";
    cout << "\n" << endl;
    ans = Guass_Seidel();
    for(int i = 0; i < N; i ++) cout << ans[i] << " ";
    cout << "\n" << endl;
    return 0;
}
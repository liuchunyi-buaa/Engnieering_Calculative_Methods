#include <bits/stdc++.h>
#define n 10
using namespace std;
int main()
{
	int i, j, l;
	vector<double> X = {-1, -0.8, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.8, 1};
	vector<double> Y(12);
	for(i = 0; i <= n; i++)
	{
		Y[i] = 1 / (1 + 25 * X[i] * X[i]);
	}
	vector<vector<double>> chafen(12, vector<double>(12));
	
	for(i = 0; i <= n; i++)
	{
		chafen[i][0] = Y[i];
	}
	for(j = 1; j <= n; j++)
	{
		for(i = 0; i <= n - j; i++)
		{
			chafen[i][j] = chafen[i + 1][j - 1] - chafen[i][j - 1];
		}
	}
//	for(j = 1; j <= 10; j++)
//	{
//		for(i = 0; i <= 10 - j; i++)
//		{
//			chafen[i][j] = (chafen[i + 1][j - 1] - chafen[i][j - 1]) / (0.2 * j);
//		}
//	}
//	for(i = 0; i <= n; i++)
//	{
//		for(j = 0; j <= n - i; j++)
//		{
//			cout << fixed << setw(12) << chafen[i][j] << " ";
//		}
//		cout << endl;
//	}
	double x, h = 0.2, t, y, k, rel_erf;
	for(i = 0; i < n; i++)
	{
		// x = X[i];
		x = X[i] + h / 2;
		t = (x - X[0]) / h;
		y = 0;
//		y = Y[i] + (Y[i + 1] - Y[i]) / (X[i + 1] - X[i]) * (x - X[i]);
		for(j = 0; j <= n; j++)
		{
			k = 1;
			for(l = 1; l <= j; l++)
			{
				k *= (t - l + 1) / l;
			}
			y += chafen[0][j] * k;
		}
		rel_erf = abs(y - 1 / (1 + 25 * x * x)) / (1 / (1 + 25 * x * x));
		cout << "$$ I_h(" << setprecision(1) << x << ") = " << fixed << setprecision(6) << y << ", \\ \\  " ;
		cout << "rel\\_erf = " << rel_erf << " $$" << endl;
	}
	return 0;
}
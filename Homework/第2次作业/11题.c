#include <stdio.h>
#include <math.h>
#define eps 1e-12
double f(double);
double niudun(double);
int main()
{
	int n, i;
	// 以下为二分法求解
	double a, b, fa, fb, x, fx;
	a = 1.6; b = 4.7;
	for(i = 1; ; i++)
	{
		fa = f(a); fb = f(b);
		x = (a + b) / 2;
		fx = f(x);
		if(fabs(fx) <= eps)
		break;
		else if(fa * fx > 0)
		a = x;
		else
		b = x;
	}
	printf("The final result is: %f\n", x);
	// 以下为牛顿迭代法求解
	x = (a + b) / 2;
	x = niudun(x);
	printf("The final result is: %f\n", x);
	return 0;
}
double f(double x)
{
	return x - tan(x);
}
double niudun(double x)
{
	double fx = f(x);
	x = x - fx / (1 - 1 / (cos(x) * cos(x)));
	fx = f(x);
	if(fabs(fx) <= eps)
	return x;
	else
	return niudun(x);
}
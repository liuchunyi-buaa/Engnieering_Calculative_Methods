#include <stdio.h>
#include <math.h>
#define eps 0.5e-5
double f(double);
int main()
{
	int n, i;
	double a, b, x, fa, fb, fx;
	a = 0; b = 1;
	for(i = 1; ; i++)
	{
		fa = f(a);
		fb = f(b);
		x = (a + b) / 2;
		fx = f(x);
		printf("i = %d, a = %f, b = %f, x = %f, f(a) = %f, f(b) = %f, f(x) = %f\n", i, a, b, x, fa, fb, fx);
		if(fabs(fx) <= eps)
		break;
		else if(fx > eps)
		a = x;
		else
		b = x;
	}
	printf("The final result is: %f\n", x);
	return 0;
}
double f(double x)
{
	return 2 * exp(-x) - sin(x);
}
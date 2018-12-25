/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 */

#include <stdio.h>
#include <stdarg.h>

double **real_dynamic(double *arg, ...)
{
	va_list valist;
	va_start(valist, arg);

	int n;
	double *lf;

	for (lf = arg, n = 0; lf != 0; lf = va_arg(valist, double *), n++);
	va_end(valist);

	// создаем динамический массив зная теперь уже кол-во переменных
	double **M = (double **)malloc((n + 1) * sizeof(double *));
	va_start(valist, arg);

	M[0] = arg;
	for (int i = 1; i <= n; i++) M[i] = va_arg(valist, double *);

	va_end(valist);
	return M;
}

int main()
{
	double d0 = 0.0;
	double d1 = 1.1;
	double d2 = 2.2;
	double d3 = 3.3;
	double d4 = 4.4;

	printf("объявленные переменные:\n");
	printf("d0 = %lf, d1 = %lf, d2 = %lf, d3 = %lf, d4 = %lf\n", d0, d1, d2, d3, d4);
	double **A = real_dynamic(&d0, &d1, &d2, &d3, &d4, 0);

	printf("динамический массив переменных:\n");
	for (int i = 0; A[i] != NULL; i++) printf("[%d] = %lf ", i, *A[i]);
	printf("\n");

    return 0;
}

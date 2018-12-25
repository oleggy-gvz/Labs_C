/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 */

#include <stdio.h>
#include <math.h>

/*
функция вычисляет через ряды Тейлоры натуральный логарифм по числу x, с точностью k
кол-ва знаков после запятой
ф-ция возвращает результат ln(x)
*/

double ln(double x, unsigned int k)
{
	if (x < 0) return NAN; // если указан отриц. аргумент
	if (x == 0) return -INFINITY; // если указан 0 как аргумент

	int i;
	double s, sn; // s - накопит. сумма всего ряда, sn - значение n-го элемента ряда
	double zn; // накопительное значения возведение z в сетепень 
	
	double eps = 1 / pow(10, k); // расчет точности равной 10 ^ (-k)
	double z = (x - 1) / (x + 1);
	// цикл перебора всех элементов i=1..n
	// повторяем цикл до тех пока модуль значения y больше величины eps
	for (s = 0, sn = 2*z, zn = z, i = 2; fabs(sn) > eps; i++)
	{
		s += sn; // добавляем в общую сумму s значение (i-1)-го элемента ряда sn
		zn *= z * z; // увеличиваем степерь числа z на 2 для i-го элемента ряда
		sn = 2.0 / (2 * i - 1) * zn; // считаем значение элемента для i-го элемента ряда
	}
	return s;
}

void show_table(double x1, double x2, double dx, unsigned int k)
{
	printf("x\tряд ln(x)\tln(x)\n"); // заголовок таблицы
	for (double x = x1; x <= x2; x += dx)
		// добавляем строку таблицы с значениями
		printf("%.1lf\t%.4lf\t\t%lf\n", x, ln(x, k), log(x));
}

int main(void)
{
	// начальное, конечное, шаг, точность (кол-во знаков после запятой)
	show_table(-0.1, 1.0, 0.1, 4);

    return 0;
}

/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 */

#include <stdio.h>
#include <stdlib.h> // для заполнения псевдослучаными значениями исходного массива
#include <locale.h>
#include <time.h> // для смены превдослучайных значений

// выделения памяти под массив x длиной z состоящий из типа y
#define NEW(x, y, z) { x = (y*)malloc((z) * sizeof(y)); }
// высвобождение памяти из под массива x
#define DEL(x) { free(x); x = NULL; }
// обмен значениями между собой переменных a и b
#define SWAP(a, b, type) { type tmp = a; a = b; b = tmp; }

// функция бинарного поиска места для вставки символа k, в упорядоченной строке a (размерностью n)
// возвращает: указатель на найденную позицию вставки
char *bin_search(char *a, int n, char k)
{
	int i1 = -1, i2 = n; // задаем границы поиска
	while (i2 - i1 > 1) // выполняем до тех пор пока между двумя границами больше 1 символа 
	{
		int c = (i2 + i1) / 2; // находим индекс среднего эл-та между двумя текущ. границами
		// если эл-т на слевой границе больш или равен искомому (k), то сдвигаем его вправо на середину
		if (*(a + c) <= k) i1 = c; // a[c] < k
		// если эл-т на правой границе больше искомого (k), то сдвигаем его влево на середину
		else i2 = c;
	}
	return a + i2; // a[i2]
}

// сортировка вставками с функцией бинарного поиска
// возвращает: по указателю отсортированную строку a
void sort_insert_mod(char *a, int n)
{
	for (int i = 1; i < n; i++) // перебираем все эл-ты массива начиная со 2-го элемента
	{
		char key = *(a + i); // key = a[i]
		char *p = bin_search(a, i, key); // находим указатель на позицию для вставки значения a[i]
		if (p == a + i) continue; // p == a [i] - если позиция символа не поменялась, переходим к след. эл-ту
	// высвобождаем место для вставки нового элемента
		for (char *pp = a + i; pp > p; pp--) *pp = *(pp-1); 	// передвигаем все элементы на место a[i] (на ед. вправо)
		*p = key;
	}
}

// сортировка вставками без SWAP
int sort_insert_2(char *a, int n)
{
	for (int i = 1; i < n; i++)
	{
		char a_i = a[i];
		int j = i;
		while (j > 0 && a[j-1] > a_i) // если предыдущ. эл-т больше вставляемого
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = a_i;
	}
	return 0;
}

// сортировка вставками
void sort_insert(char *a, int n)
{
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && a[j - 1] > a[j]; j--)
			SWAP(a[j - 1], a[j], char);
}

// функция наполнения целого массива a, размерностью n, случ. символами с кодами от x до y
void rand_str(char *a, int n, char x, char y)
{
	for (int i = 0; i < n; i++) *(a + i) = x + rand() % (y - x + 1);
	*(a + n) = '\0';
}

// функция наполнения целого массива a, размерностью n, символами из строки s
// возвращает кол-во внесенных символов
int set_str(char *a, int n, char *s)
{
	int i;
	for (i = 0; i < n && *(s+i) != '\0'; i++) // s[i] != '\0'
		*(a+i) = *(s+i); // a[i] = s[i]
	*(a+i) = '\0'; // a[i] = '\0'
	if (n != i) return i;
	return n;
}

// функция проверяет значения целого массива a, размерностью n, на наличие возрастания всех эл-тов (от 0...n-1)
// возвращает: истина / ложь
int check_sort(char *a, int n)
{
	int i;
	for (i = 0; *(a+i) <= *(a+i+1) && i < n - 1; i++);
    return (int)(i == (n - 1));
}

// функция выводит на экран результат проверки целого массива a на предмет возрастания всех эл-тов (от 0...n-1)
void show_check_sort(char *a, int n)
{
    if (check_sort(a, n) == 1) puts("тест: массив отсортирован по возрастанию");
	else puts("тест: массив НЕ отсортирован по возрастанию");
}

int main(void)
{
	srand((unsigned int)time(NULL));

	int N = 10;
	char *A;
	NEW(A, char, N);
	/*
	puts("Проверка работоспособности функции бинарного поиска в отсортированном массиве"); 
	int nn = set_str(A, N, "2369");
	char *p, c = '4';
	printf("поиск в строке: \"%s\"\n", A);
	printf("места для вставки символа: '%c'\n", c);
	p = bin_search(A, nn, c);
	if (!check_sort(A, nn)) puts("! данная строка не является отсортированной, позиция может быть некорректной");
	printf("позиция для вставки: %d (символ '%c')\n", p-A+1, p[0]);
	printf("указатель на символ: %s\n\n", p);
	*/
	puts("Проверяем сортировку вставками с помощью ф-ции бинарного поиска");
	rand_str(A, N, 48, 57); // наполняем строку A 10-ю случайными цифрами от '0'..'9'
	//set_str(A, N, "1562738495");
	printf("символы для сортировки:\t\t%s\n", A);
	sort_insert_mod(A, N);
	//sort_insert(A, N);
	//sort_insert_2(A, N);
	printf("отсортированные символы:\t%s\n", A);
	show_check_sort(A, N); // выводим на экран результат проверки на возрастание

	puts("");
	DEL(A);

	return 0;
}

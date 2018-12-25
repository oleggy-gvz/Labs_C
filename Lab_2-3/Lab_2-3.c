/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 */

#include <stdio.h>

unsigned char typedef UCHAR;

//  область памяти byte в которую сохраняется значение data типом type
#define DATA_TO_BYTE(byte, type, data) {type *tmp = (type*)byte; *tmp = data; byte = (char*)tmp; }
// область памяти byte из которой извлекается значение data типом type
#define BYTE_TO_DATA(byte, type, data) {type *tmp = (type*)byte; data = *tmp; byte = (char*)tmp; }

// область памяти byte из которую сохранеяется значение data типом type и следом переходим на адрес n-го элемента типа type в памяти (n = 0 - не переходим)
#define DATA_TO_BYTE_INC(byte, type, data, n) { type *tmp = (type*)byte; *tmp = data; *tmp += n; byte = (char*)tmp; }
// область памяти byte из которой извлекается значение data типом type и следом переходим на адрес n-го элемента типа type в памяти (n = 0 - не переходим)
#define BYTE_TO_DATA_INC(byte, type, data, n) { type *tmp = (type*)byte; data = *tmp; *tmp += n; byte = (char*)tmp; }

int pack(char *p)
{
	char *s = p;
    int to_do = 1;
	char choice[2];
	int n_dig;

	do
	{
		printf("вводим целое (1) либо дробное (2) либо конец ввода (3)\nвведите цифру выбора: ");
		scanf("%s", choice);
		switch (choice[0])
		{
		case '1':
			printf("выбрано целое\nвведите кол-во чисел для ввода: ");
			scanf("%d", &n_dig);
			*p++ = '%'; // начинаем код кол-ва цифр с символа %
			if (n_dig > 1) *p++ = (char)n_dig; // если цифр > 1, пишем
			*p++ = 'd'; // закрываем код кол-ва цифр символом d
						// пишем сами цифры в родном представлении в памяти
			for (int i = 0; i < n_dig; i++)
			{
				int d;
				printf("целое число № %d: ", i + 1);
				scanf("%d", &d);
				// кодируем текущее целое число, аналог: *((int*)p)++ = d; 
				int *p_d = (int*)p; *p_d++ = d;
				p = (char*)p_d; // сохраняем этот код в память
			}
			break;
		case '2':
			printf("выбрано дробное\nвведите кол-во чисел для ввода: ");
			scanf("%d", &n_dig);
			*p++ = '%'; // начинаем код кол-ва цифр с символа %
			if (n_dig > 1) *p++ = (char)n_dig; // если цифр > 1, пишем
			*p++ = 'f'; // закрываем код кол-ва цифр символом d
						// пишем сами цифры в родном представлении в памяти
			for (int i = 0; i < n_dig; i++)
			{
				float f;
				printf("дробное число (с запятой) № %d: ", i + 1);
				scanf("%f", &f);
				// кодируем текущее дробное число, аналог: *((int*)p)++ = f; 
				float *p_f = (float*)p; *p_f++ = f;
				p = (char*)p_f; // сохраняем этот код в память
			}
			break;
		case '3':
			puts("закончили ввод");
			to_do = 0;
			break;
		default:
			puts("ошибка, см. ниже");
		}
	} while (to_do);
	return p - s;
}

void unpack(char *p)
{
	char *t = p;
	int n_dig;

	while (*p++ == '%')
	{
		// читаем кол-во подряд идущих цифр
		if (*p == 'd' || *p == 'f') n_dig = 1; // если указано 1 число
		else n_dig = (int)*p++; // читаем кол-во чисел

		switch (*p++)
		{
		case 'd':
			printf("целые числа в кол-ве %d: ", n_dig);
			for (int i = 0; i < n_dig; i++)
			{
				int *p_i = (int*)p, d = *p_i++;
				p = (char*)p_i;
				printf("%d ", d);
			}
			printf("\n");
			break;
		case 'f':
			printf("дробные числа в кол-ве %d: ", n_dig);
			for (int i = 0; i < n_dig; i++)
			{
				float *p_f = (float*)p, f = *p_f++;
				p = (char*)p_f;
				printf("%f ", f);
			}
			printf("\n");
			break;
		default:;
		}
	}
}

void show_bin(char *p, int n)
{
	printf("представление в HEX виде области памяти в %d байт:\n", n);
	for (int i = 0; i < n; i++) printf("%02x ", (UCHAR)*p++);
	printf("\n");
}

int main(void)
{
	char s[80];
	int num = pack(s);
	unpack(s);
	show_bin(s, num);

    return 0;
}

/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 */

#include <stdio.h>
#include <stdlib.h> // для заполнения псевдослучаными значениями исходного массива
#include <time.h> // для смены превдослучайных значений
#include <string.h>

// псевдографика при отображении записей БД на сонсоль
#define MSG_WALL "| "
#define MSG_BORDER_1 "---------------------------------------------- "
#define MSG_BORDER_2 "------------------------------------------------------------ "

// стандартные информационных ссобщения на консоль
#define MSG_ERROR_IMPUT "Ошибка: неверные данные, было считано: '%s'\n"
#define MSG_FLIGH_NUMBER "авиарейс"
#define MSG_DESTINATION "пункт назначения"
#define MSG_DEP_TIME "время вылета"
#define MSG_DEP_DATE "дата вылета"
#define MSG_PRICE "стоимость"
#define MSG_FULL "заполненность"

#define SIZE_BASE 3

// типы полей элементов структуры
enum FIELD { FLIGH_NUMBER, DESTINATION, DEP_TIME, DEP_DATE, PRICE, FULL};
const char *name_field[6] = { MSG_FLIGH_NUMBER, MSG_DESTINATION, MSG_DEP_TIME, MSG_DEP_DATE, MSG_PRICE, MSG_FULL };

/********************* описание структур данных *********************/

// номер рейса
struct FlighNumber
{
	char airline[3]; // 2-х буквенно/цифровой код авиакомпании
	int num; // 4-х цифровой номер рейса 
};

// пункт назначения
struct Destination
{
    char city[25]; // город
    char country[25]; // страна
	char airport[4]; // 3-х буквенный код аэропорта (IATA-код), если а городе несколько аэропортов
};

// время
struct Time
{
	int hour; // часы
	int min; // минуты
};

// дата
struct Date
{
	int day; // день
	int month; // месяц
	int year; // год
};

// стоимость
struct Price
{
	float val; // сумма
	char curr[4]; // 3-х симвл. обозначение валюты
};

// билет на самолет
struct AirTicket
{
    struct FlighNumber fligh_num; // номер рейса
    struct Destination dest; // пункт назначения
    struct Time dep_time; // время вылета (местное)
    struct Date dep_date; // дата вылета
    struct Price cost; // стоимость
    int is_full; // признак пустоты (0), заполненности (1) билета
};

// база существующих билетов
struct DB_AirTicket
{
    struct AirTicket *arr; // массив структур авиабилетов
    int num; // кол-во используемых записей в БД
    int sz_db; // кол-во записей которых можно создать в БД (под сколько выделено памяти)
};

/********************* функции работы с полями структуры *********************/

// ввод номера рейса
int ImputFlighNumber(struct FlighNumber *fn)
{
	if (fn == NULL) return 1;
	char buf[80];
    int err = 0;
	printf(MSG_FLIGH_NUMBER); printf(":\n"); // информац. сообщение
	// ввод 2-х буквенно/цифрового кода авиакомпании 
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("код авиакомпании (2 англ. заглав. буквы либо буква и цифра): ");
        gets(buf);
		sscanf(buf, "%2[A-Z0-9]s", fn->airline);
		err = 1;
	} while (strlen(fn->airline) != 2 || strcmp(buf, fn->airline) != 0 || (fn->airline[0] >= '0' && fn->airline[0] <= '9'));
	
	err = 0;
	// ввод 4-х цифрового номера рейса 
	char tmp[80];
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("номер рейса (4 цифры): ");
        gets(buf);
		sscanf(buf, "%4[0-9]s", tmp);
		err = 1;
	} while (strlen(buf) != 4 || strcmp(buf, tmp) != 0);
	fn->num = atoi(tmp);
	return 0;
}

// ввод пункта назначения
int ImputDestination(struct Destination *d)
{
	if (d == NULL) return 1;
	char buf[80];
    int err = 0;
	printf(MSG_DESTINATION); printf(":\n");
	// информац. сообщение
	// ввод названия города
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("город (англ.): ");
        gets(buf);
		sscanf(buf, "%[A-Za-z'-]s", d->city);
		err = 1;
	} while (strcmp(buf, d->city) != 0);
	err = 0;
	// ввод названия страны
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("страна (англ.): ");
        gets(buf);
		sscanf(buf, "%['A-Za-z'-]s", d->country);
		err = 1;
	} while (strcmp(buf, d->country) != 0);
	err = 0;
	// ввод 3-х буквенного кода аэропорта 
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("если в городе аэропортов >1, то\nкод аэропорта (3 англ. заглав. буквы, пустое - нет): ");
        gets(buf);
		if (strlen(buf) == 0) { strcpy(d->airport, ""); break; } // в городе один аэропорт
		sscanf(buf, "%3[A-Z]s", d->airport);
		err = 1;
	} while (strlen(d->airport) < 3 || strcmp(buf, d->airport) != 0);
	return 0;
}

// ввод времени
int ImputTime(struct Time *t)
{
	if (t == NULL) return 1;
	char buf[80], tmp[80];
    int err = 0;
	printf(MSG_DEP_TIME); printf(":\n"); // информац. сообщение
	// ввод часа
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("час (0-23): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		t->hour = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || t->hour < 0 || t->hour > 23);
	err = 0;
	// ввод минуты
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("минуты (0-59): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		t->min = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || t->min < 0 || t->min > 59);
	return 0;
}

// ввод даты
int ImputDate(struct Date *d)
{
	if (d == NULL) return 1;
	char buf[80], tmp[80];
    int err = 0;
	printf(MSG_DEP_DATE); printf(":\n"); // информац. сообщение
	// ввод числа
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("число (1-31): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		d->day = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || d->day < 1 || d->day > 31);
	err = 0;
	// ввод месяца
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("месяц (1-12): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		d->month = atoi(tmp);
		err = 1;

	} while (strcmp(buf, tmp) != 0 || d->month < 1 || d->month > 12);
	err = 0;
	// ввод года
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("Введите год (2000-2050): ");
        gets(buf);
		sscanf(buf, "%4[0-9]s", tmp);
		d->year = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || d->year < 2000 || d->year > 2050);
	return 0;
}

// ввод цены
int ImputPrice(struct Price *p)
{
	if (p == NULL) return 1;
	char buf[80];
    int err = 0;
	printf(MSG_PRICE); printf(":\n"); // информац. сообщение
	// ввод стоимости
	char tmp[80];
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("цена (до 2-х знаков после запятой): ");
        gets(buf);
		sscanf(buf, "%[0-9,]s", tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0);
	p->val = (float)atof(tmp);
	err = 0;
	// ввод валюты 
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // сообщение об ошибке
		printf("валюта (3 англ. заглав. буквы, пустое - 'RUB'): ");
        gets(buf);
		if (strlen(buf) == 0) strcpy(buf, "RUB");
		sscanf(buf, "%3[A-Z]s", p->curr);
		err = 1;
	} while (strlen(p->curr) != 3 || strcmp(buf, p->curr) != 0);
	return 0;
}

// вывод номера рейса
void OutputFlighNumber(struct FlighNumber fn)
{
	printf(MSG_FLIGH_NUMBER); printf(": "); // информац. сообщение
	printf("%s%d\n", fn.airline, fn.num);
}

// вывод пункта назначения
void OutputDestination(struct Destination ds)
{
	printf(MSG_DESTINATION); printf(": "); // информац. сообщение
	// если несколько аэропортов в городе, то сперва его код
	if (strlen(ds.airport) != 0) printf("%s, ", ds.airport);
	printf("%s, %s\n", ds.city, ds.country);
}

// вывод времени
void OutputTime(struct Time t)
{
	printf(MSG_DEP_TIME); printf(": "); // информац. сообщение
	printf("%02d-%02d\n", t.hour, t.min);
}

// вывод даты
void OutputDate(struct Date d)
{
	printf(MSG_DEP_DATE); printf(": "); // информац. сообщение
	printf("%02d.%02d.%4d\n", d.day, d.month, d.year);
}

// вывод стоимости
void OutputPrice(struct Price p)
{
	printf(MSG_PRICE); printf(": "); // информац. сообщение
	printf("%.2f %.3s\n", p.val, p.curr);
}

/********************* функции работы с авиабилетом *********************/

// ввод авиабилета с консоли
int ImputAirTicket(char *msg, struct AirTicket *at)
{
	if (at == NULL) return 1;
	printf(MSG_BORDER_1);
	printf("авиабилет %s\n", msg);

	ImputFlighNumber(&at->fligh_num);
	ImputDestination(&at->dest);
	ImputTime(&at->dep_time);
	ImputDate(&at->dep_date);
	ImputPrice(&at->cost);

	puts(MSG_BORDER_2);
	at->is_full = 1; // теперь билет заполненный
	return 0;
}

// вывод авиабилета на консоль
void OutputAirTicket(char *msg, struct AirTicket at)
{
	printf(MSG_BORDER_1);
	printf("авиабилет %s\n", msg);
	if (!at.is_full)
	{
		printf(MSG_WALL); puts("авиабилет пустой");
	}
	else
	{
		printf(MSG_WALL); OutputFlighNumber(at.fligh_num);
		printf(MSG_WALL); OutputDestination(at.dest);
		printf(MSG_WALL); OutputTime(at.dep_time);
		printf(MSG_WALL); OutputDate(at.dep_date);
		printf(MSG_WALL); OutputPrice(at.cost);
	}
	puts(MSG_BORDER_2);
}

// отчистка авиабилета
int ClearAirTicket(struct AirTicket *at)
{
	if (at == NULL) return 1;
    memset(at, 0, sizeof(struct AirTicket));
	//at->is_full = 0;
	return 0;
}

/********************* функции тестирования *********************/

// функция наполнения строки str, размерностью n, случ. символами с кодами от x до y
void rand_str(char *str, int n, char x, char y)
{
	for (int i = 0; i < n; i++) str[i] = x + rand() % (y - x + 1);
	str[n] = '\0';
}

// наполение авиабилета случайными данными
int SetRandomDataAirTicket(struct AirTicket *at)
{
	if (at == NULL) return 1;
	// ввод номера рейса
	rand_str(at->fligh_num.airline, 2, 'A', 'Z'); // ввод 2-х буквенного кода авиакомпании 
	at->fligh_num.num = 1000 + rand() % 9000; // ввод 4-х цифрового номера рейса 1000-9999

	// ввод пункта назначения
	sprintf(at->dest.city, "city %d", rand() % 10); // ввод названия города на англ.
	sprintf(at->dest.country, "country %d", rand() % 10); // ввод названия страны на англ.
	strcpy(at->dest.airport, ""); // по умолчанию 1 аэропорт в городе
	// 50% вероятность что в городе >1, тогда вводим 3-х буквенный код аэропорта
	if (rand() % 2 == 1) rand_str(at->dest.airport, 3, 'A', 'Z');

	// ввод времени
	at->dep_time.hour = rand() % 24; // ввод часа 0-23
	at->dep_time.min = rand() % 60; // ввод минуты 0-59

	// ввод даты
	at->dep_date.day = rand() % 31 + 1; // ввод числа 1-31
	at->dep_date.month = rand() % 12 + 1; // ввод месяца 1-12
	at->dep_date.year = 2017 + rand () % 2; // ввод года от 2017 до 2018

	// ввод цены
	at->cost.val = 4000 + rand() % (80 + 1) * 100; // ввод стоимости от 4000 до 12000 RUB
	strcpy(at->cost.curr, "RUB"); // валюта всегда рубли

	at->is_full = 1; // теперь билет заполненный
	return 0;
}

/********************* функции работы с БД авиабилетов *********************/
/*********************** простые операции управления ***********************/

//  добавление записи в БД
int AddAirTicket_DB(struct DB_AirTicket *db, struct AirTicket at)
{
	if (db == NULL) return -1; // если указатель пустой
	int num = db->num; // текущ. размер БД
	// если база пустая, то выделяем память
	if (num == 0)
	{
        db->sz_db = SIZE_BASE; // по умолчанию размерность БД будет равна SIZE_BASE
        db->arr = (struct AirTicket *)malloc(db->sz_db * sizeof(struct AirTicket));
	}
	else if (num == db->sz_db) // если кол-во эл-тов уже достигло размерности базы, то выделяем память
	{
		db->sz_db *= 2; // увеличиваем размерность базы в 2 раза
        db->arr = (struct AirTicket *)realloc(db->arr, db->sz_db * sizeof(struct AirTicket));
	}
	db->arr[num] = at;
	db->num++;

	return 0;
}

//  обнуление данных для заданной записи в БД
int ClearAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // если указатель пустой
	int num = db->num; // текущ. размер БД
	if (num == 0 || index < 0 || index > num-1) return -1; // если доступ к не сущ. элементу или в базе нет данных

	ClearAirTicket(&db->arr[index]); // отчистка эл-та
	
	return 0;
}

// замена данных для заданной записи в БД
int EditAirTicket_DB(struct DB_AirTicket *db, int index, struct AirTicket at)
{
	if (db == NULL) return -1; // если указатель пустой
	int num = db->num; // текущ. размер БД
	if (num == 0 || index < 0 || index > num-1) return -1; // если доступ к не сущ. элементу или в базе нет данных
	
	db->arr[index] = at;

	return 0;
}

// удаление заданной записи из БД со сдвигом оставшихся назад
int RemoveAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // если указатель пустой
	int num = db->num; // текущ. размер БД
	if (num == 0 || index < 0 || index > num-1) return -1; // если доступ к не сущ. элементу или в базе нет данных

	for (int i = index; i < num-1; i++) db->arr[i] = db->arr[i + 1];
	ClearAirTicket(&db->arr[num-1]); // отчистка последнего эл-та
	db->num--;
	return 0;
}

/*********************** операции ввода/вывода ***********************/

// ввод данных для заданной записи в БД
int ImputAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // если указатель пустой
	int num = db->num; // текущ. размер БД
	if (num == 0 || index < 0 || index > num-1) return -1; // если доступ к не сущ. элементу или в базе нет данных

	char tmp[10];
	sprintf(tmp, "№ %d", index);
	ImputAirTicket(tmp, &db->arr[index]);
	return 0;
}

// вывод на экран заданной записи в БД
int OutputAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // если указатель пустой
	int num = db->num; // текущ. размер БД
	if (num == 0 || index < 0 || index > num-1) return -1; // если доступ к не сущ. элементу или в базе нет данных

	char tmp[10];
	sprintf(tmp, "№ %d", index);
	OutputAirTicket(tmp, db->arr[index]);
	return 0;
}

// вывод на экран всех записей в БД
int OutputAllAirTicket_DB(struct DB_AirTicket *db)
{
	if (db == NULL) return -1; // если указатель пустой
	int num = db->num; // текущ. размер БД

	for (int i = 0; i < num; i++)
	{
		char tmp[10];
		sprintf(tmp, "№ %d", i);
		OutputAirTicket(tmp, db->arr[i]);
	}
	return 0;
}

/*********************** операция сортировки ***********************/

// сравнение двух номеров рейсов (код авиакомпании, номер рейса)
int CompareFlighNumber(struct FlighNumber fn1, struct FlighNumber fn2)
{
	char str1[80], str2[80];

	sprintf(str1, "%s%d", fn1.airline, fn1.num);
	sprintf(str2, "%s%d", fn2.airline, fn2.num);

	return strcmp(str1, str2);
}

// сравнение пункта назначения (город, страна, код аэропорта)
int CompareDestination(struct Destination ds1, struct Destination ds2)
{
	char str1[80], str2[80];

	sprintf(str1, "%s%s%s", ds1.city, ds1.country, ds1.airport);
	sprintf(str2, "%s%s%s", ds2.city, ds2.country, ds2.airport);

	return strcmp(str1, str2);
}

// сравнение времени (часы, минуты)
int CompareTime(struct Time t1, struct Time t2)
{
	return (t1.hour * 60 + t1.min) - (t2.hour * 60 + t2.min);
}

// сравнение времени (год, месяц, дата)
int CompareData(struct Date d1, struct Date d2)
{
	return ((d1.year * 12 + d1.month) * 31 + d1.day) - ((d2.year * 12 + d2.month) * 31 + d2.day);
}

// сравнение цен
int ComparePrice(struct Price p1, struct Price p2)
{
	return p1.val - p2.val;
}

// сравнение авиабилетов по любому полю
// сравнение заполненного авиабилета с пустым не происходит, пустой считается самым тяжелым (в конец)
int CompareAnyField(struct AirTicket at1, struct AirTicket at2, enum FIELD f)
{
	int res = 0;
	
	// если мы сравниваем не по заполненности билетов и любой из двух - пустой, то пустой самый тяжелый
	if (f != FULL && (at1.is_full == 0 || at2.is_full == 0))
	{
		//return at2.is_full - at1.is_full;
		return -INT_MAX;
	}
	switch (f)
	{
		// FLIGH_NUMBER, DESTINATION, DEP_TIME, DEP_DATE, PRICE, FULL };
		// сравнение двух номеров рейсов (код авиакомпании, номер рейса)
	case FLIGH_NUMBER:
		res = CompareFlighNumber(at1.fligh_num, at2.fligh_num);
		break;
		// сравнение пункта назначения (город, страна, код аэропорта)
	case DESTINATION:
		res = CompareDestination(at1.dest, at2.dest);
		break;
		// сравнение времени (часы, минуты)
	case DEP_TIME:
		res = CompareTime(at1.dep_time, at2.dep_time);
		break;
		// сравнение времени (год, месяц, дата)
	case DEP_DATE:
		res = CompareData(at1.dep_date, at2.dep_date);
		break;
		// сравнение цен
	case PRICE:
		res = ComparePrice(at1.cost, at2.cost);
		break;
		// сравнение по заполненности (пустые - самые большие, в конец)
	case FULL:
		res = at1.is_full - at2.is_full;
		break;
	}
	return res;
}

// сортировка вставками записей БД по указанному номеру полю
int Sort_DB(struct DB_AirTicket *db, enum FIELD f)
{
	if (db == NULL) return -1; // если указатель пустой
	if (f < 0 || f > 6) return -1;

	int num = db->num;
	for (int i = 1; i < num; i++)
	{
        struct AirTicket at_i = db->arr[i];
		int j = i;
		while (j > 0 && CompareAnyField(db->arr[j-1], at_i, f) > 0)
		{
			db->arr[j] = db->arr[j-1];
			j--;
		}
		db->arr[j] = at_i;
	}
	return 0;
}

/*********************** операции поиска ***********************/

//  линейный поиск первой пустой записи в БД
struct AirTicket *FindEmptyAirTicket_DB(struct DB_AirTicket *db, int *n)
{
	if (db == NULL) return NULL; // если указатель пустой
	int num = db->num; // текущ. размер БД авиабилетов

	int i;
	for (i = 0; i < num && db->arr[i].is_full; i++);
	*n = (i == num) ? -1 : i; // если пустой записи не найдено, вернуть -1, иначе индекс
	return (i == num) ? NULL : &db->arr[i]; // если пустой записи не найдено, вернуть NULL, иначе указатель
}

//  линейный поиск минимальной записи заданного поля в БД
struct AirTicket *FindMinFieldAirTicket_DB(struct DB_AirTicket *db, enum FIELD f, int *n)
{
	if (db == NULL) return NULL; // если указатель пустой
	int num = db->num; // текущ. размер БД авиабилетов

	int i;
    struct AirTicket *res = &db->arr[0];
	for (i = 1; i < num; i++)
	{
		if (CompareAnyField(*res, db->arr[i], f) > 0)
		{
			res = &db->arr[i];
			*n = i;
		}
	}
	return res;
}

//  линейный поиск нужной записи или наиболее близкой к ней в БД
struct AirTicket *FindLikeFieldAirTicket_DB(struct DB_AirTicket *db, struct AirTicket at, enum FIELD f, int *n)
{
	if (db == NULL) return NULL; // если указатель пустой
	int num = db->num; // текущ. размер БД авиабилетов

	int cur_comp, comp = INT_MAX;
    struct AirTicket *res;

	for (int i = 0; i < num; i++)
	{
		cur_comp = abs(CompareAnyField(at, db->arr[i], f));
		if (cur_comp < comp)
		{
			comp = cur_comp;
			res = &db->arr[i];
			*n = i;
		}	
	}
	return res;
}

int SaveAirTicket_DB(struct DB_AirTicket *db, char *file)
{
	if (db == NULL) return 1; // если указатель пустой

	FILE *f = fopen(file, "wb");
	fwrite(&db->num, sizeof(int), 1, f);
    fwrite(db->arr, sizeof(struct AirTicket), db->num, f);
	fclose(f);
}

int LoadAirTicket_DB(struct DB_AirTicket *db, char *file)
{
	if (db == NULL) return 1; // если указатель пустой

	FILE *f = fopen(file, "rb");
	fread(&db->num, sizeof(int), 1, f);
    db->arr = (struct AirTicket *)malloc(db->num * sizeof(struct AirTicket));
    fread(db->arr, sizeof(struct AirTicket), db->num, f);
	fclose(f);
}

int main(void)
{
	srand((unsigned int)time(NULL));

	//FlighNumber fn; ImputFlighNumber(&fn); OutputFlighNumber(fn);
	//FlighNumber fn = {"AA", 1234}; OutputFlighNumber(fn);
	//FlighNumber fn1 = {"AB", 1234}, fn2 = {"AA", 1234}; printf("%d\n", CompareFlighNumber(fn1, fn2));

	//Destination ds; ImputDestination(&ds); OutputDestination(ds); 
	//Destination ds = {"Novosibirsk", "Russia", "SDR"}; OutputDestination(ds);
	//Destination ds1 = {"AA", "AB", "1"}, ds2 = {"AA", "AB", "2"}; printf("%d\n", CompareDestination(ds1, ds2));

	//Time t; ImputTime(&t); OutputTime(t);
	//Time t = {2, 30}; OutputTime(t);
	//Time t1 = {2, 30}, t2 = {22, 00}; printf("%d\n",  CompareTime(t1, t2));

	//Date d; ImputDate(&d); OutputDate(d);
	//Date d = {2, 6, 2007}; OutputDate(d);
	//Date d1 = {5, 6, 2007}, d2 = {10, 6, 2007}; printf("%d\n", CompareData(d1, d2));

	//Price p; ImputPrice(&p); OutputPrice(p);
	//Price p = {165168.879, "RUB"}; OutputPrice(p);
	//Price p1 = {168.00, "RUB"}, p2 = {200.00, "RUB"}; printf("%d\n", ComparePrice(p1, p2));

	/*
	AirTicket at; ImputAirTicket("at", &at); OutputAirTicket("at", at);
	*/

	/*
	AirTicket at = {{ "AA", 1234 }, 
					{ "Novosibirsk", "Russia", "SDR" },
					{ 2, 30 },
					{ 2, 6, 2007 },
					{ 165168.879, "RUB" }}; 
	OutputAirTicket("at", at);
	*/
	
	/*	
	AirTicket at1, at2; // создаем два пустых билета - №1, №2
	SetRandomDataAirTicket(&at1); // заполняем билет №1
	OutputAirTicket("at1", at1); OutputAirTicket("at2", at2); // вывдим на экран оба билета
	at2 = at1; // копируем билет №1 в билет №2
	ClearAirTicket(&at1); // отчищаем билет №1
	OutputAirTicket("at1", at1); OutputAirTicket("at2", at2); // вывдим на экран оба билета
	*/

    struct DB_AirTicket db_at;

    memset(&db_at, 0, sizeof(struct DB_AirTicket));

    const int N = 5; // кол-во создаваемых авиабилетов
	int k;
    enum FIELD f; // переменная с типом поля
    struct AirTicket *p, tmp;

	for (int i = 0; i < N; i++) // создаем несколько авиабилетов с данными
	{
        struct AirTicket tmp;
		SetRandomDataAirTicket(&tmp);
		AddAirTicket_DB(&db_at, tmp);
	}

    /*
    // проверка записи и чтения на диск
    struct DB_AirTicket db_at_new;
    SaveAirTicket_DB(&db_at, "c:\\out.bin");
    LoadAirTicket_DB(&db_at_new, "c:\\out.bin");
    OutputAllAirTicket_DB(&db_at_new);
    */

    OutputAllAirTicket_DB(&db_at); // выводим все созданные записи на экран

	puts("отчищаем 1-ой авиабилет, удаляем 2-ой авиабилет, и отчищаем 4-ий авиабилет (который стал 3-им):");
	ClearAirTicket_DB(&db_at, 1); // отчищаем 1-ю запись
	RemoveAirTicket_DB(&db_at, 2); // удаляем 2-ю запись
	ClearAirTicket_DB(&db_at, 3); // отчищаем 3-ю запись, которая была изначально 4-ой
	OutputAllAirTicket_DB(&db_at); // выводим все записи на экран

	p = FindEmptyAirTicket_DB(&db_at, &k); // ищем указатель на 1-ю пустую запись
	printf("первый пустой авиабилет в БД с индексом %d, его содержимое:\n", k);
	OutputAirTicket("найденый", *p); // выводим эту запись на экран

	SetRandomDataAirTicket(&tmp); // заполняем временный авиабилет случайными данными
	puts("содержимое временного авиабилета:");
	OutputAirTicket("временный", tmp); // выводим его данные на экран

	EditAirTicket_DB(&db_at, k, tmp); // заменяем 1-ю пустую запись в БД на данные из временного авиабилета 
	puts("заменяем данные в 1-ом пустом авиабилете, на новые из временного, список всех билетов:");
	OutputAllAirTicket_DB(&db_at); // выводим все созданные записи на экран

	// виды полей: FLIGH_NUMBER - авиарейс, DESTINATION - пункт назначения, 
	// DEP_TIME - время вылета, DEP_DATE - дата вылета, PRICE - стоимость, FULL - заполненность
	// сортируем БД по заданному полю f
	f = PRICE;
	printf("сортируем БД по полю: %s\n", name_field[f]);
	// сортируем структуру по полю f
	Sort_DB(&db_at, f);
	OutputAllAirTicket_DB(&db_at); // выводим все записи на экран
	
	// ищем запись в БД с минимальным значением заданного поля f
	f = DEP_TIME;
	printf("ищем запись в БД с мин. значением поля: %s\n", name_field[f]);
	// ищем указатель на структуру на мин. значением поля f
	p = FindMinFieldAirTicket_DB(&db_at, f, &k);
	printf("в БД запись под номером %d, ее содержимое:\n", k);
	OutputAirTicket("найденый", *p); // выводим эту запись на экран
	
	// ищем запись в БД с максимально совпадающим значением заданного поля f указанного во временном билете
	f = PRICE;
	printf("ищем запись в БД с наиболее близким полем: %s\n", name_field[f]);
	SetRandomDataAirTicket(&tmp); // заполняем временный авиабилет случайными данными
	puts("из следующего временного авиабилета:");
	OutputAirTicket("временный", tmp); // выводим его данные на экран
	// ищем указатель на структуру с наиболее совпадающим с полем f из временного билета
	p = FindLikeFieldAirTicket_DB(&db_at, tmp, f, &k);
	printf("в БД запись под номером %d, ее содержимое:\n", k);
	OutputAirTicket("найденый", *p); // выводим эту запись на экран

    return 0;
}

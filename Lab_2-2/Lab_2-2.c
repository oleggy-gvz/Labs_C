/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 * ���ଠ⨪� � �ணࠬ��஢���� �.2, ������ୠ� �2, ��ਠ�� 8
 *
 * �������:
 *
 */

#include <stdio.h>
#include <stdlib.h> // ��� ���������� �ᥢ����砭묨 ���祭�ﬨ ��室���� ���ᨢ�
#include <time.h> // ��� ᬥ�� �ॢ����砩��� ���祭��
#include <string.h>

// �ᥢ����䨪� �� �⮡ࠦ���� ����ᥩ �� �� ᮭ᮫�
#define MSG_WALL "| "
#define MSG_BORDER_1 "---------------------------------------------- "
#define MSG_BORDER_2 "------------------------------------------------------------ "

// �⠭����� ���ଠ樮���� �ᮡ饭�� �� ���᮫�
#define MSG_ERROR_IMPUT "�訡��: ������ �����, �뫮 ��⠭�: '%s'\n"
#define MSG_FLIGH_NUMBER "����३�"
#define MSG_DESTINATION "�㭪� �����祭��"
#define MSG_DEP_TIME "�६� �뫥�"
#define MSG_DEP_DATE "��� �뫥�"
#define MSG_PRICE "�⮨�����"
#define MSG_FULL "�������������"

#define SIZE_BASE 3

// ⨯� ����� ����⮢ ��������
enum FIELD { FLIGH_NUMBER, DESTINATION, DEP_TIME, DEP_DATE, PRICE, FULL};
const char *name_field[6] = { MSG_FLIGH_NUMBER, MSG_DESTINATION, MSG_DEP_TIME, MSG_DEP_DATE, MSG_PRICE, MSG_FULL };

/********************* ���ᠭ�� ������� ������ *********************/

// ����� ३�
struct FlighNumber
{
	char airline[3]; // 2-� �㪢����/��஢�� ��� ������������
	int num; // 4-� ��஢�� ����� ३� 
};

// �㭪� �����祭��
struct Destination
{
    char city[25]; // ��த
    char country[25]; // ��࠭�
	char airport[4]; // 3-� �㪢���� ��� ��ய��� (IATA-���), �᫨ � ��த� ��᪮�쪮 ��ய��⮢
};

// �६�
struct Time
{
	int hour; // ���
	int min; // ������
};

// ���
struct Date
{
	int day; // ����
	int month; // �����
	int year; // ���
};

// �⮨�����
struct Price
{
	float val; // �㬬�
	char curr[4]; // 3-� ᨬ��. ������祭�� ������
};

// ����� �� ᠬ����
struct AirTicket
{
    struct FlighNumber fligh_num; // ����� ३�
    struct Destination dest; // �㭪� �����祭��
    struct Time dep_time; // �६� �뫥� (���⭮�)
    struct Date dep_date; // ��� �뫥�
    struct Price cost; // �⮨�����
    int is_full; // �ਧ��� ������ (0), ������������ (1) �����
};

// ���� ��������� ����⮢
struct DB_AirTicket
{
    struct AirTicket *arr; // ���ᨢ ������� ��������⮢
    int num; // ���-�� �ᯮ��㥬�� ����ᥩ � ��
    int sz_db; // ���-�� ����ᥩ ������ ����� ᮧ���� � �� (��� ᪮�쪮 �뤥���� �����)
};

/********************* �㭪樨 ࠡ��� � ���ﬨ �������� *********************/

// ���� ����� ३�
int ImputFlighNumber(struct FlighNumber *fn)
{
	if (fn == NULL) return 1;
	char buf[80];
    int err = 0;
	printf(MSG_FLIGH_NUMBER); printf(":\n"); // ���ଠ�. ᮮ�饭��
	// ���� 2-� �㪢����/��஢��� ���� ������������ 
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("��� ������������ (2 ����. ������. �㪢� ���� �㪢� � ���): ");
        gets(buf);
		sscanf(buf, "%2[A-Z0-9]s", fn->airline);
		err = 1;
	} while (strlen(fn->airline) != 2 || strcmp(buf, fn->airline) != 0 || (fn->airline[0] >= '0' && fn->airline[0] <= '9'));
	
	err = 0;
	// ���� 4-� ��஢��� ����� ३� 
	char tmp[80];
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("����� ३� (4 ����): ");
        gets(buf);
		sscanf(buf, "%4[0-9]s", tmp);
		err = 1;
	} while (strlen(buf) != 4 || strcmp(buf, tmp) != 0);
	fn->num = atoi(tmp);
	return 0;
}

// ���� �㭪� �����祭��
int ImputDestination(struct Destination *d)
{
	if (d == NULL) return 1;
	char buf[80];
    int err = 0;
	printf(MSG_DESTINATION); printf(":\n");
	// ���ଠ�. ᮮ�饭��
	// ���� �������� ��த�
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("��த (����.): ");
        gets(buf);
		sscanf(buf, "%[A-Za-z'-]s", d->city);
		err = 1;
	} while (strcmp(buf, d->city) != 0);
	err = 0;
	// ���� �������� ��࠭�
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("��࠭� (����.): ");
        gets(buf);
		sscanf(buf, "%['A-Za-z'-]s", d->country);
		err = 1;
	} while (strcmp(buf, d->country) != 0);
	err = 0;
	// ���� 3-� �㪢������ ���� ��ய��� 
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("�᫨ � ��த� ��ய��⮢ >1, �\n��� ��ய��� (3 ����. ������. �㪢�, ���⮥ - ���): ");
        gets(buf);
		if (strlen(buf) == 0) { strcpy(d->airport, ""); break; } // � ��த� ���� ��ய���
		sscanf(buf, "%3[A-Z]s", d->airport);
		err = 1;
	} while (strlen(d->airport) < 3 || strcmp(buf, d->airport) != 0);
	return 0;
}

// ���� �६���
int ImputTime(struct Time *t)
{
	if (t == NULL) return 1;
	char buf[80], tmp[80];
    int err = 0;
	printf(MSG_DEP_TIME); printf(":\n"); // ���ଠ�. ᮮ�饭��
	// ���� ��
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("�� (0-23): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		t->hour = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || t->hour < 0 || t->hour > 23);
	err = 0;
	// ���� ������
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("������ (0-59): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		t->min = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || t->min < 0 || t->min > 59);
	return 0;
}

// ���� ����
int ImputDate(struct Date *d)
{
	if (d == NULL) return 1;
	char buf[80], tmp[80];
    int err = 0;
	printf(MSG_DEP_DATE); printf(":\n"); // ���ଠ�. ᮮ�饭��
	// ���� �᫠
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("�᫮ (1-31): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		d->day = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || d->day < 1 || d->day > 31);
	err = 0;
	// ���� �����
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("����� (1-12): ");
        gets(buf);
		sscanf(buf, "%2[0-9]s", tmp);
		d->month = atoi(tmp);
		err = 1;

	} while (strcmp(buf, tmp) != 0 || d->month < 1 || d->month > 12);
	err = 0;
	// ���� ����
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("������ ��� (2000-2050): ");
        gets(buf);
		sscanf(buf, "%4[0-9]s", tmp);
		d->year = atoi(tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0 || d->year < 2000 || d->year > 2050);
	return 0;
}

// ���� 業�
int ImputPrice(struct Price *p)
{
	if (p == NULL) return 1;
	char buf[80];
    int err = 0;
	printf(MSG_PRICE); printf(":\n"); // ���ଠ�. ᮮ�饭��
	// ���� �⮨����
	char tmp[80];
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("業� (�� 2-� ������ ��᫥ ����⮩): ");
        gets(buf);
		sscanf(buf, "%[0-9,]s", tmp);
		err = 1;
	} while (strcmp(buf, tmp) != 0);
	p->val = (float)atof(tmp);
	err = 0;
	// ���� ������ 
	do
	{
		if (err == 1) printf(MSG_ERROR_IMPUT, buf); // ᮮ�饭�� �� �訡��
		printf("����� (3 ����. ������. �㪢�, ���⮥ - 'RUB'): ");
        gets(buf);
		if (strlen(buf) == 0) strcpy(buf, "RUB");
		sscanf(buf, "%3[A-Z]s", p->curr);
		err = 1;
	} while (strlen(p->curr) != 3 || strcmp(buf, p->curr) != 0);
	return 0;
}

// �뢮� ����� ३�
void OutputFlighNumber(struct FlighNumber fn)
{
	printf(MSG_FLIGH_NUMBER); printf(": "); // ���ଠ�. ᮮ�饭��
	printf("%s%d\n", fn.airline, fn.num);
}

// �뢮� �㭪� �����祭��
void OutputDestination(struct Destination ds)
{
	printf(MSG_DESTINATION); printf(": "); // ���ଠ�. ᮮ�饭��
	// �᫨ ��᪮�쪮 ��ய��⮢ � ��த�, � ᯥࢠ ��� ���
	if (strlen(ds.airport) != 0) printf("%s, ", ds.airport);
	printf("%s, %s\n", ds.city, ds.country);
}

// �뢮� �६���
void OutputTime(struct Time t)
{
	printf(MSG_DEP_TIME); printf(": "); // ���ଠ�. ᮮ�饭��
	printf("%02d-%02d\n", t.hour, t.min);
}

// �뢮� ����
void OutputDate(struct Date d)
{
	printf(MSG_DEP_DATE); printf(": "); // ���ଠ�. ᮮ�饭��
	printf("%02d.%02d.%4d\n", d.day, d.month, d.year);
}

// �뢮� �⮨����
void OutputPrice(struct Price p)
{
	printf(MSG_PRICE); printf(": "); // ���ଠ�. ᮮ�饭��
	printf("%.2f %.3s\n", p.val, p.curr);
}

/********************* �㭪樨 ࠡ��� � ��������⮬ *********************/

// ���� ��������� � ���᮫�
int ImputAirTicket(char *msg, struct AirTicket *at)
{
	if (at == NULL) return 1;
	printf(MSG_BORDER_1);
	printf("��������� %s\n", msg);

	ImputFlighNumber(&at->fligh_num);
	ImputDestination(&at->dest);
	ImputTime(&at->dep_time);
	ImputDate(&at->dep_date);
	ImputPrice(&at->cost);

	puts(MSG_BORDER_2);
	at->is_full = 1; // ⥯��� ����� ����������
	return 0;
}

// �뢮� ��������� �� ���᮫�
void OutputAirTicket(char *msg, struct AirTicket at)
{
	printf(MSG_BORDER_1);
	printf("��������� %s\n", msg);
	if (!at.is_full)
	{
		printf(MSG_WALL); puts("��������� ���⮩");
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

// ����⪠ ���������
int ClearAirTicket(struct AirTicket *at)
{
	if (at == NULL) return 1;
    memset(at, 0, sizeof(struct AirTicket));
	//at->is_full = 0;
	return 0;
}

/********************* �㭪樨 ���஢���� *********************/

// �㭪�� ���������� ��ப� str, ࠧ��୮���� n, ���. ᨬ������ � ������ �� x �� y
void rand_str(char *str, int n, char x, char y)
{
	for (int i = 0; i < n; i++) str[i] = x + rand() % (y - x + 1);
	str[n] = '\0';
}

// ��������� ��������� ��砩�묨 ����묨
int SetRandomDataAirTicket(struct AirTicket *at)
{
	if (at == NULL) return 1;
	// ���� ����� ३�
	rand_str(at->fligh_num.airline, 2, 'A', 'Z'); // ���� 2-� �㪢������ ���� ������������ 
	at->fligh_num.num = 1000 + rand() % 9000; // ���� 4-� ��஢��� ����� ३� 1000-9999

	// ���� �㭪� �����祭��
	sprintf(at->dest.city, "city %d", rand() % 10); // ���� �������� ��த� �� ����.
	sprintf(at->dest.country, "country %d", rand() % 10); // ���� �������� ��࠭� �� ����.
	strcpy(at->dest.airport, ""); // �� 㬮�砭�� 1 ��ய��� � ��த�
	// 50% ����⭮��� �� � ��த� >1, ⮣�� ������ 3-� �㪢���� ��� ��ய���
	if (rand() % 2 == 1) rand_str(at->dest.airport, 3, 'A', 'Z');

	// ���� �६���
	at->dep_time.hour = rand() % 24; // ���� �� 0-23
	at->dep_time.min = rand() % 60; // ���� ������ 0-59

	// ���� ����
	at->dep_date.day = rand() % 31 + 1; // ���� �᫠ 1-31
	at->dep_date.month = rand() % 12 + 1; // ���� ����� 1-12
	at->dep_date.year = 2017 + rand () % 2; // ���� ���� �� 2017 �� 2018

	// ���� 業�
	at->cost.val = 4000 + rand() % (80 + 1) * 100; // ���� �⮨���� �� 4000 �� 12000 RUB
	strcpy(at->cost.curr, "RUB"); // ����� �ᥣ�� �㡫�

	at->is_full = 1; // ⥯��� ����� ����������
	return 0;
}

/********************* �㭪樨 ࠡ��� � �� ��������⮢ *********************/
/*********************** ����� ����樨 �ࠢ����� ***********************/

//  ���������� ����� � ��
int AddAirTicket_DB(struct DB_AirTicket *db, struct AirTicket at)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� ��
	// �᫨ ���� �����, � �뤥�塞 ������
	if (num == 0)
	{
        db->sz_db = SIZE_BASE; // �� 㬮�砭�� ࠧ��୮��� �� �㤥� ࠢ�� SIZE_BASE
        db->arr = (struct AirTicket *)malloc(db->sz_db * sizeof(struct AirTicket));
	}
	else if (num == db->sz_db) // �᫨ ���-�� �-⮢ 㦥 ���⨣�� ࠧ��୮�� ����, � �뤥�塞 ������
	{
		db->sz_db *= 2; // 㢥��稢��� ࠧ��୮��� ���� � 2 ࠧ�
        db->arr = (struct AirTicket *)realloc(db->arr, db->sz_db * sizeof(struct AirTicket));
	}
	db->arr[num] = at;
	db->num++;

	return 0;
}

//  ���㫥��� ������ ��� �������� ����� � ��
int ClearAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� ��
	if (num == 0 || index < 0 || index > num-1) return -1; // �᫨ ����� � �� ���. ������ ��� � ���� ��� ������

	ClearAirTicket(&db->arr[index]); // ����⪠ �-�
	
	return 0;
}

// ������ ������ ��� �������� ����� � ��
int EditAirTicket_DB(struct DB_AirTicket *db, int index, struct AirTicket at)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� ��
	if (num == 0 || index < 0 || index > num-1) return -1; // �᫨ ����� � �� ���. ������ ��� � ���� ��� ������
	
	db->arr[index] = at;

	return 0;
}

// 㤠����� �������� ����� �� �� � ᤢ���� ��⠢���� �����
int RemoveAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� ��
	if (num == 0 || index < 0 || index > num-1) return -1; // �᫨ ����� � �� ���. ������ ��� � ���� ��� ������

	for (int i = index; i < num-1; i++) db->arr[i] = db->arr[i + 1];
	ClearAirTicket(&db->arr[num-1]); // ����⪠ ��᫥����� �-�
	db->num--;
	return 0;
}

/*********************** ����樨 �����/�뢮�� ***********************/

// ���� ������ ��� �������� ����� � ��
int ImputAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� ��
	if (num == 0 || index < 0 || index > num-1) return -1; // �᫨ ����� � �� ���. ������ ��� � ���� ��� ������

	char tmp[10];
	sprintf(tmp, "� %d", index);
	ImputAirTicket(tmp, &db->arr[index]);
	return 0;
}

// �뢮� �� �࠭ �������� ����� � ��
int OutputAirTicket_DB(struct DB_AirTicket *db, int index)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� ��
	if (num == 0 || index < 0 || index > num-1) return -1; // �᫨ ����� � �� ���. ������ ��� � ���� ��� ������

	char tmp[10];
	sprintf(tmp, "� %d", index);
	OutputAirTicket(tmp, db->arr[index]);
	return 0;
}

// �뢮� �� �࠭ ��� ����ᥩ � ��
int OutputAllAirTicket_DB(struct DB_AirTicket *db)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� ��

	for (int i = 0; i < num; i++)
	{
		char tmp[10];
		sprintf(tmp, "� %d", i);
		OutputAirTicket(tmp, db->arr[i]);
	}
	return 0;
}

/*********************** ������ ���஢�� ***********************/

// �ࠢ����� ���� ����஢ ३ᮢ (��� ������������, ����� ३�)
int CompareFlighNumber(struct FlighNumber fn1, struct FlighNumber fn2)
{
	char str1[80], str2[80];

	sprintf(str1, "%s%d", fn1.airline, fn1.num);
	sprintf(str2, "%s%d", fn2.airline, fn2.num);

	return strcmp(str1, str2);
}

// �ࠢ����� �㭪� �����祭�� (��த, ��࠭�, ��� ��ய���)
int CompareDestination(struct Destination ds1, struct Destination ds2)
{
	char str1[80], str2[80];

	sprintf(str1, "%s%s%s", ds1.city, ds1.country, ds1.airport);
	sprintf(str2, "%s%s%s", ds2.city, ds2.country, ds2.airport);

	return strcmp(str1, str2);
}

// �ࠢ����� �६��� (���, ������)
int CompareTime(struct Time t1, struct Time t2)
{
	return (t1.hour * 60 + t1.min) - (t2.hour * 60 + t2.min);
}

// �ࠢ����� �६��� (���, �����, ���)
int CompareData(struct Date d1, struct Date d2)
{
	return ((d1.year * 12 + d1.month) * 31 + d1.day) - ((d2.year * 12 + d2.month) * 31 + d2.day);
}

// �ࠢ����� 業
int ComparePrice(struct Price p1, struct Price p2)
{
	return p1.val - p2.val;
}

// �ࠢ����� ��������⮢ �� ��� ����
// �ࠢ����� ������������ ��������� � ����� �� �ந�室��, ���⮩ ��⠥��� ᠬ� �殮�� (� �����)
int CompareAnyField(struct AirTicket at1, struct AirTicket at2, enum FIELD f)
{
	int res = 0;
	
	// �᫨ �� �ࠢ������ �� �� ������������ ����⮢ � �� �� ���� - ���⮩, � ���⮩ ᠬ� �殮��
	if (f != FULL && (at1.is_full == 0 || at2.is_full == 0))
	{
		//return at2.is_full - at1.is_full;
		return -INT_MAX;
	}
	switch (f)
	{
		// FLIGH_NUMBER, DESTINATION, DEP_TIME, DEP_DATE, PRICE, FULL };
		// �ࠢ����� ���� ����஢ ३ᮢ (��� ������������, ����� ३�)
	case FLIGH_NUMBER:
		res = CompareFlighNumber(at1.fligh_num, at2.fligh_num);
		break;
		// �ࠢ����� �㭪� �����祭�� (��த, ��࠭�, ��� ��ய���)
	case DESTINATION:
		res = CompareDestination(at1.dest, at2.dest);
		break;
		// �ࠢ����� �६��� (���, ������)
	case DEP_TIME:
		res = CompareTime(at1.dep_time, at2.dep_time);
		break;
		// �ࠢ����� �६��� (���, �����, ���)
	case DEP_DATE:
		res = CompareData(at1.dep_date, at2.dep_date);
		break;
		// �ࠢ����� 業
	case PRICE:
		res = ComparePrice(at1.cost, at2.cost);
		break;
		// �ࠢ����� �� ������������ (����� - ᠬ� ����訥, � �����)
	case FULL:
		res = at1.is_full - at2.is_full;
		break;
	}
	return res;
}

// ���஢�� ��⠢���� ����ᥩ �� �� 㪠������� ������ ����
int Sort_DB(struct DB_AirTicket *db, enum FIELD f)
{
	if (db == NULL) return -1; // �᫨ 㪠��⥫� ���⮩
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

/*********************** ����樨 ���᪠ ***********************/

//  ������� ���� ��ࢮ� ���⮩ ����� � ��
struct AirTicket *FindEmptyAirTicket_DB(struct DB_AirTicket *db, int *n)
{
	if (db == NULL) return NULL; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� �� ��������⮢

	int i;
	for (i = 0; i < num && db->arr[i].is_full; i++);
	*n = (i == num) ? -1 : i; // �᫨ ���⮩ ����� �� �������, ������ -1, ���� ������
	return (i == num) ? NULL : &db->arr[i]; // �᫨ ���⮩ ����� �� �������, ������ NULL, ���� 㪠��⥫�
}

//  ������� ���� �������쭮� ����� ��������� ���� � ��
struct AirTicket *FindMinFieldAirTicket_DB(struct DB_AirTicket *db, enum FIELD f, int *n)
{
	if (db == NULL) return NULL; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� �� ��������⮢

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

//  ������� ���� �㦭�� ����� ��� �������� ������� � ��� � ��
struct AirTicket *FindLikeFieldAirTicket_DB(struct DB_AirTicket *db, struct AirTicket at, enum FIELD f, int *n)
{
	if (db == NULL) return NULL; // �᫨ 㪠��⥫� ���⮩
	int num = db->num; // ⥪��. ࠧ��� �� ��������⮢

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
	if (db == NULL) return 1; // �᫨ 㪠��⥫� ���⮩

	FILE *f = fopen(file, "wb");
	fwrite(&db->num, sizeof(int), 1, f);
    fwrite(db->arr, sizeof(struct AirTicket), db->num, f);
	fclose(f);
}

int LoadAirTicket_DB(struct DB_AirTicket *db, char *file)
{
	if (db == NULL) return 1; // �᫨ 㪠��⥫� ���⮩

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
	AirTicket at1, at2; // ᮧ���� ��� ������ ����� - �1, �2
	SetRandomDataAirTicket(&at1); // ������塞 ����� �1
	OutputAirTicket("at1", at1); OutputAirTicket("at2", at2); // �뢤�� �� �࠭ ��� �����
	at2 = at1; // �����㥬 ����� �1 � ����� �2
	ClearAirTicket(&at1); // ���頥� ����� �1
	OutputAirTicket("at1", at1); OutputAirTicket("at2", at2); // �뢤�� �� �࠭ ��� �����
	*/

    struct DB_AirTicket db_at;

    memset(&db_at, 0, sizeof(struct DB_AirTicket));

    const int N = 5; // ���-�� ᮧ�������� ��������⮢
	int k;
    enum FIELD f; // ��६����� � ⨯�� ����
    struct AirTicket *p, tmp;

	for (int i = 0; i < N; i++) // ᮧ���� ��᪮�쪮 ��������⮢ � ����묨
	{
        struct AirTicket tmp;
		SetRandomDataAirTicket(&tmp);
		AddAirTicket_DB(&db_at, tmp);
	}

    /*
    // �஢�ઠ ����� � �⥭�� �� ���
    struct DB_AirTicket db_at_new;
    SaveAirTicket_DB(&db_at, "c:\\out.bin");
    LoadAirTicket_DB(&db_at_new, "c:\\out.bin");
    OutputAllAirTicket_DB(&db_at_new);
    */

    OutputAllAirTicket_DB(&db_at); // �뢮��� �� ᮧ����� ����� �� �࠭

	puts("���頥� 1-�� ���������, 㤠�塞 2-�� ���������, � ���頥� 4-�� ��������� (����� �⠫ 3-��):");
	ClearAirTicket_DB(&db_at, 1); // ���頥� 1-� ������
	RemoveAirTicket_DB(&db_at, 2); // 㤠�塞 2-� ������
	ClearAirTicket_DB(&db_at, 3); // ���頥� 3-� ������, ����� �뫠 ����砫쭮 4-��
	OutputAllAirTicket_DB(&db_at); // �뢮��� �� ����� �� �࠭

	p = FindEmptyAirTicket_DB(&db_at, &k); // �饬 㪠��⥫� �� 1-� ������ ������
	printf("���� ���⮩ ��������� � �� � �����ᮬ %d, ��� ᮤ�ন���:\n", k);
	OutputAirTicket("�������", *p); // �뢮��� ��� ������ �� �࠭

	SetRandomDataAirTicket(&tmp); // ������塞 �६���� ��������� ��砩�묨 ����묨
	puts("ᮤ�ন��� �६������ ���������:");
	OutputAirTicket("�६����", tmp); // �뢮��� ��� ����� �� �࠭

	EditAirTicket_DB(&db_at, k, tmp); // �����塞 1-� ������ ������ � �� �� ����� �� �६������ ��������� 
	puts("�����塞 ����� � 1-�� ���⮬ ���������, �� ���� �� �६������, ᯨ᮪ ��� ����⮢:");
	OutputAllAirTicket_DB(&db_at); // �뢮��� �� ᮧ����� ����� �� �࠭

	// ���� �����: FLIGH_NUMBER - ����३�, DESTINATION - �㭪� �����祭��, 
	// DEP_TIME - �६� �뫥�, DEP_DATE - ��� �뫥�, PRICE - �⮨�����, FULL - �������������
	// ����㥬 �� �� ��������� ���� f
	f = PRICE;
	printf("����㥬 �� �� ����: %s\n", name_field[f]);
	// ����㥬 �������� �� ���� f
	Sort_DB(&db_at, f);
	OutputAllAirTicket_DB(&db_at); // �뢮��� �� ����� �� �࠭
	
	// �饬 ������ � �� � ��������� ���祭��� ��������� ���� f
	f = DEP_TIME;
	printf("�饬 ������ � �� � ���. ���祭��� ����: %s\n", name_field[f]);
	// �饬 㪠��⥫� �� �������� �� ���. ���祭��� ���� f
	p = FindMinFieldAirTicket_DB(&db_at, f, &k);
	printf("� �� ������ ��� ����஬ %d, �� ᮤ�ন���:\n", k);
	OutputAirTicket("�������", *p); // �뢮��� ��� ������ �� �࠭
	
	// �饬 ������ � �� � ���ᨬ��쭮 ᮢ�����騬 ���祭��� ��������� ���� f 㪠������� �� �६����� �����
	f = PRICE;
	printf("�饬 ������ � �� � �������� ������� �����: %s\n", name_field[f]);
	SetRandomDataAirTicket(&tmp); // ������塞 �६���� ��������� ��砩�묨 ����묨
	puts("�� ᫥���饣� �६������ ���������:");
	OutputAirTicket("�६����", tmp); // �뢮��� ��� ����� �� �࠭
	// �饬 㪠��⥫� �� �������� � �������� ᮢ�����騬 � ����� f �� �६������ �����
	p = FindLikeFieldAirTicket_DB(&db_at, tmp, f, &k);
	printf("� �� ������ ��� ����஬ %d, �� ᮤ�ন���:\n", k);
	OutputAirTicket("�������", *p); // �뢮��� ��� ������ �� �࠭

    return 0;
}

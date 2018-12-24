/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 * ���ଠ⨪� � �ணࠬ��஢���� �.2, ������ୠ� �1, ��ਠ�� 6
 *
 * �������:
 *
 */

#include <stdio.h>
#include <stdlib.h> // ��� ���������� �ᥢ����砭묨 ���祭�ﬨ ��室���� ���ᨢ�
#include <locale.h>
#include <time.h> // ��� ᬥ�� �ॢ����砩��� ���祭��

// �뤥����� ����� ��� ���ᨢ x ������ z ����騩 �� ⨯� y
#define NEW(x, y, z) { x = (y*)malloc((z) * sizeof(y)); }
// ��᢮�������� ����� �� ��� ���ᨢ� x
#define DEL(x) { free(x); x = NULL; }
// ����� ���祭�ﬨ ����� ᮡ�� ��६����� a � b
#define SWAP(a, b, type) { type tmp = a; a = b; b = tmp; }

// �㭪�� ����୮�� ���᪠ ���� ��� ��⠢�� ᨬ���� k, � 㯮�冷祭��� ��ப� a (ࠧ��୮���� n)
// �����頥�: 㪠��⥫� �� ��������� ������ ��⠢��
char *bin_search(char *a, int n, char k)
{
	int i1 = -1, i2 = n; // ������ �࠭��� ���᪠
	while (i2 - i1 > 1) // �믮��塞 �� �� ��� ���� ����� ���� �࠭�栬� ����� 1 ᨬ���� 
	{
		int c = (i2 + i1) / 2; // ��室�� ������ �।���� �-� ����� ���� ⥪��. �࠭�栬�
		// �᫨ �-� �� ᫥��� �࠭�� ����� ��� ࠢ�� �᪮���� (k), � ᤢ����� ��� ��ࠢ� �� �।���
		if (*(a + c) <= k) i1 = c; // a[c] < k
		// �᫨ �-� �� �ࠢ�� �࠭�� ����� �᪮���� (k), � ᤢ����� ��� ����� �� �।���
		else i2 = c;
	}
	return a + i2; // a[i2]
}

// ���஢�� ��⠢���� � �㭪樥� ����୮�� ���᪠
// �����頥�: �� 㪠��⥫� �����஢����� ��ப� a
void sort_insert_mod(char *a, int n)
{
	for (int i = 1; i < n; i++) // ��ॡ�ࠥ� �� �-�� ���ᨢ� ��稭�� � 2-�� �����
	{
		char key = *(a + i); // key = a[i]
		char *p = bin_search(a, i, key); // ��室�� 㪠��⥫� �� ������ ��� ��⠢�� ���祭�� a[i]
		if (p == a + i) continue; // p == a [i] - �᫨ ������ ᨬ���� �� �����﫠��, ���室�� � ᫥�. �-��
	// ��᢮������� ���� ��� ��⠢�� ������ �����
		for (char *pp = a + i; pp > p; pp--) *pp = *(pp-1); 	// ��।������ �� ������ �� ���� a[i] (�� ��. ��ࠢ�)
		*p = key;
	}
}

// ���஢�� ��⠢���� ��� SWAP
int sort_insert_2(char *a, int n)
{
	for (int i = 1; i < n; i++)
	{
		char a_i = a[i];
		int j = i;
		while (j > 0 && a[j-1] > a_i) // �᫨ �।���. �-� ����� ��⠢�塞���
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = a_i;
	}
	return 0;
}

// ���஢�� ��⠢����
void sort_insert(char *a, int n)
{
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && a[j - 1] > a[j]; j--)
			SWAP(a[j - 1], a[j], char);
}

// �㭪�� ���������� 楫��� ���ᨢ� a, ࠧ��୮���� n, ���. ᨬ������ � ������ �� x �� y
void rand_str(char *a, int n, char x, char y)
{
	for (int i = 0; i < n; i++) *(a + i) = x + rand() % (y - x + 1);
	*(a + n) = '\0';
}

// �㭪�� ���������� 楫��� ���ᨢ� a, ࠧ��୮���� n, ᨬ������ �� ��ப� s
// �����頥� ���-�� ���ᥭ��� ᨬ�����
int set_str(char *a, int n, char *s)
{
	int i;
	for (i = 0; i < n && *(s+i) != '\0'; i++) // s[i] != '\0'
		*(a+i) = *(s+i); // a[i] = s[i]
	*(a+i) = '\0'; // a[i] = '\0'
	if (n != i) return i;
	return n;
}

// �㭪�� �஢���� ���祭�� 楫��� ���ᨢ� a, ࠧ��୮���� n, �� ����稥 �����⠭�� ��� �-⮢ (�� 0...n-1)
// �����頥�: ��⨭� / ����
int check_sort(char *a, int n)
{
	int i;
	for (i = 0; *(a+i) <= *(a+i+1) && i < n - 1; i++);
    return (int)(i == (n - 1));
}

// �㭪�� �뢮��� �� �࠭ १���� �஢�ન 楫��� ���ᨢ� a �� �।��� �����⠭�� ��� �-⮢ (�� 0...n-1)
void show_check_sort(char *a, int n)
{
    if (check_sort(a, n) == 1) puts("���: ���ᨢ �����஢�� �� �����⠭��");
	else puts("���: ���ᨢ �� �����஢�� �� �����⠭��");
}

int main(void)
{
	srand((unsigned int)time(NULL));

	int N = 10;
	char *A;
	NEW(A, char, N);
	/*
	puts("�஢�ઠ ࠡ��ᯮᮡ���� �㭪樨 ����୮�� ���᪠ � �����஢����� ���ᨢ�"); 
	int nn = set_str(A, N, "2369");
	char *p, c = '4';
	printf("���� � ��ப�: \"%s\"\n", A);
	printf("���� ��� ��⠢�� ᨬ����: '%c'\n", c);
	p = bin_search(A, nn, c);
	if (!check_sort(A, nn)) puts("! ������ ��ப� �� ���� �����஢�����, ������ ����� ���� �����४⭮�");
	printf("������ ��� ��⠢��: %d (ᨬ��� '%c')\n", p-A+1, p[0]);
	printf("㪠��⥫� �� ᨬ���: %s\n\n", p);
	*/
	puts("�஢��塞 ���஢�� ��⠢���� � ������� �-樨 ����୮�� ���᪠");
	rand_str(A, N, 48, 57); // ������塞 ��ப� A 10-� ��砩�묨 ��ࠬ� �� '0'..'9'
	//set_str(A, N, "1562738495");
	printf("ᨬ���� ��� ���஢��:\t\t%s\n", A);
	sort_insert_mod(A, N);
	//sort_insert(A, N);
	//sort_insert_2(A, N);
	printf("�����஢���� ᨬ����:\t%s\n", A);
	show_check_sort(A, N); // �뢮��� �� �࠭ १���� �஢�ન �� �����⠭��

	puts("");
	DEL(A);

	return 0;
}

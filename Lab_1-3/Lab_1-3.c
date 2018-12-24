/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 * ���ଠ⨪� � �ணࠬ��஢���� �.1, ������ୠ� �3, ��ਠ�� 12
 *
 * �������:
 *
 */

#include <stdio.h>
#include <string.h>

// �뤥����� ����� ��� ���ᨢ x ������ z (���樠���. '\0' ᨬ������) ����騩 �� ⨯� y 
#define NEW(x, y, z) { x = (y*)malloc((z) * sizeof(y)); memset(x, '\0', (z) * sizeof(y)); }

// ��᢮�������� ����� �� ��� ���ᨢ� x
#define DEL(x) { free(x); x = NULL; }

/*
�㭪�� 㤠����� � ��ப� �㡫������ ᨬ�����, � ⠪ �� �������� � ��砫� � � ���� ��ப�
�室��: s - ��ப� � ���ன �㤥� 㤠���� ᨬ����, � - ᨬ��� ����� �㤥� 㤠����
�����頥��� ���祭��: ����� ����� ��ப� ��᫥ 㤠����� ᨬ�����
*/
int strDelDub(char *s, char c)
{
	int j = 0; // ���稪 ᨬ����� � ����� ��ப�
	for (int i = 0; s[i] != '\0'; i++) // ��ॡ�ࠥ� �� ᨬ���� � ��ப� s
	{
		if (s[i] == c) // �᫨ ������ ᨬ��� 'c'
		{
			if (j == 0) continue; // �ய�᪠�� �� ᨬ���� 'c' �� ��ࢮ�� ᨬ����
			if (s[i + 1] == c) continue; // �᫨ ᫥��� �� ��� ⮦� ᨬ��� 'c' - �ய�᪠��
		}
		s[j] = s[i];
		j++;
	}
	// �⠢�� ����� ����砭�� ��ப�
	if (s[j - 1] == c) j--; // �᫨ �।.ᨬ��� �� '�' � 㬥��蠥� �����. ����� ��ப�
	s[j] = '\0';
	return j; // �����頥� ����� ����� ��ப�
}

/*
�㭪�� ����� ��ப�, � 㤠����� ����������� �஡���� (� � ��砫�/����) � �뢮��� �⮩ ��ப�
�室��: s - ��室��� ��ப� � ������ �㤥� ����ᠭ १���� �⥭�� � ���᮫�
spc - �ਧ��� 㤠����� ������� �஡����, �᫨ ࠢ�� 1 - �஡��� 㤠�塞
*/
void inputStr(char *s, int spc)
{
	printf("������ ��ப�:   ");
	if (s[0] == '\0')
        gets(s);
	else // ��� ���४⭮�� �⮡ࠦ���� �⫠���
		printf("%s", s);
	printf("\n�������:         \"%s\"\n", s);
	if (spc == 1) // �᫨ 㪠���� 㤠����� �஡����
	{
		strDelDub(s, ' '); // 㤠�塞 �������騥�� �஡��� � � ��砫� � ����
		printf("\n��� �஡����:    \"%s\"\n", s);
	}
}

/*
�㭪�� ������஢���� ��ப� ������� (���冷� �㪢 �������)
�室��: s_in - ��室��� ��ப� ������ �㤥� ������஢���, 
s_out - ��室��� ��ப� ������ �㤥� ����ᠭ� ������஢����� ��ப� �� s_in
*/
void strInvert(char *s_in, char *s_out)
{
	int i, n = strlen(s_in);
	for (i = 0; i < n; i++) s_out[i] = s_in[n-1-i];
	s_out[i] = '\0';
}

/*
�㭪�� ࠧ������ ��ப� �� �����ப�, ��� ࠧ����⥫� - ������� ᨬ���
ࠧ������� �ந�室�� � ⮬ ���� ��� ���� ���室 �� ᨬ���� ࠧ����⥫� � ᨬ���� �� ࠧ����⥫�
��� �������, �� ᨬ���� �� ࠧ����⥫� �� ᨬ���� ࠧ����⥫�
�室��: s - ��室��� ��ப� ������ �㤥� ࠧ������ �� �����ப� �� ࠧ����⥫�,
� - ᨬ��� ࠧ����⥫�, s_sub - ���ᨢ �����ப � ����� ���� ����ᠭ� �� �⤥�쭮�� �� �����ப�
�����頥��� ���祭��: ���-�� ��������� �����ப � ��ப� s_sub
*/
int subStr(char *s, char c, char *s_sub[])
{
	if (s[0] == '\0') return 0; // �᫨ ��।����� ��ப� �����
								// ���� ��砩, �� 1-� ᨬ��� �� �ᥣ�� ��砫� 1-�� �����ப�
	s_sub[0] = &s[0]; // 1-� ᨬ��� - ��砫� 1-�� �����ப�
	int i_sub = 1; // ���稪 ���-�� �����ப, 㦥 ࠢ�� 1

	for (int i = 1; s[i] != '\0'; i++) // ��ॡ�ࠥ� �� ᨬ���� � ��ப� s
	{
		if (s[i - 1] == '\0') // �᫨ �।��騩 ᨬ��� �⠫ ����殬 �����ப�
		{
			s_sub[i_sub] = &s[i]; // � ��� ᨬ��� �� ��砫� ����� �����ப� 
			i_sub++; // 㢥��稢��� ���-�� ��������� �����ப
			continue;
		}
		if (s[i] == c) // �᫨ ⥪�騩 ᨬ��� ࠧ����⥫�
		{
			// ���� ��砩, �� ��᫥���� ᨬ��� ࠧ����⥫�
			// �� �㤥� ࠧ������ �����ப�, �� �㤥� ���� ����� ��᫥���� �����ப�
			if (s[i + 1] == '\0') continue;
			// �᫨ �।��騩 ��� ᫥���騩 ᨬ���� - �� ࠧ����⥫�
			if (s[i + 1] != c || s[i - 1] != c)
			{
				s[i] = '\0'; //  � ��� ᨬ��� - ࠧ������� �����ப
				continue;
			}
		}
	}
	return i_sub;
}

/*
�㭪�� ������஢���� � ��ப� ��� �����ப �������, ��� ࠧ����⥫� �஡��
�室��: s_in - ��室��� ��ப� ������ �㤥� �८�ࠧ��뢠��, s_out - ��ப� � ������ �㤥�
����ᠭ� �८�ࠧ������� ��ப�
dbg - �ਧ��� �⫠���, �᫨ ࠢ�� 1, � �뢮��� �� �����ப�
*/
void invertSubStr(char *s_in, char *s_out, int dbg)
{
	char **s_sub; // 㪠��⥫� �� ���ᨢ �����ப
	char *s_in_2; // ��ப� ��� �࠭���� ����� ��।����� ��ப� s_in
	int n, max = strlen(s_in) / 2 + 1; // ����. ���-�� �����ப ���஥ ����� ���� � �������

	NEW(s_sub, char*, max); // ᮧ���� ���ᨢ ��� �࠭���� �����ப ������ max
	int m = strlen(s_in);
	NEW(s_in_2, char, m); // ᮧ���� ��ப� ��� ����� �室��� ��ப�
	strcpy(s_in_2, s_in); // �����㥬 �室��� ��ப� �� �� �� ������ ��室��� ��ப�
	// ������塞 ���ᨢ �����ப���
	n = subStr(s_in_2, ' ', s_sub); // � ��࠭塞 ����稢襥�� ���-�� �����ப
	for (int i = 0; i < n; i++)
	{
		char *s_inv;
		int l = strlen(s_sub[i]);
		NEW(s_inv, char, l); // ᮧ���� �६����� ��ப�
        if (dbg == 1) printf("%d �����ப� (%d): \"%s\"\n", i+1, l, s_sub[i]);
		strInvert(s_sub[i], s_inv);
		strcat(s_out, s_inv); // ������塞 ����।�� ������ ������஢����� �����ப� 
		if (i != n - 1) strcat(s_out, " "); // ࠧ���塞 �����ப� �஡���� (�஬� ��᫥����)
		DEL(s_inv);
	}
	DEL(s_in_2); // �᢮������� ��ப� �࠭���� ����� �室��� ��ப�
	DEL(s_sub); // �᢮������� ���ᨢ ��� �࠭���� �����ப
}

/*
�㭪�� ���஢���� �� ���४⭮��� �८�ࠧ������ ��ப� �� �ࠢ����� � ��室��� � �뢮��� १����
���஢����
�室��: s_in - ��室��� ��ப� ������ �⥫� �������஢���, s_out - ����稢���� ��ப� � 
�������஢����� ��ப��
*/
void show_test(char *s_in, char *s_out)
{
	char *s_in_2; // ��ப� ��� �࠭���� ���⭮�� �८�ࠧ������ ��ப� s_out
	 
	NEW(s_in_2, char, strlen(s_out)); // ᮧ���� ��ப� ⮩ �� ������ �� s_out
	printf("�८�ࠧ�������: \"%s\"\n", s_out);
    invertSubStr(s_out, s_in_2, 0);  // �८�ࠧ��뢠�� ��ப� s_out � s_in_2
	printf("�८�ࠧ.�����.: \"%s\"\n", s_in_2);
	if (!strcmp(s_in, s_in_2)) puts("��� �ன���, �८�ࠧ������ ���४⭮");
	else puts("��� �� �ன���, �८�ࠧ������ �� ���४⭮");
	DEL(s_in_2); // �᢮������� ��ப� �࠭���� ����� �室��� ��ப�
}

int main(void)
{
	//char s_in[80] = "    123 45   6 87  ����� "; // �室��� ��ப� ��� �⫠���, ��� ��室��
	//char s_in[80] = "    123 45   6  87  ����� "; // �室��� ��ப� ��� �⫠���, ��� �� ��室��

    char s_in[80] = {'\0'}; // �室��� ��ப�
    char *s_out; // ��室��� ��ப�, � ��� �㤥� �࠭���� १����

	// ��ன ��ࠬ���: 0 - �� 㤠�塞 �㡫����� �஡����, 1 - 㤠�塞
    inputStr(s_in, 0); // ���� ������
	NEW(s_out, char, strlen(s_in)); // �뤥�塞 ������ ��� �࠭���� १����
    invertSubStr(s_in, s_out, 0); // ����砥� �८�ࠧ������� ��ப� s_in � s_out
	show_test(s_in, s_out); // �뢮��� १����� ���
	DEL(s_out); // �᢮������� ��ப� �࠭���� ��室��� ��ப�

	return 0;
}

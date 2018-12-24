/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 * ���ଠ⨪� � �ணࠬ��஢���� �.2, ������ୠ� �3, ��ਠ�� 13 
 *
 * �������:
 *
 */

#include <stdio.h>

unsigned char typedef UCHAR;

//  ������� ����� byte � ������ ��࠭���� ���祭�� data ⨯�� type
#define DATA_TO_BYTE(byte, type, data) {type *tmp = (type*)byte; *tmp = data; byte = (char*)tmp; }
// ������� ����� byte �� ���ன ����������� ���祭�� data ⨯�� type
#define BYTE_TO_DATA(byte, type, data) {type *tmp = (type*)byte; data = *tmp; byte = (char*)tmp; }

// ������� ����� byte �� ������ ��࠭����� ���祭�� data ⨯�� type � ᫥��� ���室�� �� ���� n-�� ����� ⨯� type � ����� (n = 0 - �� ���室��)
#define DATA_TO_BYTE_INC(byte, type, data, n) { type *tmp = (type*)byte; *tmp = data; *tmp += n; byte = (char*)tmp; }
// ������� ����� byte �� ���ன ����������� ���祭�� data ⨯�� type � ᫥��� ���室�� �� ���� n-�� ����� ⨯� type � ����� (n = 0 - �� ���室��)
#define BYTE_TO_DATA_INC(byte, type, data, n) { type *tmp = (type*)byte; data = *tmp; *tmp += n; byte = (char*)tmp; }

int pack(char *p)
{
	char *s = p;
    int to_do = 1;
	char choice[2];
	int n_dig;

	do
	{
		printf("������ 楫�� (1) ���� �஡��� (2) ���� ����� ����� (3)\n������ ���� �롮�: ");
		scanf("%s", choice);
		switch (choice[0])
		{
		case '1':
			printf("��࠭� 楫��\n������ ���-�� �ᥫ ��� �����: ");
			scanf("%d", &n_dig);
			*p++ = '%'; // ��稭��� ��� ���-�� ��� � ᨬ���� %
			if (n_dig > 1) *p++ = (char)n_dig; // �᫨ ��� > 1, ��襬
			*p++ = 'd'; // ����뢠�� ��� ���-�� ��� ᨬ����� d
						// ��襬 ᠬ� ���� � த��� �।�⠢����� � �����
			for (int i = 0; i < n_dig; i++)
			{
				int d;
				printf("楫�� �᫮ � %d: ", i + 1);
				scanf("%d", &d);
				// �����㥬 ⥪�饥 楫�� �᫮, ������: *((int*)p)++ = d; 
				int *p_d = (int*)p; *p_d++ = d;
				p = (char*)p_d; // ��࠭塞 ��� ��� � ������
			}
			break;
		case '2':
			printf("��࠭� �஡���\n������ ���-�� �ᥫ ��� �����: ");
			scanf("%d", &n_dig);
			*p++ = '%'; // ��稭��� ��� ���-�� ��� � ᨬ���� %
			if (n_dig > 1) *p++ = (char)n_dig; // �᫨ ��� > 1, ��襬
			*p++ = 'f'; // ����뢠�� ��� ���-�� ��� ᨬ����� d
						// ��襬 ᠬ� ���� � த��� �।�⠢����� � �����
			for (int i = 0; i < n_dig; i++)
			{
				float f;
				printf("�஡��� �᫮ (� ����⮩) � %d: ", i + 1);
				scanf("%f", &f);
				// �����㥬 ⥪�饥 �஡��� �᫮, ������: *((int*)p)++ = f; 
				float *p_f = (float*)p; *p_f++ = f;
				p = (char*)p_f; // ��࠭塞 ��� ��� � ������
			}
			break;
		case '3':
			puts("�����稫� ����");
			to_do = 0;
			break;
		default:
			puts("�訡��, �. ����");
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
		// �⠥� ���-�� ����� ����� ���
		if (*p == 'd' || *p == 'f') n_dig = 1; // �᫨ 㪠���� 1 �᫮
		else n_dig = (int)*p++; // �⠥� ���-�� �ᥫ

		switch (*p++)
		{
		case 'd':
			printf("楫� �᫠ � ���-�� %d: ", n_dig);
			for (int i = 0; i < n_dig; i++)
			{
				int *p_i = (int*)p, d = *p_i++;
				p = (char*)p_i;
				printf("%d ", d);
			}
			printf("\n");
			break;
		case 'f':
			printf("�஡�� �᫠ � ���-�� %d: ", n_dig);
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
	printf("�।�⠢����� � HEX ���� ������ ����� � %d ����:\n", n);
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

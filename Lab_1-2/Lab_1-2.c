/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 * ���ଠ⨪� � �ணࠬ��஢���� �.1, ������ୠ� �2, ��ਠ�� 2
 *
 * �������:
 *
 */

#include <stdio.h>
#include <math.h>

/*
�㭪�� ������ �१ ��� ������� ����ࠫ�� ������ �� ��� x, � �筮���� k
���-�� ������ ��᫥ ����⮩
�-�� �����頥� १���� ln(x)
*/

double ln(double x, unsigned int k)
{
	if (x < 0) return NAN; // �᫨ 㪠��� ����. ��㬥��
	if (x == 0) return -INFINITY; // �᫨ 㪠��� 0 ��� ��㬥��

	int i;
	double s, sn; // s - �������. �㬬� �ᥣ� �鸞, sn - ���祭�� n-�� ����� �鸞
	double zn; // ������⥫쭮� ���祭�� ���������� z � �⥯��� 
	
	double eps = 1 / pow(10, k); // ���� �筮�� ࠢ��� 10 ^ (-k)
	double z = (x - 1) / (x + 1);
	// 横� ��ॡ�� ��� ����⮢ i=1..n
	// �����塞 横� �� �� ���� ����� ���祭�� y ����� ����稭� eps
	for (s = 0, sn = 2*z, zn = z, i = 2; fabs(sn) > eps; i++)
	{
		s += sn; // ������塞 � ����� �㬬� s ���祭�� (i-1)-�� ����� �鸞 sn
		zn *= z * z; // 㢥��稢��� �⥯��� �᫠ z �� 2 ��� i-�� ����� �鸞
		sn = 2.0 / (2 * i - 1) * zn; // ��⠥� ���祭�� ����� ��� i-�� ����� �鸞
	}
	return s;
}

void show_table(double x1, double x2, double dx, unsigned int k)
{
	printf("x\t�� ln(x)\tln(x)\n"); // ��������� ⠡����
	for (double x = x1; x <= x2; x += dx)
		// ������塞 ��ப� ⠡���� � ���祭�ﬨ
		printf("%.1lf\t%.4lf\t\t%lf\n", x, ln(x, k), log(x));
}

int main(void)
{
	// ��砫쭮�, ����筮�, 蠣, �筮��� (���-�� ������ ��᫥ ����⮩)
	show_table(-0.1, 1.0, 0.1, 4);

    return 0;
}

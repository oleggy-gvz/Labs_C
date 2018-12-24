/*
 * text coding: IBM866 / CP866 / csIBM866 / OEM866
 * ���ଠ⨪� � �ணࠬ��஢���� �.2, ������ୠ� �4, ��ਠ�� 8
 *
 * �������:
 *
 */

#include <stdio.h>
#include <locale.h>
#include "_malloc.h"

int main(void)
{
	/*
	add_block_sort(&tb, { &p[3], 3 });
	add_block_sort(&tb, { &p[2], 2 });
	add_block_sort(&tb, { &p[1], 1 });
	add_block_sort(&tb, { &p[0], 0 });
	int k = bin_search(&tb, &p[1]);
	*/
	/*
	add_block_sort_bin(&tb, { &p[3], 1 });
	add_block_sort_bin(&tb, { &p[2], 1 });
	add_block_sort_bin(&tb, { &p[1], 1 });
	add_block_sort_bin(&tb, { &p[0], 1 });
	*/
	/*
	//int k = find_block_size(&tb, 6);
	//del_bock(&tb, 2);
	//resize_block(&tb, 2, 0);
	//int k = find_block_adr(&tb, &p[1]);
	//merge_blocks(&tb);
	*/

	initialize_memory();
	show_memory();

	int *a = (int *)_malloc(sizeof(int));
	*a = 0xAA0102AA;
	printf("�뤥����: int a = %ld (%x),\t�����: %p\n", *a, *a, a);
	show_memory();
	
	int *b = (int *)_malloc(2 * sizeof(int));
	b[0] = 0xBB0102BB; b[1] = 0xCC0102CC;
	for (int i = 0; i < 2; i++)
		printf("�뤥����: int b[%d] = %d (%x),\t�����: %p\n", i, b[i], b[i], &b[i]);
	show_memory();

	long long *c = (long long *)_malloc(sizeof(long long));
	*c = 0xDD010203040506DD;
	printf("�뤥����: long long c = %I64d (%I64x),\n\t\t\t\t\t\t����: %p\n", *c, *c, c);
	show_memory();

	float *d = (float *)_malloc(sizeof(float));
	*d = 123.123f;
	//printf("�뤥����: float d = %f (%x),\t�����: %p\n", *d, *d, d);
	printf("�뤥����: float d = %f\n", *d);
	show_memory();

	*a = 0;
	_free((byte *)a);
	puts("�᢮������: int a");
	show_memory();

	*c = 0;
	_free((byte *)c);
	puts("�᢮������: long long c");
	show_memory();

	int *e = (int *)_malloc(sizeof(int));
	*e = 0xEE0102EE;
	printf("�뤥����: int e = %d (%x),\t�����: %p\n", *e, *e, e);
	show_memory();

	short *f = (short *)_malloc(4*sizeof(short));
	for (int i = 0; i < 4; i++)
	{
		f[i] = 0xFF01 + i;
		printf("�뤥����: short f[%d] = %d (%x),\t\t����: %p\n", i, f[i], f[i], &f[i]);
	}
	show_memory();

	*e = 0;
	_free((byte *)e);
	puts("�᢮������: int e");
	show_memory();

	for (int i = 0; i < 4; i++) f[i] = 0;
	_free((byte *)f);
	puts("�᢮������: short f[4]");
	show_memory();

	for (int i = 0; i < 2; i++) b[i] = 0;
	_free((byte *)b);
	puts("�᢮������: b[2]");
	show_memory();

	*d = 0;
	_free((byte *)d);
	puts("�᢮������: float d");
	show_memory();

    return 0;
}

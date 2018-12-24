#include "_malloc.h"
#include <stdio.h>

struct Memory MEMORY;

// ���� � ���ᨢ� ������ ���室�饣� ����� ࠧ��୮���� �� ����� sz
int find_block_size(struct TableBlocks *tb, unsigned long sz)
{
	for (int i = 0; i < tb->count; i++)
		if (sz <= tb->blocks[i].size) return i;

	return -1;
}

// ������ ���� � 㯮�冷祭��� ���ᨢ� ������ (�� ���ᠬ) �᪮���� ����� � ���ᮬ 
int bin_search(struct TableBlocks *tb, byte *adr)
{
	int l = -1, r = tb->count; // ������ �࠭��� ���᪠

	if (r == 0) return 0;
	while (r - l > 1) // �믮��塞 �� �� ��� ���� ����� ���� �࠭�栬� ����� 1 ᨬ���� 
	{
		int m = (r + l) / 2; // ��室�� ������ �।���� �-� ����� ���� ⥪��. �࠭�栬�
		// �᫨ �-� �� ᫥��� �࠭�� ����� ��� ࠢ�� �᪮����, � ᤢ����� ��� ��ࠢ� �� �।���
		// '<=' - ��室�� �. �-� ��᫥ ��᫥����� �᪮���� ����. (�᫨ �� >1)
		// '<' - ������. ����, ��室�� ��ࢮ� �᪮��� ���祭�� (�᫨ �� >1)
		// �᫨ �᪮���� ����. �� ������, � � ����� ���᪠� ����砥� ������
		// �㤠 �㦭� ��⠢��� �᪮��� ���祭�� ��᫥ ������襣�
		if (tb->blocks[m].adress <= adr) l = m;
		// �᫨ �-� �� �ࠢ�� �࠭�� ����� �᪮����, � ᤢ����� ��� ����� �� �।���
		else r = m;
	}
	return r; // �᫨ �� '<=' �⨬ �� �� �����頫 ��᫥���� �᪮��� ���祭��, � r-1
}

int find_block_adr(struct TableBlocks *tb, byte *adr)
{
	int k = bin_search(tb, adr) - 1;

	if (tb->blocks[k].adress == adr) return k;

	return -1;
}

// ���������� � ���ᨢ ������, ������ ����� � ����� ���ᨢ�
int add_block(struct TableBlocks *tb, struct Block b)
{
	int n = tb->count;

	if (n == TABLE_SIZE) return 1;	// �᫨ ���⨣��� �।�� ⠡���� ������
	tb->blocks[n] = b;
	tb->count++;

	return 0;
}

// ���������� � ���ᨢ ������, ������ ����� 
// � ��࠭����� ���஢�� (� ���浪� �����⠭�� ���ᮢ)
int add_block_sort(struct TableBlocks *tb, struct Block b)
{
	int i = 0, n = tb->count;
	// �᫨ ���⨣��� �।�� ⠡���� ������
	if (n == TABLE_SIZE) return -1;

	if (n == 0)	tb->blocks[n] = b;
	else
	{
		// ���� � ���� ���ᨢ� � ������� ���᪮� �饬 ����� �᪮�� � -� �⠭�� ����� ⥪�饣�
		for (i = n; i > 0 && b.adress < tb->blocks[i - 1].adress; i--)
			tb->blocks[i] = tb->blocks[i - 1];
		tb->blocks[i] = b; // ��६�頥� �ᯮ�짮����� ���� ����� � ���� ᢮������ �����
	}
	tb->count++; // 㢥��稢��� ���稪 ������

	return i; // �����頥� ������ ��⠢������� �-�
}

// ���������� � ���ᨢ ������, ������ ����� 
// � ��࠭����� ���஢�� (� ���浪� �����⠭�� ���ᮢ) � ������� ����୮�� ���᪠
int add_block_sort_bin(struct TableBlocks *tb, struct Block b)
{
	int k = 0, n = tb->count;
	// �᫨ ���⨣��� �।�� ⠡���� ������
	if (n == TABLE_SIZE) return -1;

	if (n == 0)	tb->blocks[n] = b;
	else
	{
		k = bin_search(tb, b.adress); // ��।��塞 ���� ��⠢��
		for (int i = n; i > k; i--) // ��।������ �� �-�� ���। ��稭�� � k
			tb->blocks[i] = tb->blocks[i - 1];
		tb->blocks[k] = b; // ��६�頥� �ᯮ�짮����� ���� ����� � ���� ᢮������ �����
	}
	tb->count++; // 㢥��稢��� ���稪 ������

	return k;
}

// 㤠����� �� ���ᨢ� ������ ��।�������� ����� �� �������
int delete_block(struct TableBlocks *tb, int n)
{
	if (n < 0 || n >= tb->count) return 1;

	int sz = tb->count;
	for (int i = n; i < sz - 1; i++)
		tb->blocks[i] = tb->blocks[i + 1];

    //tb->blocks[sz - 1] = { NULL, NULL }; // ����塞 ����� �����
    tb->blocks[sz - 1].adress = NULL;
    tb->blocks[sz - 1].size = 0; // ����塞 ����� �����

	tb->count--; // 㬥��蠥� ���稪 ������

	return 0;
}

// 㢥��祭�� ��砫� ���� ����� ���।
int inc_adress_block(struct TableBlocks *tb, int n, byte a)
{
	if (n < 0 || n >= tb->count) return 1;

	tb->blocks[n].adress += a;

	return 0;
}

// ��������� ࠧ��஢ �����, �᫨ ࠧ��� = 0 - 㤠����� �����
// minus = true - 㬥��襭�� ���. ࠧ��� �� -sz + ᤢ�� 㪠��⥫� ���। �� sz
// minus = false - ������� ������ ࠧ��� ����� � sz
int resize_block(struct TableBlocks *tb, int n, unsigned long sz, int minus)
{
	if (n < 0 || n >= tb->count) return -1;

	unsigned long *size = &tb->blocks[n].size;
    if (minus == 1)
	{
		// �᫨ ����稭� 㬥��襭�� ࠧ��� ����� �ॢ�蠥� ࠧ��� �����
		if (*size <= sz) *size = 0;
		else *size -= sz;
		// �᫨ � �⮣� ࠧ��� ����� �⠫ ࠢ�� ��� -> 㤠�塞 ����
		if (*size == 0) delete_block(tb, n);
		// �᫨ ࠧ��� �� ��⠫��, � �ய�᪠�� ������� ������ ��竨
		// (ᤢ���� ��砫� �� sz ���� ���।)
		else inc_adress_block(tb, n, (byte)sz);
	}
	else
	{
		*size = sz;
		// �᫨ � �⮣� ࠧ��� ����� �⠫ ࠢ�� ��� -> 㤠�塞 ���� 
		if (*size == 0) delete_block(tb, n);
	}
	return 0;
}

// ��ꥤ������ ᢮������ ������ � ���� ���� �᫨ ��� �ᯮ������ �筮 ��� �� ��㣮� � ⠡���
void merge_blocks(struct TableBlocks *tb)
{
	// ��ॡ�� ������ � ���� � ��砫�
	for (int i = tb->count - 1; i > 0; i--)
	{
		// ��।��塞 ���� ᫥���饣� ����� ����� ���� �ࠧ� ��᫥ �।��饣�
		char *a = (byte*)(tb->blocks[i - 1].adress + tb->blocks[i - 1].size);

		if (a == tb->blocks[i].adress) 	// �᫨ ⥪�騩 ���� ���� ஢�� ᫥��� �� �।��騬
		{
			// 㢥��稢��� ࠧ��� �।��饣� ����� �� �� �� ����砫 � ⥪�騩 ����
			// ���� �।��饣� ����� �� ���塞, �� ��⠥��� ����
			tb->blocks[i - 1].size += tb->blocks[i].size;
			// 㤠�塞 ⥪�騩 ����
			delete_block(tb, i);
		}
	}
}

// �㭪�� �����頥� ���� �� ᢮����� ���� ����� � ������ �� ����� sz ����
void* _malloc(unsigned long sz)
{
	if (sz > MEMORY.size_free) // �᫨ �ॡ��� ����� 祬 ���� ᢮������
	{
		return NULL;
	}
	// ������ ���室�饣� ᢮������� ����� �����
	int k = find_block_size(&MEMORY.blocks_free, sz);
	if (k == -1) // �᫨ �� ������ ���� ����� � ���室�騬 ��ꥬ��
	{
		return NULL;
	}
	// ������塞 ���� ����� �� ᢮������ ⠡���� ����� � ⠡���� ������� ������ �����
	// ������ ���� ������������ ����� � ⠡��� ������� ������
	int n = add_block_sort_bin(&MEMORY.blocks_used, MEMORY.blocks_free.blocks[k]);
	if (n == -1) // �᫨ ���⨣��� �।�� ࠧ��୮�� ⠡���� ������� ������
	{
		return NULL;
	}
	// ���४��㥬 ࠧ���� ������������ ����� � ⠡���� ������� ������
	// ����� ࠧ��� ࠢ���� ⮬� ����� �㦥�
    resize_block(&MEMORY.blocks_used, n, sz, 0);
	// ���४��㥬 ࠧ���� ��室���� ����� � ⠡��� ᢮������ ������ 㬥���� ��� ����� �� sz
	// � ���塞 ���� ��室���� ����� ����� ��।���� �� ���� ���। �� sz
    resize_block(&MEMORY.blocks_free, k, sz, 1);

	MEMORY.size_free -= sz; // 㬥��蠥� ࠧ��� ᢮������ ����� �� � ���-�� �����, ���஥ �뤥����

	return MEMORY.blocks_used.blocks[n].adress;
}

// �㭪�� �᢮������� ���� � ��।������ ���ᮬ
int _free(byte* adr)
{
	// ������ ����⮣� ����� ����� � �㦭� ���ᮬ � ⠡��� ������� ������
	int k = find_block_adr(&MEMORY.blocks_used, adr);
	if (k == -1) // �᫨ �� ������ ���� ����� � �㦭� ���ᮬ
	{
		return 1;
	}
	// ������塞 ���� �� ⠡���� ������� ������ � ⠡���� ᢮������ ������ �����
	// ������ ���� ������������ ����� � ⠡��� ������� ������
	int n = add_block_sort_bin(&MEMORY.blocks_free, MEMORY.blocks_used.blocks[k]);
	if (n == -1) // �᫨ ���⨣��� �।�� ࠧ��୮�� ⠡���� ᢮������ ������
	{
		return 1;
	}
	// ��ꥤ��塞 ᢮����� ����� � ���� ����  
	merge_blocks(&MEMORY.blocks_free);

	MEMORY.size_free += MEMORY.blocks_used.blocks[k].size;
	// 㢥��稢�� ࠧ��� ᢮������ ����� �� � ���-�� �����, ���஥ �᢮������
	// 㤠�塞 �᢮�����訩�� ���� �� ⠡���� ������� ������
	delete_block(&MEMORY.blocks_used, k);

	return 0;
}

void initialize_memory(void)
{
    memset(&MEMORY, 0, sizeof(struct Memory)); // ���㫥��� �ᥩ �����
    MEMORY.size_free = MEMORY_SIZE; // ࠧ��� �ᥩ ����� �� 㬮�砭��

	// ����砫쭮 � ����� ���� �����⢥��� ᢮����� ���� �����
	// ࠧ��୮���� � ��� ������
    struct Block tmp = { MEMORY.buffer , MEMORY.size_free };
    add_block_sort_bin(&MEMORY.blocks_free, tmp);
}

void show_memory(void)
{
	puts("���� �����: ");
	for (int i = 0; i < MEMORY_SIZE; i++) printf("%02x ", (unsigned char)MEMORY.buffer[i]);
	printf("\n����㯭�: %ld �� %ld ����, ᢮���. ������: %d, �������: %d\n\n", MEMORY.size_free, MEMORY_SIZE, MEMORY.blocks_free.count, MEMORY.blocks_used.count);
}

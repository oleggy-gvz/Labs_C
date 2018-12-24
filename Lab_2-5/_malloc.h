#pragma once

#define MEMORY_SIZE 25 // ࠧ��� � ����� ���� �����
#define TABLE_SIZE 10  // ����. ���-�� ����ᥩ � ⠡��� �����

typedef char byte;

// ���� ���� �����
struct Block
{
    byte* adress;	// ���� ��砫� ����� �����
	unsigned long size;	// ࠧ��� ����� � �����
};

// ⠡��� ������ �����
struct TableBlocks
{
    struct Block blocks[TABLE_SIZE]; // ���ᨢ ������ �����
    int count; // ���-�� ������ �����
};

// ������
struct Memory
{
    byte buffer[MEMORY_SIZE]; // ���� �࠭���� �����
    unsigned long size_free; // ࠧ��� �ᥩ �����

    struct TableBlocks blocks_free; // ᢮����� ����� �����
    struct TableBlocks blocks_used; // �ᯮ��㥬� ����� �����
};

// �ᯮ����⥫��
int find_block_size(struct TableBlocks *, unsigned long);
int bin_search(struct TableBlocks *, byte *);
int find_block_adr(struct TableBlocks *, byte *);
int add_block_sort_bin(struct TableBlocks *, struct Block);
int add_block_sort(struct TableBlocks *, struct Block); // �� �ᯮ����
int add_block(struct TableBlocks *, struct Block); // �� �ᯮ����
int delete_block(struct TableBlocks *, int);
int inc_adress_block(struct TableBlocks *, int, byte);
int resize_block(struct TableBlocks *, int n, unsigned long , int);
void merge_blocks(struct TableBlocks *);
void initialize_memory(void);
// �᭮���
void* _malloc(unsigned long);
int _free(byte* );
// �뢮�
void show_memory(void);

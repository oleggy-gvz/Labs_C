#pragma once

#define MEMORY_SIZE 25 // размер в байтах ВСЕЙ памяти
#define TABLE_SIZE 10  // макс. кол-во записей в таблице памяти

typedef char byte;

// один блок памяти
struct Block
{
    byte* adress;	// адрес начала записи памяти
	unsigned long size;	// размер записи в байтах
};

// таблица блоков памяти
struct TableBlocks
{
    struct Block blocks[TABLE_SIZE]; // массив блоков памяти
    int count; // кол-во блоков памяти
};

// память
struct Memory
{
    byte buffer[MEMORY_SIZE]; // место хранения памяти
    unsigned long size_free; // размер всей памяти

    struct TableBlocks blocks_free; // свободные блоки памяти
    struct TableBlocks blocks_used; // используемые блоки памяти
};

// вспомогательные
int find_block_size(struct TableBlocks *, unsigned long);
int bin_search(struct TableBlocks *, byte *);
int find_block_adr(struct TableBlocks *, byte *);
int add_block_sort_bin(struct TableBlocks *, struct Block);
int add_block_sort(struct TableBlocks *, struct Block); // не использую
int add_block(struct TableBlocks *, struct Block); // не использую
int delete_block(struct TableBlocks *, int);
int inc_adress_block(struct TableBlocks *, int, byte);
int resize_block(struct TableBlocks *, int n, unsigned long , int);
void merge_blocks(struct TableBlocks *);
void initialize_memory(void);
// основные
void* _malloc(unsigned long);
int _free(byte* );
// вывод
void show_memory(void);

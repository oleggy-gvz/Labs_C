#include "_malloc.h"
#include <stdio.h>

struct Memory MEMORY;

// поиск в массиве блоков подходящего блока размерностью не меньше sz
int find_block_size(struct TableBlocks *tb, unsigned long sz)
{
	for (int i = 0; i < tb->count; i++)
		if (sz <= tb->blocks[i].size) return i;

	return -1;
}

// бинарный поиск в упорядоченном массиве блоков (по адресам) искомого блока с адресом 
int bin_search(struct TableBlocks *tb, byte *adr)
{
	int l = -1, r = tb->count; // задаем границы поиска

	if (r == 0) return 0;
	while (r - l > 1) // выполняем до тех пор пока между двумя границами больше 1 символа 
	{
		int m = (r + l) / 2; // находим индекс среднего эл-та между двумя текущ. границами
		// если эл-т на слевой границе больш или равен искомому, то сдвигаем его вправо на середину
		// '<=' - находит сл. эл-т после последнего искомого знач. (если их >1)
		// '<' - левост. поиск, находит первое искомое значение (если их >1)
		// если искомого знач. не найден, то в обоих поисках получаем индекс
		// куда нужно вставить искомое значение после ближайшего
		if (tb->blocks[m].adress <= adr) l = m;
		// если эл-т на правой границе больше искомого, то сдвигаем его влево на середину
		else r = m;
	}
	return r; // если при '<=' хотим что бы возвращал последнее искомое значение, то r-1
}

int find_block_adr(struct TableBlocks *tb, byte *adr)
{
	int k = bin_search(tb, adr) - 1;

	if (tb->blocks[k].adress == adr) return k;

	return -1;
}

// добавление в массив блоков, нового блока в конец массива
int add_block(struct TableBlocks *tb, struct Block b)
{
	int n = tb->count;

	if (n == TABLE_SIZE) return 1;	// если достигнут предел таблицы блоков
	tb->blocks[n] = b;
	tb->count++;

	return 0;
}

// добавление в массив блоков, нового блока 
// с сохранением сортировки (в порядке возрастания адресов)
int add_block_sort(struct TableBlocks *tb, struct Block b)
{
	int i = 0, n = tb->count;
	// если достигнут предел таблицы блоков
	if (n == TABLE_SIZE) return -1;

	if (n == 0)	tb->blocks[n] = b;
	else
	{
		// идем с конца массива и линейным поиском ищем когда искомый эл -т станет меньше текущего
		for (i = n; i > 0 && b.adress < tb->blocks[i - 1].adress; i--)
			tb->blocks[i] = tb->blocks[i - 1];
		tb->blocks[i] = b; // перемещаем использованный блок памяти в блок свободной памяти
	}
	tb->count++; // увеличиваем счетчик блоков

	return i; // возвращаем индекс вставленного эл-та
}

// добавление в массив блоков, нового блока 
// с сохранением сортировки (в порядке возрастания адресов) с помощью бинарного поиска
int add_block_sort_bin(struct TableBlocks *tb, struct Block b)
{
	int k = 0, n = tb->count;
	// если достигнут предел таблицы блоков
	if (n == TABLE_SIZE) return -1;

	if (n == 0)	tb->blocks[n] = b;
	else
	{
		k = bin_search(tb, b.adress); // определяем место вставки
		for (int i = n; i > k; i--) // передвигаем все эл-ты вперед начиная с k
			tb->blocks[i] = tb->blocks[i - 1];
		tb->blocks[k] = b; // перемещаем использованный блок памяти в блок свободной памяти
	}
	tb->count++; // увеличиваем счетчик блоков

	return k;
}

// удаление из массива блоков определенного блока по индексу
int delete_block(struct TableBlocks *tb, int n)
{
	if (n < 0 || n >= tb->count) return 1;

	int sz = tb->count;
	for (int i = n; i < sz - 1; i++)
		tb->blocks[i] = tb->blocks[i + 1];

    //tb->blocks[sz - 1] = { NULL, NULL }; // обнуляем данные блока
    tb->blocks[sz - 1].adress = NULL;
    tb->blocks[sz - 1].size = 0; // обнуляем данные блока

	tb->count--; // уменьшаем счетчик блоков

	return 0;
}

// увеличение начала адреса блока вперед
int inc_adress_block(struct TableBlocks *tb, int n, byte a)
{
	if (n < 0 || n >= tb->count) return 1;

	tb->blocks[n].adress += a;

	return 0;
}

// изменение размеров блока, если размер = 0 - удаление блока
// minus = true - уменьшение сущ. размера на -sz + сдвиг указателя вперед на sz
// minus = false - задание нового размера блока в sz
int resize_block(struct TableBlocks *tb, int n, unsigned long sz, int minus)
{
	if (n < 0 || n >= tb->count) return -1;

	unsigned long *size = &tb->blocks[n].size;
    if (minus == 1)
	{
		// если величина уменьшения размера памяти превышает размер памяти
		if (*size <= sz) *size = 0;
		else *size -= sz;
		// если в итоге размер блока стал равным нулю -> удаляем блок
		if (*size == 0) delete_block(tb, n);
		// если размер еще остался, то пропускаем область которую вычли
		// (сдвигая начало на sz байт вперед)
		else inc_adress_block(tb, n, (byte)sz);
	}
	else
	{
		*size = sz;
		// если в итоге размер блока стал равным нулю -> удаляем блок 
		if (*size == 0) delete_block(tb, n);
	}
	return 0;
}

// объединение свободных блоков в один блок если они расположены точно друг за другом в таблице
void merge_blocks(struct TableBlocks *tb)
{
	// перебор блоков с конца в начало
	for (int i = tb->count - 1; i > 0; i--)
	{
		// определяем адрес следующего блока который идет сразу после предыдущего
		char *a = (byte*)(tb->blocks[i - 1].adress + tb->blocks[i - 1].size);

		if (a == tb->blocks[i].adress) 	// если текущий блок идет ровно следом за предыдущим
		{
			// увеличиваем размер предыдущего блока что бы он включал и текущий блок
			// адрес предыдущего блока не меняем, он остается старым
			tb->blocks[i - 1].size += tb->blocks[i].size;
			// удаляем текущий блок
			delete_block(tb, i);
		}
	}
}

// функция возвращает адрес на свободный блок памяти с длиной не меньше sz байт
void* _malloc(unsigned long sz)
{
	if (sz > MEMORY.size_free) // если требуют больше чем есть свободной
	{
		return NULL;
	}
	// индекс подходящего свободного блока памяти
	int k = find_block_size(&MEMORY.blocks_free, sz);
	if (k == -1) // если не найден блок памяти с подходящим объемом
	{
		return NULL;
	}
	// добавляем блок памяти из свободной таблицы памяти в таблицу занятых блоков памяти
	// индекс места добавленного блока в таблице занятых блоков
	int n = add_block_sort_bin(&MEMORY.blocks_used, MEMORY.blocks_free.blocks[k]);
	if (n == -1) // если достигнут предел размерности таблицы занятых блоков
	{
		return NULL;
	}
	// корректируем размеры добавленного блока в таблицу занятых блоков
	// задав размер равному тому который нужен
    resize_block(&MEMORY.blocks_used, n, sz, 0);
	// корректируем размеры исходного блока в таблице свободных блоков уменьшая его длину на sz
	// и меняем адрес исходного блока памяти передвинув ее адрес вперед на sz
    resize_block(&MEMORY.blocks_free, k, sz, 1);

	MEMORY.size_free -= sz; // уменьшаем размер свободной памяти на то кол-во памяти, которое выделили

	return MEMORY.blocks_used.blocks[n].adress;
}

// функция освобождает блок с определенным адресом
int _free(byte* adr)
{
	// индекс занятого блока памяти с нужным адресом в таблице занятых блоков
	int k = find_block_adr(&MEMORY.blocks_used, adr);
	if (k == -1) // если не найден блок памяти с нужным адресом
	{
		return 1;
	}
	// добавляем блок из таблицы занятых блоков в таблицу свободных блоков памяти
	// индекс места добавленного блока в таблице занятых блоков
	int n = add_block_sort_bin(&MEMORY.blocks_free, MEMORY.blocks_used.blocks[k]);
	if (n == -1) // если достигнут предел размерности таблицы свободных блоков
	{
		return 1;
	}
	// объединяем свободные блоки в один блок  
	merge_blocks(&MEMORY.blocks_free);

	MEMORY.size_free += MEMORY.blocks_used.blocks[k].size;
	// увеличивам размер свободной памяти на то кол-во памяти, которое освободили
	// удаляем освободившийся блок из таблицы занятых блоков
	delete_block(&MEMORY.blocks_used, k);

	return 0;
}

void initialize_memory(void)
{
    memset(&MEMORY, 0, sizeof(struct Memory)); // обнуление всей памяти
    MEMORY.size_free = MEMORY_SIZE; // размер всей памяти по умолчанию

	// изначально в памяти есть единственный свободный блок памяти
	// размерностью со всю память
    struct Block tmp = { MEMORY.buffer , MEMORY.size_free };
    add_block_sort_bin(&MEMORY.blocks_free, tmp);
}

void show_memory(void)
{
	puts("карта памяти: ");
	for (int i = 0; i < MEMORY_SIZE; i++) printf("%02x ", (unsigned char)MEMORY.buffer[i]);
	printf("\nдоступно: %ld из %ld байт, свобод. блоков: %d, занятых: %d\n\n", MEMORY.size_free, MEMORY_SIZE, MEMORY.blocks_free.count, MEMORY.blocks_used.count);
}

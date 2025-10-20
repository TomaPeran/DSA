#ifndef HASH_H
#define HASH_H

// structure inside the "drawer" or "bin"
typedef struct Bin {
	char *word;
	struct Bin *next;
} Bin;

typedef struct {
	Bin **table; // Array of pointers
	int size, load; // Physical and logical size
} HashTable;

HashTable *NewTable(int size);

unsigned int hash(char *word);

void Insert(HashTable *ht, char *word);

int Get(HashTable *ht, char *word);

void DeleteTable(HashTable *ht);

#endif // !HASH_H

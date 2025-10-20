#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

HashTable *NewTable(int size)
{
	// Create new hash table
	
	// Basically, pointer on an array of pointers 
	HashTable* dict = (HashTable*)malloc(sizeof(HashTable)); // dummy head
	dict->size = size;
	dict->load = 0;
	dict->table = (Bin**)malloc(size * sizeof(Bin*));

	// Allocate memory for every bin inside array
	for (int i = 0; i < size; i++) {
		dict->table[i] = (Bin*)malloc(sizeof(Bin));
		dict->table[i]->word = NULL;
		dict->table[i]->next = NULL;
	}

	return dict;
}

unsigned int hash(char *word)
{
	// Generates hash key from the word
	unsigned int key = 0;
	while(*word != '\0')
	{
		key = key*HCONST + *word;
		word++;
	}
	return key;
}
s
void Insert(HashTable *ht, char *word)
{
	// Adds a new word to the list on the appropriate inbox.

	/* This part is required for a linear collision solution
	if (ht->load == ht->size) {
		printf("Tablica puna\n");
		return;
	}
	*/

	unsigned int key = hash(word);
	unsigned int b = key % ht->size;
	ht->load++;
	

	// Adds to the head of the appropriate bin
	Bin* new_element = (Bin*)malloc(sizeof(Bin));
	new_element->word = strdup(word);
	new_element->next = NULL;
	ht->table[b]->next = new_element;

}

int Get(HashTable *ht, char *word)
{

	// Returns 0 or 1 depending on whether the word exists in the table

	unsigned int key = hash(word); // Get the key for a particular word, id in the table
	unsigned int b = key % ht->size;
	
	Bin* tmp = ht->table[b];

	
	while (tmp ->next != NULL) { // Looking for a structure inside the room
		if (!strcmp(tmp->next->word, word)) {
			return 1;
		}
		tmp = tmp->next;
	}
	

	return 0;
}

void DeleteTable(HashTable *ht)
{
	// Deletes the entire hash table (lists on all mailboxes (word and list element), mailboxes...)

	for (int i = 0; i < ht->size; i++) {
		Bin *tmp = ht->table[i];
		while (tmp != NULL) {
			Bin* obrisi = tmp;
			tmp = tmp->next;
			free(obrisi->word);
			free(obrisi);
		}
		free(tmp);
	}
	free(ht->table);
	free(ht);
}

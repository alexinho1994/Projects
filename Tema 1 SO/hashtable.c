#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashtable.h"
#include "hash.h"

void initHash(node ***hashtable, int size)
{
	*hashtable = (node **) malloc(size * sizeof(node *));
}

int findInHash(node **hashtable, char *word, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		if (findInBucket(&hashtable[i], word))
			return 1;
	}
	return 0;
}

void addInHash(node **hashtable, char *word, int size)
{
	addInBucket(&hashtable[hash(word, size)], word);
}

void clearHash(node **hashtable, int size)
{
	int i;

	for (i = 0; i < size; i++)
		clearBucket(&hashtable[i]);
}

void resizeDouble(node **hashtable, node **hashtable2, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		char *word = returnWord(hashtable[i]);

		while (word) {
			addInBucket(&hashtable2[hash(word, size*2)], word);
			removeWord(&hashtable[i], word);
			word = returnWord(hashtable[i]);
		}
	}
}

void resizeHalve(node **hashtable, node **hashtable2, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		char *word = returnWord(hashtable[i]);

		while (word) {
			addInBucket(&hashtable2[hash(word, size/2)], word);
			removeWord(&hashtable[i], word);
			word = returnWord(hashtable[i]);
		}
	}
}

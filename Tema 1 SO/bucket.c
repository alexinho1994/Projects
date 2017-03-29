#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bucket.h"

void initBucket(node **bucket)
{
	*bucket = NULL;
}

int findInBucket(node **bucket, char *word)
{
	node *curent = *bucket;

	while (curent != NULL) {
		if (strcmp(curent->word, word) == 0)
			return 1;
		curent = curent->next;
	}
	return 0;
}

void addInBucket(node **bucket, char *word)
{
	node *new, *curent;

	curent = *bucket;
	new = (node *) malloc(sizeof(node));
	new->word = (char *) malloc(strlen(word)+1 * sizeof(char));
	strcpy(new->word, word);
	new->next = NULL;
	if (*bucket == NULL)
		*bucket = new;
	else {
		while (curent->next != NULL)
			curent = curent->next;
		curent->next = new;
	}
}

void removeWord(node **bucket, char *word)
{
	node *curent = *bucket;

	if (strcmp(curent->word, word) == 0) {
		curent = curent->next;
		free(*bucket);
		*bucket = curent;
	} else {
		node *rmv;
		
		while (strcmp(curent->next->word, word))
			curent = curent->next;
		rmv = curent->next;
		curent->next = curent->next->next;
		free(rmv);
	}
}

void clearBucket(node **bucket)
{
	while (*bucket != NULL) {
		node *curent = *bucket;

		curent = curent->next;
		free(*bucket);
		*bucket = curent;
	}
}

void printBucket(node **bucket, FILE *file)
{
	node *curent = *bucket;

	if (curent) {
		while (curent) {
			fprintf(file, "%s ", curent->word);
			curent = curent->next;
		}
		fprintf(file, "\n");
	}
}

char *returnWord(node *bucket)
{
	if (bucket)
		return bucket->word;
	return NULL;
}

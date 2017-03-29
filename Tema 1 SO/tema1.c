#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash.h"
#include "bucket.h"
#include "hashtable.h"

int hashSize;

node **hashtable;

int addCommand(char *buffer)
{
	int i;

	char *com = strtok(buffer, "\n ");

	if (com == NULL)
		return 0;
	if (strcmp(com, "add") == 0) {
		char *word = strtok(NULL, "\n ");

		if (word == NULL) {
			fprintf(stderr, "Bad parameter");
			return -1;
		}
		if (!findInHash(hashtable, word, hashSize))
			addInHash(hashtable, word, hashSize);
		return 0;
	}
	if (strcmp(com, "find") == 0) {
		char *word = strtok(NULL, "\n ");

		char *file;

		if (word == NULL) {
			fprintf(stderr, "Bad parameter");
			return -1;
		}

		if (word)
			file = strtok(NULL, "\n ");
		if (file) {
			FILE *fis = fopen(file, "a");

			if (findInHash(hashtable, word, hashSize))
				fprintf(fis, "True\n");
			else
				fprintf(fis, "False\n");
			fclose(fis);
		} else {
			if (findInHash(hashtable, word, hashSize))
				printf("True\n");
			else
				printf("False\n");
		}
		return 0;
	}
	if (strcmp(com, "remove") == 0) {
		char *word = strtok(NULL, "\n ");

		if (word == NULL) {
			fprintf(stderr, "Bad parameter");
			return -1;
		}
		if (findInHash(hashtable, word, hashSize))
			removeWord(&hashtable[hash(word, hashSize)], word);
		return 0;
	}
	if (strcmp(com, "clear") == 0) {
		clearHash(hashtable, hashSize);
		return 0;
	}
	if (strcmp(com, "print") == 0) {
		char *file = strtok(NULL, "\n ");

		if (file) {
			FILE *fis = fopen(file, "a");

			for (i = 0; i < hashSize; i++)
				printBucket(&hashtable[i], fis);
			fclose(fis);
		} else {
			for (i = 0; i < hashSize; i++)
				printBucket(&hashtable[i], stdout);
		}
		return 0;
	}
	if (strcmp(com, "print_bucket") == 0) {
		char *word = strtok(NULL, "\n ");

		int index = atoi(word);

		char *file = strtok(NULL, "\n ");

		for (i = 0; i < strlen(word); i++) {
			if (word[i] < 48 || word[i] > 57) {
				fprintf(stderr, "Bad parameter");
				return -1;
			}
		}

		if (file) {
			FILE *fis = fopen(file, "a");

			if (index < hashSize)
				printBucket(&hashtable[index], fis);
			fclose(fis);
		} else
			if (index < hashSize)
				printBucket(&hashtable[index], stdout);
		return 0;
	}
	if (strcmp(com, "resize") == 0) {
		char *word = strtok(NULL, "\n ");

		if (strcmp(word, "double") == 0) {
			node **hashtable2;

			initHash(&hashtable2, hashSize*2);
			for (i = 0; i < hashSize*2; i++)
				initBucket(&hashtable2[i]);
			resizeDouble(hashtable, hashtable2, hashSize);
			free(hashtable);
			hashtable = hashtable2;
			hashSize *= 2;
			return 0;
		}
		if (strcmp(word, "halve") == 0) {
			node **hashtable2;

			initHash(&hashtable2, hashSize/2);
			for (i = 0; i < hashSize/2; i++)
				initBucket(&hashtable2[i]);
			resizeHalve(hashtable, hashtable2, hashSize);
			free(hashtable);
			hashtable = hashtable2;
			hashSize /= 2;
			return 0;
		}
	}

	return -1;

}


int main(int argc, char *argv[])
{
	int i;

	int files = 2;

	if (argc < 2) {
		fprintf(stderr, "Not enough parameters");
		return -1;
	}

	for (i = 0; i < strlen(argv[1]); i++)
		if (argv[1][i] < '0' || argv[1][i] > '9') {
			fprintf(stderr, "Bad parameter");
			return -1;
		}
	hashSize = atoi(argv[1]);

	initHash(&hashtable, hashSize);

	for (i = 0; i < hashSize; i++)
		initBucket(&hashtable[i]);

	if (files < argc) {
		char buffer[20000];

		while (files < argc) {
			FILE *input = fopen(argv[files], "r");

			files++;
			if (input) {
				while (fgets(buffer, 20000, input))
					if (addCommand(buffer))
						return -1;
				fclose(input);
			}
		}
	} else {
	char buffer[20000];

		while (fgets(buffer, 20000, stdin))
			if (addCommand(buffer))
				return -1;
	}
	return 0;
}

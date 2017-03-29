#ifndef BUCKET_H_
#define BUCKET_H_

typedef struct node {
	char *word;
	struct node *next;
} node;

void initBucket(node **bucket);
int findInBucket(node **bucket, char *word);
void addInBucket(node **bucket, char *word);
void removeWord(node **bucket, char *word);
void clearBucket(node **bucket);
void printBucket(node **bucket, FILE *file);
char *returnWord(node *bucket);


#endif

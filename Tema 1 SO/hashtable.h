#include "bucket.h"
#include "hash.h"

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

void initHash(node ***hashtable, int size);
int findInHash(node **hashtable, char *word, int size);
void addInHash(node **hashtable, char *word, int size);
void clearHash(node **hashtable, int size);
void resizeDouble(node **hashtable, node **hashtable2, int size);
void resizeHalve(node **hashtable, node **hashtable2, int size);

#endif

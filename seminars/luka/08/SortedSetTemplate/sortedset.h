#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
 void *base;
 int (*cmp_fn)(const void *, const void *);
 void (*free_fn)(const void *);
 int elem_size;
 int logical_length;
 int allocated_length;


} sortedset;

void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *), void (*freefn)(const void *));
bool SetAdd(sortedset *set, const void *elemPtr);
void *SetSearch(sortedset *set, const void *elemPtr);
static int *FindNode(sortedset *set, const void *elem);
#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_VECTOR_SIZE 8

#define NELEM(v, index) ((char *) (v)->base + (index) * (v)->elem_size)

void VectorInit(Vector* v, int elem_size, FreeFn free_fn) {
  v->elem_size = elem_size;
  v->free_fn = free_fn;

  v->logical_size = 0;
  v->allocated_size = INITIAL_VECTOR_SIZE;
  v->base = malloc(v->allocated_size * v->elem_size);
  assert(v->base);
}

void VectorDestroy(Vector* v) {
  if (v->free_fn) {
    for (int i = 0; i < v->logical_size; i++) {
      void *elem = NELEM(v, i);
      v->free_fn(elem);
    }
  }
  
  free(v->base);
}

static void VectorGrow(Vector *v) {
  if (v->logical_size == v->allocated_size) {
    v->allocated_size *= 2;
    v->base = realloc(v->base, v->allocated_size * v->elem_size);
    assert(v->base);
  }
}

void VectorAppend(Vector* v, void* elem) {
  VectorGrow(v);

  memcpy(NELEM(v, v->logical_size), elem, v->elem_size);
  v->logical_size++;
}

void VectorInsert(Vector* v, int index, void* elem) {
  VectorGrow(v);

  char *target = NELEM(v, index);
  
  int size = (v->logical_size - index) * v->elem_size;

  memmove(target + v->elem_size, target, size);
  memcpy(target, elem, v->elem_size);
  
  v->logical_size++;
}

// 0xFF 0xAB 0x12 0x11
// 0xFF 0xFF 0xFF 0xFF

void VectorOverwrite(Vector* v, int index, void* elem) {
  assert(v->logical_size > index && index >= 0);

  void *target = NELEM(v, index);

  if (v->free_fn) {
    v->free_fn(target);
  }
  memcpy(target, elem, v->elem_size);
}

void* VectorGet(Vector* v, int index) {
  assert(v->logical_size > index && index >= 0);

  return NELEM(v, index);
}

void VectorRemove(Vector* v, int index, void* elem) {
  assert(v->logical_size > index && index >= 0);

  char *target = NELEM(v, index);
  int size = (v->logical_size - index - 1) * v->elem_size;
  
  if (elem) {
   memcpy(elem, target, v->elem_size);
  } else if (v->free_fn) {
    v->free_fn(target);
  }
  
  memmove(target, target + v->elem_size, size);
  v->logical_size--;
}

int VectorSize(Vector* v) {
  return v->logical_size;
}

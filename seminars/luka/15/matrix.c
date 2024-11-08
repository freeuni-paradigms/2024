#include "matrix.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ELEM_SIZE(m) ((m)->elem_size + sizeof(char))
#define ELEM_ADDR(m, row, col) ((char *)(m)->base[row] + col * ELEM_SIZE(m))

#define BOOL_ADDR(m, row, col)  (ELEM_ADDR(m, row, col) + m->elem_size)
#define IS_SET(m, row, col) (*BOOL_ADDR(m, row, col))

typedef struct {
  int size;
  freeFn;
} VectorNode;

void MatrixInit(Matrix* m, int n, size_t elem_size, Free free_fn) {
  m->n = n;
  m->elem_size = elem_size;
  m->free_fn = free_fn;

  m->base = malloc(n * sizeof(void *));
  assert(m->base);

  for (int i = 0; i < n; i++) {
    m->base[i] = malloc(n * ELEM_SIZE(m));
    assert(m->base[i]);

    for (int j = 0; j < n; j++) {
      *BOOL_ADDR(m, i, j) = 0;
    }
  }
}

void MatrixDestroy(Matrix* m) {
  for (int i = 0; i < m->n; i++) {
    for (int j = 0; j < m->n; j++) {
      if (IS_SET(m, i, j) && m->free_fn != NULL) {
        m->free_fn(ELEM_ADDR(m, i, j));
      }
    }
    free(m->base[i]);
  }

  free(m->base);
}

void MatrixSet(Matrix* m, int row, int col, void* elem) {
  *BOOL_ADDR(m, row, col) = 1;
  memcpy(ELEM_ADDR(m, row, col), elem, m->elem_size);
}

void* MatrixGet(Matrix* m, int row, int col) {
  return ELEM_ADDR(m, row, col);
}

void MatrixRotate(Matrix* m) {
  void **baseCopy = malloc(m->n * sizeof(void *));
  for (int i = 0; i < m->n; i++) {
    baseCopy[i] = malloc(m->n * ELEM_SIZE(m));
    assert(baseCopy[i]);
  }

  for (int i = m->n - 1; i >= 0; i--) {
    for (int j = 0; j < m->n; j++) {
      void *target = (char *)baseCopy[(m->n - j)] + (m->n - i) * ELEM_SIZE(m);
      memcpy(target, ELEM_ADDR(m, i, j), ELEM_SIZE(m));
    }
  }
}

void MatrixAccumulate(Matrix* m, int row, int col, Accumulate accumulate_fn,
		      void* aux_data) {
  for (int i = 0; i < m->n; i++) {
    for (int j = 0; j < m->n; j++) {
      if (i + j == row + col || (i + (m->n - 1 - j)) == row + col) {
        accumulate_fn(ELEM_ADDR(m, i, j), aux_data);
      } 
    }
  }
}

void IntMatrixInit(IntMatrix* m, int n) {
}

void IntMatrixDestroy(IntMatrix* m) {
}

void IntMatrixSet(IntMatrix* m, int row, int col, int elem) {
}
int IntMatrixGet(IntMatrix* m, int row, int col) {
}

void Add(void* elem, void* aux_data) {
}

int IntMatrixSum(Matrix* m, int row, int col) {
}

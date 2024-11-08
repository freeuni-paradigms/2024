#ifndef PARADIGMS_PROBLEMS_MATRIX_MATRIX_H_
#define PARADIGMS_PROBLEMS_MATRIX_MATRIX_H_

#include <stddef.h>

typedef void(*Free)(void* elem);

typedef void(*Accumulate)(void* elem, void* aux_data);

typedef struct {
  void **base;
  int n;
  size_t elem_size;
  Free free_fn;
} Matrix;

// Initializes matrix with n rows and n columns.
void MatrixInit(Matrix* m, int n, size_t elem_size, Free free_fn);
// Frees up space used by matrix.
void MatrixDestroy(Matrix* m);
// Sets element in row-th row and col-th column.
void MatrixSet(Matrix* m, int row, int col, void* elem);
// Gets element on row-th row and col-th column.
void* MatrixGet(Matrix* m, int row, int col);
// Rotates matrix clock-wise by 90 degrees.
void MatrixRotate(Matrix* m);
// Calls accumualte_fn function for every element of matrix on diagonals which
// include (row, col) cell.
void MatrixAccumulate(Matrix* m, int row, int col, Accumulate accumulate_fn,
		      void* aux_data);

typedef Matrix IntMatrix;

// IMPORTANT WARNING: None of these functions bellow should access internals of
// Matrix struct defined above. Use only it's public API functions.

// Initializes integer matrix, all elements must be set to 0.
void IntMatrixInit(IntMatrix* m, int n);
void IntMatrixDestroy(IntMatrix* m);
void IntMatrixSet(IntMatrix* m, int row, int col, int elem);
int IntMatrixGet(IntMatrix* m, int row, int col);
// Returns sum of elements of matrix on diagonals which include (row, col) cell.
int IntMatrixSum(Matrix* m, int row, int col);

#endif // PARADIGMS_PROBLEMS_MATRIX_MATRIX_H_

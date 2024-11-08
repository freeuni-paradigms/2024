#include "matrix.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#define RUN(x) RunTest(#x, x);

#define ASSERT(expr) {							\
  if (!(expr)) {								\
    printf("%s:%d: Assertion failed: %s\n", __FILE__, __LINE__, #expr);	\
    return false;							\
  }									\
  }

void RunTest(char* name, bool(*t)()) {
  printf("++ Running: %s\n", name);
  bool res = t();
  printf("-- Test %s: %s\n", name, res ? "SUCCEEDED" : "FAILED");
  printf("\n\n");
}

bool MatrixEmpty() {
  Matrix m;
  MatrixInit(&m, 5, sizeof(int), /*free_fn=*/NULL);
  MatrixDestroy(&m);
  return true;
}

void StrFree(void* elem) {
  free(*(char**)elem);
}

bool StringsSetGet() {
  Matrix m;
  MatrixInit(&m, 2, sizeof(char*), StrFree);
  char* ab = strdup("ab");
  char* cd = strdup("cd");
  char* ef = strdup("ef");
  char* gh = strdup("gh");  
  MatrixSet(&m, 0, 0, &ab);
  MatrixSet(&m, 0, 1, &cd);
  MatrixSet(&m, 1, 0, &ef);
  MatrixSet(&m, 1, 1, &gh);
  ASSERT(0 == strcmp("ab", *(char**)MatrixGet(&m, 0, 0)));
  ASSERT(0 == strcmp("cd", *(char**)MatrixGet(&m, 0, 1)));
  ASSERT(0 == strcmp("ef", *(char**)MatrixGet(&m, 1, 0)));
  ASSERT(0 == strcmp("gh", *(char**)MatrixGet(&m, 1, 1)));  
  MatrixDestroy(&m);
  return true;
}

bool StringsRotate() {
  Matrix m;
  MatrixInit(&m, 2, sizeof(char*), StrFree);
  char* ab = strdup("ab");
  char* cd = strdup("cd");
  char* ef = strdup("ef");
  char* gh = strdup("gh");  
  MatrixSet(&m, 0, 0, &ab);
  MatrixSet(&m, 0, 1, &cd);
  MatrixSet(&m, 1, 0, &ef);
  MatrixSet(&m, 1, 1, &gh);
  MatrixRotate(&m);
  ASSERT(0 == strcmp("ef", *(char**)MatrixGet(&m, 0, 0)));
  ASSERT(0 == strcmp("ab", *(char**)MatrixGet(&m, 0, 1)));
  ASSERT(0 == strcmp("gh", *(char**)MatrixGet(&m, 1, 0)));
  ASSERT(0 == strcmp("cd", *(char**)MatrixGet(&m, 1, 1)));  
  MatrixDestroy(&m);
  return true;
}

// INTEGERS

bool IntMatrixEmpty() {
  Matrix m;
  IntMatrixInit(&m, 5);
  MatrixDestroy(&m);
  return true;
}

bool IntMatrixSetGet() {
  IntMatrix m;
  IntMatrixInit(&m, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ASSERT(0 == IntMatrixGet(&m, i, j));      
      IntMatrixSet(&m, i, j, 3 * i + j);
      ASSERT(3 * i + j == IntMatrixGet(&m, i, j));
    }
  }
  IntMatrixDestroy(&m);
  return true;
}

bool IntMatrix2Rotate() {
  IntMatrix m;
  IntMatrixInit(&m, 2);
  IntMatrixSet(&m, 0, 0, 0);
  IntMatrixSet(&m, 0, 1, 1);
  IntMatrixSet(&m, 1, 0, 2);
  IntMatrixSet(&m, 1, 1, 3);
  MatrixRotate(&m);
  ASSERT(2 == IntMatrixGet(&m, 0, 0));
  ASSERT(0 == IntMatrixGet(&m, 0, 1));
  ASSERT(1 == IntMatrixGet(&m, 1, 1));
  ASSERT(3 == IntMatrixGet(&m, 1, 0));  
  IntMatrixDestroy(&m);
  return true;
}

bool IntMatrixFullRotation() {
  IntMatrix m;
  IntMatrixInit(&m, 10);
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      IntMatrixSet(&m, i, j, 10 * i + j);
      ASSERT(10 * i + j == IntMatrixGet(&m, i, j));      
    }
  }
  for (int i = 0; i < 4; ++i) {
    MatrixRotate(&m);
  }
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      ASSERT(10 * i + j == IntMatrixGet(&m, i, j));      
    }
  }
  MatrixDestroy(&m);
  return true;
}

bool IntMatrixSumNoRotation() {
  IntMatrix m;
  IntMatrixInit(&m, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      IntMatrixSet(&m, i, j, 3 * i + j);
    }
  }
  ASSERT(0 + 4 + 8 == IntMatrixSum(&m, 0, 0));
  ASSERT(1 + 3 + 5 == IntMatrixSum(&m, 0, 1));
  ASSERT(2 + 4 + 6 == IntMatrixSum(&m, 0, 2));
  ASSERT(3 + 1 + 7 == IntMatrixSum(&m, 1, 0));
  ASSERT(4 + 0 + 8 + 2 + 6 == IntMatrixSum(&m, 1, 1));
  ASSERT(5 + 1 + 7 == IntMatrixSum(&m, 1, 2));
  ASSERT(6 + 4 + 2 == IntMatrixSum(&m, 2, 0));
  ASSERT(7 + 3 + 5 == IntMatrixSum(&m, 2, 1));
  ASSERT(8 + 4 + 0 == IntMatrixSum(&m, 2, 2));
  IntMatrixDestroy(&m);  
  return true;
}

bool IntMatrixSumWithRotation() {
  IntMatrix m;
  IntMatrixInit(&m, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      IntMatrixSet(&m, i, j, 3 * i + j);
    }
  }
  MatrixRotate(&m);
  ASSERT(6 + 4 + 2 == IntMatrixSum(&m, 0, 0));
  ASSERT(3 + 7 + 1 == IntMatrixSum(&m, 0, 1));
  ASSERT(0 + 4 + 8 == IntMatrixSum(&m, 0, 2));
  ASSERT(7 + 3 + 5 == IntMatrixSum(&m, 1, 0));
  ASSERT(4 + 6 + 2 + 0 + 8 == IntMatrixSum(&m, 1, 1));
  ASSERT(1 + 3 + 5 == IntMatrixSum(&m, 1, 2));
  ASSERT(8 + 4 + 0 == IntMatrixSum(&m, 2, 0));
  ASSERT(5 + 7 + 1 == IntMatrixSum(&m, 2, 1));
  ASSERT(2 + 4 + 6 == IntMatrixSum(&m, 2, 2));
  IntMatrixDestroy(&m);
  return true;
}

int main() {
  RUN(MatrixEmpty);
  RUN(StringsSetGet);
  RUN(StringsRotate);  
  RUN(IntMatrixEmpty);
  RUN(IntMatrixSetGet);
  RUN(IntMatrix2Rotate);
  RUN(IntMatrixFullRotation);
  RUN(IntMatrixSumNoRotation);
  RUN(IntMatrixSumWithRotation);  
  return 0;
}

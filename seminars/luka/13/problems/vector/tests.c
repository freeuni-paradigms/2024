#include "vector.h"
#include "students.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ASSERT_INT_EQ(a, b) {						\
    int expected = (a);							\
    int actual = (b);							\
    if (expected != actual) {						\
      printf("%s:%d Assertion failed: expected %d got %d\n", __FILE__, __LINE__, expected, actual); \
      return false;							\
    }									\
  }

#define ASSERT_STR_EQ(a, b) {						\
    char* expected = (a);							\
    char* actual = (b);							\
    if (strcmp(expected, actual) != 0) {								\
      printf("%s:%d Assertion failed: expected %s got %s\n", __FILE__, __LINE__, expected, actual); \
      return false;							\
    }									\
  }


#define TEST(t) { \
    printf("-- TESTING: %s\n", #t); \
    if (t()) {	  \
      printf("TEST %s: SUCCEEDED\n", #t);	\
    } \
    else { \
      printf("TEST %s: FAILED\n", #t);		\
    } \
    printf("####\n\n"); \
  }


// Integers

bool Empty() {
  Vector v;
  VectorInit(&v, sizeof(int), NULL);
  VectorDestroy(&v);
  return true;
}

bool AppendGet() {
  Vector v;
  VectorInit(&v, sizeof(int), NULL);
  for (int i = 0; i < 10; ++i) {
	VectorAppend(&v, &i);
  }
  ASSERT_INT_EQ(10, VectorSize(&v));
  for (int i = 0; i < 10; i++) {
	ASSERT_INT_EQ(i, *(int*)VectorGet(&v, i));
  }
  for (int i = 1; i < 10; i++) {
	ASSERT_INT_EQ(1, (int*)VectorGet(&v, i) - (int*)VectorGet(&v, i - 1));
  }
  VectorDestroy(&v);
  return true;
}

bool InsertGet() {
  Vector v;
  VectorInit(&v, sizeof(int), NULL);
  for (int i = 0; i < 10; ++i) {
	VectorInsert(&v, 0, &i);
  }
  ASSERT_INT_EQ(10, VectorSize(&v));
  for (int i = 0; i < 10; i++) {
	ASSERT_INT_EQ(9 - i, *(int*)VectorGet(&v, i));
  }
  for (int i = 1; i < 10; i++) {
	ASSERT_INT_EQ(1, (int*)VectorGet(&v, i) - (int*)VectorGet(&v, i - 1));
  }
  VectorDestroy(&v);
  return true;
}

bool InsertInTheMiddle() {
  Vector v;
  VectorInit(&v, sizeof(int), NULL);
  for (int i = 0; i < 10; ++i) {
	VectorInsert(&v, 0, &i);
  }
  ASSERT_INT_EQ(10, VectorSize(&v));
  int k = 100;
  VectorInsert(&v, 5, &k);
  ASSERT_INT_EQ(100, *(int*)VectorGet(&v, 5));
  for (int i = 0; i < 5; i++) {
	ASSERT_INT_EQ(9 - i, *(int*)VectorGet(&v, i));
  }
  for (int i = 5; i < 5; i++) {
	ASSERT_INT_EQ(9 - i, *(int*)VectorGet(&v, i + 1));
  }
  for (int i = 1; i < 11; i++) {
	ASSERT_INT_EQ(1, (int*)VectorGet(&v, i) - (int*)VectorGet(&v, i - 1));
  }
  VectorDestroy(&v);
  return true;
}

bool AppendOverwriteGet() {
  Vector v;
  VectorInit(&v, sizeof(int), NULL);
  for (int i = 0; i < 10; ++i) {
	VectorAppend(&v, &i);
  }
  for (int i = 0; i < 10; ++i) {
	int k = 9 - i;
	VectorOverwrite(&v, i, &k);
  }
  ASSERT_INT_EQ(10, VectorSize(&v));
  for (int i = 0; i < 10; i++) {
	ASSERT_INT_EQ(9 - i, *(int*)VectorGet(&v, i));
  }
  for (int i = 1; i < 10; i++) {
	ASSERT_INT_EQ(1, (int*)VectorGet(&v, i) - (int*)VectorGet(&v, i - 1));
  }
  VectorDestroy(&v);
  return true;
}

bool AppendRemoveWithNulls() {
  Vector v;
  VectorInit(&v, sizeof(int), NULL);
  for (int i = 0; i < 10; ++i) {
	VectorAppend(&v, &i);
  }
  ASSERT_INT_EQ(10, VectorSize(&v));
  for (int i = 0; i < 10; i++) {
	VectorRemove(&v, 0, NULL);
	ASSERT_INT_EQ(9 - i, VectorSize(&v));
  }
  VectorDestroy(&v);
  return true;
}

bool AppendRemove() {
  Vector v;
  VectorInit(&v, sizeof(int), NULL);
  for (int i = 0; i < 10; ++i) {
	VectorAppend(&v, &i);
  }
  ASSERT_INT_EQ(10, VectorSize(&v));
  for (int i = 0; i < 10; i++) {
	int k;
	VectorRemove(&v, 0, &k);
	ASSERT_INT_EQ(k, i);
	ASSERT_INT_EQ(9 - i, VectorSize(&v));
  }
  VectorDestroy(&v);
  return true;
}

// Strings

void StrFree(void* ptr) {
  free(*(char**)ptr);
}

bool StringsAppendGet() {
  Vector v;
  VectorInit(&v, sizeof(char*), StrFree);
  char* x = strdup("free");
  char* y = strdup("uni");
  char* z = strdup("hello world!");
  VectorAppend(&v, &x);
  VectorAppend(&v, &y);
  VectorAppend(&v, &z);
  ASSERT_INT_EQ(3, VectorSize(&v));
  ASSERT_STR_EQ("free", *(char**)VectorGet(&v, 0));
  ASSERT_STR_EQ("uni", *(char**)VectorGet(&v, 1));
  ASSERT_STR_EQ("hello world!", *(char**)VectorGet(&v, 2));
  VectorDestroy(&v);
  return true;
}

bool StringsInsertGet() {
  Vector v;
  VectorInit(&v, sizeof(char*), StrFree);
  char* x = strdup("free");
  char* y = strdup("uni");
  char* z = strdup("hello world!");
  VectorInsert(&v, 0, &x);
  VectorInsert(&v, 0, &y);
  VectorInsert(&v, 0, &z);
  ASSERT_INT_EQ(3, VectorSize(&v));
  ASSERT_STR_EQ("hello world!", *(char**)VectorGet(&v, 0));
  ASSERT_STR_EQ("uni", *(char**)VectorGet(&v, 1));
  ASSERT_STR_EQ("free", *(char**)VectorGet(&v, 2));
  VectorDestroy(&v);
  return true;
}

// Students

bool StudentsAppendGetDestroy() {
  StudentVector v;
  StudentVectorInit(&v);
  Student x;
  x.year = 2000;
  x.name = strdup("free");
  StudentVectorAppend(&v, &x);
  x.year = 2010;
  x.name = strdup("uni");
  StudentVectorAppend(&v, &x);
  ASSERT_INT_EQ(2, StudentVectorSize(&v));
  Student* y = StudentVectorGet(&v, 0);
  ASSERT_INT_EQ(2000, y->year);
  ASSERT_STR_EQ("free", y->name);
  y = StudentVectorGet(&v, 1);
  ASSERT_INT_EQ(2010, y->year);
  ASSERT_STR_EQ("uni", y->name);
  StudentVectorDestroy(&v);
  return true;
}

bool StudentsCloneRange() {
  StudentVector v;
  StudentVectorInit(&v);
  for (int i = 0; i < 10; ++i) {
	Student x;
	x.year = i;
	x.name = malloc(100);
	assert(x.name != NULL);
	sprintf(x.name, "%d", i);
	StudentVectorAppend(&v, &x);
  }
  ASSERT_INT_EQ(10, StudentVectorSize(&v));
  StudentVector c = StudentVectorCloneRange(&v, 3, 7);
  ASSERT_INT_EQ(5, StudentVectorSize(&c));
  StudentVectorDestroy(&v);
  for (int i = 3; i <= 7; ++i) {
	Student* s = StudentVectorGet(&c, i - 3);
	ASSERT_INT_EQ(i, s->year);
	char tmp[10];
	sprintf(tmp, "%d", i);
	ASSERT_STR_EQ(tmp, s->name);
  }
  StudentVectorDestroy(&c);
  return true;
}

int main(int argc, char** argv) {
  TEST(Empty);
  // Integers
  TEST(AppendGet);
  TEST(InsertGet);
  TEST(InsertInTheMiddle);
  TEST(AppendOverwriteGet);
  TEST(AppendRemoveWithNulls);
  TEST(AppendRemove);
  // Strings
  TEST(StringsAppendGet);
  TEST(StringsInsertGet);
  // Students
  TEST(StudentsAppendGetDestroy);
  TEST(StudentsCloneRange);
  return 0;
}

#include <stdio.h>
#include <string.h>

typedef int(*CmpFn)(void*, void*);

int lsearch(void* key, void* arr, int n, int elemSize, CmpFn cmpFn) {
  for (int i = 0; i < n; i++) {
	void* elemPtr = (char*)arr + (i * elemSize);
	if (cmpFn(elemPtr, key) == 0) {
	  return i;
	}
  }
  return -1;
}

// int*
int IntCmp(void* a, void* b) {
  return *(int*)a == *(int*)b;
	// return (*(int*)a) - (*(int*)b);
}

int StrCmp(void* a, void *b) {
  return strcmp(*(char**)a, *(char**)b);
}

int main() {
  /* int k = 5; */
  /* int arr[3] = {5, 1, 5}; */
  /* printf("%d\n", lsearch(&k, arr, 3, sizeof(int), IntCmp)); */

  char* k = strdup("freeuni");
  char* arr[3] = {strdup("freeuni"), strdup("foo"), strdup("bar")};
  printf("%d\n", lsearch(&k, arr, 3, sizeof(char*), StrCmp));
  return 0;
}

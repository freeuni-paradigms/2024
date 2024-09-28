#include <stdio.h>
#include <string.h>

/* void swap(int* a, int* b) { */
/*   int tmp = *a; */
/*   *a = *b; */
/*   *b = tmp; */
/* } */

void swap(void* a, void* b, int elemSize) {
  char tmp[elemSize]; // char*
  // memcpy (dst, src, num_bytes)
  memcpy(tmp, a, elemSize);
  memcpy(a, b, elemSize);
  memcpy(b, tmp, elemSize);
}

int main(int argc, char** argv) {
  short x = 5;
  int y = 7 + 65536;
  /* double x = 5.4; */
  /* double y = 9.3; */
  printf("%d %d\n", x, y);
  swap(&x, &y, sizeof(int));
  printf("%d %d\n", x, y);
  return 0;
}

// portable

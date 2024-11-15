#include "semaphore.h"
#include <stdio.h>
#include <unistd.h>

void* Increase(void* args) {
  Sem* s = args;
  SemPost(s);
  printf("INCREASE: DONE\n");
  return NULL;
}

void* Decrease(void* args) {
  Sem* s = args;
  SemWait(s);
  printf("DECREASE: DONE\n");
  return NULL;
}

int main(int argc, char** argv) {
  Sem s;
  SemInit(&s, 0);
  for (int i = 0; i < 5; i++) {
	pthread_t t;
	pthread_create(&t, 0, Decrease, &s);
  }
  pthread_t t;
  pthread_create(&t, 0, Increase, &s);
  sleep(5);
  printf("VALUE: %d\n", SemValue(&s));
  return 0;
}

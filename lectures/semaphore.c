#include "semaphore.h"

void SemInit(Sem* s, int value) {
  s->count = value;
  pthread_mutex_init(&s->m, 0);
  pthread_cond_init(&s->c, 0);
}

void SemDestroy(Sem* s) {
  pthread_mutex_destroy(&s->m);
  pthread_cond_destroy(&s->c);
}

void SemPost(Sem* s) {
  pthread_mutex_lock(&s->m);
  s->count++;
  pthread_cond_broadcast(&s->c);
  pthread_mutex_unlock(&s->m);
}

void SemWait(Sem* s) {
  pthread_mutex_lock(&s->m);
  while (s->count == 0) {
	pthread_cond_wait(&s->c, &s->m);
  }
  s->count--;
  pthread_mutex_unlock(&s->m);
}

int SemValue(Sem* s) {
  pthread_mutex_lock(&s->m);
  int ret = s->count;
  pthread_mutex_unlock(&s->m);
  return ret;
}

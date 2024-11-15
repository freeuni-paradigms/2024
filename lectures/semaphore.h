#include <pthread.h>

typedef struct {
  pthread_mutex_t m;
  pthread_cond_t c;
  int count;
} Sem;

void SemInit(Sem* s, int value);
void SemDestroy(Sem* s);
void SemPost(Sem* s);
void SemWait(Sem* s);
int SemValue(Sem* s);

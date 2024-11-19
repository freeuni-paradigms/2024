// pthread_cond_wait(conditional, mutex)
// 1) -- unlock mutex
// 2) -- sleep
// 3) -- wake - lock mutex

#include <pthread.h>

typedef struct {
  int r;
  bool w;
  pthread_mutex_t m;
  pthread_cond_t c;
} RWLock;

void RWLockInit(RWLock* l);
void RWLockDestroy(RWLock* l);
void RWLockRLock(RWLock* l);
void RWLockRUnlock(RWLock* l);
void RWLockWLock(RWLock* l);
void RWLockWUnlock(RWLock* l);

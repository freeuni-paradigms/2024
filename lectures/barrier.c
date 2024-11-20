#include "barrier.h"

void BarrierIxnit(Barrier* b, int value) {
  b->count = value;
  // mutex cond init
}

void BarrierDestroy(Barrier* b) {
  //
}

void BarrierWait(Barrier* b) {
  pthread_mutex_lock(&b->m);
  b->count--;
  // if (b->count > 0 ) {
	while (b->count > 0) {
	  pthread_cond_wait(&b->c, &b->m);
	}
	// } else {
	pthread_cond_broadcast(&b->c);
	//}
  pthread_mutex_unlock(&b->m);
}

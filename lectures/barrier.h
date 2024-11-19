typedef struct {
  int count;
  pthread_mutex_t m;
  pthread_cond_t c;
} Barrier;

void BarrierInit(Barrier* b, int value);
void BarrierDestroy(Barrier* b);
void BarrierWait(Barrier* b);

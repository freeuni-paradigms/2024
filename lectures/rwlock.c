void RWLockInit(RWLock* l) {
  l->r = 0;
  l->w = 0;
  // init mutex cond
}

void RWLockDestroy(RWLock* l) {
}

void RWLockRLock(RWLock* l) {
  pthread_mutex_lock(&l->m);
  // if
  while (l->w) {
	pthread_cond_wait(&l->c, &l->m);
  }
  l->r++;
  pthread_mutex_unlock(&l->m);
}

void RWLockRUnlock(RWLock* l) {
  pthread_mutex_lock(&l->m);
  l->r--;
  if (l->r == 0) {
	// pthread_cond_signal
	pthread_cond_broadcast(&l->c);
  }
  pthread_mutex_unlock(&l->m);
}

void RWLockWLock(RWLock* l) {
  pthread_mutex_lock(&l->m);
  while (l->r > 0 || l->w) {
	pthread_cond_wait(&l->c, &l->m);
  }
  l->w = true; // ++
  pthread_mutex_unlock(&l->m);
}

void RWLockWUnlock(RWLock* l) {
  pthread_mutex_lock(&l->m);
  l->w = false;
  pthread_cond_broadcast(&l->c);
  pthread_mutex_unlock(&l->m);
}

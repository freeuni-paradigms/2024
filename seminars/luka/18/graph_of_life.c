#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct {
  int num_total_threads;
  int threads_reached;
  int barrier_reaches; 
  pthread_mutex_t lock;
  pthread_cond_t cond;
} barrier;

typedef struct {
  int id;
  int num_iterations;
} CxovrebaArgs;

void *Ckhovreba(void *args) {
  CxovrebaArgs *margs = (CxovrebaArgs *) args;
  
  for (int i = 0; i < margs->num_iterations; i++) {
    int num_n = GetNumNeighbors(margs->id);
    int *neighbors = GetNeighbors(margs->id);

    int alive = 0;
    for (int j = 0; j < num_n; j++) {
      if (IsAlive(neighbors[j])) alive++;
    }

    pthread_mutex_lock(&barrier.lock);
    barrier.threads_reached++;

    if (barrier.num_total_threads == barrier.threads_reached) {
      barrier.threads_reached = 0;
      barrier.barrier_reaches++;
      pthread_cond_broadcast(&barrier.cond);
    } else {
      int old_reach = barrier.barrier_reaches;
      while (barrier.barrier_reaches == old_reach) {
        pthread_cond_wait(&barrier.cond, &barrier.lock);
      }
    }

    pthread_mutex_unlock(&barrier.lock);
    // barrier

    SetIsAlive(margs->id, alive == 2 || alive == 3);

    // barrier
    pthread_mutex_lock(&barrier.lock);
    barrier.threads_reached++;

    if (barrier.num_total_threads == barrier.threads_reached) {
      barrier.threads_reached = 0;
      barrier.barrier_reaches++;
      PrintAll();
      pthread_cond_broadcast(&barrier.cond);
    } else {
      int old_reach = barrier.barrier_reaches;
      while (barrier.barrier_reaches == old_reach) {
        pthread_cond_wait(&barrier.cond, &barrier.lock);
      }
    }

    pthread_mutex_unlock(&barrier.lock);
  }

  return 0;
}

void SimulateGraphOfLife(int num_nodes, int num_iterations) {
  pthread_t *threads;
  threads = malloc(num_nodes * sizeof(pthread_t));

  CxovrebaArgs *args;
  args = malloc(num_nodes * sizeof(CxovrebaArgs));

  barrier.barrier_reaches = 0;
  barrier.num_total_threads = num_nodes;
  pthread_mutex_init(&barrier.lock, 0);
  pthread_cond_init(&barrier.cond, 0);

  for (int i = 0; i < num_nodes; i++) {
    args[i].id = i;
    args[i].num_iterations = num_iterations;
    pthread_create(&threads[i], 0, &Ckhovreba, &args[i]); 
  }

  for (int i = 0; i < num_nodes; i++) {
    pthread_join(threads[i], 0);
  }

  free(threads);
  free(args);
  pthread_mutex_destroy(&barrier.lock);
  pthread_cond_destroy(&barrier.cond);
}

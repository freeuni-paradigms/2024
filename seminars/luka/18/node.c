#include "node.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num;
bool* alive;
int* num_neighbors;
int** neighbors;

void NodesInit(int num_nodes) {
  num = num_nodes;
  alive = malloc(num * sizeof(bool));
  assert(alive != NULL);
  num_neighbors = malloc(num * sizeof(int));
  assert(num_neighbors != NULL);
  neighbors = malloc(num * sizeof(int*));
  assert(neighbors != NULL);
  for (int i = 0; i < num; ++i) {
	neighbors[i] = NULL;
  }
}

void NodesDestroy() {
  free(alive);
  free(num_neighbors);
  for (int i = 0; i < num; i++) {
	if (neighbors[i] != NULL) {
	  free(neighbors[i]);
	}
  }
  free(neighbors);
}

void SetNeighbors(int id, int k, int* n) {
  num_neighbors[id] = k;
  neighbors[id]= malloc(k * sizeof(int));
  assert(neighbors[id] != NULL);
  memcpy(neighbors[id], n, k * sizeof(int));
}

bool IsAlive(int id) {
  return alive[id];
}

void SetIsAlive(int id, bool a) {
  alive[id] = a;
}

int GetNumNeighbors(int id) {
  return num_neighbors[id];
}

int* GetNeighbors(int id) {
  return neighbors[id];
}

void PrintAll() {
  for (int i = 0; i < num; ++i) {
	if (alive[i]) {
	  printf("1");
	} else {
	  printf("0");
	}
  }
  printf("\n");
}

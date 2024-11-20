#ifndef PARADIGMS_NODE_H_
#define PARADIGMS_NODE_H_

#include <stdbool.h>

bool IsAlive(int id);

void SetIsAlive(int id, bool alive);

int GetNumNeighbors(int id);

int* GetNeighbors(int id);

void PrintAll();

#endif // PARADIGMS_NODE_H_

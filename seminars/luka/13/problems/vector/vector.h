#ifndef PARADIGMS_VECTOR_
#define PARADIGMS_VECTOR_

typedef void(*FreeFn)(void* ptr);

typedef struct {
    int elem_size;
    FreeFn free_fn;

    int logical_size;
    int allocated_size;
    void *base;
} Vector;

void VectorInit(Vector* v, int elem_size, FreeFn free_fn);
void VectorDestroy(Vector* v);
void VectorAppend(Vector* v, void* elem);
void VectorInsert(Vector* v, int index, void* elem);
void VectorOverwrite(Vector* v, int index, void* elem);
void* VectorGet(Vector* v, int index);
void VectorRemove(Vector* v, int index, void* elem);
int VectorSize(Vector* v);

#endif // PARADIGMS_VECTOR_

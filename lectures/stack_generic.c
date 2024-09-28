#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// ერთერთი ფუნქცია რომელიც შეგვიძლია freeFunc-ს გადავაწოდოთ
void exampleFreeFunction(void *someArg) {

}

typedef struct s_stack {
    int allocLength;
    int logicalLength;
    
    void *base;
    int elemSize;

    void (*freeFunc)(void *);    
} Stack;

void StackNew(Stack *s, int elemSize, void (*freeFunc)(void *)) {
    s->allocLength = 4;
    s->logicalLength = 0;
    s->elemSize = elemSize;
    s->freeFunc = freeFunc;
    s->base = malloc(s->allocLength * s->elemSize); 
    assert(s->base != NULL);
}

void StackDispose(Stack *s) {
    if (s->freeFunc != NULL) {
        for (int i = 0; i < s->logicalLength; i++) {
            void *elemToFree = (char *) s->base + i * s->elemSize;
            s->freeFunc(elemToFree);
        }
    }

    free(s->base); 
}

void StackPush(Stack *s, void *value) {
    if (s->allocLength == s->logicalLength) {
        s->allocLength *= 2;
        s->base = realloc(s->base, s->allocLength * s->elemSize);
        assert(s->base != NULL);
    }

    void *target = (char *)s->base + s->logicalLength * s->elemSize;

    memcpy(target, value, s->elemSize);
    s->logicalLength++;
}

void StackPop(Stack *s, void *ret_value) {
    assert(s->logicalLength > 0);

    s->logicalLength--;
    void *source = (char *)s->base + s->logicalLength * s->elemSize;

    memcpy(ret_value, source, s->elemSize);
}



int main() {
    Stack stackOfStacks;

    StackNew(&stackOfStacks, sizeof(Stack), &StackDispose);

    for (int i = 0; i < 3; i++) {
        Stack someStackOfInts;

        StackNew(&someStackOfInts, sizeof(int), NULL);

        for (int j = 10 * i; j < 10 * (i + 1); j++) {
            StackPush(&someStackOfInts, &j);
        }

        StackPush(&stackOfStacks, &someStackOfInts);
    }

    for (int i = 0; i < 3; i++) {
        Stack someStackOfInts;

        StackPop(&stackOfStacks, &someStackOfInts);

        while (someStackOfInts.logicalLength > 0) {
            int element;
            StackPop(&someStackOfInts, &element);
            printf("Stack %d elem: %d\n", i, element);
        }
    }

    return 0;
}
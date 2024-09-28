#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct s_stack {
    int allocLength;
    int logicalLength;
    int *base;
} Stack;

void StackNew(Stack *s) {
    s->allocLength = 4;
    s->logicalLength = 0;

    s->base = malloc(s->allocLength * sizeof(int));
    assert(s->base != NULL);
}

void StackDispose(Stack *s) {
    free(s->base);
}

void StackPush(Stack *s, int value) {
    if (s->allocLength == s->logicalLength) {
        s->allocLength *= 2;
        s->base = realloc(s->base, s->allocLength * sizeof(int));
        assert(s->base != NULL);
    }

    s->base[s->logicalLength] = value;
    s->logicalLength++;
}

int StackPop(Stack *s) {
    assert(s->logicalLength > 0);
    
    s->logicalLength--;
    return s->base[s->logicalLength];
}

int main() {
    Stack s;

    Stack *sptr = malloc(sizeof(Stack));

    StackNew(sptr);

    StackNew(&s);

    for (int i = 0; i < 1000; i++) {
        StackPush(&s, i);
        StackPush(sptr, i);
    }

    for (int i = 0; i < 1000; i++) {
        printf("Stack 1: %d Stack 2 %d\n", StackPop(&s), StackPop(sptr));
    }

    StackDispose(&s);

    StackDispose(sptr);

    free(sptr);

    return 0;
}
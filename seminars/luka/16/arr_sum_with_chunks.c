#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10
#define ARR_SIZE 100000
#define MAX_NUM 10000

void generateArray(int *arr) {
    int sum = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % MAX_NUM;
        sum += arr[i];
    }
    printf("Sum of array is %d\n", sum);
}

typedef struct {
    int *arr;
    int *sum;

    int startRange;
    int count;

    sem_t *sem;
} Args;

void *calculate_sum(void *args) {
    Args *arg_ptr = (Args *)args;

    int local_sum = 0;

    for (int i = 0; i < arg_ptr->count; i++) {
        local_sum += arg_ptr->arr[arg_ptr->startRange + i];
    }

    sem_wait(arg_ptr->sem);
    *arg_ptr->sum += local_sum;
    sem_post(arg_ptr->sem);
}

int main(int argc, char **argv) {
    int arr[ARR_SIZE];

    generateArray(arr);

    int count = atoi(argv[1]);

    printf("Thread count %d\n", count);

    pthread_t *threads = malloc(sizeof(pthread_t) * count);
    Args *args = malloc(sizeof(Args) * count);

    int sum;
    sem_t sem;

    sem_init(&sem, 0, 1);

    int per_thread_count = ARR_SIZE / count;

    for (int i = 0; i < count; i++) {
        args[i].sum = &sum;
        args[i].sem = &sem;
        args[i].arr = arr;
        args[i].startRange = per_thread_count * i;
        args[i].count = per_thread_count;

        if (i == count - 1) {
            args[i].count += ARR_SIZE % count;
        }

        pthread_create(&threads[i], 0, calculate_sum, &args[i]);
    }

    for (int i = 0; i < count; i++) {
        pthread_join(threads[i], 0);
    }

    free(threads);
    free(args);

    printf("Thread sum count %d\n", sum);

    return 0;
}
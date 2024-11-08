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
    int sum;

    int count;
    int index;
    sem_t sem;
} Args;

void *calculate_sum(void *args) {
    Args *arg_ptr = (Args *)args;

    while(0xDEADBEEF) {
        sem_wait(&arg_ptr->sem);
        int local_index = arg_ptr->index;
        int count = arg_ptr->count;
        
        if (local_index + count >= ARR_SIZE) {
            count = ARR_SIZE - local_index;
        }

        if (count <= 0) {
            sem_post(&arg_ptr->sem);
            return 0;
        }

        arg_ptr->index += count;
        sem_post(&arg_ptr->sem);



        int local_sum = 0;
        
        for (int i = 0; i < count; i++) {
            local_sum += arg_ptr->arr[i + local_index];
        }

        sem_wait(&arg_ptr->sem);
        arg_ptr->sum += local_sum;
        sem_post(&arg_ptr->sem);
    }
}

int main(int argc, char **argv) {
    int arr[ARR_SIZE];

    generateArray(arr);

    int count = atoi(argv[1]);

    printf("Thread count %d\n", count);

    pthread_t *threads = malloc(sizeof(pthread_t) * count);

    Args global_args = {
        .arr = arr,
        .count = 100
    };

    sem_init(&global_args.sem, 0, 1);

    for (int i = 0; i < count; i++) {
        pthread_create(&threads[i], 0, calculate_sum, &global_args);
    }

    for (int i = 0; i < count; i++) {
        pthread_join(threads[i], 0);
    }

    free(threads);

    printf("Thread sum count %d\n", global_args.sum);

    return 0;
}
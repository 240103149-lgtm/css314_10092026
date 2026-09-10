#include <stdio.h>
#include <pthread.h>
#include <time.h>

long long counter = 0;
pthread_mutex_t lock;
int use_lock = 0;

void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        if (use_lock) pthread_mutex_lock(&lock);
        counter++;
        if (use_lock) pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void run_test() {
    counter = 0;
    pthread_t threads[10];
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < 10; i++) pthread_create(&threads[i], NULL, increment, NULL);
    for (int i = 0; i < 10; i++) pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
    
    printf("Total: %lld | Error: %lld | Time: %.2f ms\n", counter, 10000000 - counter, time_taken);
}

int main() {
    pthread_mutex_init(&lock, NULL);
    printf("--- UNLOCKED (RACE CONDITION) ---\n");
    use_lock = 0;
    for(int i=0; i<10; i++) run_test();

    printf("\n--- LOCKED (MUTEX) ---\n");
    use_lock = 1;
    run_test();
    return 0;
}


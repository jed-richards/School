/* This is a program to practice using threads and mutexes. 
 * Each thread will try to increment a value up to 1 million. 
 * Each time this is done, a global variable, incrementAttempts,
 * will be increased. THe variable attempts will be gaurded 
 * using a mutex. This code is an example of "race conditions". */

#include <stdio.h>
#include <pthread.h>

int attempts = 0;
int count = 0;
pthread_mutex_t attempts_m = PTHREAD_MUTEX_INITIALIZER;


void* incrementCount(void* arg) {
    while (count < 1000000) {
        count++;

        pthread_mutex_lock(&attempts_m);
        attempts++;
        pthread_mutex_unlock(&attempts_m);
    }    
}


int main() {

    int num_threads = 16;
    pthread_t thread[num_threads];

    /* Set threads loose */
    for (int i=0; i < num_threads; i++) {
        pthread_create(&(thread[i]),      // thread ID
                       0,                 // default attributes
                       incrementCount,    // start routine
                       NULL);             // argument
    }
   
    for (int i = 0; i < num_threads; i++)
        pthread_join(thread[i], NULL);

    printf("attempts: %d\n", attempts);
    printf("count: %d\n", count);

    return 0;
}

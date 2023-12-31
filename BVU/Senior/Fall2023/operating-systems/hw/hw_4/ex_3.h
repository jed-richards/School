#include <pthread.h>
#include <unistd.h>

struct PhiloArgs {
    pthread_mutex_t *rightFork;
    pthread_mutex_t *leftFork;
    int mealSize;
    int attempts;
} typedef PhiloArgs;

void* dine(void* arg) {
    /* Create PhiloArgs pointer */
    PhiloArgs *args = (PhiloArgs*) arg;

    while (args->mealSize > 0) {
        args->attempts++;

        /* Try to take forks. If can't take rightFork continue to next
         * iteration. If can take rightFork, try to take leftFork. If can't
         * take leftFork, release rightFork then continue to next iteration. */
        if (!pthread_mutex_trylock(args->rightFork))
            continue;

        if (!pthread_mutex_trylock(args->leftFork)) {
            pthread_mutex_unlock(args->rightFork);
            continue;
        }

        /* If here, philosopher has both forks, so EAT! */
        args->mealSize--;

        /* Drop forks */
        pthread_mutex_unlock(args->leftFork);
        pthread_mutex_unlock(args->rightFork);

        /* These philosophers don't sleep. They are always trying to eat! */
    }
}

float dine_philosophers_dine(int numPhilosophers, int mealSize)
{
    /* Create array of forks (mutexes), philosophers (threads), and
     * array of PhiloArgs */
    pthread_mutex_t fork[numPhilosophers];
    pthread_t philosopher[numPhilosophers];
    PhiloArgs philoArgs[numPhilosophers];

    /* Initialize all mutexes and PhiloArgs */
    for (int i=0; i<numPhilosophers; i++) {
        pthread_mutex_init(&fork[i], NULL);  // Default mutex init
        
        /* By convention the fork to the left of the philospher will be the 
         * same index as the philosopher. For example, let P_n represent
         * philospher n and F_m represent fork m. Then P_n's forks would be:
         * leftFork = F_n and rightFork = F_n-1. */

        /* philoArgs[i] = {rightFork[i-1], leftFork[i], mealSize, 0}; 
         * (the 0 is number of attempts to eat) */
        if (i==0) {
            philoArgs[i] = (PhiloArgs) {
                &fork[numPhilosophers-1],
                &fork[i], 
                mealSize,
                0
            };
        }
        else {
            philoArgs[i] = (PhiloArgs) {
                &fork[i-1],
                &fork[i],
                mealSize,
                0
            };
        }
    }

    /* Set philosophers loose. Its the wild west! */
    for (int i=0; i < numPhilosophers; i++) {
        pthread_create(&(philosopher[i]),  // thread ID
                       0,                  // default attributes
                       dine,               // start routine
                       &philoArgs[i]);     // argument
    }
   
    int total_attempts = 0;
    for (int i = 0; i < numPhilosophers; i++) {
        pthread_join(philosopher[i], NULL);
        pthread_mutex_destroy(&fork[i]);
        total_attempts += philoArgs[i].attempts;
    }

    return (float) total_attempts/(numPhilosophers*mealSize);
}

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 4

// Define philosopher states
typedef enum { THINKING, HUNGRY, EATING } state_t;

// Define mutex for forks and an array to keep track of the state of each philosopher
pthread_mutex_t forks[NUM_PHILOSOPHERS];
state_t states[NUM_PHILOSOPHERS];
pthread_mutex_t lock;

// Function declarations
void *philosopher(void *num);
void take_forks(int phil_num);
void put_forks(int phil_num);
void test(int phil_num);

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    pthread_mutex_init(&lock, NULL);

    // Initialize forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        states[i] = THINKING;
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)(long)i);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&lock);

    return 0;
}

void *philosopher(void *num) {
    int phil_num = (int)(long)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", phil_num);
        sleep(1);

        // Hungry
        take_forks(phil_num);

        // Eating
        printf("Philosopher %d is eating\n", phil_num);
        sleep(1);

        // Finished eating
        put_forks(phil_num);
    }
}

void take_forks(int phil_num) {
    pthread_mutex_lock(&lock);

    states[phil_num] = HUNGRY;
    printf("Philosopher %d is hungry\n", phil_num);

    // Try to take forks
    test(phil_num);

    pthread_mutex_unlock(&lock);

    // Wait until philosopher can eat
    pthread_mutex_lock(&forks[phil_num]);
}

void put_forks(int phil_num) {
    pthread_mutex_lock(&lock);

    states[phil_num] = THINKING;
    printf("Philosopher %d is putting forks down and starting to think\n", phil_num);

    // Test left and right neighbors
    test((phil_num + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
    test((phil_num + 1) % NUM_PHILOSOPHERS);

    pthread_mutex_unlock(&lock);
}

void test(int phil_num) {
    if (states[phil_num] == HUNGRY &&
        states[(phil_num + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING &&
        states[(phil_num + 1) % NUM_PHILOSOPHERS] != EATING) {

        states[phil_num] = EATING;
        pthread_mutex_unlock(&forks[phil_num]);
    }
}

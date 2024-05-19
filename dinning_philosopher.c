#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void *philosopher(void *);
void think(int);
void pickUp(int);
void eat(int);
void putDown(int);

pthread_mutex_t *chopsticks;
pthread_t *philosophers;
pthread_attr_t *attributes;
int number_of_philosophers;

int main() {
    int i;
    srand(time(NULL));

    printf("Enter the number of philosophers: ");
    scanf("%d", &number_of_philosophers);

    // Allocate memory for chopsticks, philosophers, and attributes arrays
    chopsticks = malloc(number_of_philosophers * sizeof(pthread_mutex_t));
    philosophers = malloc(number_of_philosophers * sizeof(pthread_t));
    attributes = malloc(number_of_philosophers * sizeof(pthread_attr_t));

    for (i = 0; i < number_of_philosophers; ++i) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for (i = 0; i < number_of_philosophers; ++i) {
        pthread_attr_init(&attributes[i]);
    }

    for (i = 0; i < number_of_philosophers; ++i) {
        pthread_create(&philosophers[i], &attributes[i], philosopher, (void *)(intptr_t)i);
    }

    for (i = 0; i < number_of_philosophers; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    // Free allocated memory
    free(chopsticks);
    free(philosophers);
    free(attributes);

    return 0;
}

void *philosopher(void *philosopherNumber) {
    int num = (intptr_t)philosopherNumber;
    while (1) {
        think(num);
        pickUp(num);
        eat(num);
        putDown(num);
    }
}

void think(int philosopherNumber) {
    int sleepTime = rand() % 3 + 1;
    printf("Philosopher %d will think for %d seconds\n", philosopherNumber, sleepTime);
    sleep(sleepTime);
}

void pickUp(int philosopherNumber) {
    int right = (philosopherNumber + 1) % number_of_philosophers;
    int left = (philosopherNumber + number_of_philosophers) % number_of_philosophers;
    if (philosopherNumber & 1) {
        printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
        pthread_mutex_lock(&chopsticks[right]);
        printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
        printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
        pthread_mutex_lock(&chopsticks[left]);
        printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
    }
    else {
        printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
        pthread_mutex_lock(&chopsticks[left]);
        printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
        printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
        pthread_mutex_lock(&chopsticks[right]);
        printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
    }
}

void eat(int philosopherNumber) {
    int eatTime = rand() % 3 + 1;
    printf("Philosopher %d will eat for %d seconds\n", philosopherNumber, eatTime);
    sleep(eatTime);
}

void putDown(int philosopherNumber) {
    printf("Philosopher %d will put down her chopsticks\n", philosopherNumber);
    pthread_mutex_unlock(&chopsticks[(philosopherNumber + 1) % number_of_philosophers]);
    pthread_mutex_unlock(&chopsticks[(philosopherNumber + number_of_philosophers) % number_of_philosophers]);
}

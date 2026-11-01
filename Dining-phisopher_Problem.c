#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room; /* allows at most N-1 philosophers to sit and pick up forks */

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    for (int cycle = 0; cycle < 2; cycle++)
    {
        printf("Philosopher %d is thinking\n", id);
        usleep(100000);

        sem_wait(&room);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        printf("Philosopher %d is eating (fork %d and fork %d)\n",
               id, left, right);
        usleep(150000);

        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&room);

        printf("Philosopher %d finished eating and put down forks\n", id);
    }
    return NULL;
}

int main()
{
    pthread_t philo[N];
    int ids[N];

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);
    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&philo[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(philo[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);
    sem_destroy(&room);
    return 0;
}

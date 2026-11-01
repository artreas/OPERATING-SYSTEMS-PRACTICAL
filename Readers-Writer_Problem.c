#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg)
{
    long id = (long)arg;

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %ld: read shared_data = %d\n", id, shared_data);
    usleep(200000);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt);
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg)
{
    long id = (long)arg;

    sem_wait(&wrt);
    shared_data++;
    printf("Writer %ld: wrote shared_data = %d\n", id, shared_data);
    usleep(300000);
    sem_post(&wrt);

    return NULL;
}

int main()
{
    pthread_t r[5], w[2];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_create(&w[0], NULL, writer, (void *)1);
    for (long i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, (void *)(i + 1));
    pthread_create(&w[1], NULL, writer, (void *)2);

    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);
    pthread_join(w[0], NULL);
    pthread_join(w[1], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}

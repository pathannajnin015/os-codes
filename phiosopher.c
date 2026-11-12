#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t chopstick[5];

void* philosopher(void* num)
{
    int id = *(int*)num;

    sem_wait(&room);

    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id + 1) % 5]);

    printf("Philosopher %d is eating\n", id + 1);
    sleep(1);

    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % 5]);

    printf("Philosopher %d is thinking\n", id + 1);

    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t t[5];
    int id[5];

    sem_init(&room, 0, 4);

    for(int i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    for(int i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    printf("All philosophers finished.\n");

    return 0;
}
 
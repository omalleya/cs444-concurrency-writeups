#include "concurrency2.h"

void think()
{
    int wait = (rand() % 20) + 1;
    sleep(wait);
}

void get_forks(struct philosopher *phil)
{
    //left fork lock
    if(pthread_mutex_lock(&mutex[phil->num]) != 0)
        printf("failed to get left fork\n");
        
    //right fork lock
    if(pthread_mutex_lock(&mutex[(phil->num+1) % NUM_PHILOSOPHERS]) != 0)
        printf ("failed to get right fork\n");

    fork_status();
}

void eat()
{
    int wait = (rand() % 9) + 2;
    sleep(wait);
}

void put_forks(struct philosopher *phil)
{
    //left fork unlock
    if(pthread_mutex_unlock(&mutex[phil->num]) != 0)
        printf("failed to put down left fork\n");
    //right fork unlock
    if(pthread_mutex_unlock(&mutex[(phil->num+1) % NUM_PHILOSOPHERS]) != 0)
        printf ("failed to put down right fork\n");

    fork_status();
}

void *loop(void *i)
{
    struct philosopher *j = (struct philosopher*) i;
    //free(i);
    while(1)
    {
        printf("%s num: %d\n", j->name, j->num);
        printf("philosopher %s is thinking\n", j->name);
        think();
        get_forks(j);
        printf("philosopher %s is eating\n", j->name);
        eat();
        put_forks(j);
    }
    return(NULL);
        
}

void fork_status()
{
    int i=0;
    printf("FORK STATUS: \n");
    for(i=0; i<5; i++) {
        if(pthread_mutex_trylock(&mutex[i]) == 0)
        {
            //lock was successful
            pthread_mutex_unlock(&mutex[i]);
            printf("[%d available] ", i);
        }
        else
        {
            printf("[%d in use] ", i);
            //someone else holds the lock
        }
    }
    printf("\n");
}

void init()
{
    int i=0;
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&mutex[i], NULL);
    }
}

void cleanup()
{
    int i=0;
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&mutex[i]);
    }
}
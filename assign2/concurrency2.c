#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

struct philosopher {
    int num;
    char* name;
    char* state;
};

//const char* phil_names[] = {"","","","",""};

/*threads*/
pthread_t phil_thread[5];
/* mutex lock */
pthread_mutex_t mutex[5];
/* conditional vars */
//pthread_cond_t cond[5];

void think()
{
    int wait = (rand() % 20) + 1;
    sleep(wait);
}

void get_forks(int i)
{
    //left fork lock
    if(pthread_mutex_lock(&mutex[i]) != 0)
        printf("failed");
    //right fork lock
    if(pthread_mutex_lock(&mutex[(i+1)%5]) != 0)
        printf ("failed");
}

void eat()
{
    int wait = (rand() % 9) + 2;
    sleep(wait);
}

void put_forks(int i)
{
    //left fork unlock
    if(pthread_mutex_unlock(&mutex[i]) != 0)
        printf("failed");
    //right fork unlock
    if(pthread_mutex_unlock(&mutex[(i+1)%5]) != 0)
        printf ("failed");
}

void *loop(void *i)
{
    int j = (intptr_t) i;
    //free(i);
    while(1)
    {
        printf("philosopher %d is thinking", j);
        think();
        get_forks(j);
        printf("philosopher %d is eating", j);
        eat();
        put_forks(j);
        return(NULL);
    }

}

void init()
{
    int i=0;
    for(i=0; i<5; i++)
    {
        pthread_mutex_init(&mutex[i], NULL);
        //pthread_cond_init(&cond[i]);
    }
}

void cleanup()
{
    int i=0;
    for(i=0; i<5; i++)
    {
        pthread_mutex_destroy(&mutex[i]);
        //pthread_cond_destroy(&cond[i]);
    }
}

int main()
{
    printf("test");
    /*create philosophers */
    struct philosopher *philosophers = malloc(sizeof(struct philosopher) * 5);
    philosophers[0].name = "Aristotle";

    printf(philosophers[0].name);
    
    /* initialize mutex and cond threads */
    init();

    /*create threads and join*/
    int i=0;
    for(i=0; i<5; i++)
    {
        int *j = malloc(sizeof(*j));
        *j = i;
        pthread_create(&(phil_thread[i]),
            NULL,
            (void *) loop,
            (void *)(intptr_t) i);
    }
    i=0;
    for(i=0; i<5; i++)
    {
        pthread_join(phil_thread[i], NULL);
    }

    /* cleanup */
    cleanup();

    return 0;
}
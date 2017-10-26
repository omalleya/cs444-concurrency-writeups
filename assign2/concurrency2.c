#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

const int NUM_PHILOSOPHERS = 5;

struct philosopher {
    int num;
    char* name;
    char* state;
};

char* phil_names[] = {"Aristotle","Plato","Voltaire","Galileo","Pythagoras"};

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

void get_forks(struct philosopher *phil)
{
    //left fork lock
    if(pthread_mutex_lock(&mutex[phil->num]) != 0)
        printf("failed to get left fork");
    //right fork lock
    if(pthread_mutex_lock(&mutex[(phil->num+1) % NUM_PHILOSOPHERS]) != 0)
        printf ("failed to get right fork");
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
        printf("failed");
    //right fork unlock
    if(pthread_mutex_unlock(&mutex[(phil->num+1) % NUM_PHILOSOPHERS]) != 0)
        printf ("failed");
}

void *loop(void *i)
{
    struct philosopher *j = (struct philosopher*) i;
    //free(i);
    while(1)
    {
        printf("philosopher %s is thinking\n", j->name);
        think();
        get_forks(j);
        printf("philosopher %s is eating\n", j->name);
        eat();
        put_forks(j);
    }
    return(NULL);
        
}

void init()
{
    int i=0;
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&mutex[i], NULL);
        //pthread_cond_init(&cond[i]);
    }
}

void cleanup()
{
    int i=0;
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&mutex[i]);
        //pthread_cond_destroy(&cond[i]);
    }
}

int main()
{
    /*create philosophers */
    struct philosopher *philosophers = malloc(sizeof(struct philosopher) * NUM_PHILOSOPHERS);

    int i=0;
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        philosophers[i].num = i;
        philosophers[i].name = phil_names[i];
        philosophers[i].state = "thinking";

    }
    
    /* initialize mutex and cond threads */
    init();

    /*create threads and join*/
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        pthread_create(&(phil_thread[i]),
            NULL,
            (void *) loop,
            (void *) &philosophers[i]);
    }
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        pthread_join(phil_thread[i], NULL);
    }

    /* cleanup */
    cleanup();

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

struct philosopher {
    char* name;
    char* state;
};

const char* phil_names[] = {"","","","",""};

/*threads*/
pthread_t phil_thread[5];
/* mutex lock */
pthread_mutex_t mutex[5];
/* conditional vars */
pthread_cond_t cond[5];

int create_thread(pthread_t *thread, void *func)
{
    return pthread_create(thread,
		               NULL,
		               func,
		               NULL);
}

void think()
{
    int wait = (rand() % 20) + 1;
    sleep(wait);
}

void get_forks()
{
    //
}

void eat()
{
    int wait = (rand() % 9) + 2;
    sleep(wait);
}

void put_forks()
{

}

void *loop()
{
    while(true)
    {
        think();
        get_forks();
        eat();
        put_forks();
    }
}

void init()
{
    int i=0;
    for(i=0; i<5; i++)
    {
        pthread_mutex_init(&mutex[i]);
        pthread_cond_init(&cond[i]);
    }
}

void cleanup()
{
    int i=0;
    for(i=0; i<5; i++)
    {
        pthread_mutex_destroy(&mutex[i]);
        pthread_cond_destroy(&cond[i]);
    }
}

int main()
{
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
        create_thread(&(phil_thread[i]), loop);
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
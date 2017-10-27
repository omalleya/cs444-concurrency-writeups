#include "concurrency2.h"

int main()
{
    char* phil_names[] = {"Aristotle","Plato","Voltaire","Galileo","Pythagoras"};    
    /*create philosophers */
    struct philosopher *philosophers = malloc(sizeof(struct philosopher) * NUM_PHILOSOPHERS);

    int i=0;
    for(i=0; i<NUM_PHILOSOPHERS; i++)
    {
        philosophers[i].num = i;
        philosophers[i].name = phil_names[i];
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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_PHILOSOPHERS 5

struct philosopher {
    int num;
    char* name;
};

/*threads*/
pthread_t phil_thread[NUM_PHILOSOPHERS];
/* mutex lock */
pthread_mutex_t mutex[NUM_PHILOSOPHERS];
/* conditional vars */

void think();
void get_forks(struct philosopher *);
void eat();
void put_forks(struct philosopher *);
void *loop(void *);
void init();
void cleanup();
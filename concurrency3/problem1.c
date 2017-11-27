#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_MAX 10

pthread_t threads[THREAD_MAX];

sem_t mutex;
sem_t block;
int num_using;
int active = 0;
int waiting = 0;
int must_wait = 0;

//Reference: https://pdfs.semanticscholar.org/93af/99143f8123032fbcc805656d63617a2268ab.pdf
void *use_resource(void *num) {
    int id = *((int *) num);
    
    while(1){
        sem_wait(&mutex);
        if(must_wait) {
            waiting++;
            sem_post(&mutex);
            sem_wait(&block);
        } else {
            active++;
            if(active == 3)
                must_wait = 1;
            sem_post(&mutex);
        }

        printf("Thread %d is using the resource.\n", id);
        int wait = (rand() % 5) + 2;
        sleep(wait);

        sem_wait(&mutex);
        active--;
        printf("Thread %d left resource.\n", id);
        
        if(active == 0) {
            printf("Resource is not being used.\n");
            int j;
            if(waiting < 3) {
                j = waiting;
            } else {
                j = 3;
            }
            waiting -= j;
            active = j;
            while(j > 0){
                sem_post(&block);
                j--;
            }
            if(active == 3)
                must_wait = 1;
        }
        sem_post(&mutex);
    }
    return(NULL);
}

int main() {
    sem_init(&mutex, 0, 3);
    sem_init(&block, 0, 0);  

    int i=0;
    for(i=0; i < THREAD_MAX; i++){
        int *num = malloc(sizeof(int)); 
	*num = i;
        pthread_create(&threads[i], NULL, use_resource, num);
    }

    for (i = 0; i < THREAD_MAX; i++){
		pthread_join(threads[i], NULL);
	}

    return 0;
}

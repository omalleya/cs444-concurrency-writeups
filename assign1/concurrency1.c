#include <stdio.h>
#include <cpuid.h>
#include <string.h>
#include <x86intrin.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "mt19937ar.c"

struct buffer_item {
    int num;
    unsigned int wait;
};

struct buffer_item **buffer;
int current_index = 0;

//mutex lock
pthread_mutex_t mutex;
//conditionals
pthread_cond_t condc, condp;

//function pointer to set proper random number generator function
int (*rand_generator)(unsigned int*);

int create_thread(pthread_t *thread, void *func)
{
    return pthread_create(thread,
		               NULL,
		               func,
		               NULL);
}

int GetRandomViaRDRAND(unsigned int* pResult)
{
    return (_rdrand32_step(pResult) != 0);
}

int GetRandomViaMT(unsigned int* pResult)
{
    *pResult = (int)genrand_int32();

    return 1;
}

//code on website to see if computer uses rdrand
void rdrand_check()
{
    unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;

	char vendor[13];
	
	eax = 0x01;

	__asm__ __volatile__(
	                     "cpuid;"
	                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	                     : "a"(eax)
	                     );
	
	if(ecx & 0x40000000){
		//use rdrand
        printf("using rdrand\n");
        rand_generator = &GetRandomViaRDRAND;
	}
	else{
		//use mt19937
        printf("using mt19937\n");
        rand_generator = &GetRandomViaMT;
	}
}

int GetsRandomValueInDesiredRange(int *val, int shift, int add)
{
    if((*rand_generator)(val))
    {
        //val = abs(val);
        if(*val < 0)
        {
            *val += -(*val);
        }
        //shift bit and add to get the random value in the proper range
        *val = (*val >> shift) + add;
        return (*val);
    }
    return -1;
}

void print_buffer()
{
    printf("current buff: ");
    for(int i=0; i<current_index; i++)
    {
        printf("[ num: %d, wait: %d ] ", buffer[i]->num, buffer[i]->wait);
    }
    printf("\n");
}

void *producer()
{
    while(1)
    {
        //wait for input
        fflush(stdin);
        printf("PRESS ENTER TO PRODUCE ONE ITEM. ADDITIONALLY FOR EVERY CHARACTER TYPED BEFORE ENTER IS PRESSED, AN ITEM WILL BE PRODUCED WHEN THE PRODUCER THREAD IS AVAILABLE...\n");
        getchar();

        //give producer exclusive access to buffer
        pthread_mutex_lock(&mutex);

        //if buffer is full, block
        while(current_index >= 32)
            pthread_cond_wait(&condp, &mutex);
        
        //unlock during sleep of random amount of time between 3 and 7 sec before producing
        pthread_mutex_unlock(&mutex);
        int wait;
        GetsRandomValueInDesiredRange(&wait, 29, 3);
        printf("item will be produced in %d seconds\n", wait);
        (void)sleep(wait);

        //lock again and add item to buffer
        pthread_mutex_lock(&mutex);
        struct buffer_item *item = (struct buffer_item*) malloc(sizeof(struct buffer_item));
        rand_generator(&(item->num));
        GetsRandomValueInDesiredRange(&(item->wait), 28, 2);
        buffer[current_index] = item;
        current_index++;
        print_buffer();

        //release buffer
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condc);
    }
    pthread_exit(0);
}

void *consumer()
{
    while(1)
    {
        //give consumer exclusive access to buffer
        pthread_mutex_lock(&mutex);

        //if buffer empty we block
        while(current_index <= 0)
            pthread_cond_wait(&condc, &mutex);

        //consume buffer item
        struct buffer_item *item = buffer[0];
        int temp = item->wait;

        //unlock during sleep
        pthread_mutex_unlock(&mutex);
        printf("consuming item to be completed in %d seconds\n",temp);
        (void)sleep(temp);

        //lock again and consume item
        pthread_mutex_lock(&mutex);
        buffer = &buffer[1];
        printf("consumed item's num: %d\n",item->num);
        current_index--;
        print_buffer();
        free(item);

        //release buffer
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condp);
    }
    pthread_exit(0);
}


int main()
{
    buffer = malloc(sizeof(struct buffer_item *)*32);
    
    pthread_t producer_thread, consumer_thread;

    //initialize mutex and cond threads
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);

    //check if we can use rd_rand
    rdrand_check();

    //create and join threads so program doesn't end without notice
    create_thread(&(producer_thread), producer);
    create_thread(&(consumer_thread), consumer);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    //cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condp);
    pthread_cond_destroy(&condc);
    return 0;
}
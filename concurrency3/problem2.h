#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <x86intrin.h>
#include "mt19937ar.c"

#define LIST_SIZE 6
#define THREAD_MAX 5

struct node {
    struct node *next;
    int data;
};

pthread_t searcher;
pthread_t inserter;
pthread_t deleter;

sem_t s_sem;
sem_t i_sem;
sem_t d_sem;

pthread_t ins[THREAD_MAX];
pthread_t sea[THREAD_MAX];
pthread_t del[THREAD_MAX];

pthread_mutex_t s_lock;
pthread_mutex_t i_lock;
pthread_mutex_t d_lock;
pthread_rwlock_t lock;

int num_searching;
int num_inserting;
int num_deleting;

int total_count;

int create_thread(pthread_t *, void *);
void create_random_list();
void clear_list();
void *search();
void *insert();
void *delete();

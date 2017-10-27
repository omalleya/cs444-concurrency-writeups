#include "concurrency2.h"
#include <errno.h>

int is_locked(int i) {
    int status = pthread_mutex_trylock(&mutex[i]);
    if (status == 0) {
        pthread_mutex_unlock(&mutex[i]);
        return 0;
    } else if (status == EBUSY) {
        return 1;
    } else {
        printf("failed to check mutex status\n");
        exit(1); 
    }
}

void print_forks() {
    int i;
    int count = 0;
    int result;
    for (i=0; i<NUM_PHILOSOPHERS; i++) {
        result = is_locked(i);
        if (result == 1) {
            count++;
            printf("fork %d picked up\n", i+1);
        }  else {
            printf("fork %d available\n", i+1);
        }


    }
    if (count == 0) 
        printf("all mutexes are unlocked\n");
    
}

int main()
{
    int i;
    int result = 0;
    struct philosopher *philosophers = malloc(sizeof(struct philosopher) * 2);
    philosophers[0].num = 0;
    philosophers[1].num = 3;
    philosophers[0].name = "Aristotle";
    philosophers[1].name = "Galileo";

    printf("Checking if all mutexes are unlocked\n");
    print_forks();

    printf("First philosopher at the table getting forks\n");
    get_forks(&philosophers[0]);
    //check that left and right forks are locked
    print_forks();
    printf("fork 1 and 2 should be picked up\n");

    printf("First philosopher at the table putting forks back\n");
    put_forks(&philosophers[0]);
    print_forks();

    printf("First and fourth philosopher getting forks\n");
    get_forks(&philosophers[0]);
    get_forks(&philosophers[1]);
    print_forks();
    printf("Third fork should be available\n");

    printf("Putting back fourth philospher forks\n");
    put_forks(&philosophers[1]);
    print_forks();

    printf("Putting back first philospher forks\n");
    put_forks(&philosophers[0]);
    print_forks();

    return 0;
}
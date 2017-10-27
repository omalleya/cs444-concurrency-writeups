#include "concurrency2.h"
#include <errno.h>

int main()
{
    int i;
    int result = 0;
    struct philosopher *philosophers = malloc(sizeof(struct philosopher) * 2);
    philosophers[0].num = 0;
    philosophers[1].num = 3;
    philosophers[0].name = "Aristotle";
    philosophers[1].name = "Galileo";

    //initialize mutex
    init();

    printf("Checking if all mutexes are unlocked\n");
    fork_status();

    printf("First philosopher at the table getting forks\n");
    get_forks(&philosophers[0]);
    //check that left and right forks are locked
    printf("fork 1 and 2 should be picked up in status above\n");

    printf("First philosopher at the table putting forks back\n");
    put_forks(&philosophers[0]);
    printf("all forks should be ready in status above\n");

    printf("First and fourth philosopher getting forks\n");
    get_forks(&philosophers[0]);
    get_forks(&philosophers[1]);
    printf("Third fork should be available in status above\n");

    printf("Putting back fourth philospher forks\n");
    put_forks(&philosophers[1]);

    printf("Putting back first philospgher forks\n");
    put_forks(&philosophers[0]);

    //clean mutex
    cleanup();

    return 0;
}
#include "problem2.h"

struct node *list_head;

void *delete(void *i)
{
    // get thread's id
    int *id = (int *) i;

    // if there's only the head, we don't delete
    if(total_count > 1)
    {
        // lock the rw lock for writing, this waits until all rd threads finish
        pthread_rwlock_wrlock(&lock);

        struct node *head = list_head;
        struct node *temp;

        // get random element to remove
        srand(time(NULL));
        int random_element = rand() % (total_count-1);

        printf("%d delete thread deleting\n", *id);
        num_deleting = 1;

        // deletes head
        if(random_element == 0 && head != NULL)
        {
            temp = head->next;
            free(list_head);
            list_head = temp;
            total_count--;
        } 
        // deletes tail
        else if(random_element == total_count-1)
        {
            if(total_count > 2)
            {
                while(head->next->next != NULL)
                {
                    head = head->next;
                }
                temp = head->next;
                head->next = NULL;
                free(temp);
                total_count--;
            } else {
                temp = head->next;
                head->next = NULL;
                free(temp);
                total_count--;
            }
            
        } 
        //deletes inner element
        else {
            int i=0;
            for(i=0; i<random_element; i++)
            {
                head = head->next;
            }

            if(head->next != NULL)
            {
                temp = head->next;
                head->next = temp->next;
                free(temp);
            } else {
                free(head->next);
                head->next = NULL;
            }

            total_count--;
        }

        num_deleting = 0;
        pthread_rwlock_unlock(&lock);
    }
    printf("%d delete thread ended\n", *id);
    
}

void *insert(void *i)
{
    int *id = (int *) i;

    if(!num_inserting)
    {
        pthread_rwlock_rdlock(&lock);
        pthread_mutex_lock(&i_lock);

        num_inserting++;
        printf("%d insert thread inserting\n", *id);

        srand(time(NULL));
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data = rand() % 20;
        new_node->next = NULL;

        struct node *head = list_head;

        while(head->next != NULL)
        {
            head = head->next;
        }
        head->next = new_node;

        total_count++;

        num_inserting--;

        pthread_mutex_unlock(&i_lock);
        pthread_rwlock_unlock(&lock);
    }
    printf("%d insert thread ended\n", *id);
}

void *search(void *i)
{
    int *id = (int *) i;

    if(!num_deleting)
    {
        pthread_rwlock_rdlock(&lock);
        printf("%d search thread searching\n", *id);

        srand(time(NULL));
        int random_element = rand() % 20;
        int found = 0;

        struct node *head = list_head;

        int i=0;
        while(head != NULL)
        {
            if(head->data == random_element)
            {
                found = 1;
                break;
            }
            head = head->next;
        }

        if(found)
        {
            printf("element %d found in list\n", random_element);
        }
        else {
            printf("element %d not found in list\n", random_element);
        }

        pthread_rwlock_unlock(&lock);
    }
    printf("%d search thread ended\n", *id);
}

void create_random_list()
{
    struct node *head = list_head;

    int i=0;
    for(i=0; i<LIST_SIZE; i++)
    {
        if(i < LIST_SIZE-1)
        {
            head->next = malloc(sizeof(struct node));
        }else {
            head->next = NULL;
        }
        head->data = rand() % 20;
        head = head->next;
        total_count++;
    }
}

void clear_list()
{
    struct node *temp;

    while(list_head != NULL)
    {
        temp = list_head->next;
        free(list_head);
        list_head = temp;
    }
}

int main()
{
    srand(time(NULL));

    list_head = malloc(sizeof(struct node));
    total_count = 0;
    create_random_list();

    num_searching = 0;
    num_inserting = 0;
    num_deleting = 0;

    pthread_mutex_init(&i_lock, NULL);
    pthread_rwlock_init(&lock, NULL);
    
    int i=0;
    for(i=0; i < THREAD_MAX; i++)
    {
        pthread_create(&ins[i], NULL, insert, &i);
        pthread_create(&sea[i], NULL, search, &i);
        pthread_create(&del[i], NULL, delete, &i);
    }

    for (i = 0; i < THREAD_MAX; i++)
	{
		pthread_join(ins[i], NULL);
        pthread_join(sea[i], NULL);
        pthread_join(del[i], NULL);
	}

    clear_list();
    pthread_mutex_destroy(&i_lock);
    pthread_rwlock_destroy(&lock);
    
    return 0;
}

#include "problem2.h"

struct node *list_head;

int (*rand_generator)(unsigned int*);

int GetRandomViaRDRAND(unsigned int* pResult)
{
    return (_rdrand32_step(pResult) != 0);
}

int GetRandomViaMT(unsigned int* pResult)
{
    *pResult = (int)genrand_int32();

    return 1;
}

/* code taken from class materials to see if computer uses rdrand */
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
		/* use rdrand */
        printf("using rdrand\n");
        rand_generator = &GetRandomViaRDRAND;
	}
	else{
		/* use mt19937 */
        printf("using mt19937\n");
        rand_generator = &GetRandomViaMT;
	}
}

int GetsRandomValueInDesiredRange(int *val, int shift, int add)
{
    if((*rand_generator)(val))
    {
        if(*val < 0)
        {
            *val += -(*val);
        }
        /* shift bit and add to get the random value in the proper range */
        *val = (*val >> shift) + add;
        return (*val);
    }
    return -1;
}

void *delete(void *i)
{
    while(1)
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
            int temp_num;

            // get random element to remove
            int random_element;
            if(total_count <= 1)
            {
                random_element = 0;
            }else {
                temp_num = 16-total_count;
                GetsRandomValueInDesiredRange(&random_element, 27, temp_num);
                //random_element = rand() % (total_count-1);
            };

            printf("%d delete thread: deleting\n", *id);
            num_deleting = 1;

            GetsRandomValueInDesiredRange(&temp_num, 29, 0);
            sleep(temp_num);

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
            printf("%d delete thread: ended\n", *id);
        }
    }
    
}

void *insert(void *i)
{
    while(1)
    {
        int *id = (int *) i;

        if(!num_inserting)
        {
            pthread_rwlock_rdlock(&lock);
            pthread_mutex_lock(&i_lock);

            num_inserting=1;
            printf("%d insert thread: inserting\n", *id);

            int temp;
            
            struct node *new_node = malloc(sizeof(struct node));
            GetsRandomValueInDesiredRange(&temp, 27, 4);
            new_node->data = temp;
            new_node->next = NULL;

            struct node *head = list_head;

            while(head->next != NULL)
            {
                head = head->next;
            }
            head->next = new_node;

            total_count++;

            num_inserting=0;

            pthread_mutex_unlock(&i_lock);
            pthread_rwlock_unlock(&lock);
            GetsRandomValueInDesiredRange(&temp, 28, 0);
            sleep(temp);
            printf("%d insert thread: ended\n", *id);
        } else {
            printf("%d insert thread: there's a thread already inserting, now waiting \n", *id);
            int temp;
            GetsRandomValueInDesiredRange(&temp, 28, 1);
            sleep(temp);
        }
    }
}

void *search(void *i)
{
    while(1)
    {
        int *id = (int *) i;
            pthread_rwlock_rdlock(&lock);
            printf("%d search thread: searching\n", *id);

            int temp;
            GetsRandomValueInDesiredRange(&temp, 28, 2);
            sleep(temp);
            int random_element;
            GetsRandomValueInDesiredRange(&random_element, 27, 4);
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
                printf("%d search thread: element %d found in list\n", *id, random_element);
            }
            else {
                printf("%d search thread: element %d not found in list\n", *id, random_element);
            }

            pthread_rwlock_unlock(&lock);
        
        printf("%d search thread: ended\n", *id);
    }
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
        int temp;
        GetsRandomValueInDesiredRange(&temp, 27, 4);
        head->data = temp;
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

    list_head = malloc(sizeof(struct node));
    total_count = 0;
    rdrand_check();
    create_random_list();

    num_searching = 0;
    num_inserting = 0;
    num_deleting = 0;

    pthread_mutex_init(&i_lock, NULL);
    pthread_rwlock_init(&lock, NULL);
    
    int i=0;
    for(i=0; i < THREAD_MAX; i++)
    {
        int *num = malloc(sizeof(int));
        *num = i;
        pthread_create(&ins[i], NULL, insert, num);
        pthread_create(&sea[i], NULL, search, num);
        pthread_create(&del[i], NULL, delete, num);
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

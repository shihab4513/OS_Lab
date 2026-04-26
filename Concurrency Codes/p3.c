#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include <stdbool.h>
#define N 10
#define K 6

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_shuttle_arrived = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_student_boraded = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_queue_open = PTHREAD_COND_INITIALIZER;
int waiting_count = 0;
bool shuttle_arrived = false;

void  shuttle_func


void depart()
{
    printf("Shuttle is departing\n");
}

void board(int id)
{
    printf("Student id %d boarded shuttle\n", id);
}

void *shuttle_func(void *arg)
{   
    pthread_mutex_lock(&m);
    

    pthread_mutex_unlock(&m);
    return NULL;
}


void *student_func(void *arg)
{   
    int* id = (int *)arg;

    pthread_mutex_lock(&m);

    while(shuttle_arrived)
    {
        pthread_cond_wait(&cv_queue_open, &m);
    }

    waiting_count++;
    
    while(!shuttle_arrived)
    {
        pthread_cond_wait(&cv_shuttle_arrived, &m);
    }
    board(*id);
    pthread_cond_signal(&cv_student_boraded);

    pthread_mutex_unlock(&m);

    free(id);

    return NULL;
}


int main()
{
    pthread_t shuttle, students[N];

    pthread_create(&shuttle, NULL, shuttle_func, NULL);
    for(int i=0; i<6; i++)
    {
        int *id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&students[i], NULL, student_func, id);
    }

    pthread_join(shuttle, NULL);
    for(int i=0; i<6; i++)
    {
        pthread_join(students[i], NULL);
    }

    return 0;
}
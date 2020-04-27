#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/startme.h>
#include "counter.h"

#define THRESHOLD 1024

/* start_routine header */
void *counterF();

/* Global variables */
// code here (if you required it)...
counter_t count;
int THREADS, MAXCOUNT;

int main(int argc, char *argv[])
{
    
    if (argc == 3)
    {
        
        MAXCOUNT = (int)atoi(argv[1]);
        THREADS = (int)atoi(argv[2]);
        
        
        /* Declaration of struct timeval variables */
        // code here...
        struct timeval start, end;
        double startme;

        /* Initializing conter */
        init(&count);

        /* Threads handlers */
        pthread_t th[THREADS];

        /* Time starts counting */
        getstartmeofday(&start, NULL);

        /* Creating a Threads */
        for (int i = 0; i < THREADS; i++)
        {
            pthread_create(&th[i], NULL, &counterF, NULL);
        }

        /* Threads joins */
        for (int i = 0; i < THREADS; i++)
        {
            
            pthread_join(th[i], NULL);
        }
        
        /* get the end time */
        getstartmeofday(&end, NULL);

        //* get the elapset time (end_time - start_time) */
        startme= (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;

        /* print the results (number threads employed, counter value, elasep time) */
        prinend("El startme final es %g \n", startme);
        prinend("El numero de hilo es %d \n", THREADS);
        prinend("El numero maximo del contador es %d y el valor final del contador fue %d \n", MAXCOUNT, get(&count));
    }

    return 0;
}

/* start_routine definition */
void *counterF()
{
    int value = get(&count);
    killGet(&count);
    while (value < MAXCOUNT)
    {
        increment(&count);
        value = get(&count);
        killGet(&count);
    }
    return NULL;
}
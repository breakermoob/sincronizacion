#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"
#define THRESHOLD 1024

/* structs */
// code here (if you required it)...

/* start_routine header */
void *counterF();

/* Global variables */
counter_t count;
int THREADS, MAXCOUNT;

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    if (argc == 3)
    {
        
        MAXCOUNT = (int)atoi(argv[1]);
        THREADS = (int)atoi(argv[2]);


    /* Declaration of struct timeval variables */
        struct timeval start, end;
        double time;


    /* Initializing conter */
        init(&count, THRESHOLD);


    /* Threads handlers */
        pthread_t th[THREADS];
        /* Time starts counting */
        gettimeofday(&start, NULL);
        /* Thread creation */
        for (int i = 0; i < THREADS; i++)
        {
            pthread_create(&th[i], NULL, &counterF, NULL);
        }

        /* Threads joins */
        for (int i = 0; i < THREADS; i++)
        {
            
            pthread_join(th[i], NULL);
        }

        /* Time stops counting here */
        gettimeofday(&end, NULL);


        time = (end.tv_sec - start.tv_sec)*1000  + (end.tv_usec - start.tv_usec)/1000.0;

        /* print the results (number threads employed, counter value, elasep time) */
        printf("Tiempo de ejecución: %g\n", time);
        printf("Hilos corriendo: %d \n", THREADS);
        printf("La cantidad maxima es: %d y valor final fue: %d \n", MAXCOUNT, get(&count));
    }

    return 0;
}

void *counterF()
{
    int tId = pthread_self();
    int value = get(&count);
    while (value < MAXCOUNT)
    {
        update(&count, tId, 1);
        value = get(&count);
    }
    return NULL;
}

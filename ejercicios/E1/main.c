#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval ti, tf, start,end, i, f;
    double tiempo;

    gettimeofday(&ti, NULL);
    printf("Presiona Enter\n");
    getchar();
    gettimeofday(&tf, NULL);
    tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
    printf("Tiempo de inicio: %g \n", ti.tv_usec);
    printf("Tiempo tiempo de finalización: %g \n", tf.tv_usec);
    printf("%g milisegundos de diferencia.\n",tiempo);

    gettimeofday(&i, NULL);
    gettimeofday(&f, NULL);
    tiempo= (f.tv_sec - i.tv_sec)*1000 + (f.tv_usec - i.tv_usec)/1000.0;
    printf("El tiempo minimo es: %ld\n", tiempo);

    gettimeofday(&start, NULL);
    printf("Calculando tiempo de un printf...\n");
    gettimeofday(&end, NULL);
    tiempo= (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
    printf("El tiempo minimo es %g milisegundos\n", tiempo);

}
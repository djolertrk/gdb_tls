#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 5

int __thread foo = 0xdeadbeef;

void* thread(void *in) {
        int *tmp = (int *)in;
        int value = *tmp;
        foo += *tmp;
        while (1) {
                sleep(10);
        }
}

int main(void) {

        pthread_t threads[NUMBER_OF_THREADS];
        int i;
        for (i=0; i<NUMBER_OF_THREADS; i++) {
                pthread_create(&threads[i], NULL,
                               thread,&i);
        }

        abort();
}
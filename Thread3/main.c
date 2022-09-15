#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void* thread_main(void *arg);
int sum = 0;
int main() {
    pthread_t t_id1, t_id2;
    int thread_param1 = 0;
    int thread_param2 = 5;
    void * thr_ret1;
    void * thr_ret2;
    pthread_create(&t_id1, NULL, thread_main, (void*)&thread_param1);
    pthread_create(&t_id2, NULL, thread_main, (void*)&thread_param2);
    if (pthread_join(t_id1, &thr_ret1) != 0 && pthread_join(t_id2, &thr_ret2) != 0) {
        puts("pthread_join() error");
        return -1;
    }
    printf("res = %d", sum);
    return 0;
}

void* thread_main(void *arg) {
    int start = *(int *)arg;
    printf("start = %d\n", start);
    for (int i = start + 1; i <= start + 5; i++) {
        sum += i;
    }
    return NULL;
}

/*
#include <stdio.h>
#include <pthread.h>
void * thread_summation(void *arg);
int sum = 0;
int main(int argc, char *argv[]) {
    pthread_t id_t1, id_t2;
    int range1[] = {1, 5};
    int range2[] = {6,10};
    pthread_create(&id_t1, NULL, thread_summation, (void *)range1);
    pthread_create(&id_t2, NULL, thread_summation, (void *)range2);

    pthread_join(id_t1, NULL);
    pthread_join(id_t2, NULL);
    printf("result: %d \n", sum);
    return 0;
}

void * thread_summation(void * arg) {
    int start = ((int*)arg)[0];
    int end = ((int*)arg)[1];
    while (start <= end) {
        sum += start;
        start++;
    }
    return NULL;
}
*/

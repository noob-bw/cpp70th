#include <my_header.h>

// thread
void* start_routine(void *arg) {
    printf("thread create success.tid:%ld\n", pthread_self());
    pthread_exit(NULL);
    printf("tread have eixted.\n");
}

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // in this programe, test and leran the basic operations of threads

    // create a thread
    pthread_t tid;
    pthread_create(&tid, NULL, start_routine, (void*)NULL);

    /* sleep(1); */

    // pthread_join会阻塞等待未结束的线程
    pthread_join(tid, (void**)NULL);
    return 0;
}


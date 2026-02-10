#include <my_header.h>

void* sum_till(void* arg) {
       for (int i=0; i <= 1000000; ++i) {
        *(long int*)arg += i;
    }
    pthread_exit(arg);    // (void*)ans;
}

// 竞态条件
/* Usage:  */
int main(int argc, char *argv[]){                                  
    pthread_t tid1, tid2;
    long int *value = calloc(1, sizeof(long int));
    pthread_create(&tid1, NULL, sum_till, (void*)value);
    pthread_create(&tid2, NULL, sum_till, (void*)value);

    // 获取它们的结果
    pthread_join(tid1, (void**)(&value));
    pthread_join(tid2, (void**)(&value));
    
    printf("the num of the thread1:%ld\n", *value);
    printf("the num of the thread2:%ld\n", *value);
    
    return 0;
}


#include "my_header.h"

int counter = 0;
pthread_mutex_t mutex;

void* thread_func(void* arg) {
    // TODO: 实现加锁的累加操作
    for (int i=0; i<100000; i++) {
        pthread_mutex_lock(&mutex);
        ++counter;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    // TODO: 
    // 1. 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);
    // 2. 创建3个线程
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1, NULL, thread_func, NULL);
    pthread_create(&tid2, NULL, thread_func, NULL);
    pthread_create(&tid3, NULL, thread_func, NULL);
    // 3. 等待线程结束
    pthread_join(tid1, (void**)NULL);
    pthread_join(tid2, (void**)NULL);
    pthread_join(tid3, (void**)NULL);
    // 4. 打印结果
    printf("counter:%d\n", counter);
    // 5. 销毁互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}

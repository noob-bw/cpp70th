#include <my_header.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int init_done = 0; // 初始化完成标志

void* init_thread(void* arg) {
    printf("子线程：开始初始化...\n");
    sleep(2);
    printf("子线程：初始化完成！\n");
    
    // TODO: 1. 加锁
    pthread_mutex_lock(&mutex);
    // TODO: 2. 设置 init_done = 1
    sleep(10);
    init_done = 1;
    // TODO: 3. signal 通知主线程
    pthread_cond_signal(&cond);
    // TODO: 4. 解锁
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, init_thread, NULL);
    
    pthread_mutex_lock(&mutex);
    // TODO: 用 while 检查 init_done，若未完成则 wait
    while (init_done) {
        pthread_cond_wait(&cond, &mutex);
    }
    // TODO: wait 返回后，打印“主线程收到通知”
    pthread_mutex_unlock(&mutex);
    
    pthread_join(tid, NULL);
    printf("主线程：继续执行后续任务\n");
    return 0;
}
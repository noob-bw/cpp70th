#include <my_header.h>

typedef struct {
    int id;
    int money;
} Account;

Account acct1 = {1, 100};

pthread_mutex_t mutex;

void cleanup_func(void *arg) {
    pthread_mutex_unlock(&mutex);
    return;
}

void* pthread_func(void *arg) {
    // 去acct账号上取100
    pthread_mutex_lock(&mutex);
    pthread_cleanup_push(cleanup_func, NULL);
    if (acct1.money >= 100) {
        acct1.money -= 100;
        printf("进程 %ld 取钱成功。\n", pthread_self());
    }
    else {
        printf("进程 %ld 取钱失败。\n", pthread_self());
    }
    pthread_mutex_unlock(&mutex);
    pthread_cleanup_pop(1);
}

int main(void) {
    // 初始化mutex
    pthread_mutex_init(&mutex, NULL);

    // 创建10个线程
    pthread_t tid[10];
    for (int i=0; i<10; ++i) {
        pthread_create(&tid[i], NULL, pthread_func, NULL);
    }

    // 主线程等待各个子线程结束。
    for (int i=0; i<10; ++i) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}

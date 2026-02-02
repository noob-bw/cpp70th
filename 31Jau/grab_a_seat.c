#include <my_header.h>
// 模拟一个"抢座位"的场景
// 有5个座位,10个人(线程)同时去抢座位。

pthread_mutex_t seats[5];    // 5把锁代表5个座位

void* person_thread(void* arg) {
    // 开始抢座位
    long person_id = (long)arg;
    for (int i=0; i<5; i++) {
        int err = pthread_mutex_trylock(&seats[i]);
        if (err == 0) {
            printf("线程 %ld 抢到了座位 %d。\n", person_id, i);
            sleep(3);   // 座3秒
            pthread_mutex_unlock(&seats[i]);
            return NULL;
        }
        else {
            printf("线程 %ld 没抢到座位 %d ,继续尝试其他座位.\n", person_id, i);
        }
    }
    return NULL;
}

/* Usage:  */
int main(int argc, char *argv[]){                                  
    for (int i=0; i<5; ++i) {
        pthread_mutex_init(&seats[i], NULL);
    }
    // 创建10个进程
    pthread_t tid[10];
    for (int i=0; i<10; ++i) {
        pthread_create(&tid[i], NULL, person_thread, (void*)(long)i);
    }

    // 等待进程结束
    for (int i=0; i<10; ++i) {
        pthread_join(tid[i], NULL);
    }

    for (int i=0; i<5; ++i) {
        pthread_mutex_destroy(&seats[i]);
    }
    return 0;
}


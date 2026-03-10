#include <my_header.h>

typedef struct {
    int id;
    int balance;
    // 细粒度锁
    pthread_mutex_t mutex;
} Account;



Account acct1 = {1, 100, PTHREAD_MUTEX_INITIALIZER};
Account acct2 = {2, 900, PTHREAD_MUTEX_INITIALIZER};
pthread_mutex_t Protection = PTHREAD_MUTEX_INITIALIZER;

// 破坏持有并等待
// int transfer(Account* acctA, Account* acctB, int money)
// {
//     // acctA 转账给 acct B
//     // money 是互斥资源,
//     pthread_mutex_lock(&Protection);
//     pthread_mutex_lock(&acctA->mutex);
//     pthread_mutex_lock(&acctB->mutex);
//     pthread_mutex_unlock(&Protection);

//     sleep(1);
//     acctA->balance -= money;
//     acctB->balance += money;

//     pthread_mutex_unlock(&acctB->mutex);
//     pthread_mutex_unlock(&acctA->mutex);
// }

// 破坏不能抢占
// int transfer(Account *acctA, Account *acctB, int money) {
//     while (1) {
//         pthread_mutex_lock(&acctA->mutex);
//         sleep(1);
//         int err = pthread_mutex_trylock(&acctB->mutex);
//         if (err) {
//             // 没有拿到锁
//             pthread_mutex_unlock(&acctA->mutex);
//             // 等待随机几秒，避免同时争抢
//             sleep(rand()%5);
//             continue;
//         } else {
//             // 拿到了
//         acctA->balance -= money;
//         acctB->balance += money;

//         pthread_mutex_unlock(&acctB->mutex);
//         pthread_mutex_unlock(&acctA->mutex);
//         return NULL;
//         }
//     }
//     return NULL;
// }

// 破坏循环等待
int transfer(Account* acctA, Account* acctB, int money) {
    // 只先拿id靠前得
    if (acctA->id < acctB->id) {
        pthread_mutex_lock(&acctA->mutex);
        pthread_mutex_lock(&acctB->mutex);
    } else {
        pthread_mutex_lock(&acctB->mutex);
        pthread_mutex_lock(&acctA->mutex);
    }

    acctA->balance -= money;
    acctB->balance += money;

    pthread_mutex_unlock(&acctB->mutex);
    pthread_mutex_unlock(&acctA->mutex);

}


void *pthread_A(void *arg) {
    // acct1 转账给 acct2，参数为转账金额
    int money = (int)arg;
    transfer(&acct1, &acct2, money);
    return NULL;
}

void *pthread_B(void *arg) {
    // acct2 转账给 acct1，参数为转账金额
    int money = (int)arg;
    transfer(&acct2, &acct1, money);
    return NULL;
}

int main(int argc, char *argv[]) {
    // 创建两个线程
    pthread_t tid1, tid2;
    // 线程1：acct1 转账给 acct2
    pthread_create(&tid1, NULL, pthread_A, 50);
    // 线程2：acct2 转账给 acct1
    pthread_create(&tid2, NULL, pthread_B, 70);

    // 回收线程
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("id: %d, balance: %d\n", acct1.id, acct1.balance);
    printf("id: %d, balance: %d\n", acct2.id, acct2.balance);

    return 0;
}
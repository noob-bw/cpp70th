#include <my_header.h>

void* sum_till(void* arg) {
    int *ans=(int *)malloc(sizeof(int));
    long int sum = 0;
    for (int i=*((long int*)arg); i <= 1000000; ++i) {
        sum += i;
    }
    *ans = sum;
    pthread_exit((void*)ans);    // (void*)ans;
}

/* Usage:  */
int main(int argc, char *argv[]){                                  
    pthread_t tid1, tid2;
    int num1=1,num2=50000;
    pthread_create(&tid1, NULL, sum_till, (void*)&num1);
    pthread_create(&tid2, NULL, sum_till, (void*)&num2);

    // 获取它们的结果
    long int *sum1 = NULL,*sum2 = NULL;
    pthread_join(tid1, (void**)(&sum1));
    pthread_join(tid2, (void**)(&sum2));
    
    printf("the num of the thread1:%ld\n", *sum1);
    printf("the num of the thread2:%ld\n", *sum2);
    
    return 0;
}


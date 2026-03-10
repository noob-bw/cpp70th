#pragma once 

#include <my_header.h>

typedef struct {
    pthread_cond_t cond;
    pthread_mutex_t mutex;

    // 只能取值0或1。0表示资源已被获取，目前不可用；1表示资源未被获取，目前可用。
    int value; 
} BSem;

// API
// value只能取值0或1
void bsem_init(BSem* bsem, int value);

// 当资源不可用时，调用bsem_wait()等待资源；当bsem_wait()返回时，已获取了资源。
void bsem_wait(BSem* bsem);

// 当不再需要资源时，调用bsem_post()释放资源，并通知至少一个等待该资源的线程。
void bsem_post(BSem* bsem);

// 当不再需要资源时，调用bsem_post()释放资源，并通知所有等待该资源的线程。
void bsem_postall(BSem* bsem);

// 将资源置为不可用状态
void bsem_reset(BSem* bsem);

// 销毁二元信号量
void bsem_destroy(BSem* bsem);


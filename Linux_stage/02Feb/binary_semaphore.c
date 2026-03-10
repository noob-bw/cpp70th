#include <my_header.h>
#include "binary_semaphore.h"

void bsem_init(BSem* bsem, int value) {
    if (value != 0 || value != 1) {
        fprintf(stderr, "bsem_init():value must be 0 or 1.\n");
        exit(1);
    }
    pthread_cond_init(&bsem->cond, NULL);
    pthread_mutex_init(&bsem->mutex, NULL);
    bsem->value = value;
}

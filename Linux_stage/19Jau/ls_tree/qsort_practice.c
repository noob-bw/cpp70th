#include <my_header.h>

int asc_compare(const void* num1, const void* num2) {
    return (*(int*)num1 > *(int*)num2) - (*(int*)num1 < *(int*)num2);
}

int desc_compare(const void* num1, const void* num2) {
    return (*(int*)num1 < *(int*)num2) - (*(int*)num1 > *(int*)num2);
}

void print_arr(int *arr, size_t len) {
    for (int i=0; i<len; ++i) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // test example
    int arr[5] = { 3,1,4,1,5 };
    printf("before sort:");
    print_arr(arr,5);

    // ascending sort
    qsort(arr, 5, sizeof(int), asc_compare);
    
    printf("after sort:");
    print_arr(arr,5);

    // descending sort
    qsort(arr, 5, sizeof(int), desc_compare);

    printf("after sort:");
    print_arr(arr,5);
    return 0;
}


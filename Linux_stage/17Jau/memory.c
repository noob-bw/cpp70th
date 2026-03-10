#include <stdio.h>
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int main(void) {
    int nums[] = {10, 20, 30, 40, 50};
    char* strs[] = {"abc", "123", "hello", "777", "666"};
    int nums_len = ARR_SIZE(nums); 
    int strs_len = ARR_SIZE(strs);

    // 断点可以打在这里下面然后用于查看内存
    return 0;
}

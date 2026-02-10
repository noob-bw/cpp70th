#include <stdio.h>

/*
    双索引分区方法: 单向分区法
    用索引来模拟指针的作用
    思路:
    1.初始化第一个索引idx,用来遍历整个数组,idx从0开始
    2.再初始化一个索引odd_loc,从0开始,用来指示下一个奇数应该放置的位置
    3.在idx索引遍历数组的过程中,只要idx索引找到一个奇数,那就和odd_loc位置的元素交换
    4.当idx遍历完整个数组时,所有的奇数就都被交换到前面去了

    优点: 遍历数组的次数更少效率更高, 不占用额外的临时空间
    缺点: 相对没那么好理解, 分区后改变了元素的相对位置，是一个不稳定的分区算法
    但和上面的双指针分区稍有区别的是: 奇数部分相对位置是可以保证的
*/
void separate_odd_even(int arr[], int len) {
    int odd_idx = 0;
    for (int idx = 0; idx < len; idx++) {   // idx索引用于遍历数组
        if (arr[idx] % 2 != 0) {    
            // idx索引找到了一个奇数,就和odd_loc位置的元素交换
            if (idx != odd_idx) {
                int tmp = arr[idx];
                arr[idx] = arr[odd_idx];
                arr[odd_idx] = tmp;
            }
            odd_idx++;
        }
    }
}

int main(void) {
    int arr[] = { 1, 10, 22, 3, 132, 42, 23, 324, 5, 645, 10, 222 };
    int len = sizeof(arr) / sizeof(arr[0]);
    separate_odd_even(arr, len);
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

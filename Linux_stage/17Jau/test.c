#include <stdio.h>
int main(void){
    int *p = NULL;
    ++*p;       // 解引用空指针         
    return 0;
}


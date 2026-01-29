#include <my_header.h>

int compare(const void* str1, const void* str2) {
    const char *stra = *(const char**)str1;
    const char *strb = *(const char**)str2;

    int x = tolower(stra[0]);
    int y = tolower(strb[0]);
    return ((x-y)>0) - ((x-y)<0);
}

/* Usage:  */
int main(int argc, char *argv[]){                                  
    char *str[3] = { "banana","Apple","cheery" };
    for (int i=0; i<3; ++i) {
        printf("%s\n", str[i]);
    }

    qsort(str, 3, sizeof(char*), compare);
    
    for (int i=0; i<3; ++i) {
        printf("%s\n", str[i]);
    }
    return 0;
}


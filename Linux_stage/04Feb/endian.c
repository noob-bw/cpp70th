#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    long int num = 0x12345678;

    char *c = (char*)num;
    char *cur = c;
    for (int i=0; cur[i]; ++i) {
        printf("%c ", cur[i]);
    }
    return 0;
}


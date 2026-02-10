#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    int fd = open("1.txt", O_RDONLY);
    ERROR_CHECK(fd, -1, "open");

    printf("pos:%ld\n", lseek(fd, 0, SEEK_END));

    return 0;
}


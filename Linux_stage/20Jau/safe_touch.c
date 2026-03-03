#include <my_header.h>

/* Usage:./safe_touch 1.txt  */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    int fd = open(argv[1], O_CREAT | O_EXCL, 0600);
    ERROR_CHECK(fd, -1, "open failed");

    close(fd);
    return 0;
}


#include <my_header.h>

/* Usage:./my_cat 1.txt  */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc,2);
    
    int fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd, -1, "open failed");
    
    char buf[4096] = { 0 };
    int count = 0;
    while ((count = read(fd, buf, sizeof(buf))) != 0) {
        write(STDOUT_FILENO, buf, sizeof(buf));
    }

    close(fd);
    return 0;
}


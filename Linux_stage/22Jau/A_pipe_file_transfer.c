#include <my_header.h>

/* Usage: ./transfer pipe path */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);
    // transfer the path
    int pipe_fd = open(argv[1], O_WRONLY);
    ERROR_CHECK(pipe_fd, -1, "open");

    int ret = write(pipe_fd, argv[2], strlen(argv[2]));
    ERROR_CHECK(ret, -1, "write");

    close(pipe_fd);
    return 0;
}


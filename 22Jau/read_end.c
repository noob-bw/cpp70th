#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // open the pipe
    int pipe_fd = open("1.pipe", O_RDONLY);
    ERROR_CHECK(pipe_fd, -1, "open");

    while (1) {
        char buf[5] = { 0 };
        int ret = read(pipe_fd, buf, sizeof(buf));
        if (ret <= 0) {
            perror("read");
            exit(1);
        }
        printf("read:%s\n", buf);
        /* sleep(5); */
    }
    return 0;
}


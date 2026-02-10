#include <my_header.h>

int main(int argc, char *argv[]){                                  
    int pipe_fd = open("1.pipe", O_WRONLY|O_CREAT|O_TRUNC, 0664);
    ERROR_CHECK(pipe_fd, -1, "open");

    while (1) {
        int ret = write(pipe_fd, "helloworld", 5);
        printf("write a time\n");
        ERROR_CHECK(ret, -1, "write");
        sleep(5);
    }
    return 0;
}


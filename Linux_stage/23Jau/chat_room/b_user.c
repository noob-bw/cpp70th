#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // open the pipe
    int read_fd = open("1.pipe", O_RDONLY);
    ERROR_CHECK(read_fd, -1, "read end::read");
    int write_fd = open("2.pipe", O_WRONLY);
    if (write_fd == -1) {
        perror("read end::write");
        close(read_fd);
        exit(1);
    }

    printf("Welcome!\n");
    // process communicate
    while(1) {
        char buf[1024] = {0};
        // input in stdin
        printf("B:");
        ssize_t bytes_stdin = read(STDIN_FILENO, buf, sizeof(buf));
        if (bytes_stdin == 0) {
            printf("You have left the chat room.\n");
            break;
        }
        // output to A
        ssize_t bytes_write = write(write_fd, buf, bytes_stdin);
        ERROR_CHECK(bytes_write, -1, "write to pipe");

        // read from B
        bzero(buf, sizeof(buf));
        ssize_t betes_read = read(read_fd, buf, sizeof(buf));
        if (betes_read <= 0) {
            perror("read from pipe");
            break;
        }
        // output on screen
        printf("%s\n", buf);

    }
    return 0;
}


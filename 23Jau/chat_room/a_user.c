#include <my_header.h>

int main(int argc, char *argv[]){                                  
    // open the pipe
    int write_fd = open("1.pipe", O_WRONLY);
    ERROR_CHECK(write_fd, -1, "write end::write");
    int read_fd = open("2.pipe", O_RDONLY);
    if (read_fd == -1) {
        perror("write end::read");
        close(write_fd);
        exit(1);
    }

    printf("welcome!\n");
    // process communicate
    while (1) {
        char buf[1024] = {0};
        // input in stdin
        printf("A:");
        ssize_t bytes_stdin = read(STDIN_FILENO, buf, sizeof(buf));
        if (bytes_stdin == 0) {
            printf("You have left the chat room.\n");
            break;
        }
        // output to B
        ssize_t bytes_write = write(write_fd, buf, bytes_stdin);
        ERROR_CHECK(bytes_write, -1, "write to pipe");

        // read from A
        bzero(buf, sizeof(buf));
        ssize_t betes_read = read(read_fd, buf, sizeof(buf));
        if (betes_read <= 0) {
            perror("read from pipe");
            break;
        }
        // output on screen
        printf("%s\n", buf);


    }
    // recycling resources
    close(read_fd);
    close(write_fd);

    return 0;
}


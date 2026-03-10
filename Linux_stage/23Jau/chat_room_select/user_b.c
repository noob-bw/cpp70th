#include <my_header.h>

#define MAX_BUFFER_SIZE 1024
/* Usage:  */
int main(int argc, char *argv[]){                                  
    // open the PIPE
    int read_fd= open("1.pipe", O_RDONLY);
    ERROR_CHECK(read_fd, -1, "B::open read end");
    int write_fd= open("2.pipe", O_WRONLY);
    if (write_fd == -1) {
        perror("B::open write end");
        close(read_fd);
        exit(1);
    }

    // prepare a buffer
    char buf[MAX_BUFFER_SIZE];

    printf("Welcome to the chat room!\n");

    // create a monitor set
    fd_set monitor_set;
    while (1) {
        FD_ZERO(&monitor_set);
        FD_SET(STDIN_FILENO,&monitor_set);
        FD_SET(read_fd,&monitor_set);

        // start to monitor
        int ready_num = select(read_fd+1, &monitor_set, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &monitor_set)) {
            // initial buffer
            bzero(buf, sizeof(buf));
            printf("B:");
            // input in stdin and output them to screen, and then send it to PIPE
            int bytes_read = read(STDIN_FILENO, buf, sizeof(buf));
            if (bytes_read <= 0) {
                perror("read from pipe");
                printf("You have left the chat room!\n");
                break;
            }
            /* fgets(buf, sizeof(buf), stdin); */
            printf("%s", buf);
            write(write_fd, buf, strlen(buf));
        }
        if (FD_ISSET(read_fd, &monitor_set)) {
            bzero(buf, sizeof(buf));
            ssize_t bytes_read = read(read_fd, buf, sizeof(buf));
            if (bytes_read <= 0) {
                perror("read from pipe");
                break;
            }
            printf("A:%s\n", buf);
        }
    }
    close(read_fd);
    close(write_fd);
    return 0;
}


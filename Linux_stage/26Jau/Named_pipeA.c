#include <my_header.h>

/* Usage: /programe file_name */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);
    
    // open the pipe and a file to be send
    int write_fd = open("1.pipe", O_WRONLY);
    ERROR_CHECK(write_fd,-1, "open pipe");
    int read_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(read_fd, -1, "open file");

    char buf[1024] = { 0 };
    while (1) {
        bzero(buf, sizeof(buf));
        ssize_t bytes_read = read(read_fd, buf, sizeof(buf));
        if (bytes_read == 0) { break; }
        if (bytes_read < 0) { perror("read from file"); }
        ssize_t bytes_writen = write(write_fd, buf, bytes_read);
        ERROR_CHECK(bytes_writen, -1, "writen into pipe");
    }

    close(read_fd);
    close(write_fd);
    return 0;
}


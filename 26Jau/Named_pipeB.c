#include <my_header.h>

/* Usage: ./programe file_name */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    int read_fd = open("1.pipe", O_RDONLY);
    ERROR_CHECK(read_fd, -1, "open pipe");
    int write_fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0664);
    ERROR_CHECK(write_fd, -1, "open file");

    char buf[1024];
    while(1) {
        bzero(buf, sizeof(buf));
        ssize_t bytes_read = read(read_fd, buf, sizeof(buf));
        ERROR_CHECK(bytes_read, -1, "read from pipe");
        if (bytes_read == 0) { break; }
        ssize_t bytes_writen = write(write_fd, buf, bytes_read);
        ERROR_CHECK(bytes_writen, -1, "write in to file");
    }
    
    close(write_fd);
    close(read_fd);

    return 0;
}


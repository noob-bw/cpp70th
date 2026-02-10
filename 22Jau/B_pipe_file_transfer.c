#include <my_header.h>

/* Usage: ./transfer pipe */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    int pipe_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(pipe_fd, -1, "open");

    char path[256] = { 0 };
    int ret = read(pipe_fd, path, sizeof(path));
    if (ret <= 0) {
        perror("read");
        exit(1);
    }
    /* printf("read:%s\n", path); */

    // 处理读到的路径，用它来创建目录或文件
    // 先假设路径中只有路径
    ret = mkdir(path, 0775);
    ERROR_CHECK(ret, -1, "mkdir");

    close(pipe_fd);

    return 0;
}


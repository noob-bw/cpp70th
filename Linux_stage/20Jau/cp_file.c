#include <my_header.h>

/* Usage:./cp_file 1.txt 2.txt  */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);

    // 打开文件流
    int src_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open the first one failed");
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0775);
    if (dest_fd == -1) {
        close(src_fd);
        perror("open the second failed");
        exit(1);
    }

    // 复制文件
    char buf[8192];
    size_t count = 0;
    while ((count = read(src_fd, buf, 4096)) != 0) {
        write(dest_fd, buf, count);
    }

    // 关闭文件流
    close(src_fd);
    close(dest_fd);
    return 0;
}


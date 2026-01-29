#include <my_header.h>

/* Usage: ./to_upper [file_name] */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    // 打开文件
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "main::open");

    // 预留空间
    int ret = ftruncate(fd, 13); ERROR_CHECK(ret, -1, "main:: ftruncate");
    // 建立映射
    char *p = (char*)mmap(NULL, 13, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "main::mmap");

    // 操作
    for (int i=0; i<13; ++i) {
        p[i] = toupper(p[i]); 
    }

    // 关闭映射
    munmap(p,13);
    close(fd);
    return 0;
}


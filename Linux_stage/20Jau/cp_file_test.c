#include <my_header.h>

long long current_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000;
}

void copy_file(const char *src_path, const char * dest_path, size_t buf_size) {
    // 打开文件流
    int src_fd = open(src_path, O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open the first one failed");
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0775);
    if (dest_fd == -1) {
        close(src_fd);
        perror("open the second failed");
        exit(1);
    }

    // 复制文件
    char buf[8192];
    size_t count = 0;
    while ((count = read(src_fd, buf, buf_size)) != 0) {
        write(dest_fd, buf, count);
    }

    // 关闭文件流
    close(src_fd);
    close(dest_fd);
}

/* Usage:./cp_file 1.txt 2.txt  */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);
    
    long long time1 = current_time();
    copy_file(argv[1],argv[2], 128);
    long long time2 = current_time();
    copy_file(argv[1],argv[2], 256);
    long long time3 = current_time();
    copy_file(argv[1],argv[2], 512);
    long long time4 = current_time();
    copy_file(argv[1],argv[2], 1024);
    long long time5 = current_time();
    copy_file(argv[1],argv[2], 2096);
    long long time6 = current_time();

    printf("128 = %lld\n", (time2 - time1));
    printf("256 = %lld\n", (time3 - time2));
    printf("512 = %lld\n", (time4 - time3));
    printf("1024 = %lld\n", (time5 - time4));
    printf("2096 = %lld\n", (time6 - time5));

    return 0;
}


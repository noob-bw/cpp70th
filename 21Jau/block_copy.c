#include <my_header.h>

#define BLOCK_SIZE (1024*1024*8)

/* Usage: ./block_copy src dest */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);

    // 打开文件
    int src_fd= open(argv[1], O_RDONLY);
    ERROR_CHECK(src_fd, -1, "src open");
    int dest_fd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0664);
    if (dest_fd == -1) {
        perror("dest open");
        close(src_fd);
        exit(1);
    }

    // 获取源文件大小、占位
    struct stat sb;
    int ret = fstat(src_fd, &sb);
    ERROR_CHECK(ret, -1, "main::fstat");
    off_t src_size = sb.st_size;
    ret = ftruncate(dest_fd, src_size);
    ERROR_CHECK(ret, -1, "main::ftruncate");
    
    // 对空文件映射是非法的，单独处理
    if (src_size == 0) {
        close(src_fd);
        close(dest_fd);
        return 0;
    }

    // 传输
    off_t bytes_copied = 0;
    while (bytes_copied < src_size) {
        // 确认本次复制的大小
        off_t current_block_size = (BLOCK_SIZE > (src_size - bytes_copied) ? 
                                    (src_size - bytes_copied) :
                                    BLOCK_SIZE);

        // 映射源文件
        void *srcp = mmap(NULL, current_block_size, PROT_READ, MAP_SHARED, src_fd, bytes_copied);
        ERROR_CHECK(srcp, MAP_FAILED, "src mmap");
        // 映射目标文件
        void *destp = mmap(NULL, current_block_size, PROT_READ|PROT_WRITE, MAP_SHARED, dest_fd, bytes_copied);
        ERROR_CHECK(destp, MAP_FAILED, "dest mmap");

        // 开始传输
        memcpy(destp, srcp, current_block_size);

        // 关闭映射
        munmap(srcp, current_block_size);
        munmap(destp, current_block_size);
        
        // 更新已复制的字节数
        bytes_copied += current_block_size;
    }
    // 清理资源
    close(src_fd);
    close(dest_fd);

    return 0;
}


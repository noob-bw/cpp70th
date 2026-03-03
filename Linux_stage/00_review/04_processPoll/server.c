#include <my_header.h>

/* Usage: ./server hostname port */
// example: ./server 192.168.128.162 4399 
int main(int argc, char *argv[]){                                  
    // 假设这里是传入的字符串，默认有10个工作进程
    char *hostname = "127.0.0.1";
    char *post = "4399";

    // 创建 10 个工作进程
    pid_t pid;
    for (int i=0; i<10; ++i) {
        pid = fork();
        ERROR_CHECK(pid, -1, "fork");
        if (pid == 0) {
            // child process
            
        }
    }
    
    // 创建完成陷入死循环
    while(1);

    return 0;
}


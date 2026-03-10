#include <my_header.h>

/* Usage:  ./main 127.0.0.1 port workNum */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 4);

    // 1. 创建进程池
    //      1. 将传入的字符串 workNum 转换成 int
    //      2. 使用 fork() 创建好子进程
    int ProcessNum= 0;
    sscanf(argv[3], "%d", &ProcessNum);

    pid_t pid;
    for (int i=0; i<ProcessNum; ++i) {
        pid = fork();
        if (pid == 0) {
            // 执行子进程函数
            while (1) {
                sleep(1);
            }
        }

        // 父进程可以在这里记录子进程的状态之类的
    }

    // 2. 父进程和客户端进行连接
    //      1. getaddrinfo() 获取 ip 地址和端口
    //      2. 进行连接
    struct addrinfo hints, *ip;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family= AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int status = getaddrinfo(argv[1], argv[2], &hints, &ip);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo:%s\n", gai_strerror(status));
        return 1;
    }

    int sockfd = socket(ip->ai_family, ip->ai_socktype, 0);
    ERROR_CHECK(sockfd, -1, "socket");

    status = bind(sockfd, ip->ai_addr, ip->ai_addrlen);
    ERROR_CHECK(status, -1, "bind");

    status = listen(sockfd, ProcessNum);
    ERROR_CHECK(status, -1, "listen");

    int newfd = accept(sockfd, NULL, NULL);
    ERROR_CHECK(newfd, -1, "accept");

    printf("Connected.\n");

    // 3. 与子进程进行通信，将 sockfd 给子进程，使子进程直接与客户端进行通信
    //      1. 普通 Pipe 是字节流，无法传输文件描述符或者其他控制信息
    //         所以要使用socketpair创建本地套接字，以及sendmsg和recvmsg通过本地套接字传递文件描述符
    //      2. sockepari 创建本地套接字
    //      3. 使用 sendmsg 传递文件描述符
    

    return 0;
}


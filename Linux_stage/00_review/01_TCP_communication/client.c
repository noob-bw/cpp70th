#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // 1. 创建 socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");

    // 2. 开始连接
    char *ip = "127.0.0.1";
    int port = 666;
    unsigned int buf;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = buf;
    inet_pton(AF_INET, ip, &buf);
    int ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");

    // 3. 开始通讯
    char msg[128] = { 0 };
    ret = send(sockfd, "hello server!", 13, 0);
    ERROR_CHECK(ret, -1, "send");

    ret = recv(sockfd, msg, sizeof(msg), 0);
    ERROR_CHECK(ret, -1, "recv");
    printf("server:%s\n", msg);
    
    close(sockfd);

    return 0;
}


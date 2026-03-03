#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    
    // 1. 创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. 绑定 socket
    char *ip = "127.0.0.1";
    int port = 666;
    struct sockaddr_in addr;
    unsigned int buf;
    inet_pton(AF_INET, ip, &buf);
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = buf;
    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");
    
    // 3. listen 进入监听
    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");

    // 4. accept 建立连接
    socklen_t len;
    len = sizeof(struct sockaddr);
    int newfd = accept(sockfd, NULL, &len);
    ERROR_CHECK(newfd, -1, "accept");
    printf("newfd = %d\n", newfd);

    // 5. 开始通讯
    char msg[128] = { 0 };
    ret = recv(newfd, msg, sizeof(msg), 0);
    ERROR_CHECK(ret, -1, "recv");
    printf("client:%s\n", msg);

    ret = send(newfd, "hello client!", 13, 0);
    ERROR_CHECK(ret, -1, "send");
    
    close(newfd);
    close(sockfd);

    return 0;
}


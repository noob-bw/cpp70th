#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // 1. 建立连接
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");

    char *ip = "127.0.0.1";
    int port = 666;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    unsigned int netip;
    inet_pton(AF_INET, ip, &netip);

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = netip;

    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");

    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");

    int newfd = accept(sockfd, NULL, NULL);
    ERROR_CHECK(newfd, -1, "accept");

    
    char buf[128] = { 0 };
    fd_set rdset;
    // 使用 select 
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(newfd, &rdset);
        select(newfd+1, &rdset, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &rdset) != 0) {
            memset(buf, 0, sizeof(buf));
            ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret == 0) {
                break;
            }

            send(newfd, buf, sizeof(buf), 0);
        }
        else if (FD_ISSET(newfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recv(newfd, buf, sizeof(buf), 0);
            ERROR_CHECK(ret, -1, "recv");
            if (ret == 0) {
                printf("byebye\n");
                close(sockfd);
                close(newfd);
                return 0;
            }
            printf("client:%s\n", buf);
        }
    }
    close(newfd);
    close(sockfd);
    return 0;
}


#include <my_header.h>
#define MAX_EVENT 256

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // 模拟 argv[] 传来的参数
    char *hostname = "127.0.0.1";
    char *port = "4399";

    // 获取地址
    struct addrinfo hints, *ip;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int status = getaddrinfo(hostname, port, &hints, &ip);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo:%s\n", gai_strerror(status));
        return -1;
    }

    // 建立连接
    int sockfd = socket(ip->ai_family, ip->ai_socktype, ip->ai_protocol);
    ERROR_CHECK(sockfd, -1, "socket");
    status = connect(sockfd, ip->ai_addr, ip->ai_addrlen);
    ERROR_CHECK(status, -1, "connect");

    // 使用epoll
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    struct epoll_event event, evs[MAX_EVENT];
    // 将要监听的描述加入监听集合
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    status = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(status, -1, "EPOLL_CTL_ADD STDIN_FILENO");
    event.data.fd = sockfd;
    status = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    ERROR_CHECK(status, -1, "EPOLL_CTL_ADD sockfd");
    // 开始监听，执行逻辑
    int readyNum = 0;
    char buf[256] = { 0 };
    while (1) {
        readyNum = epoll_wait(epfd, evs, MAX_EVENT, -1);
        for (int i=0; i<readyNum; ++i) {
            bzero(buf, sizeof(buf));
            if (evs[i].data.fd == STDIN_FILENO) {
                read(STDIN_FILENO, buf, sizeof(buf));
                send(sockfd, buf, strlen(buf)-1, 0);
            } else if (evs[i].data.fd == sockfd) {
                status = recv(sockfd, buf, sizeof(buf), 0);
                if (status == 0) {
                    close(sockfd);
                    close(epfd);
                    return 0;
                }
                ERROR_CHECK(status, -1, "recv");
                printf("server:%s\n", buf);
            }
        }
    }
    close(sockfd);
    close(epfd);
    return 0;
}


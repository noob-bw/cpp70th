#include <my_header.h>
#define MAX_EVENTS 256

/* Usage:  */
int main(int argc, char *argv[]){                                  
    const char *hostname = "127.0.0.1";
    char *port = "4399";

    // 使用 getaddrinfo 获取地址
    struct addrinfo hints, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int ret = getaddrinfo(hostname, port, &hints, &res);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo error:%s\n", gai_strerror(ret));
        return -1;
    }

    // 建立连接
    int sockfd = socket(res->ai_family, res->ai_socktype, 0);
    ERROR_CHECK(sockfd, -1, "socket");

    ret = bind(sockfd, res->ai_addr, res->ai_addrlen);
    ERROR_CHECK(ret, -1, "bind");

    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");

    int newfd = accept(sockfd, NULL, NULL);
    ERROR_CHECK(newfd, -1, "accept");

    printf("connection established!\n");

    // 使用 epoll
    // 1. 创建epoll实例
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    // 2. 配置事件结构体
    struct epoll_event event, evs[MAX_EVENTS];
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_ctr_add STDIN_FILENO");
    event.events = EPOLLIN;
    event.data.fd = newfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, newfd, &event);
    ERROR_CHECK(ret, -1, "epoll_Ctr_add newfd");
    // 3. 注册文件描述符
    int readyNum = 0;
    char buf[256] = { 0 };
    while (1) {
        readyNum = epoll_wait(epfd, evs, MAX_EVENTS, -1);
        ERROR_CHECK(readyNum, -1, "epoll_wait");
        for (int i=0; i<readyNum; ++i) {
            if (evs[i].data.fd == STDIN_FILENO) {
                // 输入缓冲区来了数据
                bzero(buf, sizeof(buf));
                read(STDIN_FILENO, buf, sizeof(buf));
                send(newfd, buf, strlen(buf)-1, 0);
            } else if (evs[i].data.fd == newfd) {
                // 网络文件描述符来了数据
                bzero(buf, sizeof(buf));
                ret = recv(newfd, buf, sizeof(buf), 0);
                if (ret == 0) {
                    printf("byebye.\n");
                    close(sockfd);
                    close(newfd);
                    close(epfd);
                    return 0;
                }
                ERROR_CHECK(ret, -1, "recv");
                printf("client:%s\n", buf);
            }
        }
    }  
    close(sockfd);
    close(newfd);
    close(epfd);
    return 0;
}


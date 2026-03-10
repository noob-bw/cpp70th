#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");

    char *ip = "127.0.0.1";
    int port = 666;
    unsigned int netip = 0;
    inet_pton(AF_INET, ip, &netip);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = netip;
    int ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");

    char buf[128] = { 0 };
    fd_set rdset;
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockfd, &rdset);
        select(sockfd+1, &rdset, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret == 0) {
                break;
            }
            send(sockfd, buf, ret, 0);
        } else if (FD_ISSET(sockfd, &rdset)) {
            memset(buf, 0, sizeof(buf));
            ret = recv(sockfd, buf, sizeof(buf), 0);
            ERROR_CHECK(ret, -1, "recv");
            if (ret == 0) {
                break;
            }
            printf("server:%s\n", buf);
        }
    }
    close(sockfd);
    return 0;
}


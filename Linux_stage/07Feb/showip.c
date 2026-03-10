// 学习getaddrinfo的使用
#include <my_header.h>

/* Usage: ./showip.c postname  */
int main(int argc, char *argv[]){                                  
    // 输入合法检测
    if (argc != 2) {
        fprintf(stderr, "argc is invalid.\n");
        fprintf(stderr, "example: ./showip.c www.google.com\n");
        exit(1);
    }

    char ipstr[INET6_ADDRSTRLEN];
    
    // 设置hints
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // 调用getaddrinfo解析域名
    int status;
    struct addrinfo *res, *p;   // res接收结果链表，p遍历结果链表
    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        // 读取失败  
        fprintf(stderr, "getaddrinfo failed:%s\n",gai_strerror(status));
        exit(1);
    }

    // 成功遍历结果链表获取信息
    for (p=res; p!=NULL; p=p->ai_next) {
        char *ipver;
        void *addr;
        
        if (p->ai_family == AF_INET) {
            // IPV4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {
            // IPV6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // 转换并打印 IP
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("%s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res);
    return 0;
}


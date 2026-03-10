#include <my_header.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法: %s <域名>\n", argv[0]);
        exit(1);
    }

    struct addrinfo hints, *res, *p;
    char ipstr[INET6_ADDRSTRLEN];  // 足够容纳IPv6地址
    int status;

    // 1. 设置查询条件
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;      // 不限制IPv4或IPv6
    hints.ai_socktype = SOCK_STREAM;  // TCP套接字

    // 2. 执行域名解析
    printf("正在解析域名: %s\n", argv[1]);
    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo错误: %s\n", gai_strerror(status));
        exit(1);
    }

    // 3. 遍历结果链表
    printf("\n找到的IP地址:\n");
    printf("----------------------------------------\n");
    
    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        // 4. 根据地址族获取IP地址指针
        if (p->ai_family == AF_INET) {  // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {  // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // 5. 转换为可读字符串
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("  %s: %s\n", ipver, ipstr);
    }

    // 6. 释放内存
    freeaddrinfo(res);
    
    return 0;
}

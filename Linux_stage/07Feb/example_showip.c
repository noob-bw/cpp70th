// showip.c -- show IP addresses for a host given on the command line.
#include <my_header.h>
// showip.c
#define _GNU_SOURCE  // for glibc (optional)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

void print_sockaddr(const struct sockaddr *sa, socklen_t salen, const char *canonname) {
    char ipstr[INET6_ADDRSTRLEN];
    void *addr;
    const char *ipver;

    if (sa->sa_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)sa;
        addr = &(s->sin_addr);
        ipver = "IPv4";
    } else if (sa->sa_family == AF_INET6) {
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)sa;
        addr = &(s->sin6_addr);
        ipver = "IPv6";
    } else {
        printf("Unknown address family\n");
        return;
    }

    // 将二进制地址转为可读字符串
    if (inet_ntop(sa->sa_family, addr, ipstr, sizeof(ipstr)) == NULL) {
        perror("inet_ntop");
        return;
    }

    in_port_t port = (sa->sa_family == AF_INET)
        ? ((struct sockaddr_in *)sa)->sin_port
        : ((struct sockaddr_in6 *)sa)->sin6_port;

    printf("%s address: %s:%d", ipver, ipstr, ntohs(port));
    if (canonname) {
        printf(" (canonical name: %s)", canonname);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <hostname or IP> <port or service>\n", argv[0]);
        fprintf(stderr, "Example: %s www.google.com https\n", argv[0]);
        fprintf(stderr, "         %s 127.0.0.1 8080\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *hostname = argv[1];
    const char *service = argv[2];

    struct addrinfo hints = {0};
    hints.ai_family = AF_UNSPEC;    // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_CANONNAME;  // Request canonical name

    struct addrinfo *result, *rp;
    int ret = getaddrinfo(hostname, service, &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    printf("Resolved addresses for '%s' on service '%s':\n", hostname, service);
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        print_sockaddr(rp->ai_addr, rp->ai_addrlen, rp->ai_canonname);
    }

    freeaddrinfo(result); // 必须释放！
    return 0;
}

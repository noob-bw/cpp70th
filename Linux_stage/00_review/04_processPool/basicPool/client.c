#include <my_header.h>

/* Usage: ./client 127.0.0.1 port */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);

    struct addrinfo hints, *ip;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(argv[1], argv[2], &hints, &ip);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo:%s\n", gai_strerror(status));
        return 1;
    }

    int sockfd = socket(ip->ai_family, ip->ai_socktype, 0);
    ERROR_CHECK(sockfd, -1, "socket");

    status = connect(sockfd, ip->ai_addr, ip->ai_addrlen);
    ERROR_CHECK(status, -1, "connect");

    printf("Connected.\n");

    return 0;
}


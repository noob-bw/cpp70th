#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    char addr[INET_ADDRSTRLEN];
    inet_pton(AF_INET,"192.168.203.128", addr);
    bind(sock_fd, addr, INET_ADDRSTRLEN);
    return 0;
}


#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    int fd = open("1.txt", O_WRONLY|O_CREAT|O_TRUNC, 0775);
    ERROR_CHECK(fd, -1, "open");
    printf("123\n");

    int stdout_cp = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    printf("Hello world\n");
    
    dup2(stdout_cp, STDOUT_FILENO);
    printf("how are you?\n");

    dup2(fd, STDOUT_FILENO);
    printf("I'm fine");

    fflush(stdout);
    dup2(stdout_cp, STDOUT_FILENO);
    printf("thank you");
    return 0;
}


#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    pid_t pid = fork();

    if (pid == 0) {
        printf("This is child process.\n");
    }
    else if (pid > 0) {
        sleep(1);
        printf("This is parent process.\n");
    }

    return 0;
}


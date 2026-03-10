#include <my_header.h>

void handler(int sig) {
    switch(sig) {
    case SIGINT: printf("\nCought SIGINT,continue...");
                 break;
    case SIGQUIT:   printf("\nCought SIGQUIT,continue...");
                 break;
    case SIGSTOP:   printf("\nCought SIGSTOP,continue...");
                 break;
    }
}

// 使用signal函数捕获SIGINT,SIGQUIT,SIGSTP信号，学习signal的使用
int main(int argc, char *argv[]) {
    // 1. 分别捕获 SIGINT, SIGQUIT 和 SIGTSTP
    /* sighandler_t old_hander = signal(SIGINT, handler); */
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    signal(SIGSTOP, handler);


    /* ERROR_CHECK(old_hander, SIG_ERR, "signal"); */


    int counter = 0;
    for (;;) {
        usleep(100000);
        printf("\r%d", counter++);
        fflush(stdout);
    }
    return 0;
}

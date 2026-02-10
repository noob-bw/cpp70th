#include <my_header.h>
#include <signal.h>
#include <sys/types.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    // .test_kill signo pid ...
    if (argc < 2) {
        fprintf(stderr, "argc error\n");
        exit(1);
    }

    int sig;
    sscanf(argv[1], "%d" ,&sig);

    int pid;
    for (int i=2; i<argc; ++i) {
        sscanf(argv[i], "%d", &pid);
        int ret = kill(pid, sig);
        ERROR_CHECK(ret, -1, "kill");
    }
    return 0;
}


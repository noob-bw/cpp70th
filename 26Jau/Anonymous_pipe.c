#include <my_header.h>

/* Usage:  */
int main(int argc, char *argv[]){                                  
    int c_to_p[2];
    int p_to_c[2];
    int ret = pipe(c_to_p);
    ERROR_CHECK(ret, -1, "pipe c_to_p");
    ret = pipe(p_to_c);
    ERROR_CHECK(ret, -1, "pipe p_to_c");

    char buf[512];
    if (fork()) {
        // parent process
        close(p_to_c[0]);
        close(c_to_p[1]);
        bzero(buf, sizeof(buf));
        read(c_to_p[0], buf, sizeof(buf));
        printf("parent:%s\n", buf);
        write(p_to_c[1], "Hello!", 6);
        wait(NULL);
    } else {
        // child process
        close(c_to_p[0]);
        close(p_to_c[1]);
        bzero(buf, sizeof(buf));
        write(c_to_p[1], "World!\n", 6);
        read(p_to_c[0], buf, sizeof(buf));
        printf("child:%s\n", buf);
    }
    return 0;
}


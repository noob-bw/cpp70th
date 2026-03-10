#include <my_header.h>

// user: ./strtok path_name
int main(int argc,char *argv[]) {
    ARGS_CHECK(argc, 2);
    // practice strtoke
    char *path = strtok(argv[1], "/");
    while (path) {
        printf("strtok:%s\n", path);
        path = strtok(NULL, "/");
    }
    /* path = strtok(argv[1], "/"); */
    /* printf("strtok:%s\n", path); */
    /* path = strtok(argv[1], "/"); */
    /* printf("strtok:%s\n", path); */

    return 0;
}

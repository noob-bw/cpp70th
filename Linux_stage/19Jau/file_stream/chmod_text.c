#include <my_header.h>

// ./chmod_text 777 1.txt
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc,3);

    mode_t mode;
    sscanf(argv[1],"%o",&mode);
    chmod(argv[2],mode);
    return 0;
}


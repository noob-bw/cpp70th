#include <my_header.h>

/* Usage: ./mkdir_batch path_name  */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    char path[512];
    for (int i=1; i <= 5; ++i) {
        snprintf(path, 512, "%s/test%d",argv[1],i);
        int ret = mkdir(path, 0775);
        ERROR_CHECK(ret, -1, "mkdir");
        char child_path[1024];
        /* printf("path = %s\n",path); */
        for (int j=0; j<10; ++j) {
            snprintf(child_path, 1024, "%s/text%d%d", path, i, j);
            /* printf("child_path = %s\n",child_path); */
            ret = mkdir(child_path, 0775);
            ERROR_CHECK(ret, -1, "child mkdir");
        }
    }
    
    return 0;
}


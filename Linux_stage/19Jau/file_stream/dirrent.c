#include <my_header.h>

int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc,2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir failed");
    struct dirent *dirent_p = NULL;
    while((dirent_p = readdir(dirp)) != NULL) {
        printf("%s\n",dirent_p->d_name);
    }
    closedir(dirp);
    return 0;
}


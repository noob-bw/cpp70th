#include <my_header.h>

int main(int argc, char *argv[]){                                  
    // ./batch_mkdir path_name
    ARGS_CHECK(argc,2);
    int count = 5;
    
    // 初始目录
    char path[512] = { 0 };
    char child_path[512] = { 0 };

    getcwd(path,sizeof(path));
    snprintf(child_path,sizeof(path),"%s%s",path,argv[1]);
    printf("%s\n",child_path);


    for (int i=0;i<count;++i) {
        int ret = snprintf(child_path,sizeof(child_path),"%s%s%d",path,child_path,i); 
        if (ret < 0) {
            perror("snprintf failed");
            exit(1);
        }
        /* printf("%s\n",child_path); */
    }

    return 0;
}


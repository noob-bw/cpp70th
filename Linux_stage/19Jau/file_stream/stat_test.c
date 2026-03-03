#include <my_header.h>

// 打印1.txt的文件信息

int main(int argc, char *argv[]){                                  
    // open 1.txt dir stream
    DIR *dirp = NULL;
    dirp = opendir("1.txt");
    ERROR_CHECK(dirp,NULL,"open 1.txt failed.\n");

    struct stat stat_buf;
    int ret = stat("1.txt",&stat_buf);

    printf("%o --- %ld --- %d --- %d --- %ld --- %ld \n",stat_buf.st_mode,stat_buf.st_nlink,
           stat_buf.st_uid,stat_buf.st_gid,stat_buf.st_size,stat_buf.st_mtim.tv_sec);
    
    closedir(dirp);
    return 0;
}


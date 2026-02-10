#include <my_header.h>

int main(int argc, char *argv[]){                                  
    // ./youth_ls path
    ARGS_CHECK(argc,2);

    // 打开目录流
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir fialed");
    
    // 切换工作目录与打开的目录一致
    int res = chdir(argv[1]);
    ERROR_CHECK(res,-1,"chdir failed");
    
    // 读取文件名，并打印
    struct dirent *dirrent_p = NULL;
    while ((dirrent_p = readdir(dirp)) != NULL) {
        struct stat stat_buf;
        int ret = stat(dirrent_p->d_name,&stat_buf);
        ERROR_CHECK(ret,-1,"stat failed");
        
        printf("%o %ld %d %d %ld %ld %s\n",
               stat_buf.st_mode,
               stat_buf.st_nlink,
               stat_buf.st_uid,
               stat_buf.st_gid,
               stat_buf.st_size,
               stat_buf.st_mtim.tv_sec,
               dirrent_p->d_name);
    }
    
    

    // 关闭目录流
    closedir(dirp);
    return 0;
}


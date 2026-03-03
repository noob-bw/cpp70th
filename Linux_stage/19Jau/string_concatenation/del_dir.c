#include <my_header.h>

void deleteDir(const char* path);

int main(int argc, char *argv[])
{
    // ./deleteDir dir
    ARGS_CHECK(argc, 2);

    deleteDir(argv[1]);
    return 0;
}

void deleteDir(const char* path) {
	// 打开目录
    DIR *pdir = opendir(path);
    ERROR_CHECK(pdir, NULL, "deleteDir::opendir");

    // 遍历目录流，依次删除每一个目录项
    struct dirent *pdirent;
    while ((pdirent = readdir(pdir)) != NULL) {
        // 忽略.和..
        if (strcmp(pdirent->d_name,".") == 0 || strcmp(pdirent->d_name,"..") == 0) { continue; }
        // 如果该目录项是目录，则调用deleteDir递归删除
        if (pdirent->d_type == DT_DIR) {
            char child_path[512];
            snprintf(child_path, 512, "%s/%s",path, pdirent->d_name);
            deleteDir(child_path);
        }
        // 如果该目录项是文件，则调用unlink删除文件
        if (pdirent->d_type == DT_REG) {
            char child_path[512];
            snprintf(child_path, 512, "%s/%s",path, pdirent->d_name);
            int ret = unlink(child_path);
            ERROR_CHECK(ret, -1, "deleteDir::unlink");
        }
    }

    // 目录为空了，可以删除该目录了

    int ret = rmdir(path);
    ERROR_CHECK(ret, -1, "deleteDir::rmdir");
	// 关闭目录流
    closedir(pdir);
}

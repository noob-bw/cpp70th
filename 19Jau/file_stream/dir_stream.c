#include <my_header.h>


int main(int argc, char *argv[]){                                  
    // 获取当前工作目录
    char orgin_path[50] = {0};
    char *ret = getcwd(orgin_path,50);
    ERROR_CHECK(ret,NULL,"getpwd failed");
    printf("%s\n",orgin_path);

    // 切换到指定目录
    int res = chdir("../arg");
    ERROR_CHECK(res,-1,"chdir failed");

    char new_path[50] = {0};
    ret = getcwd(new_path,50);
    ERROR_CHECK(ret,NULL,"getpwd failed");
    printf("%s\n",new_path);

    // 在新目录中创建文件,并写入内容
    FILE *fp = fopen("1.txt","w+");
    ERROR_CHECK(fp,NULL,"fopen failed");
    char *suf = "hello world!\n";
    fwrite(suf,1,strlen(suf),fp);

    // 切换回原工作目录，打印
    res = chdir(orgin_path);
    ERROR_CHECK(res,-1,"chidr failed");
    printf("%s\n",orgin_path);
    return 0;
}


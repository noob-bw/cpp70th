#include <my_header.h>

// 将src_path处的文件复制到dest_path处
// ./copy_file src_path dest_path

void copy_file(const char *src_path, const char *dest_path) {
    FILE *src_fp = NULL;
    src_fp = fopen(src_path,"r");
    if (src_fp == NULL) {
        perror("open src failed.\n");
        exit(-1);
    }

    FILE *dest_fp = NULL;
    dest_fp = fopen(dest_path,"w");
    if (dest_fp == NULL) {
        perror("open dest failed.\n");
        fclose(src_fp);
        exit(-1);
    }

    char buf[1024]={0};
    size_t count;
    while((count = fread(buf,sizeof(char),count,src_fp)) > 0) {
        fwrite(buf,sizeof(char),count,dest_fp);
    }
    
    fclose(src_fp);
    fclose(dest_fp);
}

int main(int argc, char *argv[]){                                  
    // check the number of argc
    if (argc != 3) {
        fprintf(stderr,"args error!\n");
        exit(1);
    }

    copy_file(argv[1],argv[2]);

    return 0;
}


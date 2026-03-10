#include <my_header.h>

struct date {
    int month;
    int day;
    int hour;
    int min;
};

void str_to_lower(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

int compare(const void *dir1, const void *dir2) {
    const struct dirent *dp = *(const struct dirent**)dir1;
    const struct dirent *dp2 = *(const struct dirent**)dir2;

    char name[256];
    char name2[256];
    strcpy(name, dp->d_name);
    strcpy(name2, dp2->d_name);

    str_to_lower(name);
    str_to_lower(name2);

    return strcmp(name, name2);
}

struct date* get_local_time(time_t time) {
    struct tm *ptm = localtime(&time);
    struct date* pdate = (struct date*)malloc(sizeof(struct date));
    pdate->month = ptm->tm_mon+1;
    pdate->day = ptm->tm_mday;
    pdate->hour = ptm->tm_hour;
    pdate->min = ptm->tm_min;
    return pdate;
}

void get_mode(mode_t mode, char *str) {
    switch (mode & S_IFMT) {
    case S_IFBLK:   str[0] = 'b';       break;
    case S_IFCHR:   str[0] = 'c';       break;
    case S_IFDIR:   str[0] = 'd';       break;
    case S_IFIFO:   str[0] = 'p';       break;
    case S_IFLNK:   str[0] = 'l';       break;
    case S_IFREG:   str[0] = '-';       break;
    case S_IFSOCK:  str[0] = 's';       break;
    default: str[0] = '?';              break;
    }

    str[1] = (mode & 0400) == 0 ? '-' : 'r';
    str[2] = (mode & 0200) == 0 ? '-' : 'w';
    str[3] = (mode & 0100) == 0 ? '-' : 'x';
    str[4] = (mode & 0040) == 0 ? '-' : 'r';
    str[5] = (mode & 0020) == 0 ? '-' : 'w';
    str[6] = (mode & 0010) == 0 ? '-' : 'x';
    str[7] = (mode & 0004) == 0 ? '-' : 'r';
    str[8] = (mode & 0002) == 0 ? '-' : 'w';
    str[9] = (mode & 0001) == 0 ? '-' : 'x';
}


/* Usage: ./ls_sorted [path_name] */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    // open the dir stream
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "main::opendir");
    struct dirent *pdirent = NULL;
    
    // record the num of dir
    int count=0;
    while ((pdirent = readdir(dirp)) != NULL) {
        count++;
    }

    // create a struct pointer array
    rewinddir(dirp);
    struct dirent** dir_arr = (struct dirent**)malloc(sizeof(struct dirent*)*count);
    int idx=0;
    while ((pdirent = readdir(dirp)) != NULL) {
        dir_arr[idx] = pdirent; 
        idx++;
    }

    // sort the struct pointer array
    qsort(dir_arr, count, sizeof(struct dirent*), compare);

    for (int i=0; i<count; ++i) {
        char path[512] = { 0 };
        snprintf(path, 512, "%s/%s", argv[1],dir_arr[i]->d_name);
        /* printf("path:%s\n",path); */
        struct stat statbuf;
        int ret = stat(path, &statbuf);
        ERROR_CHECK(ret, -1, "main::stat");

        struct date *pdate = get_local_time(statbuf.st_mtim.tv_sec);

        // 获取mode字符串
        char mode_buf[11] = { 0 };
        get_mode(statbuf.st_mode, mode_buf);

        // test
        /* printf("mode_buf:%s\n",mode_buf); */
        /* printf("%ld\n",statbuf.st_nlink); */
        /* printf("%3d月 %2d %02d:%02d\n",pdate->month, pdate->day,pdate->hour, pdate->min); */

        printf("%s %ld %s %s %9ld %3d月 %2d %02d:%02d %s\n", 
               mode_buf,
               statbuf.st_nlink,
               getpwuid(statbuf.st_uid)->pw_name,
               getgrgid(statbuf.st_gid)->gr_name,
               statbuf.st_size,
               pdate->month, pdate->day,
               pdate->hour, pdate->min,
               dir_arr[i]->d_name);
    }

    return 0;
}


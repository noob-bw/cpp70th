#include <my_header.h>

struct date {
    int year;
    int month;
    int day;
    int hour;
    int min;
};

struct date * get_date(time_t time) {
    struct date *date_p = (struct date *)malloc(sizeof(struct date));
    struct tm *tm_p = localtime(&time);
    date_p->year = tm_p->tm_year + 1900;
    date_p->month = tm_p->tm_mon + 1;
    date_p->day = tm_p->tm_mday;
    date_p->hour = tm_p->tm_hour;
    date_p->min = tm_p->tm_min;
    return date_p;
}

void mode_to_string(mode_t mode,char *str) {
    char type = '?';
    switch (mode & S_IFMT) {
    case S_IFBLK:  type = 'b';      break;
    case S_IFCHR:  type = 'c';      break;
    case S_IFDIR:  type = 'd';      break;
    case S_IFIFO:  type = 'p';      break;
    case S_IFLNK:  type = 's';      break;
    case S_IFREG:  type = '-';      break;
    case S_IFSOCK: type = 'k';      break;
    default:       type = '?';      break;
    }
    str[0] = type;

    str[1] = (mode & 0400) != 0 ? 'r' : '-';
    str[2] = (mode & 0200) != 0 ? 'w' : '-';
    str[3] = (mode & 0100) != 0 ? 'x' : '-';
    str[4] = (mode & 0040) != 0 ? 'r' : '-';
    str[5] = (mode & 0020) != 0 ? 'w' : '-';
    str[6] = (mode & 0010) != 0 ? 'x' : '-';
    str[7] = (mode & 0004) != 0 ? 'r' : '-';
    str[8] = (mode & 0002) != 0 ? 'w' : '-';
    str[9] = (mode & 0001) != 0 ? 'x' : '-';
    
}

/* Usage: ./my_ls path_name */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    DIR *dirp = NULL;
    dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir failed");

    struct dirent *dirent_s = NULL;

    while ((dirent_s = readdir(dirp)) != NULL) {
        char path[1024] = { 0 };
        snprintf(path, 1024, "%s/%s",argv[1],dirent_s->d_name);


        struct stat *statbuf = (struct stat *)malloc(sizeof(struct stat));
        int ret = stat(path, statbuf);
        ERROR_CHECK(ret, -1, "stat failed");

        char mode_buf[11] = { 0 };
        mode_to_string(statbuf->st_mode,mode_buf);

        struct date *date_p = get_date(statbuf->st_mtim.tv_sec);

        printf("%s %ld %s %s %8ld %d月 %d %02d:%02d %s\n", 
               mode_buf,
               statbuf->st_nlink,
               getpwuid(statbuf->st_uid)->pw_name,
               getgrgid(statbuf->st_gid)->gr_name,
               statbuf->st_size,
               date_p->month,
               date_p->day,
               date_p->hour,
               date_p->min,
               dirent_s->d_name);
    }


    closedir(dirp);

    return 0;
}


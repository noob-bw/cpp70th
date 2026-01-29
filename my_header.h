#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>

#define ARGS_CHECK(argc,num) \
	do { \
		if (argc != num) { \
			fprintf(stderr,"Args error!\n"); \
			exit(1); \
		} \
	} while (0) 
#define ERROR_CHECK(ret,error_flag,msg) \
	do { \
		if (ret == error_flag) { \
		       perror(msg); \
			exit(1); \
		} \	
	}while (0)


#endif

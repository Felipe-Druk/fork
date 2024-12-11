#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <string.h>

#define ERROR -1
#define SUCES 0
#define ERRORLINK "read link "

const int ARG = 2;
const int DIR_ARG = 1;

int my_ls(const char *directory_path);

void print_info(struct dirent *entry, struct stat *statbuf);

void print_info_link(struct dirent *entry, struct stat *statbuf, const char* target_path);

int
main(int argc, char *argv[])
{
    if(argc != ARG){
	    perror("bad arg");
	    return ERROR;
    }

    return my_ls(argv[DIR_ARG]);
}

int 
my_ls(const char* directory_path ){
    DIR *dir = opendir(directory_path);
    if(dir == NULL){
	    perror("arg inalid");
        return ERROR;
    }

    struct dirent * entry;
    struct stat statbuf;
    entry = readdir(dir);
    char target_path[PATH_MAX];
    while (entry)
    {
        stat(entry->d_name, &statbuf);
        if(entry->d_type == DT_LNK){
		char link[strlen(entry->d_name) + strlen(directory_path) +1];
		link[0] = '\0';
		strcat(link, directory_path);
		strcat(link, "/");
		strcat(link, entry->d_name);
		int len = readlink(link, target_path, sizeof(target_path));
		if (len != ERROR) {
			print_info_link(entry, &statbuf, target_path);
            }
            else
            {
		    printf("link error %s\n" , link);
		    perror(ERRORLINK);
	    }
            print_info(entry, &statbuf);
        } else {
            print_info(entry, &statbuf);
        }
        entry = readdir(dir);
    }
    closedir(dir);

    return SUCES;
}

void print_info(struct dirent *entry, struct stat *statbuf){
    printf("%s %i  %u %u \n", entry->d_name, entry->d_type, statbuf->st_mode, statbuf->st_uid);
}

void print_info_link(struct dirent *entry, struct stat *statbuf, const char* target_path){
        printf("%s %i  %u %u ", entry->d_name, entry->d_type, statbuf->st_mode, statbuf->st_uid);
        printf(" -> %s\n", target_path);
}